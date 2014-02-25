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
using namespace std;

#include <iostream>
#include <math.h>

GLfloat OBS[] = { 1.0, 1.0, 1.0 };
GLfloat VRP[] = { 0.0,0.0,0.0 };
GLfloat CR[] = { 0.0, 1.0, 0.020 };

bool camera_mode = true;
const GLfloat ASPECT_RATIO = 1.5;
GLint INIT_WINDOW_POSITION[2] = { 150, 150 };
GLint WindowSize[2]   = { 750, 750 / ASPECT_RATIO };
GLint ViewportSize[2] = { 750, 750 / ASPECT_RATIO };

void Display();
void Draw_Axis_Lines();
void Draw_Sphere(GLfloat x, GLfloat y, GLfloat z);
void Keyboard_Press(unsigned char pressedKey, int mouseX, int mouseY);
void Draw_Axis_Lines(){
    float XO[3] = {-1,0,0}, YO[3] = {0,-1,0}, ZO[3] = {0,0,-1};
    float XP[3] = {1,0,0} , YP[3] = {0,1,0} , ZP[3] = {0,0,1};
    glPushMatrix ();
       glLineWidth (0.5);
       glBegin (GL_LINES);
          glColor3f (1,0,0);  glVertex3fv (XO);  glVertex3fv (XP);    // X axis is red.
          glColor3f (0,1,0);  glVertex3fv (YO);  glVertex3fv (YP);    // Y axis is green.
          glColor3f (0,0,1);  glVertex3fv (ZO);  glVertex3fv (ZP);    // z axis is blue.
          glColor3f (1,1,1);
       glEnd();
 
   glPopMatrix ();
}

void Draw_Sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r){
    GLUquadricObj* quadro = gluNewQuadric();
    glPushMatrix();
        glTranslatef(x,y,z);
        gluSphere(quadro,r, 48, 48);
    glPopMatrix();
}

void Config_Camera(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (camera_mode){
        /*GLdouble fovy,
         GLdouble aspect,
         GLdouble zNear,
         GLdouble zFar*/
        gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
    }
    else{
        /*glOrtho(
          left,right,bottom,top,zNear,zFar
        );*/
        glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 100);
    }
    gluLookAt(
        OBS[0], OBS[1], OBS[2],
        VRP[0], VRP[1], VRP[2],
        CR[0],CR[1],CR[2]);
    glMatrixMode(GL_MODELVIEW);
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Config_Camera();

    Draw_Axis_Lines();

    // Draw_Sphere(0,0,0,0.3);
    // Draw_Sphere(0,0.3,0,0.14);
    glutSolidCube(0.4);
    
    glutSwapBuffers();
}

void Keyboard_Press(unsigned char pressedKey, int mouseX, int mouseY){
    char pressedChar = char(pressedKey);
    switch(pressedKey){
        case 'c':
            // on/off luz de camara
            camera_mode = !camera_mode;
            break;

        case 27:
            cout << "Bye!" <<endl;
            exit(0);
            break;

        case 'q':
            cout << "Bye!" <<endl;
            exit(0);
            break;
    }
    Display();
}

void Resize_Window(int w, int h) {
    WindowSize[0] = w;
    WindowSize[1] = h;
    if (ASPECT_RATIO > w/h) {
        ViewportSize[0] = w;
        ViewportSize[1] = w / ASPECT_RATIO;
    }
    else {
        ViewportSize[1] = h;
        ViewportSize[0] = h * ASPECT_RATIO;
    }

    glViewport(0.5*(w-ViewportSize[0]), 0.5*(h-ViewportSize[1]), ViewportSize[0], ViewportSize[1]);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WindowSize[0], WindowSize[1]);
    glutCreateWindow("IDI: Camaras");

    glutReshapeFunc(Resize_Window);
    glutKeyboardFunc(Keyboard_Press);
    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}