all: create
OBJ = kernel.o terminal.o boot.o inb_outb.o keyboard.o \
      keymap.o gdt.o idt.o pic.o interrupt.o
OBJAS = interruptas.o idts.o gdts.o boot.o
CC = i686-elf-gcc
CCAS = i686-elf-as
CFLAGS = -ffreestanding -O2 -Wall
INCLUDEDIR = include/

interruptas.o: interrupt.s
	$(CCAS) $< -o interruptas.o

idts.o: idt.s
	$(CCAS) $< -o idts.o

gdts.o: gdt.s
	$(CCAS) $< -o gdts.o

boot.o: boot.s
	$(CCAS) $< -o boot.o

interrupt.o: interrupt.c $(INCLUDEDIR)interrupt.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

pic.o: pic.c $(INCLUDEDIR)pic.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

idt.o: idt.c $(INCLUDEDIR)idt.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

gdt.o: gdt.c $(INCLUDEDIR)gdt.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

inb_outb.o: $(INCLUDEDIR)inb_outb.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

keymap.o: keymap.c $(INCLUDEDIR)keyboard.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

keyboard.o: keyboard.c $(INCLUDEDIR)keyboard.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

terminal.o: terminal.c $(INCLUDEDIR)terminal.h $(INCLUDEDIR)vga.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

kernel.o: kernel.c $(INCLUDEDIR)kernel.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

create: $(OBJAS) $(OBJ)
	$(CC) -T linker.ld -o myos.bin $(CFLAGS) -nostdlib *.o -lgcc
	grub2-file --is-x86-multiboot myos.bin
	\cp -f myos.bin isodir/boot/myos.bin
	grub2-mkrescue -o myos.iso isodir

clean:
	rm -f *.o myos.bin myos.iso $(INCLUDEDIR)*~ ./*~
