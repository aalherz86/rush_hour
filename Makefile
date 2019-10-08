CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -lm #-lXrandr

# COMMENT: "-lssl -lcrypto" were added to our Makefile 

all: car

car: car.cpp log.cpp aliA.cpp mohanadA.cpp hussainJ.cpp
	g++ $(CFLAGS) car.cpp log.cpp  aliA.cpp mohanadA.cpp hussainJ.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -lssl -lcrypto -o car

clean:
	rm -f car
	rm -f *.o

