#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
  #include <OpenGL/OpenGL.h>
  #include <GLUT/glut.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

Model m;

void reshape(int w, int h){

  glViewport(0,0,w,h);
  glLoadIdentity();

}

void display(void) {

  glClearColor(0.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // glColor3f(1.0,0.0,0.0);
  // glutWireTorus(0.25,0.75,30,30);
  glColor3f(0.0,0.0,1.0);
  glutWireCube(.45);
  glRotatef(30,1,0,1); // rotate 30 en x
  glutSwapBuffers();

}

int main(int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(100,100);
  glutInitWindowPosition(600,600);
  glutCreateWindow("IDI");

  m.load("HomerProves.obj");

  //CallBacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  //MainLoop
  glutMainLoop();
  return 0;

}

/*
g++ -o load_obj load_obj.cpp model.cpp -lglut -lGLU -lGL
g++ -c load_obj.cpp -lglut -lGLU -lGL
./load_obj
*/