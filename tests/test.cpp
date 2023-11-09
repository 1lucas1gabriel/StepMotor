#define BOOST_TEST_MODULE _TEST_STEPMOTOR_H_
#include "StepMotor.h"
#include <boost/test/included/unit_test.hpp>

/**
 * SETUP TEST
 * 
 * Create a new instance for each testing
*/

/**
 * TEARDOWN
 * 
 * ...
*/


/**
 * MOCKUPS AND STUBS
 * 
 * 
 * Interface hardware functions - from macro expansion needs to be changed
 * Compilation will not target any emmbedded device.
 * During compilation need to pass stub source files for those macros
*/

/**
 * GENERAL UNIT TESTING TIPS
 * 
 *  
 * - If you're writing strict unit tests (as opposed to integration tests) 
 * with stubs and mocks you shouldn't have dependencies on embedded hardware.
 * 
 * - Unit testing for void methods:
 *      - imperative: You're either asking the object to do something to 
 *      itself. e.g change state (It's assumed that it will be done).
 *      You can verify if the task was actually performed. 
 *      Verify if state change actually took place.
 * 
 *      - Informational: Just notifying someone that something happened 
 *      (without expecting action or response) respectively. They are rare 
 *      as a member of the public interface of the object... hence not normally 
 *      unit-tested. However if you must, You can verify if the handling to be 
 *      done on a notification takes place.
 */

BOOST_AUTO_TEST_CASE(_test__setTorqueForce){

    // Setup
    StepMotor baseMotor(BIPOLAR_2PHASE, MIN_TORQUE, 11,10,9,8); 
    //baseMotor.begin();

    uint8_t expected_value = 0;
    // BOOST_TEST (actual_value == expected_value)
}

BOOST_AUTO_TEST_CASE(_test__setMotorType){

    // Setup
    StepMotor baseMotor(BIPOLAR_2PHASE, MIN_TORQUE, 11,10,9,8); 
    //baseMotor.begin();

    uint8_t expected_value = 0;
    // BOOST_TEST (actual_value == expected_value)
}