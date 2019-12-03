ARCH := i686
BUILD_DIR = $(TO_ROOT)/build
CC := $(ARCH)-elf-g++

CFLAGS ?= -O0 -g
# 没有运行时支持，所以-fno-rtti、-fno-exceptions
CFLAGS += -std=gnu++14 -ffreestanding -fno-exceptions -Wall -Wextra -fno-rtti
CFLAGS += -I $(TO_ROOT)/include
LDFLAGS ?= -T $(TO_ROOT)/src/linker.ld -ffreestanding -nostdlib
LIBS ?= -lgcc

MKRESCUE ?= grub-mkrescue

ISO ?= INLOW.iso
