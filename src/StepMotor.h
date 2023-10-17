#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

/*****************************************************************
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
 * 
 * 									0b00001000 => In1
 * 									0b00010000 => In1
 * 
 * 										  1010
 * 										 1010
 * 
 * ***************************************************************/

#ifdef __AVR
#include <Arduino.h>

#define writeToPort(nibble_cmd)	{ *portOutputRegister(_pin1Port) |=  (nibble_cmd << X);}
#define clearPinPort()			{ *portOutputRegister(_pin1Port) &= ~(0x0F << X);}
#define stepDelay(delayTime)	{ delay(delayTime);}

#define pin1_input()			{ *portModeRegister(_pin1Port) &= ~_pin1PortBit;}
#define pin2_input()			{ *portModeRegister(_pin2Port) &= ~_pin2PortBit;}
#define pin3_input()			{ *portModeRegister(_pin3Port) &= ~_pin3PortBit;}
#define pin4_input()			{ *portModeRegister(_pin4Port) &= ~_pin4PortBit;}

#define pin1_output()			{ *portModeRegister(_pin1Port) |=  _pin1PortBit;}
#define pin2_output()			{ *portModeRegister(_pin2Port) |=  _pin2PortBit;}
#define pin3_output()			{ *portModeRegister(_pin3Port) |=  _pin3PortBit;}
#define pin4_output()			{ *portModeRegister(_pin4Port) |=  _pin4PortBit;}

//#else #define for other architectures
#endif


/*************************************************************
 *  LOOKUP TABLES - STEP SEQUENCE MATRIX - REMINDER: SAVE IN FLASH
 * ***********************************************************/

// Full Step and Maximum Torque (2 phase ON per step)
static const uint8_t uni_4phase_clock_fullstep_torque[4] 			= {0x9, 0x3, 0x6, 0xC};
static const uint8_t uni_4phase_counter_clock_fullstep_torque[4] 	= {0xC, 0x6, 0x3, 0x9};

// Full Step and Reduced Torque (1 phase ON per step)
static const uint8_t uni_4phase_clock_fullstep[4] 					= {0x8, 0x1, 0x2, 0x4};
static const uint8_t uni_4phase_counter_clock_fullstep[4] 			= {0x4, 0x2, 0x1, 0x8};

// Half Step (Mix of 1 and 2 Phase ON per step)
static const uint8_t uni_4phase_clock_halfstep[8] 					= {0x9, 0x1, 0x3, 0x2, 0x6, 0x4, 0xC, 0x8};
static const uint8_t uni_4phase_counter_clock_halfstep[8] 			= {0x8, 0xC, 0x4, 0x6, 0x2, 0x3, 0x1, 0x9};


// Full Step and Maximum Torque (2 phase ON per step)
static const uint8_t bi_2phase_clock_fullstep_torque[4] 			= {0xA, 0x9, 0x5, 0x6};
static const uint8_t bi_2phase_counter_clock_fullstep_torque[4] 	= {0x6, 0x5, 0x9, 0xA};

// Full Step and Reduced Torque (1 phase ON per step)
static const uint8_t bi_2phase_clock_fullstep[4] 					= {0x8, 0x1, 0x4, 0x2};
static const uint8_t bi_2phase_counter_clock_fullstep[4] 			= {0x2, 0x4, 0x1, 0x8};

// Half Step (Mix of 1 and 2 Phase ON per step)
static const uint8_t bi_2phase_clock_halfstep[8] 					= {0x8, 0x9, 0x1, 0x5, 0x4, 0x6, 0x2, 0xA};
static const uint8_t bi_2phase_counter_clock_halfstep[8] 			= {0xA, 0x2, 0x6, 0x4, 0x5, 0x1, 0x9, 0x8};



typedef enum{	

	UNIPOLAR_4PHASE		= 0x00, 
	BIPOLAR_2PHASE		= 0x01
} SM_motortype_t;

typedef enum {
	
	HALF_TORQUE			= 0x00, 
	FULL_TORQUE 		= 0x01
} SM_torqueforce_t;

typedef enum {
	
	CLOCKWISE			= 0x00, 
	COUNTER_CLOCKWISE	= 0x01
} SM_direction_t;

typedef enum {
	
	SLOW_MS				= 100, 
	MEDIUM_MS			= 50,
	FAST_MS 			= 30
} SM_stepdelay_t;



class StepMotor 
{
public:
	StepMotor(	uint8_t in1Pin,
				uint8_t in2Pin,
				uint8_t in3Pin,
				uint8_t in4Pin,
				SM_motortype_t 		motorType,
				SM_torqueforce_t 	torqueForce);
	
	virtual void begin();
    virtual void end();
	virtual void setMov(uint16_t nSteps, 
						SM_stepdelay_t delay_ms = MEDIUM_MS, 
						SM_direction_t direction = CLOCKWISE);

	
protected:
#ifdef __AVR
	uint8_t	_pin1Port;
	uint8_t	_pin2Port;
	uint8_t	_pin3Port;
	uint8_t _pin4Port;  	//!< Unique Port for all IO pins register
    
	// only port is needed. Additional variables to allow shifting trought the register
    uint8_t _pin1PortBit;    	//!< bit number in IO register for pin1
    uint8_t _pin2PortBit;    	//!< bit number in IO register for pin2
    uint8_t _pin3PortBit;    	//!< bit number in IO register for pin3
    uint8_t _pin4PortBit;    	//!< bit number in IO register for pin4

//#else #define for other architectures
#endif
	
	// Internal Variables & Methods
	SM_motortype_t 		_motorType;		//!< Motor type
	SM_torqueforce_t 	_torqueForce;	//!< Torque force
	
	void _setMotorType(SM_motortype_t motorType);
	void _setTorqueForce(SM_torqueforce_t torqueForce);
	void _rotate_stepMotor(uint8_t *stepSequenceMatrix, uint16_t nSteps, SM_stepdelay_t delay_ms);
};

#endif // STEP_MOTOR_H





/* HALF_STEP already considered - needs adapting internal function
 * 1 phase actuated by time (less torque)
 * 2 phases actuated at the same time (full torque)
 * 
 * Improve Velocity deviation methods to vary 
 * Improve Velocity Control method (Scale and range
 */