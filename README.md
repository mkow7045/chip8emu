# CHIP-8 Emulator (SDL3)  
*A CHIP-8 emulator written in C++ and SDL3.*  

## Overview  
This project implements a full CHIP-8 emulator, running on desktop platforms using the SDL3 library for graphics, input and sound.  
The same core emulator logic has been ported to an embedded target (see the STM32 version [here](https://github.com/mkow7045/chip8emu-stm32)).  

## Features  
- Full CHIP-8 instruction set  
- 64×32 monochrome display, scaled up for windowed mode  
- 16-key hex keypad input (mapped to keyboard)  
- Delay and sound timers at 60 Hz  
- Sound via SDL3 audio (beep)  
- Rapid development & debugging environment for embedded port  

## Requirements  
- Desktop OS: Windows, Linux or macOS (SDL3 support)  
- C++ compiler supporting C++17 or later  
- SDL3 library installed  

## Building & Running  
```bash
git clone https://github.com/mkow7045/chip8emu.git
cd chip8emu
make
./chip8emu <path-to-rom.ch8>
```


<img width="633" height="475" alt="obraz" src="https://github.com/user-attachments/assets/13e303a9-a226-4678-a1db-c293f70dea70" />

<img width="632" height="472" alt="obraz" src="https://github.com/user-attachments/assets/e9803340-8cb8-4156-8de4-3881e8b0b5ba" />


