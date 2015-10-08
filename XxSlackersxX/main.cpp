/*
 *  CSCI 441, Computer Graphics, Fall 2015
 *
 *
 *  Project: Midterm Assignment - Guild Wars
 *  File: main.cpp
 *
 *	Author: Jack Wesley Nelson, Stephen Unger, Jamie Koning - Fall 2015
 *
 Grading Rubric

 Your submission will be graded according to the following rubric.

 Topic	Percentage	Requirement Description
 B�zier Curves & Surfaces	40%	Track is closed (end point = start point), C0 continuous, & C1 continuous. (This doesn't need to be enforced in-program, as long as input control points specifiy C0 & C1 continuous curves.)

 One Hero moves by arc-length parameterization and moves at a constant speed regardless of control point spacing. The other Hero moves by equal parameter steps.

 Terrain is comprised of B�zier Surfaces. The Wandering Hero can be controlled and moves around the terrain properly.
 3D Drawing & Animation	5%	Heroes are animated & comprised of GLUT primitives / GLU quadrics. Scene is comprised of track and other scenic objects.
 Cameras, Menus, Text, & Viewports	20%	Arcball camera follows Hero and rotates correctly; user can control rotation. Free camera is correctly implemented, can move around the scene, and is user-controllable. Camera is set up in Camera.h file. Camera from Hero's point of view works correctly; it is attached to the Hero and looks along the Hero's direction of movement.

 First-person camera view is placed in a separate viewport. User can toggle between cameras through use of a menu attached to the right mouse button. User can toggle between Heroes to follow through menu as well.

 Frames Per Second are rendered to screen. Hero name is displayed above Hero.
 Lights & Materials	15%	Two different lights used along with two different materials. Used as described above with one light being dynamic in nature. Lights are defined in a Light.h file and Materials are defined in a Material.h file.
 File I/O	5%	File format is documented in the README.txt file. A third-party should be able to write a World Scene in your format based on your documentation. File format supports two different types of objects that can be placed in the scene and objects are correctly placed and rendered in the scene. Two non-trivially different example files are included. Each example fully utilizes the file format (i.e. places objects of each type).
 Submission, Presentation, & Guild Reflection	15%	Submission includes source code, Makefile, and README.txt.
 Source code is well documented. Webpage named <HeroName>.html submitted and updated with screenshot from latest assignment. Submission compiles and executes in the lab machine environment. Presentation is of high quality and equal division of work is reported by team members.
 */

// HEADERS /////////////////////////////////////////////////////////////////////

// OpenGL / GLUT Libraries we need
#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <GL/glui.h>			// include our GLUI header


// C Libraries we need
#include <time.h>			// for time() to seed our RNG
#include <stdio.h>			// allow to print to terminal
#include <stdlib.h>			// access to rand() and exit()
#include <math.h>			// for cosf(), sinf(), etc.


// C++ Libraries we'll use
#include <fstream>			// we'll use ifstream	
#include <string>			// for, well strings!
#include <vector>			// and vectors (the storage container, not directional)
using namespace std;


// Headers We've Written
#include "Point.h"
#include "Camera.h"
// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth = 640;
static size_t windowHeight = 480;
static float aspectRatio;

GLint leftMouseButton, rightMouseButton;    // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse

GLint menuId;				    // handle for our menu

vector<Point> controlPoints;
float trackPointVal = 0.0f;
Camera camera;

// getRand() ///////////////////////////////////////////////////////////////////
//
//  Simple helper function to return a random number between 0.0f and 1.0f.
//
////////////////////////////////////////////////////////////////////////////////
float getRand() {
    return rand() / (float)RAND_MAX;
}

// drawGrid() //////////////////////////////////////////////////////////////////
//
//  Function to draw a grid in the XZ-Plane using OpenGL 2D Primitives (GL_LINES)
//
////////////////////////////////////////////////////////////////////////////////
void drawGrid() {
	/*
	*	We will get to why we need to do this when we talk about lighting,
	*	but for now whenever we want to draw something with an OpenGL
	*	Primitive - like a line, quad, point - we need to disable lighting
	*	and then reenable it for use with the GLUT 3D Primitives.
	*/
	glDisable(GL_LIGHTING);
	//Set primitive to lines
	glBegin(GL_LINES);
	//set color to white
	glColor3f(1, 1, 1);
	//iterate from -50 to 50 drawing lines across the grid in the xz-plane
	for (int i = -50; i < 50; i++) {
		//first line this iteration
		glVertex3f((float)i, 0, (float)-50);
		glVertex3f((float)i, 0, (float)50);
		//second line this iteration
		glVertex3f((float)-50, 0, (float)i);
		glVertex3f((float)50, 0, (float)i);
	}
	//end glBegin(GL_Lines);
	glEnd();
	/*
	*	As noted above, we are done drawing with OpenGL Primitives, so we
	*	must turn lighting back on.
	*/
	glEnable(GL_LIGHTING);
}

// resizeWindow() //////////////////////////////////////////////////////////////
//
//  GLUT callback for window resizing. Resets GL_PROJECTION matrix and viewport.
//
////////////////////////////////////////////////////////////////////////////////
void resizeWindow(int w, int h) {
    aspectRatio = w / (float)h;

    windowWidth = w;
    windowHeight = h;

    //update the viewport to fill the window
    glViewport(0, 0, w, h);

    //update the projection matrix with the new window properties
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100000);
}



// mouseCallback() /////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse clicks. We save the state of the mouse button
//      when this is called so that we can check the status of the mouse
//      buttons inside the motion callback (whether they are up or down).
//
////////////////////////////////////////////////////////////////////////////////
void mouseCallback(int button, int state, int thisX, int thisY) {
    //update the left and right mouse button states, if applicable
    if(button == GLUT_LEFT_BUTTON)
        leftMouseButton = state;
    
    //and update the last seen X and Y coordinates of the mouse
    mouseX = thisX;
    mouseY = thisY;
}

// mouseMotion() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse movement. We update cameraPhi, cameraTheta, and/or
//      cameraRadius based on how much the user has moved the mouse in the
//      X or Y directions (in screen space) and whether they have held down
//      the left or right mouse buttons. If the user hasn't held down any
//      buttons, the function just updates the last seen mouse X and Y coords.
//
////////////////////////////////////////////////////////////////////////////////
void mouseMotion(int x, int y) {
    if(leftMouseButton == GLUT_DOWN) {
		camera.updateCameraRotation(x - mouseX, mouseY - y);
        camera.recomputeOrientation();     //update camera (x,y,z) based on (radius,theta,phi)
    }

    mouseX = x;
    mouseY = y;
}



// initScene() /////////////////////////////////////////////////////////////////
//
//  A basic scene initialization function; should be called once after the
//      OpenGL context has been created. Doesn't need to be called further.
//
////////////////////////////////////////////////////////////////////////////////
void initScene()  {
    glEnable(GL_DEPTH_TEST);

    //******************************************************************
    // this is some code to enable a default light for the scene;
    // feel free to play around with this, but we won't talk about
    // lighting in OpenGL for another couple of weeks yet.
    float lightCol[4] = { 1, 1, 1, 1};
    float ambientCol[4] = { 0.0, 0.0, 0.0, 1.0 };
    float lPosition[4] = { 10, 10, 10, 1 };
    glLightfv( GL_LIGHT0, GL_POSITION,lPosition );
    glLightfv( GL_LIGHT0, GL_DIFFUSE,lightCol );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
	
    // tell OpenGL not to use the material system; just use whatever we 
    // pass with glColor*()
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    //******************************************************************

    glShadeModel(GL_FLAT);

    srand( time(NULL) );	// seed our random number generator

    // give the camera a scenic starting point.
	camera = Camera(6, 4, 3);
	camera.setTheta(-M_PI / 3.0f);
	camera.setPhi(M_PI / 2.8f);
	camera.recomputeOrientation();
}

// renderScene() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for scene rendering. Sets up the modelview matrix, renders
//      a scene to the back buffer, and switches the back buffer with the
//      front buffer (what the user sees).
//
////////////////////////////////////////////////////////////////////////////////
void renderScene(void) {
	// clear the render buffer
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// update the modelview matrix based on the camera's position
	glMatrixMode(GL_MODELVIEW);                           // make sure we aren't changing the projection matrix!
	glLoadIdentity();
	camera.lookAt();

	drawGrid();

	//push the back buffer to the screen
    glutSwapBuffers();
}


// normalKeysDown() ////////////////////////////////////////////////////////////
//
//  GLUT keyboard callback; gets called when the user presses a key.
//
////////////////////////////////////////////////////////////////////////////////
void normalKeysDown(unsigned char key, int x, int y) {

	//if q key is pressed
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}
	//if a key is pressed
	if (key == 'a' || key == 'A' || key == 65 || key == 97) {
	}
	//if s key is pressed
	if (key == 's' || key == 'S' || key == 83 || key == 115) {
		//move the camera forward 
		camera.moveBackward();
	}
	//if d key is pressed
	if (key == 'd' || key == 'D' || key == 68 || key == 100) {
	}
	//if w key is pressed
	if (key == 'w' || key == 'W' || key == 87 || key == 119) {
		//move the camera forward 
		camera.moveForward();
	}

}

// myTimer() ////////////////////////////////////////////////////////////////////
//
//  GLUT timer callback; gets called when a timer expires
//
////////////////////////////////////////////////////////////////////////////////
void myTimer( int value ) {
    // redraw our display
    glutPostRedisplay();
    // register a new timer callback
    glutTimerFunc( 1000.0f / 60.0f, myTimer, 0 );
}

// myMenu() /////////////////////////////////////////////////////////////////////
//
//  Handles our Menu events
//
////////////////////////////////////////////////////////////////////////////////
void myMenu( int value ) {
	// TODO #02: handle our menu options
	if (value == 0) {
		exit(0);
	}
}

// createMenus() ///////////////////////////////////////////////////////////////
//
//  Handles creating a menu, adding menu entries, and attaching the menu to
//  a mouse button
//
////////////////////////////////////////////////////////////////////////////////
void createMenus() {
	// TODO #01: Create a Simple Menu
	menuId = glutCreateMenu(myMenu);
	glutAddMenuEntry("Quit", 0);
	glutAddMenuEntry("Display/Hide Control Cage", 1);
	glutAddMenuEntry("Display/Hide Bezier Curve", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// registerCallbacks() /////////////////////////////////////////////////////////
//
//  Register all of our callbacks for GLUT.
//
////////////////////////////////////////////////////////////////////////////////
void registerCallbacks() {
    // keyboard callbacks
    glutSetKeyRepeat(   GLUT_KEY_REPEAT_ON );
    glutKeyboardFunc(   normalKeysDown     );

    // mouse callbacks
    glutMouseFunc(      mouseCallback      );
    glutMotionFunc(     mouseMotion        );

    // display callbacks
    glutDisplayFunc(    renderScene        );
    glutReshapeFunc(    resizeWindow       );

    // timer callback
    glutTimerFunc( 1000.0f / 60.0f, myTimer, 0 );
}

// loadControlPoints() /////////////////////////////////////////////////////////
//
//  Load our control points from file and store them in a global variable.
//
////////////////////////////////////////////////////////////////////////////////
bool loadControlPoints( char* filename ) {
	// TODO #04: read in control points from file.  Make sure the file can be
	// opened and handle it appropriately.
	//start the file stream
	fstream file;
	//open the points file
	file.open(filename);
	//make a string to store each line
	string currentLine;
	//check that the file is open
	if (file.is_open()) {
		//get the first line
		if (getline(file, currentLine)) {
			//this line will be the number of points in the file, but we don't need it.
		}
		//get the rest of the lines
		while (getline(file, currentLine)) {
			string first, second, third;
			//get the coordinates
			//first
			int length = currentLine.find(',', 0);
			first = currentLine.substr(0, length);
			currentLine.erase(0, length + 1);
			//second
			length = currentLine.find(',', 0);
			second = currentLine.substr(0, length);
			currentLine.erase(0, length + 1);
			//third
			third = currentLine;
			currentLine = "";
			//push a Point to the vector, converting each string to a float.
			controlPoints.push_back(Point(atof(first.c_str()), atof(second.c_str()), atof(third.c_str())));
		}
		//close the file
		file.close();
	}
	//the file wasn't opened, print an error message.
	else {
		fprintf(stdout, "Unable to open file.");
	}
	return true;
}

// main() //////////////////////////////////////////////////////////////////////
//
//  Program entry point. Takes a single command line argument for our 
//    control points file.
//
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv ) {

    // TODO #03: make sure a control point CSV file was passed in.  Then read the points from file
	//make sure on argument was passed in.
	if (argc == 2) {
		loadControlPoints(argv[1]);
	}
	else {
		fprintf(stdout, "Please provide a csv file.\n");
		exit(-1);
	}
    // create a double-buffered GLUT window at (50, 50) with predefined window size
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( windowWidth, windowHeight );
    glutCreateWindow( "(A4) - How to Train Your Dragon" );

    fprintf(stdout, "[INFO]: /-------------------------------------------------------------\\\n");
    fprintf(stdout, "[INFO]: | OpenGL Information                                          |\n");
    fprintf(stdout, "[INFO]: |-------------------------------------------------------------|\n");
    fprintf(stdout, "[INFO]: |   OpenGL Version:  %40s |\n", glGetString(GL_VERSION));
    fprintf(stdout, "[INFO]: |   OpenGL Renderer: %40s |\n", glGetString(GL_RENDERER));
    fprintf(stdout, "[INFO]: |   OpenGL Vendor:   %40s |\n", glGetString(GL_VENDOR));
    fprintf(stdout, "[INFO]: |   GLUI Version:    %40.2f |\n", GLUI_VERSION);
    fprintf(stdout, "[INFO]: \\-------------------------------------------------------------/\n");

    // do some basic OpenGL setup
    initScene();

    // create our menu options and attach to mouse button
    createMenus();

    // register callback functions...
    registerCallbacks();

    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}