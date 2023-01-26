#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#include <Arduino.h>

#ifdef __AVR
#define IN1_LOW()		{ *portOutputRegister(	_in1PinPort) &= ~_in1PinBit;}
#define IN1_HIGH()		{ *portOutputRegister(	_in1PinPort) |=  _in1PinBit;}
#define IN1_INPUT()		{ *portModeRegister(	_in1PinPort) &= ~_in1PinBit;}
#define IN1_OUTPUT()	{ *portModeRegister(	_in1PinPort) |=  _in1PinBit;}
#define IN2_LOW()		{ *portOutputRegister(	_in2PinPort) &= ~_in2PinBit;}
#define IN2_HIGH()		{ *portOutputRegister(	_in2PinPort) |=  _in2PinBit;}
#define IN2_INPUT()		{ *portModeRegister(	_in2PinPort) &= ~_in2PinBit;}
#define IN2_OUTPUT()	{ *portModeRegister(	_in2PinPort) |=  _in2PinBit;}
#define IN3_LOW()		{ *portOutputRegister(	_in3PinPort) &= ~_in3PinBit;}
#define IN3_HIGH()		{ *portOutputRegister(	_in3PinPort) |=  _in3PinBit;}
#define IN3_INPUT()		{ *portModeRegister(	_in3PinPort) &= ~_in3PinBit;}
#define IN3_OUTPUT()	{ *portModeRegister(	_in3PinPort) |=  _in3PinBit;}
#define IN4_LOW()		{ *portOutputRegister(	_in4PinPort) &= ~_in4PinBit;}
#define IN4_HIGH()     	{ *portOutputRegister(	_in4PinPort) |=  _in4PinBit;}
#define IN4_INPUT()		{ *portModeRegister(	_in4PinPort) &= ~_in4PinBit;}
#define IN4_OUTPUT()   	{ *portModeRegister(	_in4PinPort) |=  _in4PinBit;}
#else
#define IN1_LOW()       { digitalWrite(_in1Pin, LOW); }      
#define IN1_HIGH()      { digitalWrite(_in1Pin, HIGH);}     
#define IN1_INPUT()     { pinMode(	 _in1Pin, INPUT); }       
#define IN1_OUTPUT()    { pinMode(	 _in1Pin, OUTPUT);}      
#define IN2_LOW()       { digitalWrite(_in2Pin, LOW); }      
#define IN2_HIGH()      { digitalWrite(_in2Pin, HIGH);}     
#define IN2_INPUT()     { pinMode(	 _in2Pin, INPUT); }       
#define IN2_OUTPUT()    { pinMode(	 _in2Pin, OUTPUT);}      
#define IN3_LOW()       { digitalWrite(_in3Pin, LOW); }      
#define IN3_HIGH()      { digitalWrite(_in3Pin, HIGH);}     
#define IN3_INPUT()     { pinMode(	 _in3Pin, INPUT); }       
#define IN3_OUTPUT()    { pinMode(	 _in3Pin, OUTPUT);}      
#define IN4_LOW()       { digitalWrite(_in4Pin, LOW); }      
#define IN4_HIGH()      { digitalWrite(_in4Pin, HIGH);}     
#define IN4_INPUT()     { pinMode(	 _in4Pin, INPUT); }     
#define IN4_OUTPUT()    { pinMode(	 _in4Pin, OUTPUT);}
#endif


// bipolar  motors: 2 distinct phases
// unipolar motors: 4 distinct phases
typedef enum {Unipolar, Bipolar} motorType;
typedef enum {Half, Full} torqueForce;
typedef enum {Clk, CtrClk} directRot;


class StepMotor 
{
public:
	StepMotor(	uint8_t in1Pin,
				uint8_t in2Pin,
				uint8_t in3Pin,
				uint8_t in4Pin,
				motorType motorT,
				torqueForce torqueF = Full);
	
	virtual void begin();
    virtual void end();
	virtual void setMov(uint16_t nSteps, uint8_t speed = 1, directRot directR = Clk);
	virtual void setMotorType(motorType motorT);
	virtual void setTorqueForce(torqueForce torqueF);
	
protected:
#ifdef __AVR
    uint8_t _in1PinPort;   	//!< Pole 1 Port in IO pin register
    uint8_t _in2PinPort;   	//!< Pole 2 Port in IO pin register
    uint8_t _in3PinPort;   	//!< Pole 3 Port in IO pin register
    uint8_t _in4PinPort;   	//!< Pole 4 Port in IO pin register
    
    uint8_t _in1PinBit;    	//!< Pole 1 bit number in IO pin register
    uint8_t _in2PinBit;    	//!< Pole 2 bit number in IO pin register
    uint8_t _in3PinBit;    	//!< Pole 3 bit number in IO pin register
    uint8_t _in4PinBit;    	//!< Pole 4 bit number in IO pin register
#else
    uint8_t _in1Pin;    	//!< Pole 1 pin
    uint8_t _in2Pin;    	//!< Pole 2 pin
    uint8_t _in3Pin;    	//!< Pole 3 pin
    uint8_t _in4Pin;    	//!< Pole 4 pin
#endif
	
	// Internal Variables & Methods
	motorType 	_motorT;	//!< Motor type: Bipolar or Unipolar
	torqueForce _torqueF;	//!< Torque force: Full or Half

	void _RELEASE_PINS();
	void _BI_CLKWISE_ROT_FULL_TORQUE(uint16_t nSteps, uint8_t speed);		
	void _BI_CTR_CLKWISE_ROT_FULL_TORQUE(uint16_t nSteps, uint8_t speed);
	void _UNI_CLKWISE_ROT_FULL_TORQUE(uint16_t nSteps, uint8_t speed);		
	void _UNI_CTR_CLKWISE_ROT_FULL_TORQUE(uint16_t nSteps, uint8_t speed);
/*
	void _BIPOLAR_POSITIVE_ANGLE_FULL_STEP(uint8_t speed);			
	void _BIPOLAR_NEGATIVE_ANGLE_FULL_STEP(uint8_t speed);			
	void _UNIPOLAR_POSITIVE_ANGLE_FULL_STEP(uint8_t speed);			
	void _UNIPOLAR_NEGATIVE_ANGLE_FULL_STEP(uint8_t speed);	
*/		
};

#endif // STEP_MOTOR_H
