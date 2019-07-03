# A Space Invaders game
This is a small demo project showing how one may use a digilent zybo board and a playstation
controller to create a small space invaders like game.

There are 2 main components to the demo. The hardware description (a combination of VHDL and Vivado
specific files), and software (c/c++ files).

## Directory structure
The project directory structure is as follows:
- bd: Board layout and pin constraints
- ip\_repo: IP modules, including VHDL for IP functionality (meaty bits).
- scripts: Project support files. Used by the Makefile to regenerate the project (after git clone).
- sdk: Where software applications live (the actual space invaders game).
- vivado: Location of regenerated project files. Nothing in here needs to be committed to git.

## Project usage
It is strongly recommended that you stick with the Makefile for all operations where possible. The
Vivado IDE is not Git friendly, hence the Makefile wraps operations to ensure that a git compatible
project and supporing files is generated. Once the project itself is generated, you may use most GUI
features as usual, with the exception of SDK features, which should also be started from the Makefile.

### Example - Getting started
```
> git clone https://github.com/Aloz1/Zybo-SpaceInvaders
> make open_gui
```

### Example - Starting the SDK
```
> make open_sdk
```

### Example - Cleaning the project
```
> make clean
```

## Points of interest

### Hardware
Hardware within this project shows how a PS1 controller may be decoded in VHDL (with some help from
software via AXI). Source code related to PS1 controller protocol decoding is in
`ip\_repo/PMOD\_PSX\_1.0/hdl`.

The general hardware layout is described by the overall board block diagram.

There is also a VGA interface utilised by the project, but this was not written by me.

### Software
The general structure of the game relies heavily on multithereading (multitasking in FreeRTOS terms).
This design decision was chosen to demonstrate an understanding of multithreading, and to experiment
with the idea of a massively multithreaded game. Each space invader lives within its own thread,
with signaling occuring between invaders to indicate a change in direction. Invaders and lasers both
derive from Collidable, meaning they are also able to signal to each other when they have collided.
Signals are passed between threads using xTaskNotify.

Note: Files relating to VGA were not written by me.
