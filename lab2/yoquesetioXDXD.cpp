#if defined(__APPLE__)
        #include <OpenGL/OpenGL.h>
        #include <GLUT/GLUT.h>
#else
        #include <GL/gl.h>
        #include <GL/freeglut.h>
#endif
 
#include <iostream>
#include "model.h"
 
using namespace std;
 
Model m;
 
void refresh(void) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        glBegin(GL_TRIANGLES);
                //for(int i = 0; i < m.faces().size(); i+=3){
                const Face &f = m.faces()[12];
                glVertex3dv(&m.vertices()[f.v[0]]);
                //}
        glEnd();
               
        glutSwapBuffers();
}
 
void ini() {   
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(600, 600);
        glutCreateWindow("IDI: Carrega objectes");     
}
 
int main(int argc, const char * argv[]) {
        glutInit(&argc, (char **)argv);
        ini();
       
        m.load("HomerProves.obj");
 
        glutDisplayFunc(refresh);
       
        glutMainLoop();
 
        return 0;
}