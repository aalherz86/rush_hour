CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: rush_hour

rush_hour: rush_hour.cpp log.cpp timers.cpp aliA.cpp mohanadA.cpp hussainJ.cpp
	g++ $(CFLAGS) rush_hour.cpp log.cpp timers.cpp aliA.cpp mohanadA.cpp hussainJ.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -orush_hour

clean:
	rm -f rush_hour
	rm -f *.o

