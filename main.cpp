////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Contains main function to create a window and run engine
///
/// Basic support for directional light, depth buffer, setting up 3d projection,
/// setting up a 3d camera, drawing a cube model, and running a set fixed frame
/// rate.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes

// STL
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
using namespace std;

// GL
#include <GL/glut.h>

// My program
#include "Model.h"
#include "Vector.h"

////////////////////////////////////////////////////////////////////////////////
// Global variables - avoid these

// Window
int g_width{1360};
int g_height{768};
int g_window{0};

// Camera
float g_theta{0.f};

// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
float g_delay{0.f};
float g_framesPerSecond{0.f};

// Model
unique_ptr<Model> m; // Model*

////////////////////////////////////////////////////////////////////////////////
// Functions

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
void
initialize() {
  glClearColor(0.f, 0.f, 0.4f, 0.f);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback for resize of window
///
/// Responsible for setting window size (viewport) and projection matrix.
void
resize(GLint _w, GLint _h) {
  g_width = _w;
  g_height = _h;

  // Viewport
  glViewport(0, 0, g_width, g_height);

  // Projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.f, GLfloat(g_width)/g_height, 0.01f, 100.f);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Timer function to fix framerate in a GLUT application
/// @param _v Value (not used here)
///
/// Note, this is rudametary and fragile.
void
timer(int _v) {
  if(g_window != 0) {
    glutPostRedisplay();

    g_delay = std::max(0.f, 1.f/FPS - g_frameRate);
    glutTimerFunc((unsigned int)(1000.f*g_delay), timer, 0);
  }
  else
    exit(0);
}

void print_data() {
  cout << "Model contains:" << endl
    << "\t" << m->m_points.size() << " points" << endl
    << "\t" << m->m_normals.size() << " normals" << endl
    << "\t" << m->m_textures.size() << " textures" << endl
    << "\t" << m->m_faces.size() << " faces" << endl;
}

void
getModel(){
  std::cout<<"Loading Model\n";
  std::cout<<"Name of Model to import: ";
  std::string location;
  //Location of model
  std::cin >> location;
  m.reset(new Model(location));
  //When Making model give normal
  //then vertex
  print_data();
}
////////////////////////////////////////////////////////////////////////////////
/// @brief loads model




////////////////////////////////////////////////////////////////////////////////
/// @brief Draw function for single frame
void
draw() {
  using namespace std::chrono;

  //////////////////////////////////////////////////////////////////////////////
  // Clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //////////////////////////////////////////////////////////////////////////////
  // Draw

  // Camera
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(10*std::sin(g_theta), 0.f, 10*std::cos(g_theta),
            0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

  // Single directional light
  static GLfloat lightPosition[] = { 0.5f, 1.0f, 1.5f, 0.0f };
  static GLfloat whiteLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  static GLfloat darkLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, darkLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);

  // Model
  glColor3f(0.6f, 0.f, 0.f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);
    for(int i = 0; i < m->m_faces.size(); i++){
      for(int z = 0; z < 3; z++){
        const Vector3& n = m->m_normals[m->m_faces[i].m_v[z].m_n];
        glNormal3f(n.getX(), n.getY(), n.getZ());
        const Vector3& v = m->m_points[m->m_faces[i].m_v[z].m_p];
        glVertex3f(v.getX(), v.getY(), v.getZ());
      }  
    } 

  glEnd();

  //Old Model
  /*
  glBegin(GL_QUADS);

  glNormal3f( 0.f, -1.f,  0.f); // top
  glVertex3f(-1.f, -1.f, -1.f);
  glVertex3f(-1.f, -1.f,  1.f);
  glVertex3f( 1.f, -1.f,  1.f);
  glVertex3f( 1.f, -1.f, -1.f);

  glNormal3f( 0.f,  1.f,  0.f); // bottom
  glVertex3f(-1.f,  1.f, -1.f);
  glVertex3f(-1.f,  1.f,  1.f);
  glVertex3f( 1.f,  1.f,  1.f);
  glVertex3f( 1.f,  1.f, -1.f);

  glNormal3f( 0.f,  0.f, -1.f); // back
  glVertex3f(-1.f, -1.f, -1.f);
  glVertex3f(-1.f,  1.f, -1.f);
  glVertex3f( 1.f,  1.f, -1.f);
  glVertex3f( 1.f, -1.f, -1.f);

  glNormal3f( 0.f,  0.f,  1.f); // front
  glVertex3f(-1.f, -1.f,  1.f);
  glVertex3f(-1.f,  1.f,  1.f);
  glVertex3f( 1.f,  1.f,  1.f);
  glVertex3f( 1.f, -1.f,  1.f);

  glNormal3f(-1.f,  0.f,  0.f); // left
  glVertex3f(-1.f, -1.f, -1.f);
  glVertex3f(-1.f, -1.f,  1.f);
  glVertex3f(-1.f,  1.f,  1.f);
  glVertex3f(-1.f,  1.f, -1.f);

  glNormal3f( 1.f,  0.f,  0.f); // right
  glVertex3f( 1.f, -1.f, -1.f);
  glVertex3f( 1.f, -1.f,  1.f);
  glVertex3f( 1.f,  1.f,  1.f);
  glVertex3f( 1.f,  1.f, -1.f);

  glEnd();

  */

  //////////////////////////////////////////////////////////////////////////////
  // Show
  glutSwapBuffers();

  //////////////////////////////////////////////////////////////////////////////
  // Record frame time
  high_resolution_clock::time_point time = high_resolution_clock::now();
  g_frameRate = duration_cast<duration<float>>(time - g_frameTime).count();
  g_frameTime = time;
  g_framesPerSecond = 1.f/(g_delay + g_frameRate);
  printf("FPS: %6.2f\n", g_framesPerSecond);
}




////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses
/// @param _key Key
/// @param _x X position of moue
void
keyPressed(GLubyte _key, GLint _x, GLint _y) {
  switch(_key) {
    // Escape key : quit application
    case 27:
      std::cout << "Destroying window: " << g_window << std::endl;
      glutDestroyWindow(g_window);
      g_window = 0;
      break;
    // Unhandled
    default:
      std::cout << "Unhandled key: " << (int)(_key) << std::endl;
      break;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses of special keys
/// @param _key Key
/// @param _x X position of mouse
/// @param _y Y position of mouse
void
specialKeyPressed(GLint _key, GLint _x, GLint _y) {
  switch(_key) {
    // Arrow keys
    case GLUT_KEY_LEFT:
      g_theta -= 0.02;
      break;
    case GLUT_KEY_RIGHT:
      g_theta += 0.02;
      break;
    // Unhandled
    default:
      std::cout << "Unhandled";
      
  }
}

////////////////////////////////////////////////////////////////////////////////
// Main

////////////////////////////////////////////////////////////////////////////////
/// @brief main
/// @param _argc Count of command line arguments
/// @param _argv Command line arguments
/// @return Application success status

int
main(int _argc, char** _argv) {
  //Create single model
  
  //m.draw();
  //Load Model
  getModel();
  //////////////////////////////////////////////////////////////////////////////
  // Initialize GLUT Window
  std::cout << "Initializing GLUTWindow" << std::endl;
  // GLUT
  glutInit(&_argc, _argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(g_width, g_height); // HD size
  g_window = glutCreateWindow("Linux > Windows");

  // GL
  initialize();

  //////////////////////////////////////////////////////////////////////////////
  // Assign callback functions
  std::cout << "Assigning Callback functions" << std::endl;
  glutReshapeFunc(resize);
  glutDisplayFunc(draw);
  glutKeyboardFunc(keyPressed);
  glutSpecialFunc(specialKeyPressed);
  glutTimerFunc(1000/FPS, timer, 0);

  // Start application
  std::cout << "Starting Application" << std::endl;
  glutMainLoop();

  return 0;
}
