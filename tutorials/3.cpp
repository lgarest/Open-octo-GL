#if defined(_WIN32)
    #include "glut.h"
    #include <windows.h>
#elif defined __APPLE__
  #include <OpenGL/OpenGL.h>
  #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

struct Vertex{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
Vertex v, a, b, c;
GLuint VBO;


void ini(){
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(300, 300);
  glutCreateWindow("Tutorials: 02");  
}

static void DrawTriangle(Vertex a, Vertex b, Vertex c){
    glBegin(GL_TRIANGLES);
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glVertex3f(c.x, c.y, c.z);
    glEnd();
}

static void DrawPoint(Vertex v){
    glBegin(GL_POINTS);
    glVertex3f(v.x, v.y, v.z);
    glEnd();
}

static void RenderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,1,1); // white
    DrawTriangle(a,b,c); // draw triangle
    glColor3f(0,0,0); // black
    DrawPoint(v); // draw point

    glutSwapBuffers();
}

int main(int argc, char const *argv[]){
    
    glutInit (&argc, (char **)argv);
    ini();

    glutDisplayFunc(RenderSceneCB);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;

    a.x = -0.5f;
    a.y = -0.5f;
    a.z = 0.0f;

    b.x = 0.5f;
    b.y = -0.5f;
    b.z = 0.0f;

    c.x = 0.0f;
    c.y = 0.5f;
    c.z = 0.0f;    

    Vertex vertices[1];

    vertices[0] = v;

    glutMainLoop();
    return 0;
}