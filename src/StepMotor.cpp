/*
 * MIT License
 *
 * Copyright (c) 2023 Lucas Morais
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


/*****************************************************************
 * @file StepMotor.cpp
 * @brief StepMotor library source code for Arduino & ARM Cortex-M3 (STM32)
 * @details
 * 		Source: https://github.com/1lucas1gabriel/StepMotor
 *****************************************************************/


#include "StepMotor.h"

/*******************************************************************
 * @brief StepMotor Class constructor.
 *******************************************************************/
StepMotor::StepMotor( 	SM_motortype_t motorType, 
						SM_torqueforce_t torqueForce,
						uint8_t in1Pin, 
						uint8_t in2Pin, 
						uint8_t in3Pin, 
						uint8_t in4Pin){

	_setMotorType(motorType);
	_setTorqueForce(torqueForce);

#ifdef __AVR
    // Map selected pin to a PORT and bit position (AVR targets only)
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

/*******************************************************************
 * @brief Initialize StepMotor controller pins.
 *******************************************************************/
void StepMotor::begin(){
	
	// Set Output PinMode and Turn Off to save current
    pin1_output();
	pin2_output();
	pin3_output();
	pin4_output();
    _set_stepCmd(0x0);
}

/*******************************************************************
 * @brief Release StepMotor controller pins.
 *******************************************************************/
void StepMotor::end(){
	
	// Set Input PinMode and Turn Off to save current
    pin1_input();
	pin2_input();
	pin3_input();
	pin4_input();
    _set_stepCmd(0x0);
}

/********************************************************************
 * @brief Rotate StepMotor by nSteps at the expected direction.
 ********************************************************************/
void StepMotor::setMov(	uint16_t nSteps, 
						SM_stepdelay_t delay_ms, 
						SM_direction_t direction){

	/**
	 * - Following table documents how internal and external variables
	 *  are mapped to set an adequate movement command.
	 * 
	 *| _motorType 	| _torqueForce 	| direction | cmd (BIN) |
	 *|-------------|---------------|-----------|-----------|
	 *|	UNI_4PHASE	| MIN_TORQUE	| CLK		| 0b0000 	|
	 *|	UNI_4PHASE	| MIN_TORQUE	| CTR_CLK	| 0b0001 	|
	 *|	UNI_4PHASE	| MAX_TORQUE	| CLK		| 0b0010 	|
	 *|	UNI_4PHASE	| MAX_TORQUE	| CTR_CLK	| 0b0011 	|
	 *|	BI_2PHASE	| MIN_TORQUE	| CLK		| 0b0100 	|
	 *|	BI_2PHASE	| MIN_TORQUE	| CTR_CLK	| 0b0101 	|
	 *|	BI_2PHASE	| MAX_TORQUE	| CLK		| 0b0110 	|
	 *|	BI_2PHASE	| MAX_TORQUE	| CTR_CLK	| 0b0111 	|
	 */

	uint8_t cmd = (_motorType << 2) | ((_torqueForce << 1) | direction);

	switch (cmd){

	case 0:
		_control_stepCmd(uni_4phase_fullstep_mintorque_clk, true, nSteps, delay_ms);
		break;
	case 1:
		_control_stepCmd(uni_4phase_fullstep_mintorque_ctr_clk, true, nSteps, delay_ms);
		break;
	case 2:
		_control_stepCmd(uni_4phase_fullstep_maxtorque_clk, true, nSteps, delay_ms);
		break;
	case 3:
		_control_stepCmd(uni_4phase_fullstep_maxtorque_ctr_clk, true, nSteps, delay_ms);
		break;
	case 4:
		_control_stepCmd(bi_2phase_fullstep_mintorque_clk, true, nSteps, delay_ms);
		break;
	case 5:
		_control_stepCmd(bi_2phase_fullstep_mintorque_ctr_clk, true, nSteps, delay_ms);
		break;
	case 6:
		_control_stepCmd(bi_2phase_fullstep_maxtorque_clk, true, nSteps, delay_ms);
		break;
	case 7:
		_control_stepCmd(bi_2phase_fullstep_maxtorque_ctr_clk, true, nSteps, delay_ms);
		break;	
	default:
		break;
	}
}


/*******************************************************************
 * @brief Set StepMotor type to be used controlled.
 *******************************************************************/
void StepMotor::_setMotorType(SM_motortype_t motorType){

	_motorType = motorType;
}

/*******************************************************************
 * @brief Set torque force type to be used by StepMotor.
 *******************************************************************/
void StepMotor::_setTorqueForce(SM_torqueforce_t torqueForce){

	_torqueForce = torqueForce;
}

/*******************************************************************
 * @brief Control sequenced steps & speed applied to the StepMotor.
 *******************************************************************/
void StepMotor::_control_stepCmd(	uint8_t *stepSequenceMatrix, 
									bool is4stepMatrix, 
									uint16_t nSteps, 
									SM_stepdelay_t delay_ms){

	// currentStep iterates for nSteps times and loops back over stepSeqMatrix positions. 
	// If is4stepMatrix true currentStep goes from 0 to 3 and returns to the matrix beginning. 
	// Else it goes from 0 to 7 and returns again.
	uint8_t currentStep = 0;

	// is4stepMatrix included to support non-4stepMatrixes
	if (is4stepMatrix){
		for(uint16_t i = 0; i < nSteps; i++){
		
			currentStep = (0x0003 & i);
			_set_stepCmd(stepSequenceMatrix[currentStep]);
			stepDelay(delay_ms);		
		}
	}
	else{
		for(uint16_t i = 0; i < nSteps; i++){
		
			currentStep = (0x0007 & i);
			_set_stepCmd(stepSequenceMatrix[currentStep]);
			stepDelay(delay_ms);		
		}
	}
	// Turn off StepMotor pins to save current
	_set_stepCmd(0x0);
}

/*******************************************************************
 * @brief Set a step command to the StepMotor pins.
 *******************************************************************/
void StepMotor::_set_stepCmd(uint8_t nibble_cmd){

	// nibble_cmd is splited to pass bit status value to each pin.
	// e.g. nibble_cmd = 0x1100. (0x1000 >> 3) & 0x1 = TRUE. Calls pin_high()
	if((nibble_cmd >> 3) & 0x1) pin1_high() else pin1_low();
	if((nibble_cmd >> 2) & 0x1) pin2_high() else pin2_low();
	if((nibble_cmd >> 1) & 0x1) pin3_high() else pin3_low();
	if((nibble_cmd >> 0) & 0x1) pin4_high() else pin4_low();
}