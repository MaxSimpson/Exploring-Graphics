################################################################################
## GCC
################################################################################
CXX = g++ -std=c++14
#OPT = -O0 -ggdb # Debug mode
OPT = -O3

################################################################################
# Open gl
################################################################################
#DEFS += -DGL_WITHOUT_SHADERS
GL_DEFS += -DGL_WITH_SHADERS
GL_LIBS = -lGL -lGLU -lglut

################################################################################
# Qt
################################################################################
QT_DIR = /usr/include/x86_64-linux-gnu/qt5
QT_DEFS = -fPIC
QT_INCL = -I$(QT_DIR)
QT_LIBS = -lQt5Core -lQt5Gui -lQt5OpenGL

################################################################################
## Rules
################################################################################
DEFS = $(GL_DEFS) $(QT_DEFS)
INCL = $(QT_INCL)
LIBS = $(GL_LIBS) $(QT_LIBS)

OBJS = \
			 Camera.o \
			 CompileShaders.o \
			 GLUtility.o \
			 Image.o \
			 Light.o \
			 Material.o \
			 Model.o \
			 Scene.o \
			 WorldModel.o \
			 main.o

default: engine

engine: $(OBJS)
	$(CXX) $(OPT) $(DEFS) $(OBJS) $(LIBS) -o engine

%.o: %.cpp
	$(CXX) $(OPT) $(DEFS) $(INCL) -MMD -c $< -o $@
	cat $*.d >> Dependencies
	rm -f $*.d

clean:
	rm -f Dependencies $(OBJS) engine

-include Dependencies
