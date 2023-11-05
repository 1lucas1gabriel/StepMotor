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

#include <StepMotor.h>

/* Create and configure stepMotors*/
StepMotor baseMotor(BIPOLAR_2PHASE, MIN_TORQUE, 11,10,9,8);
StepMotor joinMotor(UNIPOLAR_4PHASE, MIN_TORQUE, 5,4,3,2);

void setup(){
  
  /* Initialize devices */
  baseMotor.begin();
  joinMotor.begin();

  /* Request device to move. Parameters needed: Number of steps, speed, direction */
  baseMotor.setMov(10, FAST_MS, COUNTER_CLOCKWISE);

  delay(3000);
  joinMotor.setMov(10, FAST_MS, COUNTER_CLOCKWISE);

  /* Release devices and allow usage of pins */
  baseMotor.end();
  joinMotor.end();
}

void loop(){    
}