OBJECTS = loader.o kmain.o io.o monitor.o \
          gdt.o gdt_flush.o idt.o idt_flush.o isr.o \
		  timer.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -Iinclude
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel

kernel: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel

os.iso: kernel
	cp kernel iso/boot/kernel
	genisoimage -R                              \
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
	qemu-system-i386 -boot d -cdrom os.iso -m 512

clean:
	rm -rf *.o kernel os.iso