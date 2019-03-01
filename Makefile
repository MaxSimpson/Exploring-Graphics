CXX = g++ -std=c++14
OPT = -O3

OBJS = main.o Model.o Scene.o Camera.o Light.o WorldModel.o

LIBS = -lGL -lGLU -lglut

default: engine

engine: $(OBJS)
	$(CXX) $(OPT) $(OBJS) $(LIBS) -o engine

%.o: %.cpp
	$(CXX) $(OPT) -MMD -c $< -o $@
	cat $*.d >> Dependencies
	rm -f $*.d

clean:
	rm -f Dependencies $(OBJS) engine

-include Dependencies
