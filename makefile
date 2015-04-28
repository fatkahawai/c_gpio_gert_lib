#
# Makefile
#

all : libgertboard.so.1

clean :
	rm *.o *.so *.so.1 *.so.1.0 

libgertboard.so.1 : libgertboard.so
	ln -sf libgertboard.so.1.0 libgertboard.so.1 ;\
	export LD_LIBRARY_PATH=.


libgertboard.so : libgertboard.so.1.0
	ln -sf libgertboard.so.1.0 libgertboard.so

libgertboard.so.1.0 : atod.o gb_spi.o gb_common.o
	gcc -shared -Wl,-soname,libgertboard.so.1 -o libgertboard.so.1.0 atod.o gpio_input.o gb_spi.o gb_common.o

# The next lines generate the various object files

gb_common.o : gb_common.c gb_common.h
	gcc -Wall -fPIC -c gb_common.c 

gb_spi.o : gb_spi.c gb_spi.h
	gcc -Wall -fPIC -c gb_spi.c

atod.o : atod.c atod.h
	gcc -D_DEBUG -Wall -fPIC -c atod.c

gpio_input.o : gpio_input.c gpio_input.h
	gcc -D_DEBUG -Wall -fPIC -c gpio_input.c
