# MCU and tools
MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
AVRDUDE_PROGRAMMER = usbasp

# Directories
SRC_DIR = source
BUILD_DIR = build

# File extensions
C_SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
CPP_SRCS := $(shell find $(SRC_DIR) -type f -name "*.cc")
ASM_SRCS := $(shell find $(SRC_DIR) -type f -name "*.S")

# Object files
OBJ := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(C_SRCS:.c=.o))
OBJ += $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(CPP_SRCS:.cc=.o))
OBJ += $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(ASM_SRCS:.S=.o))

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -Iinclude
CXXFLAGS = $(CFLAGS)
ASMFLAGS = -mmcu=$(MCU)
LDFLAGS = -mmcu=$(MCU) -Os

# Output files
TARGET = $(BUILD_DIR)/firmware
HEX = $(TARGET).hex

# Default target
all: $(HEX)

# Create build directory if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Pattern rules
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(ASMFLAGS) -c $< -o $@

# Link
$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

# Generate HEX
$(HEX): $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Flash
flash: $(HEX)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -p $(MCU) -U flash:w:$<:i

# Clean
clean:
	rm -rf $(BUILD_DIR)

help: 
	echo "make all для того чтобы собрать прошивку"
	echo "make clean чтобы удалить временные файлы"
	echo "make flash чтобы прошить плату через usbasp"

.PHONY: all flash clean help
.SILENT: help
