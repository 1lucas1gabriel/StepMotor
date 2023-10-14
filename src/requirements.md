Required Changes:
0. Study Arduino StepMotor library in order to capture additional insights
1. Adjust delay function to be absent of specific library/architecture 
2. Document port (8bits) over pin conection required (4 pins) | In1 | In2 | In3 | In4 |
3. Implement function to write values on uC port (e.g. DDR1)
4. Implement matrix mapping for different motor step types.
[DONE] 5. Refactor functions names and structure when writing motor steps (unipolar, bipolar, etc)
6. Refactor enumeration and name conventions
7. Change notation method to doxygen documentation
8. Check how to use this-> properly


Best Practices Reference: https://stackoverflow.com/questions/1805351/best-practices-for-reusable-embedded-c

Library Requirements:
1. Library shall be a general purpose library for step motor controlling (absent of architecture / platform)
2. Library shall use configuration files (Header file) to set project specific configs (e.g. writing pins to a AVR port, delay function)
3. Library shall have documented API (including README.md file and GitHub page)
4. Library shall be tested through unit tests
5. Library shall use a version system (branch for QA, dev, releases)
6. Library shall have a license to use

Functional Requirements:
1. StepMotor shall allow motor speed control to the user
2. _rotate_stepMotor
3. setMov
4. begin(), end(), output/input macro functions
