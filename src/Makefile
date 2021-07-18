C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
      -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Iinclude
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel

kernel: $(C_OBJECTS) $(S_OBJECTS)
	ld $(LDFLAGS) $(S_OBJECTS) $(C_OBJECTS)  -o kernel

os.iso: kernel
	cp kernel iso/boot/kernel
	genisoimage -R                      \
		-b boot/grub/stage2_eltorito    \
		-no-emul-boot                   \
		-boot-load-size 4               \
		-A os                           \
		-input-charset utf8             \
		-quiet                          \
		-boot-info-table                \
		-o os.iso                       \
		iso

run: os.iso
	qemu-system-i386 -boot d -cdrom os.iso -m 512 -vnc :0

clean:
	rm -rf $(C_OBJECTS) $(S_OBJECTS) kernel os.iso