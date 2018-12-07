CXX = g++ -std=c++14
OPT = -03

OBJS = main.o

default: main.o

main.o: main.cpp
	$(CXX) $(OPT) $< -o $@

clean:
	rm -f main.o
