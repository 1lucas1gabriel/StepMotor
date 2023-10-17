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
    // Calculate bit and unique port register for writing commands to a step motor (AVR targets only)
    _pin1Port 	= digitalPinToPort(in1Pin);
	_pin2Port 	= digitalPinToPort(in2Pin);
	_pin3Port 	= digitalPinToPort(in3Pin);
    _pin4Port 	= digitalPinToPort(in4Pin);

    _pin1PortBit 	= digitalPinToBitMask(in1Pin);
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
    clearPinPort();
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
    clearPinPort(); 
}

/*!
 * \brief Rotate StepMotor nSteps at the established speed and direction
 */
void StepMotor::setMov(	uint16_t nSteps, 
						SM_stepdelay_t delay_ms, 
						SM_direction_t direction){	
	
	if(_motorType == BIPOLAR_2PHASE && direction == CLOCKWISE)
		_BI_CLKWISE_ROT_FULL_TORQUE(nSteps, speed);

	if(_motorType == BIPOLAR_2PHASE && direction == COUNTER_CLOCKWISE)
		_BI_CTR_CLKWISE_ROT_FULL_TORQUE(nSteps, speed);

	if(_motorType == UNIPOLAR_4PHASE && direction == CLOCKWISE)
		_UNI_CLKWISE_ROT_FULL_TORQUE(nSteps, speed);

	if(_motorType == UNIPOLAR_4PHASE && direction == COUNTER_CLOCKWISE)
		_UNI_CTR_CLKWISE_ROT_FULL_TORQUE(nSteps, speed);
	
	// Turn off StepMotor pins to save current
	clearPinPort();
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
 * \brief Rotate step motor by using sequence step.
 */
void StepMotor::_rotate_stepMotor(uint8_t *stepSequenceMatrix, uint16_t nSteps, SM_stepdelay_t delay_ms){

	for(uint16_t i = 0; i < nSteps; i++){
		//----------------------------------------------------------//
		// To sync movement and repeat for nSteps:					//
		// bitwise operation just select last 2 LSB from iterator	//
		// 2 LSB needed to order from 1 up to 4 step (00,01,10,11)	//
		//----------------------------------------------------------//

		// 0x0003 (0x00000011) & 11 (0b00001011) => 3 (0b11)
		// uni_4phase_clock_fullstep_torque[4] 	= {0x9, 0x3, 0x6, 0xC}; 
		// 0xC = 0x1100

		// needs to create a logic or function to go through 8 steps instead of 4
		// uni_4phase_clock_halfstep[8] = {0x9, 0x1, 0x3, 0x2, 0x6, 0x4, 0xC, 0x8};

		uint8_t currentStep = (0x0003 & i);

		// writing nibble to a PORT
		writeToPort(stepSequenceMatrix[currentStep] & 0x0F);

		// stop step until the next step -> impacts on motor velocity
		stepDelay(delay_ms);		
	}
}