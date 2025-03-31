#Makefile: MovieLab
#Name: Hoon Yang
# Variables
CC 		= gcc
DEBUG 	= -g -DDEBUG
CFLAGS	= -Wall -std=c11 -g -c
LFLAGS  = -g
LDFLAGS = -lm

OBJFILES = MovieLab.o FileIO.o Image.o ImageList.o Movie.o DIPs.o

# Default target
all: MovieLab

test: all
	valgrind ./MovieLab
# Target for clean-up
clean:
	rm -f *.o
	rm -f MovieLab
	rm -f out.yuv

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: Movie.h Constants.h FileIO.h Image.h DIPs.h MovieLab.c
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o
# Target for FileIO.o
FileIO.o: Constants.h Image.h FileIO.h FileIO.c
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
# Target for DIPs.o
DIPs.o: Constants.h Image.h DIPs.h DIPs.c
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
# Target for Image.o
Image.o: Constants.h Image.h Image.c
	$(CC) $(CFLAGS) Image.c -o Image.o
# Target for ImageList.o
ImageList.o: Constants.h Image.h ImageList.h ImageList.c
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o
# Target for Movie.o
Movie.o: Movie.h Constants.h ImageList.h Movie.c
	$(CC) $(CFLAGS) Movie.c -o Movie.o

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: $(OBJFILES)
	$(CC) $(LFLAGS) $(LDFLAGS) $(OBJFILES) -o MovieLab

run: MovieLab
	./MovieLab

