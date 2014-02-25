#include <GL/gl.h>
#include <GL/freeglut.h>

void refresh(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

int main(int argc, char const *argv[]){
  glutInit(&argc, (char **)argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (600, 600);
  glutCreateWindow("IDI:_Practica_1");
  glutDisplayFunc(refresh);
  glutMainLoop();
  return 0;
}