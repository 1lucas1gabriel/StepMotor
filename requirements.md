Required Changes:

Best Practices Reference: https://stackoverflow.com/questions/1805351/best-practices-for-reusable-embedded-c

--------------------------------------------------------------------------------
LIBRARY DEVOPS REQUIREMENTS

[FUTURE_VERSION]1. Library shall use configuration files (Header file) to set project specific configs (e.g. pin config, function mapping)
[FUTURE_VERSION] 2. Library shall be implemented in C (struct-like instead of classes)
[IN_PROGRESS] 2. Library shall have a documented API (including README.md file and GitHub page)
[TO_DO] 3. Library shall be tested through unit tests
[DONE] 4. Library shall use a control version system (branch for QA, dev, releases)
[DONE]  5. Library shall have a license to use

[DONE] 6. Library shall include examples about how to use API.
[TO_DO] 7. Library examples (src code) shall be documented describing examples functionalities, date, library version, pinout, uc configurations.


--------------------------------------------------------------------------------
CONCEPTUAL REQUIREMENTS
WHAT?
[DONE] 1. User shall be allowed to control Step motor speed.
[DONE] 2. User shall be allowed to control the rotational direction of Step Motor (Clockwise / Counter Clockwise).
[DONE] 3. User shall define required torque applied by the step motor (Max, Min).
[DONE] 4. User shall be allowed to use the library with unipolar / bipolar step motors.
[DONE] 5. User shall be allowed to choose any MCU digital pin for the Step Motor connections.
[FUTURE_VERSION] 6. User shall define maximum amount of steps allowed to the Step Motor (it will lead to counting steps). 

HOW?
[DONE] 1. Library shall be a general purpose library (absent of architecture / platform).
[DONE] 2. User shall always define 4 digital pin connections for the Step Motor control.
[DONE] 3. Library shall only control the Step Motor by using FULL step method.

--------------------------------------------------------------------------------
IMPLEMENTATION REQUIREMENTS
[DONE] 1. Implement a matrix mapping method to command different Step Motor types.
[DONE] 2. Enumeration and matrixes shall follow a convention for readbility.
[EVALUATE]3. Implement the delay control (btw step commands) following RTOS?

[FUTURE_VERSION] 1. Library shall define a writeToPort function. 
[FUTURE_VERSION] 2. writeToPort function shall set all 4 registers (pin connections) at once.
[FUTURE_VERSION] 3. writeToPort function shall be enabled by the user at API (High) level.
[FUTURE_VERSION] 4. User shall ensure all 4 pins are properly connected to enable writing to a Port.


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