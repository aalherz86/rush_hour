CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr
CPPFLAGS = rush_hour.cpp log.cpp timers.cpp aliA.cpp mohanadA.cpp hussainJ.cpp Image.cpp

all: rush_hour

rush_hour: $(CPPFLAGS)
	g++ $(CFLAGS) $(CPPFLAGS) libggfonts.a -Wall -Wextra $(LFLAGS) -orush_hour

clean:
	rm -f rush_hour
	rm -f *.o

