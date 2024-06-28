/**
 * Lucas Morais
 * Lib version: 1.0
 * Date: Nov, 2023
 * 
 * joystickControl program describes how to use joystick readings 
 * (x and y axis) to control two step motors. It can also be used with two
 * potentiometer. This bare metal program is a basic implementation, which
 * could be enhaced by applying Kalman filters to the sensor readings in
 * order to stabilize step motors controlling.

 * Setup:
 *    - base step motor: (Bipolar) HP printer motor
 *    - join step motor: (Unipolar) 28BYJ-48 
*/
#include "Arduino.h"
#include "StepMotor.h"

StepMotor baseMotor(BIPOLAR_2PHASE, MIN_TORQUE, 8,7,6,5);
StepMotor joinMotor(UNIPOLAR_4PHASE, MIN_TORQUE, 12,11,10,9);

void setup();
void loop();


int main(){

    // initialize avr and setup resources
    init();
    setup();

    while(1){
        loop();
    }

    return 0;
}


void setup(){

    baseMotor.begin();
    joinMotor.begin();
    Serial.begin(9600);
}

void loop(){
    
    int x_value, y_value;

    x_value = analogRead(A0);
    Serial.print("x: ");
    Serial.print(x_value);

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
