CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -lm #-lXrandr

all: car

car: car.cpp log.cpp aliA.cpp mohanadA.cpp hussainJ.cpp
	g++ $(CFLAGS) car.cpp log.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -o car

clean:
	rm -f car
	rm -f *.o

