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

/*
g++ -o load_obj load_obj.cpp model.cpp -lglut -lGLU -lGL
g++ -c load_obj.cpp -lglut -lGLU -lGL
./load_obj

*/

Model m;
int lastx = 0, lasty = 0, currx = 0, curry = 0;
int left_pressed = false;

void ini(){
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(300, 300);
  glutCreateWindow("IDI: Objects loading");  
}

void reshape(int w, int h){

  if (w > h)
    glViewport((w-h)/2.0, 0, h, h);
  else
    glViewport(0, (h-w)/2.0, w, w);

  // glLoadIdentity();

}

void keyboard(unsigned char key, int x, int y){

  switch (key){
    case 'q':
    case 27:
      exit(0);
      break;
  }
}


void display_model(Model a){
    for(int i = 0; i < a.faces().size(); ++i){
      const Face &f = a.faces()[i];
      glVertex3dv(&a.vertices()[f.v[0]]);
      glVertex3dv(&a.vertices()[f.v[1]]);
      glVertex3dv(&a.vertices()[f.v[2]]);
    }
}

void display(void) {

  //limpia colores de la pantalla
  glClearColor(0.0, 0.0, 0.0, 0.0);
  //limpia los buffers de color y de profundidad
  // glColor3f(1.0,0.0,0.0);
  // glutWireTorus(0.25,0.75,30,30);
  // glutWireCube(.45);
  glColor3f(1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

  glBegin(GL_TRIANGLES); // empieza a pintar
    display_model(m);
  glEnd(); // termina de pintar
  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
  /* button: key pressed
     state: state of the button
     x, y: coords */
  if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN){
    left_pressed = true;
    currx = x;
    curry = y;
  }
  else{
    left_pressed = false;
  }
}
void onmotion(int x, int y){
  if (left_pressed){
    glRotatef(y-curry,1,0,0);
    glRotatef(x-currx,0,1,0);
    currx = x;
    curry = y;
  }
  display();
}

int main(int argc, char** argv){

  glutInit(&argc, argv);
  ini();

  m.load("HomerProves.obj");
  //CallBacks  
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(onmotion);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  //MainLoop
  glutMainLoop();
  return 0;

}