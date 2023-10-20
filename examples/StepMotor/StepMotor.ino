#include <StepMotor.h>

StepMotor baseMotor(11,10,9,8, BIPOLAR_2PHASE, MAX_TORQUE);
StepMotor joinMotor(5,4,3,2, UNIPOLAR_4PHASE, MAX_TORQUE);

void setup(){
  
  baseMotor.begin();
  joinMotor.begin();

  baseMotor.setMov(50, SLOW_MS, CLOCKWISE);

  delay(1000);
  baseMotor.setMov(50, SLOW_MS, COUNTER_CLOCKWISE);

  delay(1000);
  baseMotor.setMov(50, SLOW_MS, CLOCKWISE);



  delay(1000);
  joinMotor.setMov(50, SLOW_MS, CLOCKWISE);

  delay(1000);
  joinMotor.setMov(50, SLOW_MS, COUNTER_CLOCKWISE);

  delay(1000);
  joinMotor.setMov(50, SLOW_MS, CLOCKWISE);


  //baseMotor.end();
  joinMotor.end();

}

void loop(){
    
}