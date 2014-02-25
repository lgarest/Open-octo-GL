#include <GL/gl.h>
#include <GL/freeglut.h>

void refresh(void){
    glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);   
       glBegin(GL_TRIANGLES); 
            glVertex3f(-0.5,-0.5,0.0); 
            glVertex3f(0.5,0.0,0.0); 
            glVertex3f(0.0,0.5,0.0); 
        glEnd(); 
            glutSwapBuffers(); 
}

int main(int argc, char const *argv[]){
  glutInit(&argc, (char **)argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (600, 600);
  glutCreateWindow("IDI:_Lab_1");
  glClearColor(0.0,0.0,0.0,0.0);
  glutDisplayFunc(refresh);
  glutMainLoop();
  return 0;
}
