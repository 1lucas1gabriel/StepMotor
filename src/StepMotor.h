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
 * @file StepMotor.h
 * @brief StepMotor library header file for Arduino
 * @details
 * 		Source: https://github.com/1lucas1gabriel/StepMotor
 * 		CurrentVersion: 1.0
 * 		Date: Oct, 2023
 * 
 * @verbatim
 * --------------------------------------------------------------
 * StepMotor: v.1.0
 * StepMotor library allows to drive stepper motors in a simple way.
 * It can also be quickly re-used between diferent architectures by 
 * appling small changes in interface (hardware-dependent) functions.
 * 
 * API functions are designed to include:
 * 
 * 1. Control of step speed (discrete values), direction of rotation and applied torque.
 * 2. Allows to choose any MCU digital pin for the Step Motor connections.
 * 3. Allows usage of unipolar / bipolar step motors.
 * 
 * --------------------------------------------------------------
 * Setup:
 * StepMotor library always requires four-pins connection to drive
 * step motors properly. It uses only FULL step method to command the step motors,
 * allowing one or two phase to be activated simultaneously (MIN/MAX 
 * torque applied, respectively). It's highly recommended to use adequate 
 * drivers to drive those devices, see examples below.
 * 
 * * Bipolar Step Motor (2 phase)
 * 		* Driver: L293 H-bridge
 * 		* Coils per phase: 2
 
 * * Unipolar Step Motor (4 phase)
 * 		* Driver: ULN 2003
 * 		* Coils per phase: 1
 * 
 * @endverbatim
 *****************************************************************/

#ifndef STEPMOTOR_H
#define STEPMOTOR_H

#ifdef ARDUINO_ARCH_AVR
#include "Arduino.h"

#define stepDelay(delayTime)	delay(delayTime)
#define pinToPort(pin)			digitalPinToPort(pin)
#define pinToPortBit(pin)		digitalPinToBitMask(pin)

#define pin_high(	pinPort, pinPortBit)	{ *portOutputRegister(pinPort) |=  pinPortBit;}
#define pin_low(	pinPort, pinPortBit)	{ *portOutputRegister(pinPort) &= ~pinPortBit;}
#define pin_output(	pinPort, pinPortBit)	{ *portModeRegister(pinPort)   |=  pinPortBit;}
#define pin_input(	pinPort, pinPortBit)	{ *portModeRegister(pinPort)   &= ~pinPortBit;}

#endif


// Full Step and Maximum Torque (2 phase ON per step)
static const uint8_t uni_4phase_fullstep_maxtorque_clk[4] 		= {0x9, 0x3, 0x6, 0xC};
static const uint8_t uni_4phase_fullstep_maxtorque_ctr_clk[4] 	= {0xC, 0x6, 0x3, 0x9};

// Full Step and Minimum Torque (1 phase ON per step)
static const uint8_t uni_4phase_fullstep_mintorque_clk[4] 		 = {0x8, 0x1, 0x2, 0x4};
static const uint8_t uni_4phase_fullstep_mintorque_ctr_clk[4] 	= {0x4, 0x2, 0x1, 0x8};

// Full Step and Maximum Torque (2 phase ON per step)
static const uint8_t bi_2phase_fullstep_maxtorque_clk[4] 		= {0xA, 0x9, 0x5, 0x6};
static const uint8_t bi_2phase_fullstep_maxtorque_ctr_clk[4] 	= {0x6, 0x5, 0x9, 0xA};

// Full Step and Minimum Torque (1 phase ON per step)
static const uint8_t bi_2phase_fullstep_mintorque_clk[4] 		= {0x8, 0x1, 0x4, 0x2};
static const uint8_t bi_2phase_fullstep_mintorque_ctr_clk[4]	= {0x2, 0x4, 0x1, 0x8};


/**
 * Defines the StepMotor type used.
 */
typedef enum{	

	UNIPOLAR_4PHASE		= 0b00, 
	BIPOLAR_2PHASE		= 0b01
} SM_motortype_t;

/**
 * Defines torque force type applied by the StepMotor.
 */
typedef enum {
	
	MIN_TORQUE			= 0b00, 
	MAX_TORQUE	 		= 0b01
} SM_torqueforce_t;

/**
 * Defines rotational direction for the StepMotor.
 */
typedef enum {
	
	CLOCKWISE			= 0b00, 
	COUNTER_CLOCKWISE	= 0b01
} SM_direction_t;

/**
 * Defines delay time applied to the StepMotor between each step command.
 */
typedef enum {
	
	SLOW_MS				= 30, 
	MEDIUM_MS			= 15,
	FAST_MS 			= 5
} SM_stepdelay_t;


/**
 * @brief StepMotor Class
 */
class StepMotor{
public:
	StepMotor(	SM_motortype_t	motorType, 
				SM_torqueforce_t torqueForce,
				uint8_t in1Pin, 
				uint8_t in2Pin, 
				uint8_t in3Pin, 
				uint8_t in4Pin);

	virtual void begin();
    virtual void end();
	virtual void setMov(uint16_t nSteps, 
						SM_stepdelay_t delay_ms, 
						SM_direction_t direction);

private:
	SM_motortype_t 		_motorType;		///< Defines StepMotor motor type
	SM_torqueforce_t 	_torqueForce;	///< Defines StepMotor torque force
	
	uint8_t		_pin1Port;			///< PORT register for pin1
	uint8_t		_pin2Port;			///< PORT register for pin2
	uint8_t		_pin3Port;			///< PORT register for pin3
	uint8_t 	_pin4Port;  		///< PORT register for pin4

    uint8_t		_pin1PortBit;    	///< Bit number in IO register for pin1
    uint8_t 	_pin2PortBit;    	///< Bit number in IO register for pin2
    uint8_t 	_pin3PortBit;    	///< Bit number in IO register for pin3
    uint8_t 	_pin4PortBit;    	///< Bit number in IO register for pin4

	void _setMotorType(SM_motortype_t motorType);
	void _setTorqueForce(SM_torqueforce_t torqueForce);
	void _controlStepCmd(const uint8_t *stepSequenceMatrix, bool is4stepMatrix, uint16_t nSteps, SM_stepdelay_t delay_ms);
	void _setStepCmd(uint8_t nibble_cmd);
};

#endif // STEPMOTOR_H