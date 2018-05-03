all: create
OBJ = kernel.o terminal.o boot.o inb_outb.o keyboard.o \
      keymap.o gdt.o idt.o pic.o interrupt.o stdio.o \
      stdlib.o string.o math.o getmmap.o
OBJAS = interruptas.o idts.o gdts.o boot.o


CC = i686-elf-gcc
CCAS = i686-elf-as
CFLAGS = -ffreestanding -O2 -Wall


INCLUDEDIR = include/
ARCHDIR = arch/
DRVDIR = drivers/
KRNDIR = kernel/
SHLIBC = sh_libc/
SHLIBCINC = sh_libc/include/
MEMDIR = memory/


interruptas.o: $(KRNDIR)interrupt.s
	$(CCAS) $< -o interruptas.o

idts.o: $(ARCHDIR)idt.s
	$(CCAS) $< -o idts.o

gdts.o: $(ARCHDIR)gdt.s
	$(CCAS) $< -o gdts.o

boot.o: boot.s
	$(CCAS) $< -o boot.o

interrupt.o: $(KRNDIR)interrupt.c $(INCLUDEDIR)interrupt.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

pic.o: $(ARCHDIR)pic.c $(INCLUDEDIR)pic.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

idt.o: $(ARCHDIR)idt.c $(INCLUDEDIR)idt.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

gdt.o: $(ARCHDIR)gdt.c $(INCLUDEDIR)gdt.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

inb_outb.o: $(INCLUDEDIR)inb_outb.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

keymap.o: $(DRVDIR)keymap.c $(INCLUDEDIR)keyboard.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

keyboard.o: $(DRVDIR)keyboard.c $(INCLUDEDIR)keyboard.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

terminal.o: $(DRVDIR)terminal.c $(INCLUDEDIR)terminal.h $(INCLUDEDIR)vga.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

kernel.o: $(KRNDIR)kernel.c $(INCLUDEDIR)kernel.h $(INCLUDEDIR)multiboot.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

stdio.o: $(SHLIBC)stdio.c $(SHLIBCINC)stdio.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

stdlib.o: $(SHLIBC)stdlib.c $(SHLIBCINC)stdlib.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

string.o: $(SHLIBC)string.c $(SHLIBCINC)string.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

math.o: $(SHLIBC)math.c $(SHLIBCINC)math.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

getmmap.o: $(MEMDIR)getmmap.c $(INCLUDEDIR)getmmap.h
	$(CC) -c $^ -std=gnu99 $(CFLAGS) -Wextra

create: $(OBJAS) $(OBJ)
	$(CC) -T linker.ld -o myos.bin $(CFLAGS) -nostdlib *.o -lgcc
	grub2-file --is-x86-multiboot myos.bin
	\cp -f myos.bin isodir/boot/myos.bin
	grub2-mkrescue -o myos.iso isodir

clean:
	rm -f *.o myos.bin myos.iso $(INCLUDEDIR)*~ ./*~
