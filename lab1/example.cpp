
#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
 
#define width 900
#define height 900
 
using namespace std;
 
// Set the main color definitions.
GLfloat white3[] = {1.0, 1.0, 1.0};
GLfloat black3[] = {0.0, 0.0, 0.0};
 
 
GLfloat startX  =  0.0;
GLfloat startY  =  0.0;
GLfloat endX    =  10.0;
GLfloat endY    =  10.0;
 
// Implementations.
 
void display1(void)
{
  // Clear all Pixels.
  glClear(GL_COLOR_BUFFER_BIT);
 
  // Draw white Rectangle.
  glColor3f(white3[0], white3[1], white3[2]);
 
// Creation of a POLYGON.
  glBegin(GL_POLYGON);
    glVertex3f(startX, startY, 0.0);
    glVertex3f(endX, startY, 0.0);
    glVertex3f(endX, endY, 0.0);
    glVertex3f(startX, endY, 0.0);
  glEnd();
  glFlush();
 
  cout << startX << " " << endX << endl;
}
 
void init(void)
{
  // Background black color.
  glClearColor(0.0, 0.0, 0.0, 0.0);
 
  // Initialize viewing values.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Set the Orthogonal System.
  glOrtho(0.0, width, 0.0, height, 0.0, 0.0);
}
 
int main(int argc, char** argv)
{
  glutInit(&amp;argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Hello World.");
  init();
  glutDisplayFunc(display1);
  glutMainLoop();
  return 0;
}