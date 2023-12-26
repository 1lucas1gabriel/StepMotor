/**
 * Lucas Morais
 * Lib version: 1.0
 * Date: Oct, 2023
 * 
 * Basic program describes how to use StepMotor library to control
 * an arm robot with two StepMotors (base & join). Those devices
 * can be configured to drive min/max torque (activating 1 or 2
 * phases to be activated simultaneously). 
 * 
 * Setup:
 *    - base step motor: (Bipolar) HP printer motor
 *    - join step motor: (Unipolar) 28BYJ-48 
*/
#include "Arduino.h"
#include "StepMotor.h"

void setup();
void loop();
void teardown();


/* Create and configure stepMotors*/
StepMotor baseMotor(BIPOLAR_2PHASE, MIN_TORQUE, 11,10,9,8);
StepMotor joinMotor(UNIPOLAR_4PHASE, MIN_TORQUE, 5,4,3,2);

int main(){

  // initialize avr and setup resources
  init();
  setup();

  while(1){
    loop();
  }

  teardown();
  return 0;
}


void setup(){

  baseMotor.begin();
  joinMotor.begin();
}


void loop(){

  /* Request device to move. Parameters needed: Number of steps, speed, direction */
  baseMotor.setMov(100, SLOW_MS, COUNTER_CLOCKWISE);
  delay(1000);
  baseMotor.setMov(100, SLOW_MS, COUNTER_CLOCKWISE);
  delay(1000);

  joinMotor.setMov(50, SLOW_MS, COUNTER_CLOCKWISE);
  delay(1000);
  joinMotor.setMov(50, SLOW_MS, COUNTER_CLOCKWISE);

}


void teardown(){

  /* Release devices and allow usage of pins */
  baseMotor.end();
  joinMotor.end();
}