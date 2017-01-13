include ../include/Makefile.inc

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

%.o: %.S
	$(CC) $(CFLAGS) $? -o $@

%.lo: %.o
	ld $(LDFLAGS) -T$(basename $?).lds -Map $(basename $?).map $(basename $?).o -o $(basename $?).lo

%.bin: %.lo
	objcopy $(OCFLAGS) -O binary $^ $@

clean:
	-$(RM) fd.img *.o *.lo *.map *.bin