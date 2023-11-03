/**
 * read serial for base, join values (task1)
 * send to queue
 * receive from queue
 * execute movement base, join (task2, task3)
 * 
 * deal with queue overflow & multiples commands inputs on serial (buffer?)
*/




#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>
#include <StepMotor.h>

StepMotor baseMotor(BIPOLAR_2PHASE, MIN_TORQUE, 11,10,9,8);
StepMotor joinMotor(UNIPOLAR_4PHASE, MIN_TORQUE, 5,4,3,2);

/* tasks */
void taskMoveStepMotor(void *pvParam);
void taskReadJoystickPosition(void *pvParam);


/* Create handles to manage Serial and Sensor readings */
SemaphoreHandle_t xSerial_semaphore;
QueueHandle_t     xQueue_SERIAL;

void setup(){
  
  baseMotor.begin();
  joinMotor.begin();
  Serial.begin(9600);

  /* wait Serial initialization */
  while(!Serial);
  
  /* Create semaphore and queue */
  xQueue_SERIAL = xQueueCreate( 1, sizeof( int ));
  xSerial_semaphore = xSemaphoreCreateMutex();

  if (xSerial_semaphore == NULL){
     Serial.println("Error: semaphore not adequately create");
     while(1); /* Error when creating semaphore. Do nothing */
  }

  /* Setup tasks */
  xTaskCreate(
    taskMoveStepMotor
    ,(const char*) "baseMotor"
    ,128
    ,&baseMotor
    ,1
    ,NULL);

  xTaskCreate(
    taskMoveStepMotor
    ,(const char*) "joinMotor"
    ,128
    ,&joinMotor
    ,1
    ,NULL);

  xTaskCreate(
    taskReadJoystickPosition
    ,(const char*) "joystickSensor"
    ,128
    ,NULL
    ,1
    ,NULL);
}


void loop(){
    /* Do nothing */
}

void taskMoveStepMotor(void *pvParam){
    
    StepMotor* pstepmotor = (StepMotor*) pvParam;
    UBaseType_t uxHighWaterMark;
    int step_rcv = 0;

    while(1){
      
      /* wait until something new in queue */
      xQueuePeek(xQueue_SERIAL, (void *)&step_rcv, portMAX_DELAY);
      
      pstepmotor->setMov(step_rcv, SLOW_MS, COUNTER_CLOCKWISE);
      
      /* check stack occupancy, print high water mark */
      xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("task_stepmotor high water mark (words): ");
        Serial.println(uxHighWaterMark);
      xSemaphoreGive(xSerial_semaphore);  
    }
}


void taskReadJoystickPosition(void *pvParam){

    (void) pvParam;
    UBaseType_t uxHighWaterMark;
    int step = 100;

  while(1){
    /*
    adc_read = analogRead(0);
    voltage = ((float)adc_read/ADC_MAX)*MAX_VOLTAGE_ADC;
    */ 
    
    /* send new readings to the queue */
    xQueueOverwrite(xQueue_SERIAL, (void *)&step);

    /* check stack occupancy, print high water mark */
      xSemaphoreTake(xSerial_semaphore, portMAX_DELAY );
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        Serial.print("task_joystick high water mark (words): ");
        Serial.println(uxHighWaterMark);
        Serial.print("Steps: ");
        Serial.println(step);
      xSemaphoreGive(xSerial_semaphore); 

    /* wait 1 sec */
      vTaskDelay( 10000 / portTICK_PERIOD_MS );
  }
}
