TOOLS = ../../Tools/
QEMU = ../../qemu/

QEMUMACHINE = qemu-system-i386w

CC = gcc

CFLAGS = -c -fno-builtin
LDFLAGS = -nostdlib -nostartfiles -nodefaultlibs
OCFLAGS = -R .note -R .comment

RM = rm
RN = mv