#include "StepperMotor.h"

StepperMotor::StepperMotor(
			uint8_t in1Pin,
			uint8_t in2Pin,
			uint8_t in3Pin,
			uint8_t in4Pin,
			motorType motorT,
			torqueForce torqueF):
			_motorT(motorT), _torqueF(torqueF)
{
#ifdef __AVR
    // Calculate bit and port register for fast pin read and writes (AVR targets only)
    _in1PinPort = digitalPinToPort(in1Pin);
    _in2PinPort = digitalPinToPort(in2Pin);
    _in3PinPort = digitalPinToPort(in3Pin);
    _in4PinPort = digitalPinToPort(in4Pin);    

    _in1PinBit = digitalPinToBitMask(in1Pin);
    _in2PinBit = digitalPinToBitMask(in2Pin);
    _in3PinBit = digitalPinToBitMask(in3Pin);
    _in4PinBit = digitalPinToBitMask(in4Pin);

#else
    // Use the slow digitalRead() and digitalWrite() functions for non-AVR targets
    _in1Pin = in1Pin;
    _in2Pin = in2Pin;
    _in3Pin = in3Pin;
    _in4Pin = in4Pin;

#endif
}

/*!
 * \brief Initialize StepMotor controller.
 */
void StepperMotor::begin(){
	
	// Set Output PinMode 
    STEPPER_IN1_OUTPUT();
    STEPPER_IN2_OUTPUT();
    STEPPER_IN3_OUTPUT();
    STEPPER_IN4_OUTPUT();

    // Set All Pins Low (saves current draining)
    STEPPER_IN1_LOW();
    STEPPER_IN2_LOW();
    STEPPER_IN3_LOW();
    STEPPER_IN4_LOW();
}

/*!
 * \brief Release StepMotor controller pins.
 */
void StepperMotor::end(){
	
	// Reset PinMode as Input
    STEPPER_IN1_INPUT();
    STEPPER_IN2_INPUT();
    STEPPER_IN3_INPUT();
    STEPPER_IN4_INPUT();

    // Set All Pins Low
    STEPPER_IN1_LOW();
    STEPPER_IN2_LOW();
    STEPPER_IN3_LOW();
    STEPPER_IN4_LOW();    
}

/*!
 * \brief Move StepMotor to the target angle at the established speed
 */
void StepperMotor::setMov(int angle, uint8_t speed = 10){
	
	// Clockwise Movement -- Bipolar
	if(_motorT == Bipolar && angle >= 0){
	
		for(int i = 0; i < angle; i++){
			// step 1
			STEPPER_IN1_HIGH();
			STEPPER_IN2_LOW();
			STEPPER_IN3_HIGH();
			STEPPER_IN4_LOW();
			delay(100/speed);
			
			// step 2
			STEPPER_IN1_HIGH();
			STEPPER_IN2_LOW();
			STEPPER_IN3_LOW();
			STEPPER_IN4_HIGH();
			delay(100/speed);
			
			// step 3
			STEPPER_IN1_LOW();
			STEPPER_IN2_HIGH();
			STEPPER_IN3_LOW();
			STEPPER_IN4_HIGH();
			delay(100/speed);

			// step 4			
			STEPPER_IN1_LOW();
			STEPPER_IN2_HIGH();
			STEPPER_IN3_HIGH();
			STEPPER_IN4_LOW();
			delay(100/speed);			
		}
	}
	// Counter-Clockwise Movement -- Bipolar
	if(_motorT == Bipolar && angle < 0){
	
		for(int i = 0; i < (-1)*angle; i++){
			// step 4			
			STEPPER_IN1_LOW();
			STEPPER_IN2_HIGH();
			STEPPER_IN3_HIGH();
			STEPPER_IN4_LOW();
			delay(100/speed);
			
			// step 3
			STEPPER_IN1_LOW();
			STEPPER_IN2_HIGH();
			STEPPER_IN3_LOW();
			STEPPER_IN4_HIGH();
			delay(100/speed);
			
			// step 2
			STEPPER_IN1_HIGH();
			STEPPER_IN2_LOW();
			STEPPER_IN3_LOW();
			STEPPER_IN4_HIGH();
			delay(100/speed);
			
			// step 1
			STEPPER_IN1_HIGH();
			STEPPER_IN2_LOW();
			STEPPER_IN3_HIGH();
			STEPPER_IN4_LOW();
			delay(100/speed);
		}
	}
	// Clockwise Movement -- Unipolar
	if(_motorT == Unipolar && angle >= 0){
	
		for(int i = 0; i < angle; i++){
			// step 1
			STEPPER_IN1_HIGH();
			STEPPER_IN2_LOW();
			STEPPER_IN3_LOW();
			STEPPER_IN4_HIGH();
			delay(100/speed);
			
			// step 2
			STEPPER_IN1_LOW();
			STEPPER_IN2_LOW();
			STEPPER_IN3_HIGH();
			STEPPER_IN4_HIGH();
			delay(100/speed);
			
			// step 3
			STEPPER_IN1_LOW();
			STEPPER_IN2_HIGH();
			STEPPER_IN3_HIGH();
			STEPPER_IN4_LOW();
			delay(100/speed);
			
			// step 4			
			STEPPER_IN1_HIGH();
			STEPPER_IN2_HIGH();
			STEPPER_IN3_LOW();
			STEPPER_IN4_LOW();
			delay(100/speed);			
		}
	}
	// Counter-Clockwise Movement -- Unipolar
	if(_motorT == Unipolar && angle < 0){
	
		for(int i = 0; i < (-1)*angle; i++){
			// step 4			
			STEPPER_IN1_HIGH();
			STEPPER_IN2_HIGH();
			STEPPER_IN3_LOW();
			STEPPER_IN4_LOW();
			delay(100/speed);
					
			// step 3
			STEPPER_IN1_LOW();
			STEPPER_IN2_HIGH();
			STEPPER_IN3_HIGH();
			STEPPER_IN4_LOW();
			delay(100/speed);
								
			// step 2
			STEPPER_IN1_LOW();
			STEPPER_IN2_LOW();
			STEPPER_IN3_HIGH();
			STEPPER_IN4_HIGH();
			delay(100/speed);
					
			// step 1
			STEPPER_IN1_HIGH();
			STEPPER_IN2_LOW();
			STEPPER_IN3_LOW();
			STEPPER_IN4_HIGH();
			delay(100/speed);	
		}
	}
	
	// Release StepMotor pins to save current
	STEPPER_IN1_LOW();
	STEPPER_IN2_LOW();
	STEPPER_IN3_LOW();
	STEPPER_IN4_LOW();
}

void StepperMotor::setMotorType(motorType motorT){
	// Needs check if motorT in motorType list
	_motorT = motorT;
}

void StepperMotor::setTorqueForce(torqueForce torqueF){
	// Needs check if torqueF in torqueForce list
	_torqueF = torqueF;
}
/*
- Implement Bipolar vs Unipolar wrap up in raw code which implement driving sequence
- Implement Full Step vs Half Step to save current vs increase torque
- Improve Velocity Control method (Scale and range)
- Improve Velocity Control by removing "delay" function to reuse code in other platforms
- Improve Velocity deviation methods to vary acceleration
*/

/*
** HALF_STEP not considered yet ** 

BIPOLAR_POSITIVE_ANGLE_FULL_STEP			* 1 phase actuated by time (less torque)
BIPOLAR_NEGATIVE_ANGLE_FULL_STEP			* 1 phase actuated by time (less torque)
BIPOLAR_POSITIVE_ANGLE_FULL_STEP_TORQUE		* 2 phases actuated at the same time (full torque)
BIPOLAR_NEGATIVE_ANGLE_FULL_STEP_TORQUE		* 2 phases actuated at the same time (full torque)

UNIPOLAR_POSITIVE_ANGLE_FULL_STEP			* 1 phase actuated by time (less torque)
UNIPOLAR_NEGATIVE_ANGLE_FULL_STEP			* 1 phase actuated by time (less torque)
UNIPOLAR_POSITIVE_ANGLE_FULL_STEP_TORQUE	* 2 phases actuated at the same time (full torque)
UNIPOLAR_NEGATIVE_ANGLE_FULL_STEP_TORQUE	* 2 phases actuated at the same time (full torque)

*/



