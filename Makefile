CC=gcc
LD=gcc
CFLAGS=-ggdb -std=c99 -Wall
LIBS= -lm

testArraysStrings: testArraysStrings.o arraysStrings.o vectors.o
	$(LD) -o testArraysStrings testArraysStrings.o arraysStrings.o vectors.o $(LIBS)
	
vectors.o: vectors.h vectors.c
	$(CC) $(FLAGS) -c vectors.c -o vectors.o
	
arraysStrings.o: arraysStrings.h arraysStrings.c
	$(CC) $(FLAGS) -c arraysStrings.c -o arraysStrings.o
	

testArraysStrings.o: testArraysStrings.c
	$(CC) $(FLAGS) -c testArraysStrings.c -o testArraysStrings.o

clean:
	rm *.o
	rm testArraysStrings
