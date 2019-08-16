# MicroTree
This project was born as a LED installation meant to be put in a tree, hence the name of the project. It has later evolved to be a framework for building animations that can be controlled from touchOSC. It is based on the PJRC Teensy microcontroller (tested with Teensy 3.2 and 3.6 so far) in combination with the PJRC octo adaptor. An ESP8266 receives OSC packets via UDP over WIFI, and relays the OSC packets to the Teensy in order to control variables, and switch between animations. The FastLED library is used to control the LEDs.

I am trying to structure the project so that main.cpp, utility_function.cpp, osc.cpp, + their respective header files form the core. If I want to build in a new function or program I add it as a separate .cpp and .h to keep things tidy.
Each program should have all the necessary function to manipulate it's program specific parameters in the same file as the program. When I add a new program I also add a new "enum program" in main.h, and a new case for the program in the updateLEDs function in utility_functions.cpp.
Some variables are global and all programs use them. Like hue1, hue2, saturation1, saturation2, value1, value2, and some others. The idea is that I only need to define the funtions for manipulating them once, OSC messages can activate these functions, and when I add a new program I often don't have to add a lot of controls in TouchOSC because they are already there.


## Future goals
* Document my code better. So other people can understand it, use it, and contribute to it
* Document the hardware setup
* Document the TouchOSC setup
* Upload the code for the ESP to GIT
* Add more cool programs and functionality!
  * I want a program the lets me mix other programs toghether like a DJ mixes songs together
  * Fireworks effect
* Think out better solutions for the physical connecting and setup of all the equipment
  * Better connection box. Preferably water proof
  * Easy power connection plugs on everything
