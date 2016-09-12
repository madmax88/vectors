cc=clang
cflags=-Wall -Werror

all: libmax.so example

libmax.so: libmax.o
	$(cc) $(cflags) -shared -fPIC libmax.o -o libmax.so

libmax.o:
	$(cc) $(cflags) -c libmax.c -o libmax.o

example: libmax.so
	$(cc) $(cflags) -L./ example.c -lmax -o example

clean:
	rm -f libmax.o
	rm -f libmax.so
	rm -f example
