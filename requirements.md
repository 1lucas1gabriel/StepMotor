Required library development changes:
0. Add ReadMe with library features and constraints
1. encapsulate StepMotor, Core and dependencies per submodules (repositories)
2. create include or libs folder to facilitate referencing by projects

1. Refactor functions to mitigate imperative programming style
2. Select unit testing framework
3. Setup  unit testing framework
4. Create Makefile to implement unit test development
5. Develop test cases
6. Create mockups and stubs
7. Run test locally and extract metrics
8. Plan to apply testing automation (CI/CD)

9. Include command in Make to auto-generate documentation (HTML/PDF)
10. Create folder in main to store PDF doc.
11. Generate auto documentation with gh-pages (HTML)

Required library functional changes:
1. Include parsing source2Cmd feature into library (apply feature absent of technology layer)
2. Create a external project for RTOS usage with step motor library

Best Practices Reference: https://stackoverflow.com/questions/1805351/best-practices-for-reusable-embedded-c
--------------------------------------------------------------------------------
LIBRARY DEVOPS REQUIREMENTS

[FUTURE_VERSION] 1. Library shall be implemented in C (struct-like instead of classes)
[DONE] 2. Library shall have a documented API (including README.md file and GitHub page)
[TODO] 3. Library shall be tested through unit tests
[DONE] 4. Library shall use a control version system (branch for QA, dev, releases)
[DONE] 5. Library shall have a license to use
[DONE] 6. Library shall include examples about how to use API.
[DONE] 7. Library examples shall be documented describing examples, date, library version, pinout, uc configurations.


--------------------------------------------------------------------------------
# CONCEPTUAL REQUIREMENTS

## Version 1.0
- Services
[DONE] S0. Library shall define the command interface to control the device by using steps (stepMov) 
[DONE] S1. User shall define the step speed for each stepMov command requested from the device (slow, medium, fast).
[DONE] S2. User shall define the rotational direction for each stepMov command requested from the device (clockwise / counter clockwise).
[DONE] S3. User shall define the amount of steps required for each stepMov command requested from the device (int).
- Dev Config
[TODO] C1. User shall to set/define the torque method to be applied by the device (Max, Min).
[DONE] C2. User shall to set the device type to be used by the library (unipolar, bipolar).
[DONE] C3. User shall to set the 4 digital pins to be used by the library to command the device.
- Implementation
[DONE] I1. Library shall implement their functions by using tech-independent strategy.
[DONE] I2. Library shall support mapping each individual digital pin to the MCU Port/bit. 
[DONE] I3. Each device shall be controlled by using FULL step method.


## Version 1.1 - 
- Services
[TODO] S1. Library shall define the command interface to control the device by using angular measurement (angMov).
[TODO] S1.1 User shall define the (step) speed for each angMov command requested from the device (slow, medium, fast).
[TODO] S1.2 User shall define the rotational direction for each angMov command requested from the device (clockwise / counter clockwise).
[TODO] S1.3 User shall define the angle required for each angMov command requested from the device (int).
[TODO] S2. Library shall define the interface to get the current status of movement of the device (moving, stopped).
[TODO] S3. Library shall define the interface to reset the device position to default step zero.
[TODO] S4. Library shall define responses to each movement command request (cmd_ack, cmd_nack).
- Dev Config
[TODO] C1. Library shall to set/define the interface to set the maximum amount of steps performed by the device (1 rev).
- Fail Safes
[TODO] F1. When not specified, the library shall to set the default step speed of the device to "slow".
[TODO] F1. When not specified, the library shall to set the default torque of the device to "Min".
[TODO] F3. Library shall not execute command requests if steps request exceeds the maximum steps amount of the device.
- Implementation 
[TODO] I1. Library shall implement positive increment for clockwise rotation and negative increment for counter clockwise.
[TODO] I2. Each device shall store its current step position relative to default step zero.
[TODO] I3. Each device shall store its current status of movement (moving, stopped)
[TODO] I4. Each device shall store its maximum step amount.
[TODO] I5. Library shall define the internal interface to convert the angle measurement to steps of the device.

--------------------------------------------------------------------------------

[FUTURE_VERSION] S1. Include parser of commands into library interface

[FUTURE_VERSION] S1. Library shall define the interface to calibrate (move) and update default step zero of the device.
[FUTURE_VERSION] S2. Device shall provide means to measure default step zero position (switch sensor).
[FUTURE_VERSION] S3. Library shall define the interface to read current device step zero position.

[FUTURE_VERSION] 1. Library shall define a writeToPort function. 
[FUTURE_VERSION] 2. writeToPort function shall set all 4 registers (pin connections) at once.
[FUTURE_VERSION] 3. writeToPort function shall be enabled by the user at API (High) level.
[FUTURE_VERSION] 4. User shall ensure all 4 pins are properly connected to enable writing to a Port.

[EVALUATE]3. Implement the delay control (btw step commands) following RTOS?

--------------------------------------------------------------------------------
CALIBRATION
base Step Motor: HP printer internal motor
join Step Motor: 28BYJ-48

1. SLOW SPEED
- base (360º) rotation: 576 steps
- join (360º) rotation: 1960 steps

2. MEDIUM SPEED
- base (360º) rotation: 578 steps
- join (360º) rotation: 1960 steps

3. FAST SPEED
- base (360º) rotation: 584 steps
- join (360º) rotation: 1960 steps