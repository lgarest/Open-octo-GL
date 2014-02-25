#include <GL/gl.h>
#include <GL/freeglut.h>

#include <math.h>
#include <iostream>
using namespace std;

#include "model.h"

// Angles variables.
const GLfloat PI = 3.1415926535;
const GLfloat VIEWER_ANGLE_INCREMENT = PI / 60.0;
GLfloat viewerAzimuth = 0.8;
GLfloat viewerZenith  = 1.3;
GLfloat ViewerDistance = 1;

// Viewport & window variables.
const GLfloat ASPECT_RATIO = 1.5;
GLint INIT_WINDOW_POSITION[2] = { 150, 150 };
GLint WindowSize[2]   = { 750, 750 / ASPECT_RATIO };
GLint ViewportSize[2] = { 750, 750 / ASPECT_RATIO };

// Camera position variables.
GLfloat OBS[] = { 5.0, 5.0, 5.0 };
GLfloat VRP[] = { 0.0,0.0,0.0 };
GLfloat CR[] = { 0.0, 1.0, 0.020 };

// Lights related variables.
const GLfloat LIGHT_AMBIENT[] = { 0.001, 0.001, 0.001, 1.0};
const GLfloat LIGHT_DIFFUSE[] = { 1.0, 1.0, 1.0, 1.0};
const GLfloat LIGHT_SPECULAR[] = { 0.8, 0.8, 0.8, 1.0};

// Program modes bools
bool camera_mode;
Model m;

void HelpDisplay();
void ResizeWindow(int w, int h);
void ConfigCamera();
void Display();
void Display_Model(Model a);

void HelpDisplay(){
    cout << "-----------------ZOOM & INFO CONTROLS-----------------"<<endl;
    cout << "|'h' to show this menu.                              |"<<endl;
    cout << "|'q' or 'esc' to quit.                               |"<<endl;
    // cout << "|                                                    |"<<endl;
    // cout << "---------------------MOVEMENT-------------------------"<<endl;
    cout << "------------------------------------------------------"<<endl;
}

void ResizeWindow(int w, int h){
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

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // // gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    // glMatrixMode(GL_MODELVIEW);
}

void ConfigCamera(){
    // Set up the properties of the viewing camera.
    /*gluLookAt(
      GLdouble eyex,\
      GLdouble eyey, |> position of the camera
      GLdouble eyez,/
          GLdouble centerx,\
          GLdouble centery, |> VPR
          GLdouble centerz,/
      GLdouble upx,\
      GLdouble upy, |> rotation
      GLdouble upz / );*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (camera_mode){
        /*GLdouble 
        fovy, aspect, zNear, zFar*/
        gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
    }
    else{
        /*glOrtho(GLdouble left, right, bottom, top, zNear, zFar );*/
        // glOrtho(left, right, bottom, top, zNear,  zFar);
        glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 1.0);
    }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Position and orient viewer.
    gluLookAt(
        OBS[0], OBS[1], OBS[2],
        VRP[0], VRP[1], VRP[2],
         CR[0],  CR[1], CR[2]);
}

void Display(){
    HelpDisplay();
    ConfigCamera();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Render scene.
    // EARTH
    glDepthMask(GL_TRUE);
    glutSwapBuffers();
    glFlush();
}

void Display_Model(Model a){
    glBegin(GL_TRIANGLES);
        for(int i = 0; i < a.faces().size(); ++i){
            const Face &f = a.faces()[i];
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat*) &Materials[f.mat].ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat*) &Materials[f.mat].diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat*) &Materials[f.mat].specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat*) &Materials[f.mat].shininess);
            
            // glNormal3dv(&a.normals()[f.normalC[0]]);
            glNormal3dv(&a.normals()[f.n[0]]);
            glVertex3dv(&a.vertices()[f.v[0]]);

            glNormal3dv(&a.normals()[f.n[1]]);
            glVertex3dv(&a.vertices()[f.v[1]]);

            glNormal3dv(&a.normals()[f.n[2]]);
            glVertex3dv(&a.vertices()[f.v[2]]);
        }
    glEnd();
}

void Keyboard_Press(unsigned char pressedKey, int mouseX, int mouseY){
    char pressedChar = char(pressedKey);
    switch(pressedKey){
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

int main(int argc, char **argv) {
    glutInit (&argc, argv);

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0]+400, INIT_WINDOW_POSITION[1]-50);
    glutInitWindowSize( WindowSize[0], WindowSize[1] );
    glutCreateWindow( "IDI: Solar System 3.0" );

    glutReshapeFunc(ResizeWindow);
    // glutKeyboardFunc(KeyboardPress);
    // glutSpecialFunc(NonASCIIKeyboardPress);
    glutDisplayFunc(Display);

    return 0;
}