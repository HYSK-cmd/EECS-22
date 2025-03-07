#Makefile: PhotoLab

all: PhotoLab PhotoLabTest
        
clean:
    rm -f *.o
    rm -f PhotoLab
    rm -f PhotoLabTest
    rm -f libFilter.a

# compilation rules
FileIO.o: Constants.h FileIO.c FileIO.h
    gcc -c FileIO.c -o FileIO.o -Wall -std=c11

DIPs.o: Constants.h DIPs.h DIPs.c
    gcc -c DIPs.c -o DIPs.o -Wall -std=c11

Advanced.o: Constants.h Advanced.h Advanced.c
    gcc -c Advanced.c -o Advanced.o -Wall -std=c11

PhotoLab.o: Constants.h FileIO.h DIPs.h Advanced.h 
    gcc -c PhotoLab.c -o PhotoLab.o -Wall -std=c11

PhotoLabTest.o: Constants.h FileIO.h DIPs.h Advanced.h PhotoLab.c
    gcc -c PhotoLab.c -o PhotoLabTest.o -Wall -std=c11 -DDEBUG

PhotoLab: PhotoLab.o FileIO.o libFilter.a
    gcc PhotoLab.o FileIO.o -L. -lFilter -lm -o PhotoLab

PhotoLabTest: PhotoLabTest.o FileIO.o libFilter.a
    gcc PhotoLabTest.o FileIO.o -L. -lFilter -lm -o PhotoLabTest

libFilter.a: DIPs.o Advanced.o  
    ar rc libFilter.a DIPs.o Advanced.o
    ranlib libFilter.a

run: PhotoLab
    ./PhotoLab

run-test: PhotoLabTest
    ./PhotoLabTest