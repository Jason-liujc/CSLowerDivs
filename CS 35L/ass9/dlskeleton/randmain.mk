CC=gcc

all: randlibhw.so, randlibsw.so,randcpuid.o,  randmain


randlibhw.so: randlibhw.c
	$(CC) randlibhw.c -shared -fPIC -o randlibhw.so

randlibsw.so: randlibsw.c
	$(CC) randlibsw.c -shared -fPIC -o randlibsw.so

randcpuid.o: randcpuid.c
	$(CC) -c randcpuid.c

randmain: randcpuid.o
	$(CC) randmain.c randcpuid.o -ldl -Wl,-rpath=$(PWD) -o randmain