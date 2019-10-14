ARCH := i686
BUILD_DIR = $(TO_ROOT)/build
GCC := $(ARCH)-elf-gcc

CFLAGS ?= -O0 -g
CFLAGS += -std=gnu99 -ffreestanding -fno-exceptions -Wall -Wextra
LDFLAGS ?= -T $(TO_ROOT)/src/linker.ld -ffreestanding -nostdlib
LIBS ?= -lgcc

MKRESCUE ?= grub-mkrescue

ISO ?= INLOW.iso
