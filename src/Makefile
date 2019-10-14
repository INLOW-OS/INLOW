TO_ROOT = ..
include $(TO_ROOT)/config/config.mk

BUILD = $(BUILD_DIR)/$(ARCH)

OBJ := kernel/kernel.o
OBJ += arch/i686/loader.o

OBJ := $(addprefix $(BUILD)/, $(OBJ))


all: $(BUILD)/kernel

$(BUILD)/kernel: $(OBJ)
	$(GCC) $(LDFLAGS) -o $(BUILD)/kernel.elf $^ $(LIBS)

$(BUILD)/kernel/%.o: kernel/%.c
	@mkdir -p $(dir $@)
	$(GCC) $(CFLAGS) -c -o $@ $^

$(BUILD)/arch/i686/%.o: arch/i686/%.s
	@mkdir -p $(dir $@)
	$(GCC) $(ASFLAGS) -c -o $@ $^

clean:
	rm -rf $(BUILD)

.PHONY: all clean
