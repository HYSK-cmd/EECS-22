#Makefile: PhotoLab

# variable definitions
CC	= gcc
DEBUG	= -g -DDEBUG
CFLAGS	= -Wall -std=c11 -g -c
LFLAGS  = -g
LDFLAGS =  -L. -lFilter -lm

all: PhotoLab PhotoLabTest

clean:
	rm -f *.o
	rm -f PhotoLab
	rm -f PhotoLabTest
	rm -f libFilter.a


# compilation rules
Image.o: Constants.h Image.h Image.c
	$(CC) $(CFLAGS) Image.c -o Image.o

FileIO.o: Constants.h Image.h FileIO.h FileIO.c
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: Constants.h Image.h DIPs.h DIPs.c
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Advanced.o: Constants.h Image.h Advanced.h Advanced.c
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

Test.o : Constants.h FileIO.h DIPs.h Advanced.h Test.h Test.c
	$(CC) $(CFLAGS) Test.c -o Test.o

#main function
PhotoLab.o: Constants.h FileIO.h DIPs.h Advanced.h Test.h Image.h PhotoLab.c
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o

PhotoLabTest.o: Constants.h FileIO.h DIPs.h Advanced.h Test.h Image.h PhotoLab.c
    	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLabTest.o  -DDEBUG

PhotoLab: PhotoLab.o FileIO.o Image.o Test.o libFilter.a
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o Image.o Test.o $(LDFLAGS) -o PhotoLab

PhotoLabTest: PhotoLabTest.o FileIO.o Image.o Test.o libFilter.a
	$(CC) $(LFLAGS) PhotoLabTest.o FileIO.o Image.o Test.o $(LDFLAGS) -o PhotoLabTest


libFilter.a: DIPs.o Advanced.o Test.o 
	ar rc libFilter.a DIPs.o Advanced.o Test.o
	ranlib libFilter.a

run: PhotoLab
	./PhotoLab

run-test: PhotoLabTest
	./PhotoLabTest