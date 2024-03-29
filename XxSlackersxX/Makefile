TARGET = MP
OBJECTS = Main.o Material.o Light.o Point.o Character.o Camera.o ARCamera.o CubicBezierCurve.o BezierPatch.o BezierCurve.o Tree.o

CXX    = g++
CFLAGS = -Wall -g 

#############################
## SETUP GLUI
##      We must link against
##  GLUI before we link against
##  GLUT.
##
##     If you want to build
##  on your own machine, you
##  need to change the
##  appropriate paths.
#############################

# Windows Lab builds 
ifeq ($(OS), Windows_NT)
	INCPATH += -IC:/CSCI441GFx/include/
	LIBPATH += -LC:/CSCI441GFx/lib/

# Non-Windows build
else
	INCPATH += -I/Users/jpaone/Desktop/include/
	LIBPATH += -L/Users/jpaone/Desktop/lib
endif

LIBS += -lglui

#############################
## SETUP OpenGL & GLUT 
#############################

# Windows builds 
ifeq ($(OS), Windows_NT)
	INCPATH += -IC:/Strawberry/c/include/
	LIBS += -lglut -lopengl32 -lglu32 -LC:/Strawberry/c/lib/

# Mac builds
else ifeq ($(shell uname), Darwin)
	LIBS += -framework GLUT -framework OpenGL

# Linux and all other builds
else
	LIBS += -lglut -lGL -lGLU
endif

#############################
## COMPILATION INSTRUCTIONS 
#############################

all: $(TARGET)

clean:
	rm -f *o $(TARGET)

depend:
	rm -f Makefile.bak
	mv Makefile Makefile.bak
	sed '/^# DEPENDENCIES/,$$d' Makefile.bak > Makefile
	echo '# DEPENDENCIES' >> Makefile
	$(CXX) $(INCPATH) -MM *.cpp >> Makefile

.c.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cc.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cpp.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

$(TARGET): $(OBJECTS) 
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $^ $(LIBPATH) $(LIBS)

# DEPENDENCIES
Main.o: Main.cpp
Material.o: Material.cpp Material.h
Point.o: Point.cpp Point.h
Character.o: Character.cpp Character.h
Camera.o: Camera.cpp Camera.h
ARCamera.o: ARCamera.cpp ARCamera.h
Light.o: Light.cpp Light.h
CubicBezierCurve.o: CubicBezierCurve.cpp CubicBezierCurve.h
BezierPatch.o: BezierPatch.cpp BezierPatch.h
BezierCurve.o: BezierCurve.cpp BezierCurve.h
Tree.o: Tree.cpp Tree.h
