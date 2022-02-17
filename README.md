## Tinguely EV3 - *Tinguely Block*

## Introduction

The **Tinguely EV3** project aims to provide a tangible interface that allows user to program EV3 devices with [Scratch blocks](https://scratch.mit.edu/ev3) in real life. It replaces [EV3 Classroom](https://education.lego.com/en-us/downloads/mindstorms-ev3/software#downloads) for educational purposes by empowering collaboration and learning by giving physical forms to digital information, thus taking advantage of the human ability to grasp and manipulate physical objects and materials. 

Blocks are physical devices containing an Arduino nano. They communicate each others on a serial line with magnetics connector in their notches. Each Scratch block has an unique ID and a pre-defined list of parameters. The lowest block sends its ID and parameters as a binary chain to the upper block. The later sends its ID and parameters with the data received from above. The uppermost block receives the full binary chain that represents the Scratch program and send it to a Raspberry Pi for decoding and generation of a Python code that can be run on EV3 devices.   

**This repository contains the code that has to run on the Arduino Nano for each block of the tangible interface**. Depending on the block, the code has to be changed by the developper. This has been done with a `#define` logic that will be explined below. 

**For the code that has to run on the Raspberry Pi for frame decoding and code translation, check the TinguelyPi repository.**

A complete [User guide](https://hackmd.io/@jonathanmichel/B11DPn8wY) and [Developer guide](https://hackmd.io/@jonathanmichel/Hyz4LfKOF) (both in french) are available for additionnal information.


## Configuration

Instead of Arduino IDE, this code uses [VSCode](https://code.visualstudio.com/) wit the [Platform IO](https://platformio.org/) extension. It allows to code Arduino with C++. The [platformio.ini](platformio.ini) file describes the configuration required for this project.

## Code structure

Main code in [src/main.cpp](src/main.cpp). All definitions in `includes/` and source files in `src/`.

Communication with other blocks is handled by `com` and `debug` provide a debug interface over `Serial.print()`. 

## Usage

When programming an Arduino Nano for a specific Scratch block, change `#define` in [block.h](https://github.com/jonathanmichel/SPS_TinguelyBlock/blob/6b5e8a844318c5f7475ac615f336f10d06d94a40/includes/block.h#L23) depending on the required block. The goal is to provide an implementation for the methods [`blockInit()`](https://github.com/jonathanmichel/SPS_TinguelyBlock/blob/6b5e8a844318c5f7475ac615f336f10d06d94a40/includes/block.h#L41) and [`readParameters()`](https://github.com/jonathanmichel/SPS_TinguelyBlock/blob/6b5e8a844318c5f7475ac615f336f10d06d94a40/includes/block.h#L42) for each block. Theses implementations are in a dedicated source file in `src/blocks/`. 

For blocks that use booleans (like [c_if](src/blocks/c_if.cpp), [c_repeat_until](src/blocks/c_repeat_until.cpp), ...), a boolean implementation as to be provided. The current logic allows to change the implementation to use with a `#define` in [boolean.h](https://github.com/jonathanmichel/SPS_TinguelyBlock/blob/6b5e8a844318c5f7475ac615f336f10d06d94a40/includes/boolean.h#L11). Once again, booleans implementation for each block are in `src/booleans/` and have to provide code for the method [`readBoolean()`](https://github.com/jonathanmichel/SPS_TinguelyBlock/blob/6b5e8a844318c5f7475ac615f336f10d06d94a40/includes/boolean.h#L28). 

The standard Arduino serial line is used at 9600 bauds for print debug. 

A software serial line is used for communication between the blocks. It works at 9600 bauds on pins D2 (Tx) and D3 (Rx) as configured in [com.cpp](src/com.cpp).


## Authors

* **Jonathan Michel** - [jonathanmichel](https://github.com/jonathanmichel) 