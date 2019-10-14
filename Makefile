TO_ROOT = .
include $(TO_ROOT)/config/config.mk

all: src iso

src:
	$(MAKE) -C src

iso: $(ISO)

$(ISO): $(BUILD_DIR)/$(ARCH)/kernel.elf
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $(BUILD_DIR)/$(ARCH)/kernel.elf iso/boot/kernel.elf
	echo 'set timeout=0'                   >  iso/boot/grub/grub.cfg
	echo 'set default=0'                   >> iso/boot/grub/grub.cfg
	echo ''                                >> iso/boot/grub/grub.cfg
	echo 'menuentry "INLOW" {'             >> iso/boot/grub/grub.cfg
	echo '    multiboot /boot/kernel.elf'  >> iso/boot/grub/grub.cfg
	echo '    boot'                        >> iso/boot/grub/grub.cfg
	echo '}'                               >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(ISO) iso
	rm -rf iso

# 此模式Esc + 2再输入quit退出
qemu-curses: $(ISO)
	qemu-system-i386 -cdrom $^ -curses

install-toolchain:
	$(TO_ROOT)/config/toolchain-install.sh

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(ISO)

.PHONY: all src iso qemu clean
