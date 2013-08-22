# Albert Gural
# e: ag@albertgural.com
# w: http://albertgural.com
# d: 2013/08/18 - 2013/08/18

MCU=atmega168p                      # ATmega168 MCU.
CPU=12000000L                       # 12 MHz external clock.
SOURCES_PROJECT=src/photuris.cpp    # Photuris.ino source file.
PROJECT_NAME=photuris               # Result will be photuris.hex.
PROGRAMMER=usbasp                   # USBasp programmer (see http://www.fischl.de/usbasp).
PORT=usb                            # USB Port for USBasp programer.
AP_PATH=./
BAUDRATE=115200                     # Programming Baud rate.
LFUSE=0xD6                          # External full-swing crystal, no clock speed division
HFUSE=0xD5                          # WDT not always on, EEPROM save on reprogram, BOD=2.7V
EFUSE=0xF9                          # Bootloader 1024 words (app: 0x000-0xBFF, boot: 0xC00-0xFFF)
LIB=CapacitiveSensor Wire

CC=avr-gcc
CCP=avr-g++
AR=avr-ar rcs
OBJ=avr-objcopy
AVRDUDE=avrdude

CFLAGS=-c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) -DF_CPU=$(CPU) -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -I$(AP_PATH)arduino -I$(AP_PATH)arduino/variants/standard
LDFLAGS=-Os -Wl,--gc-sections -mmcu=$(MCU) -L$(AP_PATH)arduino -L$(AP_PATH) -L$(AP_PATH) -lm
EEPFLAGS=-O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0
HEXFLAGS=-O ihex -R .eeprom
AVRDUDEFLAGS=-c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUDRATE)

LIBINCS=$(addprefix $(AP_PATH)arduino/libraries/,$(LIB))
INCLUDE:=$(addprefix -I,$(shell find $(LIBINCS) -type d -not -path "*/examples*"))
ARFILE=$(AP_PATH)arduino/core.a
OBJECTS_PROJECT=$(SOURCES_PROJECT:.cpp=.o)

SOURCES_ARDUINO_C:=$(shell find $(AP_PATH)arduino -name '*.c' -not -path "*/libraries*") $(shell find $(LIBINCS) -name '*.c')
OBJECTS_ARDUINO_C=$(SOURCES_ARDUINO_C:.c=.o)

SOURCES_ARDUINO_CPP:=$(shell find $(AP_PATH)arduino -name '*.cpp' -not -path "*/libraries*") $(shell find $(LIBINCS) -name '*.cpp')
OBJECTS_ARDUINO_CPP=$(SOURCES_ARDUINO_CPP:.cpp=.o)

OBJECTS=$(OBJECTS_PROJECT) $(OBJECTS_ARDUINO_C) $(OBJECTS_ARDUINO_CPP)
OBJECTS_CORE=$(OBJECTS_ARDUINO_C) $(OBJECTS_ARDUINO_CPP)
ELFCODE=$(join $(PROJECT_NAME),.elf)
EEPCODE=$(join $(PROJECT_NAME),.eep)
HEXCODE=$(join $(PROJECT_NAME),.hex)
DEBUG_PROJECT=$(SOURCES_PROJECT:.cpp=.d)
DEBUG_ARDUINO_C=$(SOURCES_ARDUINO_C:.c=.d)
DEBUG_ARDUINO_CPP=$(SOURCES_ARDUINO_CPP:.cpp=.d)
DEBUG=$(DEBUG_PROJECT) $(DEBUG_ARDUINO_C) $(DEBUG_ARDUINO_CPP)
DBGCODE=$(join $(PROJECT_NAME),.d)

$(ARFILE): $(OBJECTS)
	$(AR) $(ARFILE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

$(ELFCODE): 
	$(CC) $(LDFLAGS) $(OBJECTS_PROJECT) $(ARFILE) -o $@

$(EEPCODE):
	$(OBJ) $(EEPFLAGS) $(ELFCODE) $@

$(HEXCODE):
	$(OBJ) $(HEXFLAGS) $(ELFCODE) $@

clean_obj:
	rm -rf $(OBJECTS) $(ARFILE) $(DEBUG)

clean_results:
	rm -rf $(ELFCODE) $(EEPCODE) $(HEXCODE) $(DBGCODE)

clean: clean_obj clean_results

all: clean $(SOURCES) $(ARFILE) $(ELFCODE) $(EEPCODE) $(HEXCODE)

fuse:
	$(AVRDUDE) $(AVRDUDEFLAGS) -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m -U efuse:w:$(EFUSE):m

upload:
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$(HEXCODE):i

# TODO: update this to the actual bootload command.
bootload:
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$(HEXCODE):i

