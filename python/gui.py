import tkinter as tk
import serial
import threading
from serial.tools import list_ports

# Maps to parse serial input into strings
state_strings = ['SLEEPING', 'CHECK_IN', 'ENTERING', 'READY', 'WASHING', 'ERROR', 'FINISHED', 'CHECK_OUT']

class ArduinoCommunication:
    def __init__(self, baud_rate=9600):
        self.serial_port = self.detect_com_port() # rileva la porta seriale
        if self.serial_port is None:
            raise ValueError("Nessuna porta seriale trovata") # se non trova la porta seriale, tira errore
        
        self.serial_port = serial.Serial(self.serial_port, baud_rate) # apre la porta seriale
        self.data = {'state': '', 'temperature': '', 'distance': ''} # inizializza il dizionario
        self.is_reading = False # variabile per il thread
        self.read_thread = threading.Thread(target=self.read_data_thread) # crea il thread
        self.read_thread.start() # avvia il thread
        self.wash_count = 0 # variabile per il conteggio dei lavaggi
        self.wash_in_progress = False  # Variable to track if a wash is in progress

        # Create a label for maintenance message
        self.maintenance_label = tk.Label(root, text="Maintenance required", fg="red", font=("Helvetica", 14)) # crea il label, ma non lo mostra
        self.maintenance_label.pack(padx=10, pady=5, anchor='w') #aggiustamenti grafici
        self.update_maintenance_label() # aggiorna il label

    def detect_com_port(self): # funzione per rilevare la porta seriale
        ports = list_ports.comports()
        for port in ports:
            if "Arduino Uno" in port.description: # se trova la porta seriale, la ritorna
                return port.device
        return None

    def read_data_thread(self): # funzione per leggere i dati dal thread
        self.is_reading = True # variabile per il thread
        while self.is_reading: # ciclo while per leggere i dati
            if self.serial_port.in_waiting > 0: 
                data = self.serial_port.readline().decode().strip().split(':') # legge i dati dalla seriale, li decodifica e li divide in una lista
                if len(data) == 3: 
                    self.data['state'], self.data['temperature'], self.data['distance'] = data # se i dati sono 3 li assegna al dizionario
                    self.update_gui() # aggiorna la gui

    def update_gui(self):
        state_label.config(text=f"State: {self.data['state']}") # aggiorna i label, inserendo i dati
        temp_label.config(text=f"Temperature: {self.data['temperature']} °C") # aggiorna i label, inserendo i dati
        distance_label.config(text=f"Distance: {self.data['distance']} metri") # aggiorna i label, inserendo i dati
        wash_count_label.config(text=f"Wash Count: {self.wash_count}") # aggiorna i label, inserendo i dati

        # Check if a wash is in progress and has just finished
        if self.wash_in_progress and self.data['state'] == 'FINISHED':
            self.increase_wash_count() #incrementa il conteggio dei lavaggi
            self.wash_in_progress = False # resetta la variabile
        elif self.data['state'] == 'WASHING':
            self.wash_in_progress = True

        self.update_maintenance_label() 

    def stop_reading(self): # funzione per fermare il thread
        self.is_reading = False
        self.read_thread.join()
        self.serial_port.close()

    def increase_wash_count(self): # funzione per incrementare il conteggio dei lavaggi
        # Increment the wash count
        self.wash_count += 1

    def send_maintenance_done(self): # funzione per inviare il messaggio di manutenzione
        self.serial_port.write("Maintenance done\n".encode())

    def show_maintenance_label(self): #funzionw per mostrare il label di manutenzione
        self.maintenance_label.pack()

    def hide_maintenance_label(self): # funzione per nascondere il label di manutenzione
        self.maintenance_label.pack_forget()

    def update_maintenance_label(self): # funzione per aggiornare il label di manutenzione
        if self.data['state'] == 'ERROR':
            self.show_maintenance_label()
        else:
            self.hide_maintenance_label()

def on_button_click(): # funzione per il click del bottone
    if arduino.data['state'] == 'ERROR':
        arduino.send_maintenance_done()
        arduino.hide_maintenance_label()

#crea la finestra
root = tk.Tk()
root.title('SmartCarWash')

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
arduino = ArduinoCommunication()

# Create a button
button = tk.Button(root, text="Manutenzione fatta!", command=on_button_click, bg='orange', fg='white')
button.pack(side=tk.BOTTOM, pady=10)

# Set the window size
root.geometry("400x350")

# Start the tkinter main loop
root.mainloop()

# Stop reading data when the tkinter window is closed
arduino.stop_reading()
