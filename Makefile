CC=gcc
CFLAGS=-O -Wall

all: la

la: la.c la.h
	$(CC) $(CFLAGS) -o la la.c -lncurses

clean:
	rm -f la

distclean: clean
