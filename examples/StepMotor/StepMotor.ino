#include <StepperMotor.h>

StepperMotor baseMotor(8,9,10,11, Bipolar);
StepperMotor joinMotor(2,3,4,5, Unipolar);

void setup(){
  
  baseMotor.begin();
  baseMotor.setMov(20, 2);

  delay(1000);
  joinMotor.begin();
  joinMotor.setMov(20, 2);  

  delay(1000);
  joinMotor.setMov(-20, 10);

  delay(1000);
  baseMotor.setMov(-20, 10);

}

void loop(){
    
}