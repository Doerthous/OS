include ../include/Makefile.inc
OBJS = cstart.o ../lib/spio.o ../lib/spstring.o ../lib/spsnprintf.o \
		../lib/spgdt.o ../lib/spidt.o
CFLAGS += -I../include/
.PHONY: run
run: LDFLAGS += -s
run: OCFLAGS += -S
run: fd.img
	$(QEMU)qemu-system-i386w -fda fd.img

.PHONY: debug
debug: CFLAGS += -g
debug: fd.img
	-start $(GDB)
	$(QEMU)$(QEMUMACHINE) -S -gdb tcp::1234,nowait,nodelay,server,ipv4 -m 16 -boot order=a -vga std -fda fd.img	

fd.img: boot.bin loader.bin kernel.bin
	$(RN) $< fd.img
	$(TOOLS)imgcpy loader.bin fd.img=A:\loader.bin
	$(TOOLS)imgcpy kernel.bin fd.img=A:\kernel.bin

%.bin: %.lo
	objcopy $(OCFLAGS) -O binary $^ $@

kernel.lo: kernel.o $(OBJS)
	ld $(LDFLAGS) -Tkernel.lds -Map kernel.map kernel.o $(OBJS) -o kernel.lo
%.lo: %.o
	ld $(LDFLAGS) -T$(basename $?).lds -Map $(basename $?).map $(basename $?).o -o $(basename $?).lo
	
%.o: %.S
	$(CC) $(CFLAGS) $? -o $@
%.o: %.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	-$(RM) fd.img $(OBJS) *.o *.lo *.map *.bin 
