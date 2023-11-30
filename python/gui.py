import tkinter as tk
import serial
import threading

# Maps to parse serial input into strings
state_strings = ['SLEEPING', 'CHECK_IN', 'ENTERING', 'READY', 'WASHING', 'ERROR', 'FINISHED', 'CHECK_OUT']

class ArduinoCommunication:
    def __init__(self, port, baud_rate=9600):
        self.serial_port = serial.Serial(port, baud_rate)
        self.data = {'state': '', 'temperature': '', 'distance': ''}
        self.is_reading = False
        self.read_thread = threading.Thread(target=self.read_data_thread)
        self.read_thread.start()
        self.wash_count = 0
        self.wash_in_progress = False  # Variable to track if a wash is in progress

        # Create a label for maintenance message
        self.maintenance_label = tk.Label(root, text="Maintenance required", fg="red", font=("Helvetica", 14))
        self.maintenance_label.pack(padx=10, pady=5, anchor='w')
        self.update_maintenance_label()

    def read_data_thread(self):
        self.is_reading = True
        while self.is_reading:
            if self.serial_port.in_waiting > 0:
                data = self.serial_port.readline().decode().strip().split(':')
                if len(data) == 3:
                    self.data['state'], self.data['temperature'], self.data['distance'] = data
                    self.update_gui()

    def update_gui(self):
        state_label.config(text=f"State: {self.data['state']}")
        temp_label.config(text=f"Temperature: {self.data['temperature']} °C")
        distance_label.config(text=f"Distance: {self.data['distance']} units")
        wash_count_label.config(text=f"Wash Count: {self.wash_count}")

        # Check if a wash is in progress and has just finished
        if self.wash_in_progress and self.data['state'] == 'FINISHED':
            self.increase_wash_count()
            self.wash_in_progress = False
        elif self.data['state'] == 'WASHING':
            self.wash_in_progress = True

        self.update_maintenance_label()

    def stop_reading(self):
        self.is_reading = False
        self.read_thread.join()
        self.serial_port.close()

    def increase_wash_count(self):
        # Increment the wash count
        self.wash_count += 1

    def send_maintenance_done(self):
        # Send "Maintenance done" message to Arduino
        self.serial_port.write("Maintenance done\n".encode())

    def show_maintenance_label(self):
        # Show the maintenance label when maintenance is required
        self.maintenance_label.pack()

    def hide_maintenance_label(self):
        # Hide the maintenance label when maintenance is not required
        self.maintenance_label.pack_forget()

    def update_maintenance_label(self):
        # Update the maintenance label based on the current state
        if self.data['state'] == 'ERROR':
            self.show_maintenance_label()
        else:
            self.hide_maintenance_label()

# Function to be called when the button is clicked
def on_button_click():
    if arduino.data['state'] == 'ERROR':
        arduino.send_maintenance_done()
        arduino.hide_maintenance_label()

# Create the tkinter master object
root = tk.Tk()
root.title('Smart Bridge')

# Create labels for displaying data
state_label = tk.Label(root, text="State: ", anchor='w', font=("Helvetica", 14))
state_label.pack(padx=10, pady=5, anchor='w')

temp_label = tk.Label(root, text="Temperature: ", anchor='w', font=("Helvetica", 14))
temp_label.pack(padx=10, pady=5, anchor='w')

distance_label = tk.Label(root, text="Distance: ", anchor='w', font=("Helvetica", 14))
distance_label.pack(padx=10, pady=5, anchor='w')

# Wash Count Label
wash_count_label = tk.Label(root, text="Wash Count: 0", anchor='w', font=("Helvetica", 14))
wash_count_label.pack(padx=10, pady=5, anchor='w')

# Initialize Arduino communication
arduino = ArduinoCommunication('COM15')

# Create a button
button = tk.Button(root, text="Manutenzione fatta!", command=on_button_click, bg='orange', fg='white')
button.pack(side=tk.BOTTOM, pady=10)

# Set the window size
root.geometry("400x350")

# Start the tkinter main loop
root.mainloop()

# Stop reading data when the tkinter window is closed
arduino.stop_reading()
