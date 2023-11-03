/**
 * program to describe how to implement baremetal joystick control
 * needs futher improvements (Kalman filter applied to sensor readings)
*/

#include <StepMotor.h>

StepMotor baseMotor(BIPOLAR_2PHASE, MIN_TORQUE, 11,10,9,8);
StepMotor joinMotor(UNIPOLAR_4PHASE, MIN_TORQUE, 5,4,3,2);

void setup(){
  
  baseMotor.begin();
  joinMotor.begin();
  Serial.begin(9600);
}

void loop(){
    
    int x_value, y_value;

    x_value = analogRead(A0);
    //Serial.print("x: ");
    Serial.print(x_value);

    // 0 -[ 512 ]- 1023
    if((x_value >= 300) && (x_value <= 800)){
        
        /* save guard to stop movement. no really needed */
        baseMotor.setMov(0, SLOW_MS, CLOCKWISE);
    }
    else if (x_value > 800){

        //set_speed = map(x_value, 550, 1023, 10, 100);
        baseMotor.setMov(10, MEDIUM_MS, CLOCKWISE);

    }
    /* x_value < 300*/
    else{

        baseMotor.setMov(10, MEDIUM_MS, COUNTER_CLOCKWISE);
    }

    


    y_value = analogRead(A1);
    Serial.print(",");
    Serial.println(y_value);

    // 0 -[ 512 ]- 1023
    if((y_value >= 200) && (y_value <= 800)){
        
        /* save guard to stop movement. no really needed */
        joinMotor.setMov(0, SLOW_MS, CLOCKWISE);
    }
    else if (y_value > 800){

        //set_speed = map(x_value, 550, 1023, 10, 100);
        joinMotor.setMov(20, MEDIUM_MS, CLOCKWISE);

    }
    /* y_value < 100*/
    else{

        joinMotor.setMov(20, MEDIUM_MS, COUNTER_CLOCKWISE);
    }
}