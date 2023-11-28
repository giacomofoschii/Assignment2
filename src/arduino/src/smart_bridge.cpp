#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "tasks/BlinkTask.h"
#include "tasks/DetectionTask.h"
#include "tasks/GateTask.h"
#include "tasks/WashTask.h"

Scheduler scheduler;
CarWasher* pCarWasher;
//SerialMonitor* pSerialMonitor


void setup() {
  scheduler.init(50);
  pCarWasher = new CarWasher();
  pCarWasher->init();
  
  //pSerialCommunication = new SerialCommunication(pCarWasher);
  //pSerialCommunicaiton->init();

  BlinkTask* pBlinkTask = new BlinkTask(LED_2);
  pBlinkTask->init(2000);
  pBlinkTask->setActive(false);

  DetectionTask* pDetectionTask = new DetectionTask(pCarWasher);
  pDetectionTask->init(300);  

  GateTask* pGateTask = new GateTask(pCarWasher, pBlinkTask);
  pGateTask->init(200);

  WashTask* pWashtTask = new WashTask(pCarWasher, pBlinkTask/*, pSerialCommunication*/);
  pWashtTask->init(200);

  scheduler.addTask(pBlinkTask);
  scheduler.addTask(pDetectionTask);
  scheduler.addTask(pGateTask);
  scheduler.addTask(pWashtTask);

}

void loop() {
  scheduler.schedule();
  //pSerialCommunication.update();
}
