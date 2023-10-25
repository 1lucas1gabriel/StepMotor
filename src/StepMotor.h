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
 * @brief StepMotor library header file for Arduino & ARM Cortex-M3 (STM32)
 * @details
 * 		Source: https://github.com/1lucas1gabriel/StepMotor
 * 
 * @verbatim
 * 	Required mapping between uC Port and Step Motor connection:
 * 	
 * 	0. One Single PORT must be used to connect all 4 pins.
 * 	1. Pin connection must be sequenced over a same PORT.
 *  2. Written nibble to a Port refers to a step command.
 * 
 * 
 *  Pin connection example
 * 
 * 						-----------------------------------------
 *  uC: 8 LSB Port		| b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
 * 						-----------------------------------------
 * 	StepMotor:						   ---------------------
 *  pin connection (nibble_cmd)		   | In1| In2| In3| In4|
 * 									   ---------------------
 * @endverbatim
 *****************************************************************/

#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#ifdef __AVR
#include <Arduino.h>

// [FUTURE_VERSION]: Performance library - Writing (4bits) directly to a PORT register 
//#define writeToPort(nibble_cmd)	{ *portOutputRegister(_pin1Port) |=  (nibble_cmd << X);}
//#define clearPinPort()			{ *portOutputRegister(_pin1Port) &= ~(0x0F << X);}
#define stepDelay(delayTime)	{ delay(delayTime);}

#define pin1_high()				{ *portOutputRegister(_pin1Port) |=  _pin1PortBit;}
#define pin2_high()				{ *portOutputRegister(_pin2Port) |=  _pin2PortBit;}
#define pin3_high()				{ *portOutputRegister(_pin3Port) |=  _pin3PortBit;}
#define pin4_high()				{ *portOutputRegister(_pin4Port) |=  _pin4PortBit;}

#define pin1_low()				{ *portOutputRegister(_pin1Port) &=  ~_pin1PortBit;}
#define pin2_low()				{ *portOutputRegister(_pin2Port) &=  ~_pin2PortBit;}
#define pin3_low()				{ *portOutputRegister(_pin3Port) &=  ~_pin3PortBit;}
#define pin4_low()				{ *portOutputRegister(_pin4Port) &=  ~_pin4PortBit;}

#define pin1_input()			{ *portModeRegister(_pin1Port) &= ~_pin1PortBit;}
#define pin2_input()			{ *portModeRegister(_pin2Port) &= ~_pin2PortBit;}
#define pin3_input()			{ *portModeRegister(_pin3Port) &= ~_pin3PortBit;}
#define pin4_input()			{ *portModeRegister(_pin4Port) &= ~_pin4PortBit;}

#define pin1_output()			{ *portModeRegister(_pin1Port) |=  _pin1PortBit;}
#define pin2_output()			{ *portModeRegister(_pin2Port) |=  _pin2PortBit;}
#define pin3_output()			{ *portModeRegister(_pin3Port) |=  _pin3PortBit;}
#define pin4_output()			{ *portModeRegister(_pin4Port) |=  _pin4PortBit;}

//#else [FUTURE_VERSION]: ARM CORTEX M3 (STM32)
#endif


// Full Step and Maximum Torque (2 phase ON per step)
static const uint8_t uni_4phase_fullstep_maxtorque_clk[4] 		= {0x9, 0x3, 0x6, 0xC};
static const uint8_t uni_4phase_fullstep_maxtorque_ctr_clk[4] 	= {0xC, 0x6, 0x3, 0x9};

// Full Step and Minimum Torque (1 phase ON per step)
static const uint8_t uni_4phase_fullstep_mintorque_clk[4] 		= {0x8, 0x1, 0x2, 0x4};
static const uint8_t uni_4phase_fullstep_mintorque_ctr_clk[4] 	= {0x4, 0x2, 0x1, 0x8};

// Full Step and Maximum Torque (2 phase ON per step)
static const uint8_t bi_2phase_fullstep_maxtorque_clk[4] 		= {0xA, 0x9, 0x5, 0x6};
static const uint8_t bi_2phase_fullstep_maxtorque_ctr_clk[4] 	= {0x6, 0x5, 0x9, 0xA};

// Full Step and Minimum Torque (1 phase ON per step)
static const uint8_t bi_2phase_fullstep_mintorque_clk[4] 		= {0x8, 0x1, 0x4, 0x2};
static const uint8_t bi_2phase_fullstep_mintorque_ctr_clk[4]	= {0x2, 0x4, 0x1, 0x8};

// TBD [FUTURE_VERSION]: Half Step implementation
// Half Step (Mix of 1 and 2 Phase ON per step)
// static const uint8_t uni_4phase_halfstep_clk[8] 				= {0x9, 0x1, 0x3, 0x2, 0x6, 0x4, 0xC, 0x8};
// static const uint8_t uni_4phase_halfstep_ctr_clk[8] 			= {0x8, 0xC, 0x4, 0x6, 0x2, 0x3, 0x1, 0x9};

// TBD [FUTURE_VERSION]: Half Step implementation
// Half Step (Mix of 1 and 2 Phase ON per step)
//static const uint8_t bi_2phase_halfstep_clk[8]				= {0x8, 0x9, 0x1, 0x5, 0x4, 0x6, 0x2, 0xA};
//static const uint8_t bi_2phase_halfstep_ctr_clk[8] 			= {0xA, 0x2, 0x6, 0x4, 0x5, 0x1, 0x9, 0x8};


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
	void _controlStepCmd(uint8_t *stepSequenceMatrix, bool is4stepMatrix, uint16_t nSteps, SM_stepdelay_t delay_ms);
	void _setStepCmd(uint8_t nibble_cmd);
};

#endif // STEP_MOTOR_H