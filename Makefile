all: rowind

CC = gcc
CFLAGS = -Wall -fPIC
DEPS = librowind.h
OBJ = librowind.o rowind_client.o
PREFIX = /usr/local

VERSION = 1.0

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

rowind: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

librowind.so.$(VERSION): librowind.o
	gcc -shared -Wl,-soname,librowind.so.1 \
		-o $@ librowind.o -lc

clean:
	rm *.o rowind

install: rowind librowind.so.1.0 librowind.h
	install -m 0755 rowind $(PREFIX)/bin
	install -m 0755 librowind.so.1.0 $(PREFIX)/lib
	install -m 0644 librowind.h $(PREFIX)/include
	ln -sf $(PREFIX)/lib/librowind.so.1 $(PREFIX)/lib/librowind.so
	ldconfig -v -n $(PREFIX)/lib
