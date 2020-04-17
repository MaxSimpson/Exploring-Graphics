################################################################################
## GCC
################################################################################
CXX = g++ -std=c++17
#OPT = -O0 -ggdb # Debug mode
OPT = -O3

################################################################################
# Open gl
################################################################################
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
LIBS = -lstdc++fs $(GL_LIBS) $(QT_LIBS)

OBJS = \
			 Camera.o \
			 Collider.o \
			 CompileShaders.o \
			 BoxCollider.o \
			 GLUtility.o \
			 Image.o \
			 Light.o \
			 Material.o \
			 MatManager.o \
			 Model.o \
			 Prefab.o \
			 Scene.o \
			 SphereCollider.o \
			 WorldModel.o \
			 main.o

DEPS = ${OBJS:%.o=%.d}

APP = engine

default: $(APP)

$(APP): $(OBJS)
	@echo Linking $@
	@$(CXX) $(OPT) $(OBJS) $(LIBS) -o $@

%.o: %.cpp
	@echo Compiling $<
	@$(CXX) $(OPT) $(DEFS) $(INCL) -MMD -c $< -o $@

clean:
	@echo Cleaning objects, dependencies, and application
	@rm -f $(OBJS) $(DEPS) $(APP)

-include ${DEPS}
