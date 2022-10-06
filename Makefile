#
#             LUFA Library
#     Copyright (C) Dean Camera, 2019.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

MCU          = atmega32u4
ARCH         = AVR8
BOARD        = BOARD_USER
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = BootloaderDFU
SRC          = $(TARGET).c Descriptors.c LEDs.cpp BootloaderAPI.c BootloaderAPITable.S $(LUFA_SRC_USB)
CC_FLAGS     = -Wfatal-errors -DUSE_LUFA_CONFIG_HEADER -UAVR -IConfig -IAVR++ -DBOOT_START_ADDR=$(BOOT_START_OFFSET)
C_STANDARD   = gnu11
CPP_STANDARD = gnu++14

LD_FLAGS     = -Wl,--section-start=.text=$(BOOT_START_OFFSET) $(BOOT_API_LD_FLAGS)
# LTO          = Y

AVRDUDE_PROGRAMMER = usbtiny

AVRDUDE_FLAGS = -B.1 -D

LUFA_PATH    = LUFA/LUFA

-include local.$(shell hostname).mk

# Flash size and bootloader section sizes of the target, in KB. These must
# match the target's total FLASH size and the bootloader size set in the
# device's fuses.
FLASH_SIZE_KB         = 32
BOOT_SECTION_SIZE_KB  = 4

# Bootloader address calculation formulas
# Do not modify these macros, but rather modify the dependent values above.
CALC_ADDRESS_IN_HEX   = $(shell printf "0x%X" $$(( $(1) )) )
BOOT_START_OFFSET     = $(call CALC_ADDRESS_IN_HEX, ($(FLASH_SIZE_KB) - $(BOOT_SECTION_SIZE_KB)) * 1024 )
BOOT_SEC_OFFSET       = $(call CALC_ADDRESS_IN_HEX, ($(FLASH_SIZE_KB) * 1024) - ($(strip $(1))) )

# Bootloader linker section flags for relocating the API table sections to
# known FLASH addresses - these should not normally be user-edited.
BOOT_SECTION_LD_FLAG  = -Wl,--section-start=$(strip $(1))=$(call BOOT_SEC_OFFSET, $(3)) -Wl,--undefined=$(strip $(2))
# BOOT_API_LD_FLAGS     = $(call BOOT_SECTION_LD_FLAG, .apitable_trampolines, BootloaderAPI_Trampolines, 96)
# BOOT_API_LD_FLAGS    += $(call BOOT_SECTION_LD_FLAG, .apitable_jumptable,   BootloaderAPI_JumpTable,   32)
# BOOT_API_LD_FLAGS    += $(call BOOT_SECTION_LD_FLAG, .apitable_signatures,  BootloaderAPI_Signatures,  8)

# Default target
default: chip-reset avrdude

asm:
	"C:/Program Files/avr-gcc-11.1.0-x64-windows/bin/"avr-gcc -S -pipe -gdwarf-2 -g2 -mmcu=atmega32u4 -fshort-enums -fno-inline-small-functions -Wall -fno-strict-aliasing -funsigned-char -funsigned-bitfields -ffunction-sections -I. -DARCH=ARCH_AVR8 -DF_CPU=16000000UL -mrelax -fno-jump-tables -x c++ -Os -std=gnu++14 -fno-exceptions -fno-threadsafe-statics -Wfatal-errors -DUSE_LUFA_CONFIG_HEADER -UAVR -IConfig -IAVR++ -DBOOT_START_ADDR=0x7000 -I. -ILUFA/LUFA/.. -DARCH=ARCH_AVR8 -DBOARD=BOARD_BOARD_USER -DF_USB=$(F_CPU) -MMD -MP -MF obj/LEDs.d LEDs.cpp -o obj/LEDs.S
	
chip-reset:
	avrdude -c usbtiny -p m32u4 -B100 -e
	avrdude -c usbtiny -p m32u4 -B100 -U lfuse:w:0xCE:m	-U hfuse:w:0xD0:m	-U efuse:w:0xFB:m

version:
	@echo -n "GCC Ver	"avr-gcc" "
	avr-gcc --version | head -n 1
	@echo -n "GXX Ver	"avr-g++" "
	avr-g++ --version | head -n 1

.PHONY: defualt asm chip-reset version bootloader-assembly

bootloader-assembly: obj/BootloaderDFU.s

obj/BootloaderDFU.s: BootloaderDFU.c
	"C:\Program Files\avr-gcc\avr8-gnu-toolchain-win32_x86\bin/"avr-gcc -S -pipe -gdwarf-2 -g2 -mmcu=atmega32u4 -fshort-enums -fno-inline-small-functions -Wall -fno-strict-aliasing -funsigned-char -funsigned-bitfields -ffunction-sections -I. -DARCH=ARCH_AVR8 -DF_CPU=16000000UL -mrelax -fno-jump-tables -x c -Os -std=gnu11 -Wstrict-prototypes -Wfatal-errors -DUSE_LUFA_CONFIG_HEADER -UAVR -IConfig -IAVR++ -DBOOT_START_ADDR=0x7000 -I. -ILUFA/LUFA/.. -DARCH=ARCH_AVR8 -DBOARD=BOARD_BOARD_USER -DF_USB=16000000UL BootloaderDFU.c -o obj/BootloaderDFU.s

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk
