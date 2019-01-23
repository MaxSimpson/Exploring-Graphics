CXX = g++ -std=c++14
OPT = -O3

OBJS = main.o Model.o Scene.o Camera.o Light.o WorldModel.o

LIBS = -lGL -lGLU -lglut

default: engine

engine: $(OBJS)
	$(CXX) $(OPT) $(OBJS) $(LIBS) -o engine

%.o: %.cpp
	$(CXX) $(OPT) -c $< -o $@

clean:
	rm -f $(OBJS) engine
