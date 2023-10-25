Required Changes:


Best Practices Reference: https://stackoverflow.com/questions/1805351/best-practices-for-reusable-embedded-c

--------------------------------------------------------------------------------
LIBRARY DEVOPS REQUIREMENTS

2. Library shall use configuration files (Header file) to set project specific configs (e.g. pin config, function mapping)
3. Library shall have a documented API (including README.md file and GitHub page)
4. Library shall be tested through unit tests
5. Library shall use a control version system (branch for QA, dev, releases)
6. Library shall have a license to use

--------------------------------------------------------------------------------
CONCEPTUAL REQUIREMENTS
WHAT?
[DONE] 1. User shall be allowed to control Step motor speed.
[DONE] 2. User shall be allowed to control the rotational direction of Step Motor (Clockwise / Counter Clockwise).
[DONE] 3. User shall define required torque applied by the step motor (Max, Min).
[DONE] 4. User shall be allowed to use the library with unipolar / bipolar step motors.
[DONE] 5. User shall be allowed to choose any MCU digital pin for the Step Motor connections.
6. User shall set maximum amount of steps allowed to the Step Motor (it will lead to counting steps).

HOW?
[IN_PROGRESS]  1. Library shall be a general purpose library (absent of architecture / platform).
[DONE] 2. User shall always define 4 digital pin connections for the Step Motor control.
[DONE] 3. Library shall only control the Step Motor by using full step method.

--------------------------------------------------------------------------------
IMPLEMENTATION REQUIREMENTS
[DONE] 1. Implement a matrix mapping method to command different Step Motor types.
[DONE] 2. Enumeration and matrixes shall follow a convention for readbility.
[TO_DO]3. Implement the delay control (btw step commands) following RTOS?

[FUTURE_VERSION] 1. Library shall define a writeToPort function. 
[FUTURE_VERSION] 2. writeToPort function shall set all 4 registers (pin connections) at once.
[FUTURE_VERSION] 3. writeToPort function shall be enabled by the user at API (High) level.
[FUTURE_VERSION] 4. User shall ensure all 4 pins are properly connected to enable writing to a Port.

--------------------------------------------------------------------------------
CALIBRATION
1. SLOW SPEED
- base (360º) rotation: 576 steps
- join (360º) rotation: 1960 steps

2. MEDIUM SPEED
- base (360º) rotation: 578 steps
- join (360º) rotation: 1960 steps

3. FAST SPEED
- base (360º) rotation: 584 steps
- join (360º) rotation: 1960 steps