CFLAGS  = -g -Wall -pedantic
CC  = gcc

all: \
	myfind_methods \
	myfind \

myfind_methods: myfind_methods.h myfind_methods.o
	$(CC) -c $(CFLAGS) $@.c -o $@

myfind: myfind_methods.o myfind.o myfind_methods.h
	$(CC) $(CFLAGS) $@.c -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f myfind_methods
	rm -f myfind
	rm -f *.o
	rm -f *.out
	rm -f *.err
	rm -rf *.dSYM
