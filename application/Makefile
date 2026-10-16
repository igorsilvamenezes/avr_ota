# =====================================================================
# Application firmware Makefile (ATmega128 @ 8 MHz)
# =====================================================================

# ------------------------------------------------------------ Target
MCU         := atmega128
F_CPU       := 8000000UL
TARGET      := app
BUILD_DIR   := build

# ------------------------------------------------------------ Tools
CC          := avr-gcc
OBJCOPY     := avr-objcopy
OBJDUMP     := avr-objdump
SIZE        := avr-size
AVRDUDE     := avrdude

# ------------------------------------------------------------ Programmer
PROGRAMMER        := usbasp
AVRDUDE_PART      := m128
ISP_BITCLOCK      :=          # empty = USBasp default (fine at 8 MHz)
ISP_BITCLOCK_SLOW := 10       # ~94 kHz: needed while the chip runs at 1 MHz

AVRDUDE_FLAGS = -c $(PROGRAMMER) -p $(AVRDUDE_PART) \
                $(if $(strip $(ISP_BITCLOCK)),-B $(ISP_BITCLOCK))

# ------------------------------------------------------------ Fuses
# 0 = programmed. See Step 0 for the meaning of every bit.
LFUSE := 0x3F   # ext. crystal, SUT=11, BOD on @ 4.0 V (use 0xBF for 3.3 V)
HFUSE := 0xC1   # JTAG off, CKOPT on, EESAVE on, BOOTSZ=8 KB, BOOTRST off
EFUSE := 0xFF   # M103C off, WDTON off

# ------------------------------------------------------------ Sources
APP_SRCS    := $(wildcard src/*.c src/*/*.c)
COMMON_SRCS := $(wildcard ../common/src/*.c)

OBJS := $(APP_SRCS:%.c=$(BUILD_DIR)/%.o) \
        $(COMMON_SRCS:../common/src/%.c=$(BUILD_DIR)/common/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := include ../common/include

# ------------------------------------------------------------ Flags
CFLAGS  := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -std=c99 -g \
           -Wall -Wextra -Werror \
           -ffunction-sections -fdata-sections \
           $(addprefix -I,$(INC_DIRS)) -MMD -MP
LDFLAGS := -mmcu=$(MCU) -Wl,--gc-sections \
           -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

ELF := $(BUILD_DIR)/$(TARGET).elf
HEX := $(BUILD_DIR)/$(TARGET).hex
BIN := $(BUILD_DIR)/$(TARGET).bin
LSS := $(BUILD_DIR)/$(TARGET).lss

# Sections that are not program memory and must not go into hex/bin.
NON_FLASH := -R .eeprom -R .fuse -R .lock -R .signature

# ------------------------------------------------------------ Rules
.PHONY: all size flash read-fuses fuses clean

all: $(HEX) $(BIN) $(LSS) size

$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/common/%.o: ../common/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $(NON_FLASH) $< $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $(NON_FLASH) $< $@

$(LSS): $(ELF)
	$(OBJDUMP) -h -S $< > $@

size: $(ELF)
	$(SIZE) $<

flash: $(HEX)
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$<:i

read-fuses:
	$(AVRDUDE) $(AVRDUDE_FLAGS) \
	    -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h -U lock:r:-:h

# Guarded on purpose: a wrong fuse value can lock you out of the chip.
fuses:
ifneq ($(CONFIRM),yes)
	$(error Refusing to write fuses. Re-run with: make fuses CONFIRM=yes)
endif
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U efuse:w:$(EFUSE):m -U hfuse:w:$(HFUSE):m
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:$(LFUSE):m

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)# =====================================================================
# Application firmware Makefile (ATmega128 @ 8 MHz)
# =====================================================================

# ------------------------------------------------------------ Target
MCU         := atmega128
F_CPU       := 8000000UL
TARGET      := app
BUILD_DIR   := build

# ------------------------------------------------------------ Tools
CC          := avr-gcc
OBJCOPY     := avr-objcopy
OBJDUMP     := avr-objdump
SIZE        := avr-size
AVRDUDE     := avrdude

# ------------------------------------------------------------ Programmer
PROGRAMMER        := usbasp
AVRDUDE_PART      := m128
ISP_BITCLOCK      :=          # empty = USBasp default (fine at 8 MHz)
ISP_BITCLOCK_SLOW := 10       # ~94 kHz: needed while the chip runs at 1 MHz

AVRDUDE_FLAGS = -c $(PROGRAMMER) -p $(AVRDUDE_PART) \
                $(if $(strip $(ISP_BITCLOCK)),-B $(ISP_BITCLOCK))

# ------------------------------------------------------------ Fuses
# 0 = programmed. See Step 0 for the meaning of every bit.
LFUSE := 0x3F   # ext. crystal, SUT=11, BOD on @ 4.0 V (use 0xBF for 3.3 V)
HFUSE := 0xC1   # JTAG off, CKOPT on, EESAVE on, BOOTSZ=8 KB, BOOTRST off
EFUSE := 0xFF   # M103C off, WDTON off

# ------------------------------------------------------------ Sources
APP_SRCS    := $(wildcard src/*.c src/*/*.c)
COMMON_SRCS := $(wildcard ../common/src/*.c)

OBJS := $(APP_SRCS:%.c=$(BUILD_DIR)/%.o) \
        $(COMMON_SRCS:../common/src/%.c=$(BUILD_DIR)/common/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := include ../common/include

# ------------------------------------------------------------ Flags
CFLAGS  := -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -std=c99 -g \
           -Wall -Wextra -Werror \
           -ffunction-sections -fdata-sections \
           $(addprefix -I,$(INC_DIRS)) -MMD -MP
LDFLAGS := -mmcu=$(MCU) -Wl,--gc-sections \
           -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

ELF := $(BUILD_DIR)/$(TARGET).elf
HEX := $(BUILD_DIR)/$(TARGET).hex
BIN := $(BUILD_DIR)/$(TARGET).bin
LSS := $(BUILD_DIR)/$(TARGET).lss

# Sections that are not program memory and must not go into hex/bin.
NON_FLASH := -R .eeprom -R .fuse -R .lock -R .signature

# ------------------------------------------------------------ Rules
.PHONY: all size flash read-fuses fuses clean

all: $(HEX) $(BIN) $(LSS) size

$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/common/%.o: ../common/src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $(NON_FLASH) $< $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $(NON_FLASH) $< $@

$(LSS): $(ELF)
	$(OBJDUMP) -h -S $< > $@

size: $(ELF)
	$(SIZE) $<

flash: $(HEX)
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$<:i

read-fuses:
	$(AVRDUDE) $(AVRDUDE_FLAGS) \
	    -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h -U lock:r:-:h

# Guarded on purpose: a wrong fuse value can lock you out of the chip.
fuses:
ifneq ($(CONFIRM),yes)
	$(error Refusing to write fuses. Re-run with: make fuses CONFIRM=yes)
endif
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U efuse:w:$(EFUSE):m -U hfuse:w:$(HFUSE):m
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U lfuse:w:$(LFUSE):m

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
