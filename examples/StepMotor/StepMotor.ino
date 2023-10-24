#include <StepMotor.h>

StepMotor baseMotor(BIPOLAR_2PHASE, MIN_TORQUE, 11,10,9,8);
StepMotor joinMotor(UNIPOLAR_4PHASE, MIN_TORQUE, 5,4,3,2);

void setup(){
  
  baseMotor.begin();
  joinMotor.begin();

  baseMotor.setMov(584, FAST_MS, COUNTER_CLOCKWISE);


  delay(3000);
  joinMotor.setMov(1960/2, FAST_MS, COUNTER_CLOCKWISE);
/*
  delay(1000);
  joinMotor.setMov(200, FAST_MS, COUNTER_CLOCKWISE);

  delay(1000);
  joinMotor.setMov(100, SLOW_MS, CLOCKWISE);
*/
  baseMotor.end();
  joinMotor.end();

}

void loop(){
    
}