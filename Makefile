CFLAGS?=-O3
.PHONY: all
all: hexdump
hexdump:

RM?=rm -f
.PHONY: clean
clean:
	$(RM) hexdump core *.o *~
