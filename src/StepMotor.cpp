#include "StepMotor.h"

StepMotor::StepMotor(
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
void StepMotor::begin(){
	
	// Set Output PinMode and Turn Off to save current
    IN1_OUTPUT();
    IN2_OUTPUT();
    IN3_OUTPUT();
    IN4_OUTPUT();
    this->_RELEASE_PINS();
}

/*!
 * \brief Release StepMotor controller pins.
 */
void StepMotor::end(){
	
	// Set Input PinMode and Turn Off to save current
    IN1_INPUT();
    IN2_INPUT();
    IN3_INPUT();
    IN4_INPUT();
    this->_RELEASE_PINS(); 
}

/*!
 * \brief Rotate StepMotor nSteps at the established speed and direction
 */
void StepMotor::setMov(uint16_t nSteps, uint8_t speed, directRot directR){	
	
	if(_motorT == Bipolar && directR == Clk)
		_BI_CLKWISE_ROT_FULL_TORQUE(nSteps, speed);

	if(_motorT == Bipolar && directR == CtrClk)
		_BI_CTR_CLKWISE_ROT_FULL_TORQUE(nSteps, speed);

	if(_motorT == Unipolar && directR == Clk)
		_UNI_CLKWISE_ROT_FULL_TORQUE(nSteps, speed);

	if(_motorT == Unipolar && directR == CtrClk)
		_UNI_CTR_CLKWISE_ROT_FULL_TORQUE(nSteps, speed);
	
	// Turn off StepMotor pins to save current
	this->_RELEASE_PINS();
}

/*!
 * \brief Set which motor type will be used (Bipolar or Unipolar)
 */
void StepMotor::setMotorType(motorType motorT){
	// Needs check if motorT in motorType list
	_motorT = motorT;
}

/*!
 * \brief Set which torque force will be used (Half or Full)
 */
void StepMotor::setTorqueForce(torqueForce torqueF){
	// Needs check if torqueF in torqueForce list
	_torqueF = torqueF;
}


/***********************************************************
 *  INTERNAL METHODS *
 *********************************************************** /

/*!
 * \brief Turn off pins to save current
 */
void StepMotor::_RELEASE_PINS(){
	IN1_LOW();
	IN2_LOW();
	IN3_LOW();
	IN4_LOW();
}

/*!
 * \brief Clockwise Rotation of Bipolar Motor at Full Torque
 */
void StepMotor::_BI_CLKWISE_ROT_FULL_TORQUE(uint16_t nSteps, uint8_t speed){

	for(uint16_t i = 0; i < nSteps; i++){
		//----------------------------------------------------------//
		// To sync movement and repeat for nSteps:					//
		// bitwise operation just select last 2 LSB from iterator	//
		// 2 LSB needed to order from 1 up to 4 step (00,01,10,11)	//
		//----------------------------------------------------------//
		uint8_t currentStep = (0x0003 & i);

		switch(currentStep){
			case 0:
				IN1_HIGH();
				IN2_LOW();
				IN3_HIGH();
				IN4_LOW();
			break;
			case 1:
				IN1_HIGH();
				IN2_LOW();
				IN3_LOW();
				IN4_HIGH();
			break;
			case 2:
				IN1_LOW();
				IN2_HIGH();
				IN3_LOW();
				IN4_HIGH();
			break;
			case 3:
				IN1_LOW();
				IN2_HIGH();
				IN3_HIGH();
				IN4_LOW();
			break;
		}
		// stop step until the next step -> impacts on motor velocity
		delay(100/speed);		
	}
}

/*!
 * \brief Counter Clockwise Rotation of Bipolar Motor at Full Torque
 */
void StepMotor::_BI_CTR_CLKWISE_ROT_FULL_TORQUE(uint16_t nSteps, uint8_t speed){

	for(uint16_t i = 0; i < nSteps; i++){
		//----------------------------------------------------------//
		// To sync movement and repeat for nSteps:					//
		// bitwise operation just select last 2 LSB from iterator	//
		// 2 LSB needed to order from 1 up to 4 step (00,01,10,11)	//
		//----------------------------------------------------------//
		uint8_t currentStep = (0x0003 & i);

		switch(currentStep){
			case 0:
				IN1_LOW();
				IN2_HIGH();
				IN3_HIGH();
				IN4_LOW();				
			break;
			case 1:
				IN1_LOW();
				IN2_HIGH();
				IN3_LOW();
				IN4_HIGH();
			break;
			case 2:
				IN1_HIGH();
				IN2_LOW();
				IN3_LOW();
				IN4_HIGH();
			break;
			case 3:
				IN1_HIGH();
				IN2_LOW();
				IN3_HIGH();
				IN4_LOW();
			break;
		}
		// stop step until the next step -> impacts on motor velocity
		delay(100/speed);		
	}
}

/*!
 * \brief Clockwise Rotation of Unipolar Motor at Full Torque
 */
void StepMotor::_UNI_CLKWISE_ROT_FULL_TORQUE(uint16_t nSteps, uint8_t speed){

	for(uint16_t i = 0; i < nSteps; i++){
		//----------------------------------------------------------//
		// To sync movement and repeat for nSteps:					//
		// bitwise operation just select last 2 LSB from iterator	//
		// 2 LSB needed to order from 1 up to 4 step (00,01,10,11)	//
		//----------------------------------------------------------//
		uint8_t currentStep = (0x0003 & i);

		switch(currentStep){
			case 0:
				IN1_HIGH();
				IN2_LOW();
				IN3_LOW();
				IN4_HIGH();
			break;
			case 1:
				IN1_LOW();
				IN2_LOW();
				IN3_HIGH();
				IN4_HIGH();
			break;
			case 2:
				IN1_LOW();
				IN2_HIGH();
				IN3_HIGH();
				IN4_LOW();
			break;
			case 3:
				IN1_HIGH();
				IN2_HIGH();
				IN3_LOW();
				IN4_LOW();
			break;
		}
		// stop step until the next step -> impacts on motor velocity
		delay(100/speed);		
	}
}

/*!
 * \brief Counter Clockwise Rotation of Unipolar Motor at Full Torque
 */
void StepMotor::_UNI_CTR_CLKWISE_ROT_FULL_TORQUE(uint16_t nSteps, uint8_t speed){

	for(uint16_t i = 0; i < nSteps; i++){
		//----------------------------------------------------------//
		// To sync movement and repeat for nSteps:					//
		// bitwise operation just select last 2 LSB from iterator	//
		// 2 LSB needed to order from 1 up to 4 step (00,01,10,11)	//
		//----------------------------------------------------------//
		uint8_t currentStep = (0x0003 & i);

		switch(currentStep){
			case 0:
				IN1_HIGH();
				IN2_HIGH();
				IN3_LOW();
				IN4_LOW();			
			break;
			case 1:
				IN1_LOW();
				IN2_HIGH();
				IN3_HIGH();
				IN4_LOW();
			break;
			case 2:
				IN1_LOW();
				IN2_LOW();
				IN3_HIGH();
				IN4_HIGH();
			break;
			case 3:
				IN1_HIGH();
				IN2_LOW();
				IN3_LOW();
				IN4_HIGH();
			break;
		}
		// stop step until the next step -> impacts on motor velocity
		delay(100/speed);		
	}
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



