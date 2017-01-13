TOOLS = ../../Tools/
QEMU = ../../qemu/
QEMUMACHINE = qemu-system-i386w
CC = gcc
RM = rm

.PHONY: run
run: fd.img
	$(QEMU)$(QEMUMACHINE) -fda fd.img

fd.img: boot.S
	$(CC) -c boot.S
	ld -s -Tboot.lds -Map boot.map boot.o -o boot.lo
	objcopy -R .note -R .comment -S -O binary boot.lo fd.img

clean:
	-$(RM) fd.img *.o *.lo *.map