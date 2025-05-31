CFLAGS?=-O3
.PHONY: all
all: od hexdump
hexdump:
od:

RM?=rm -f
.PHONY: clean
clean:
	$(RM) hexdump od core *.o *~
