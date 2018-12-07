CXX = g++ -std=c++14
OPT = -O3

OBJS = main.o
LIBS = -lGL -lGLU -lglut

default: main.o

main.o: main.cpp
	$(CXX) $(OPT) $< $(LIBS) -o $@

clean:
	rm -f main.o
