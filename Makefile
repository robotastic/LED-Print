CC=gcc
CFLAGS=-I.
DEPS=serprt.h helper.h
OBJ=loop.o serprt.o helper.o scroll.o print.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	gcc -o LEDLoop loop.o serprt.o helper.o  $(CFLAGS)
	gcc -o LEDScroll scroll.o serprt.o helper.o  $(CFLAGS)
	gcc -o LEDPrint print.o serprt.o helper.o  $(CFLAGS)
