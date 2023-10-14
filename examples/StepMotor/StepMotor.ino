#include <StepMotor.h>

StepMotor baseMotor(8,9,10,11, BIPOLAR_2PHASE, FULL_TORQUE);
StepMotor joinMotor(2,3,4,5, UNIPOLAR_4PHASE, FULL_TORQUE);

void setup(){
  
  baseMotor.begin();
  baseMotor.setMov(120, 5, CLOCKWISE);

  delay(1000);
  joinMotor.begin();
  joinMotor.setMov(100, 5, CLOCKWISE);  

  delay(1000);
  joinMotor.setMov(100, 10, COUNTER_CLOCKWISE);

  delay(1000);
  baseMotor.setMov(120, 10, COUNTER_CLOCKWISE);

}

void loop(){
    
}