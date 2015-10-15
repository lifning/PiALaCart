.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
    $(error "Please set DEVKITARM in your environment.")
endif

include $(DEVKITARM)/ds_rules

export TARGET := $(shell basename $(CURDIR))
export TOPDIR := $(CURDIR)

.PHONY: arm7/$(TARGET).elf arm9/$(TARGET).elf

# main targets
all: check-format $(TARGET).nds

check-format:
	# TODO: clang-format verifier

$(TARGET).nds: arm7/$(TARGET).elf arm9/$(TARGET).elf
	ndstool -c $(TARGET).nds -7 arm7/$(TARGET).elf -9 arm9/$(TARGET).elf

arm7/$(TARGET).elf:
	$(MAKE) -C arm7

arm9/$(TARGET).elf:
	$(MAKE) -C arm9

clean:
	$(MAKE) -C arm9 clean
	$(MAKE) -C arm7 clean
	rm -f $(TARGET).nds $(TARGET).arm7 $(TARGET).arm9
