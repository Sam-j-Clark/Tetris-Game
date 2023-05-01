# File:   Makefile
# Author: Vince Alain W. Verwilligen, Sam Clark
# Date:   21 Oct 2021
# Descr:  Makefile for tetris

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr -I../../extra/
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: tetris.out


# Compile: create object files from C source files.
tetris.o: tetris.c task_manager.h
	$(CC) -c $(CFLAGS) $< -o $@

task_manager.o: task_manager.c task_manager.h led_matrix.h tetrion.h tetromino.h ../../drivers/avr/system.h ../../drivers/button.h ../../drivers/led.h ../../utils/task.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

led_matrix.o: led_matrix.c led_matrix.h ../../drivers/avr/system.h ../../drivers/display.h ../../fonts/font5x5_1.h ../../utils/font.h ../../utils/tinygl.h ../../utils/uint8toa.h
	$(CC) -c $(CFLAGS) $< -o $@

tetrion.o: tetrion.c ../../drivers/avr/system.h tetrion.h tetromino.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

tetromino.o: tetromino.c tetromino.h ../../drivers/avr/system.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

sound.o: sound.c sound.h ../../drivers/avr/system.h ../../extra/mmelody.h ../../drivers/avr/pio.h ../../extra/tweeter.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/timer.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/button.h ../../drivers/avr/system.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/display.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/led.h ../../drivers/avr/system.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/ledmat.h ../../drivers/avr/system.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/navswitch.h ../../drivers/avr/system.h ../../drivers/avr/delay.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../utils/font.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

task.o: ../../utils/task.c ../../utils/task.h ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../utils/tinygl.h ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

uint8toa.o: ../../utils/uint8toa.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

mmelody.o: ../../extra/mmelody.c ../../extra/mmelody.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

tweeter.o: ../../extra/tweeter.c ../../extra/tweeter.h ../../drivers/avr/system.h ../../extra/ticker.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
tetris.out: tetris.o task_manager.o led_matrix.o sound.o tetrion.o tetromino.o system.o button.o pio.o timer.o display.o font.o led.o ledmat.o mmelody.o navswitch.o task.o tinygl.o tweeter.o uint8toa.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: tetris.out
	$(OBJCOPY) -O ihex tetris.out tetris.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash tetris.hex; dfu-programmer atmega32u2 start


