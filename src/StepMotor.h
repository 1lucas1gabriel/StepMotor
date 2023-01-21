#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#include <Arduino.h>

#ifdef __AVR
#define STEP_IN1_LOW()		{ *portOutputRegister(	_in1PinPort) &= ~_in1PinBit; }   //!< IN1 pin low
#define STEP_IN1_HIGH()		{ *portOutputRegister(	_in1PinPort) |=  _in1PinBit; }   //!< IN1 pin high
#define STEP_IN1_INPUT()	{ *portModeRegister(	_in1PinPort) &= ~_in1PinBit; }   //!< IN1 pin input
#define STEP_IN1_OUTPUT()	{ *portModeRegister(	_in1PinPort) |=  _in1PinBit; }   //!< IN1 pin output
#define STEP_IN2_LOW()		{ *portOutputRegister(	_in2PinPort) &= ~_in2PinBit; }   //!< IN2 pin low
#define STEP_IN2_HIGH()		{ *portOutputRegister(	_in2PinPort) |=  _in2PinBit; }   //!< IN2 pin high
#define STEP_IN2_INPUT()	{ *portModeRegister(	_in2PinPort) &= ~_in2PinBit; }   //!< IN2 pin input
#define STEP_IN2_OUTPUT()	{ *portModeRegister(	_in2PinPort) |=  _in2PinBit; }   //!< IN2 pin output
#define STEP_IN3_LOW()		{ *portOutputRegister(	_in3PinPort) &= ~_in3PinBit; }   //!< IN3 pin low
#define STEP_IN3_HIGH()		{ *portOutputRegister(	_in3PinPort) |=  _in3PinBit; }   //!< IN3 pin high
#define STEP_IN3_INPUT()	{ *portModeRegister(	_in3PinPort) &= ~_in3PinBit; }   //!< IN3 pin input
#define STEP_IN3_OUTPUT()	{ *portModeRegister(	_in3PinPort) |=  _in3PinBit; }   //!< IN3 pin output
#define STEP_IN4_LOW()		{ *portOutputRegister(	_in4PinPort) &= ~_in4PinBit; }   //!< IN4 pin low
#define STEP_IN4_HIGH()     { *portOutputRegister(	_in4PinPort) |=  _in4PinBit; }   //!< IN4 pin high
#define STEP_IN4_INPUT()	{ *portModeRegister(	_in4PinPort) &= ~_in4PinBit; }   //!< IN4 pin input
#define STEP_IN4_OUTPUT()   { *portModeRegister(	_in4PinPort) |=  _in4PinBit; }   //!< IN4 pin output
#else
#define STEP_IN1_LOW()        { digitalWrite(_in1Pin, LOW); }                 //!< IN1 pin low
#define STEP_IN1_HIGH()       { digitalWrite(_in1Pin, HIGH); }                //!< IN1 pin high
#define STEP_IN1_INPUT()      { pinMode(	 _in1Pin, INPUT); }               //!< IN1 pin input
#define STEP_IN1_OUTPUT()     { pinMode(	 _in1Pin, OUTPUT); }              //!< IN1 pin output
#define STEP_IN2_LOW()        { digitalWrite(_in2Pin, LOW); }                 //!< IN2 pin low
#define STEP_IN2_HIGH()       { digitalWrite(_in2Pin, HIGH); }                //!< IN2 pin high
#define STEP_IN2_INPUT()      { pinMode(	 _in2Pin, INPUT); }               //!< IN2 pin input
#define STEP_IN2_OUTPUT()     { pinMode(	 _in2Pin, OUTPUT); }              //!< IN2 pin output
#define STEP_IN3_LOW()        { digitalWrite(_in3Pin, LOW); }                 //!< IN3 pin low
#define STEP_IN3_HIGH()       { digitalWrite(_in3Pin, HIGH); }                //!< IN3 pin high
#define STEP_IN3_INPUT()      { pinMode(	 _in3Pin, INPUT); }               //!< IN3 pin input
#define STEP_IN3_OUTPUT()     { pinMode(	 _in3Pin, OUTPUT); }              //!< IN3 pin output
#define STEP_IN4_LOW()        { digitalWrite(_in4Pin, LOW); }                 //!< IN4 pin low
#define STEP_IN4_HIGH()       { digitalWrite(_in4Pin, HIGH); }                //!< IN4 pin high
#define STEP_IN4_INPUT()      { pinMode(	 _in4Pin, INPUT); }               //!< IN4 pin input
#define STEP_IN4_OUTPUT()     { pinMode(	 _in4Pin, OUTPUT); }              //!< IN4 pin output
#endif


// bipolar  motors: 2 distinct phases
// unipolar motors: 4 distinct phases
typedef enum {Unipolar, Bipolar} motorType;
typedef enum {Low, High} torqueForce;


class StepMotor 
{
public:
	StepMotor(	uint8_t in1Pin,
				uint8_t in2Pin,
				uint8_t in3Pin,
				uint8_t in4Pin,
				motorType motorT,
				torqueForce torqueF = High);
	
	virtual void begin();
    virtual void end();
	virtual void setMov(int angle, uint8_t speed = 10);
	virtual void setMotorType(motorType motorT);
	virtual void setTorqueForce(torqueForce torqueF);
	//virtual void stopMov();
	//virtual void calibrate();
	
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
	motorType 	_motorT;	//!< Motor type: Bipolar or Unipolar
	torqueForce _torqueF;	//!< Torque force: High or Low
};

#endif // STEP_MOTOR_H
