all: rowind

CC = gcc
CFLAGS = -Wall
DEPS = librowind.h
OBJ = librowind.o rowind_client.o
PREFIX = /usr/local

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

rowind: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm *.o rowind

install: rowind
	install -m 0755 rowind $(PREFIX)/bin
