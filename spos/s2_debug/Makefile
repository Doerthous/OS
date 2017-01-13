TOOLS = ../../Tools/
QEMU = ../../qemu/
QEMUMACHINE = qemu-system-i386w
CC = gcc
RM = rm
CFLAGS = -c
LDFLAGS = 
OCFLAGS = -R .note -R .comment

.PHONY: run
run: LDFLAGS += -s
run: OCFLAGS += -S
run: fd.img
	$(QEMU)$(QEMUMACHINE) -fda fd.img

.PHONY: debug
debug: CFLAGS += -g
debug: fd.img
	-start $(GDB)
	$(QEMU)$(QEMUMACHINE) -S -gdb tcp::1234,nowait,nodelay,server,ipv4 -m 16 -boot order=a -vga std -fda fd.img	

fd.img: boot.S
	$(CC) $(CFLAGS) boot.S
	ld $(LDFLAGS) -Tboot.lds -Map boot.map boot.o -o boot.lo
	objcopy $(OCFLAGS) -O binary boot.lo fd.img

clean:
	-$(RM) fd.img *.o *.lo *.map