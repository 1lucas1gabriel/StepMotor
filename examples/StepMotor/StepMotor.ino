#include <StepMotor.h>

StepMotor baseMotor(11,10,9,8, BIPOLAR_2PHASE, FULL_TORQUE);
StepMotor joinMotor(5,4,3,2, UNIPOLAR_4PHASE, FULL_TORQUE);

void setup(){
  
  baseMotor.begin();
  baseMotor.setMov(120, SLOW_MS, CLOCKWISE);

  delay(1000);
  joinMotor.begin();
  joinMotor.setMov(100, MEDIUM_MS, CLOCKWISE);  

  delay(1000);
  joinMotor.setMov(100, FAST_MS, COUNTER_CLOCKWISE);

  delay(1000);
  baseMotor.setMov(120, SLOW_MS, COUNTER_CLOCKWISE);

}

void loop(){
    
}