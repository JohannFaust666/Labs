CC = gcc
AR = ar rcs
LIBS = -ldl

all: static dynamic main

static: arithmetics.o
	$(AR) libarithmetics.a arithmetics.o

dynamic: arithmetics.o
	$(CC) -shared -o libarithmetics.so arithmetics.o

main: main.c
	$(CC) main.c $(LIBS) -o main

arithmetics.o: arithmetics.c
	$(CC) -c arithmetics.c

clean:
	rm -f *.o *.a *.so main
