CXX = g++ -std=c++14
OPT = -O3
DEF = -DGL_WITH_SHADERS
#DEF = -DGL_WITHOUT_SHADERS

OBJS = main.o Model.o Scene.o Camera.o Light.o WorldModel.o CompileShaders.o

LIBS = -lGL -lGLU -lglut

default: engine

engine: $(OBJS)
	$(CXX) $(OPT) $(DEF) $(OBJS) $(LIBS) -o engine

%.o: %.cpp
	$(CXX) $(OPT) $(DEF) -MMD -c $< -o $@
	cat $*.d >> Dependencies
	rm -f $*.d

clean:
	rm -f Dependencies $(OBJS) engine

-include Dependencies
