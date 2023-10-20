#include "StepMotor.h"


StepMotor::StepMotor(
			uint8_t in1Pin,
			uint8_t in2Pin,
			uint8_t in3Pin,
			uint8_t in4Pin,
			SM_motortype_t 		motorType,
			SM_torqueforce_t 	torqueForce)
{
	this->_setMotorType(motorType);
	this->_setTorqueForce(torqueForce);

#ifdef __AVR
    // Map pins to according PORT and bit position (AVR targets only)
    _pin1Port 		= digitalPinToPort(in1Pin);
	_pin2Port 		= digitalPinToPort(in2Pin);
	_pin3Port 		= digitalPinToPort(in3Pin);
    _pin4Port 		= digitalPinToPort(in4Pin);

    _pin1PortBit	= digitalPinToBitMask(in1Pin);
    _pin2PortBit	= digitalPinToBitMask(in2Pin);
    _pin3PortBit 	= digitalPinToBitMask(in3Pin);
    _pin4PortBit 	= digitalPinToBitMask(in4Pin);

//#else #define for other architectures
#endif
}

/*!
 * \brief Initialize StepMotor controller.
 */
void StepMotor::begin(){
	
	// Set Output PinMode and Turn Off to save current
    pin1_output();
	pin2_output();
	pin3_output();
	pin4_output();
    _set_stepCmd(0x0);
}

/*!
 * \brief Release StepMotor controller pins.
 */
void StepMotor::end(){
	
	// Set Input PinMode and Turn Off to save current
    pin1_input();
	pin2_input();
	pin3_input();
	pin4_input();
    _set_stepCmd(0x0);
}

/*!
 * \brief Rotate StepMotor nSteps at the established speed and direction
 */
void StepMotor::setMov(	uint16_t nSteps, 
						SM_stepdelay_t delay_ms, 
						SM_direction_t direction){

	/*-------------------------------------------------------
	 *| _motorType 	| _torqueForce 	| direction | cmd (BIN) |
	 *-------------------------------------------------------
	 *|	UNI_4PHASE	| MIN_TORQUE	| CLK		| 0b0000 	|
	 *|	UNI_4PHASE	| MIN_TORQUE	| CTR_CLK	| 0b0001 	|
	 *|	UNI_4PHASE	| MAX_TORQUE	| CLK		| 0b0010 	|
	 *|	UNI_4PHASE	| MAX_TORQUE	| CTR_CLK	| 0b0011 	|
	 *|	BI_2PHASE	| MIN_TORQUE	| CLK		| 0b0100 	|
	 *|	BI_2PHASE	| MIN_TORQUE	| CTR_CLK	| 0b0101 	|
	 *|	BI_2PHASE	| MAX_TORQUE	| CLK		| 0b0110 	|
	 *|	BI_2PHASE	| MAX_TORQUE	| CTR_CLK	| 0b0111 	|
	 *-------------------------------------------------------
	 */

	uint8_t cmd = (_motorType << 2) | ((_torqueForce << 1) | direction);

	switch (cmd){

	case 0:
		_rotate_stepMotor(uni_4phase_fullstep_mintorque_clk, true, nSteps, delay_ms);
		break;
	case 1:
		_rotate_stepMotor(uni_4phase_fullstep_mintorque_ctr_clk, true, nSteps, delay_ms);
		break;
	case 2:
		_rotate_stepMotor(uni_4phase_fullstep_maxtorque_clk, true, nSteps, delay_ms);
		break;
	case 3:
		_rotate_stepMotor(uni_4phase_fullstep_maxtorque_ctr_clk, true, nSteps, delay_ms);
		break;
	case 4:
		_rotate_stepMotor(bi_2phase_fullstep_mintorque_clk, true, nSteps, delay_ms);
		break;
	case 5:
		_rotate_stepMotor(bi_2phase_fullstep_mintorque_ctr_clk, true, nSteps, delay_ms);
		break;
	case 6:
		_rotate_stepMotor(bi_2phase_fullstep_maxtorque_clk, true, nSteps, delay_ms);
		break;
	case 7:
		_rotate_stepMotor(bi_2phase_fullstep_maxtorque_ctr_clk, true, nSteps, delay_ms);
		break;	
	default:
		break;
	}
}


/***********************************************************
 *  INTERNAL METHODS *
 *********************************************************** /

/*!
 * \brief Set which motor type will be used.
 */
void StepMotor::_setMotorType(SM_motortype_t motorType){

	_motorType = motorType;
}

/*!
 * \brief Set which torque force will be used.
 */
void StepMotor::_setTorqueForce(SM_torqueforce_t torqueForce){

	_torqueForce = torqueForce;
}

/*!
 * \brief Rotate step motor by using sequence step matrix.
 */
void StepMotor::_rotate_stepMotor(uint8_t *stepSequenceMatrix, bool is4stepMatrix, uint16_t nSteps, SM_stepdelay_t delay_ms){

	
	// currentStep iterates for nSteps times and loops back over stepSeqMatrix positions.
	// If is4stepMatrix it goes from 0 to 3 and returns to the matrix begin.
	// If is (8stepMatrix) it goes from 0 to 7 and returns again.
	uint8_t currentStep = 0x0;

	if (is4stepMatrix){
		for(uint16_t i = 0; i < nSteps; i++){
		
			currentStep = (0x0003 & i);
			_set_stepCmd(stepSequenceMatrix[currentStep]);

			// stop step until the next step -> impacts on stepmotor velocity
			stepDelay(delay_ms);		
		}
	}
	else{
		for(uint16_t i = 0; i < nSteps; i++){
		
			currentStep = (0x0007 & i);
			_set_stepCmd(stepSequenceMatrix[currentStep]);

			// stop step until the next step -> impacts on stepmotor velocity
			stepDelay(delay_ms);		
		}
	}
	// Turn off StepMotor pins to save current
	_set_stepCmd(0x0);
}

/* !
 * \brief Set a step command to the StepMotor pins.
 */
void StepMotor::_set_stepCmd(uint8_t nibble_cmd){

	// split nibble command to pass bit value to each pin status
	// e.g. nibble_cmd = 0x1100. (0x1100 >> 3) & 0x1 = TRUE. Calls pin_high()
	if((nibble_cmd >> 3) & 0x1) pin1_high() else pin1_low();
	if((nibble_cmd >> 2) & 0x1) pin2_high() else pin2_low();
	if((nibble_cmd >> 1) & 0x1) pin3_high() else pin3_low();
	if((nibble_cmd >> 0) & 0x1) pin4_high() else pin4_low();
}