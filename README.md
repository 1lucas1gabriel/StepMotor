# StepMotor
StepMotor v.1.0 library allows to drive step motors in a such handy way. Users can use the library to control bipolar or unipolar step motors by using 4 digital pins connected to the target microcontroller. StepMotor library originally was targeted to be used with ATMEGA328p (Arduino) but it can also be quickly re-used between diferent architectures by appling small changes in the interface functions.

The repository includes automated *Makefile* for quick building to *avr microcontroller* targets. You can refer to the *Makefile.incl* file in *root* folder to setup different targeted devices. Additionally, remember to refer to each *Makefile* under the *examples* and *src* folder in order to define compilation and linking process of the library. Please, also note this library has dependencies on the arduino core functions (tech-dependent layer) which is automatically pulled as a submodule from the [avr-arduino-core](https://github.com/1lucas1gabriel/avr-arduino-core/). 

*By default the StepMotor library was already pre-compiled to generate a static library (.a file). It can be changed and re-compiled to target to new devices.*


## Library features

1. User can control step movement of each configured device.
2. User can define step movement parameters (speed, direction, torque) for each device.
3. Device torque can be configured to minimum or maximum (one or two coils activated by time). 
3. Library allows the user to choose any digital pin to setup device connection.
4. Library allows usage of unipolar / bipolar step motors.
5. Library implement driver control via *Full* step method (4 steps by cycle).


## Setting up devices
StepMotor library always requires four-pins connection to drive step motors properly. It uses only FULL step method to command the step motors, allowing one or two phase to be activated simultaneously (minimum / maximum applied torque, respectively). When using step motors,it is highly recommended to use adequate drivers to drive these devices, see examples below:

- Bipolar Step Motor (2 phases)
	- Driver: L293 H-bridge
	- Coils per phase: 2
- Unipolar Step Motor (4 phases)
	- Driver: ULN 2003
	- Coils per phase: 1


## Folder Description
- **doc:** Stores API documentation by using Doxygen framework.
- **examples:** Includes .cpp src files and Makefiles as an easy-to-start example.
- **extra:** Includes additional information (e.g. datasheet) about the supported Step Motors.
- **src:** Includes both source and header files. It also stores the pre-compiled library (.a file).


## Dependencies
To use this library some resources are required as pre-installed on your host PC.
- avr-arduino-core Repository (already included as a *submodule*)
- GCC-AVR toolchain (gcc-avr, binutils-avr, avr-libc)
- avrdude tool
- Make