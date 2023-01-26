#include <StepMotor.h>

StepMotor baseMotor(8,9,10,11, Bipolar, Full);
StepMotor joinMotor(2,3,4,5, Unipolar, Full);

void setup(){
  
  baseMotor.begin();
  baseMotor.setMov(120, 5, Clk);

  delay(1000);
  joinMotor.begin();
  joinMotor.setMov(100, 5, Clk);  

  delay(1000);
  joinMotor.setMov(100, 10, CtrClk);

  delay(1000);
  baseMotor.setMov(120, 10, CtrClk);

}

void loop(){
    
}