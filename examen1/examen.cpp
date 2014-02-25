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
GLfloat OBS[] = { 1.0, 1.0, 1.0 };
GLfloat VRP[] = { 0.0,0.0,0.0 };
GLfloat CR[] = { 0.0, 1.0, 0.020 };

// Lights related variables.
const GLfloat LIGHT_AMBIENT[]  = { 0.001, 0.001, 0.001, 1.0};
const GLfloat LIGHT_DIFFUSE[]  = { 1.0, 1.0, 1.0, 1.0};
const GLfloat LIGHT_SPECULAR[] = { 0.8, 0.8, 0.8, 1.0};

// Program modes bools
bool camera_mode;
bool verbose = true;
Model m;

void HelpDisplay();
void NonASCIIKeyboard_Press(int pressedKey, int mouseX, int mouseY);
void Resize_Window(int w, int h);
void ConfigCamera();
void Display();
void Display_Model(Model a, GLfloat size);
void Display_Floor(GLfloat x, GLfloat z);
void Keyboard_Press(unsigned char pressedKey, int mouseX, int mouseY);

void HelpDisplay(){
    cout << "-----------------ZOOM & INFO CONTROLS-----------------"<<endl;
    cout << "|'h' to show this menu.                              |"<<endl;
    cout << "|'q' or 'esc' to quit.                               |"<<endl;
    // cout << "|                                                    |"<<endl;
    // cout << "---------------------MOVEMENT-------------------------"<<endl;
    cout << "------------------------------------------------------"<<endl;
}

void NonASCIIKeyboard_Press(int pressedKey, int mouseX, int mouseY) {
    glutIgnoreKeyRepeat(false);
    switch(pressedKey) {
        case GLUT_KEY_RIGHT:{
            viewerAzimuth += VIEWER_ANGLE_INCREMENT;
            if (viewerAzimuth > 2*PI) 
                viewerAzimuth -= 2*PI;

            break; 
        }
        case GLUT_KEY_LEFT:{ 
            viewerAzimuth -= VIEWER_ANGLE_INCREMENT; 
            if (viewerAzimuth < 0.0)  
                viewerAzimuth += 2*PI; 
            break; 
        }
        case GLUT_KEY_UP:{ 
            viewerZenith -= VIEWER_ANGLE_INCREMENT; 
            if (viewerZenith < VIEWER_ANGLE_INCREMENT) 
                viewerZenith = VIEWER_ANGLE_INCREMENT; 
            break; 
        }
        case GLUT_KEY_DOWN:{ 
            viewerZenith += VIEWER_ANGLE_INCREMENT; 
            if (viewerZenith > PI - VIEWER_ANGLE_INCREMENT)  
                viewerZenith = PI - VIEWER_ANGLE_INCREMENT; 
            break; 
        }
    }
    Display();
}

void Resize_Window(int w, int h){
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
    glMatrixMode(GL_MODELVIEW);
}

void Display(){
    // HelpDisplay();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    ConfigCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    
    // glLoadIdentity();

    // Render scene.

    Display_Model(m, 0.6);
    // Display_Floor(5,5);

    glDepthMask(GL_TRUE);
    glutSwapBuffers();
    // glFlush();
}

void Display_Model(Model a, GLfloat size){
    GLfloat xmin, xmax, ymin, ymax, zmin, zmax;
    GLfloat xcentral, ycentral, zcentral;
    GLfloat scalemodel;
    xmin = xmax = a.vertices()[0];
    ymin = ymax = a.vertices()[1];
    zmin = zmax = a.vertices()[2];

    for (int i = 0; i < a.vertices().size(); i+=3) {
        if(xmin>a.vertices()[i]) xmin = a.vertices()[i];
        if(xmax<a.vertices()[i]) xmax = a.vertices()[i];

        if(ymin>a.vertices()[i]) ymin = a.vertices()[i+1];
        if(ymax<a.vertices()[i]) ymax = a.vertices()[i+1];

        if(zmin>a.vertices()[i]) zmin = a.vertices()[i+2];
        if(zmax<a.vertices()[i]) zmax = a.vertices()[i+2];
    }
    // we set the central point for each model axis
    xcentral = (xmin+xmax)/2;
    ycentral = (ymin+ymax)/2;
    zcentral = (zmin+zmax)/2;

    if(verbose){cout << "x:" << xmax << ',' << xmin<<endl; cout << "y:" << ymax << ',' << ymin<<endl; cout << "z:" << zmax << ',' << zmin<<endl; }

    scalemodel = abs(ymax - ymin);
    if (scalemodel < abs(xmax - xmin)) scalemodel = abs(xmax - xmin);
    if (scalemodel < abs(zmax - zmin)) scalemodel = abs(zmax - zmin);
    scalemodel = size/scalemodel;

    if (verbose) {cout << "s:" << scalemodel; cout << "(" << xcentral; cout << "," << ycentral; cout << "," << zcentral; cout << ")" << endl; }

    glPushMatrix();
        // we scale model to the desired total size
        glScalef(scalemodel,scalemodel,scalemodel);
        // we translate the model to be drawn in the (0,0,0)
        glTranslatef(-xcentral,-ycentral,-zcentral);
        // now we draw the vertexs and the normals
        glBegin(GL_TRIANGLES);
            for(int i = 0; i < a.faces().size(); ++i){
                const Face &f = a.faces()[i];
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat*) &Materials[f.mat].ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat*) &Materials[f .mat].diffuse);  
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat*) &Materials[ f.mat].specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat*) &Materials[f.mat].shininess);

                // If the normals vector is empty we render the normals from the face.
                // cout <<"n.size()"<< f.n.size() << endl;
                if(f.n.size() == 0) {
                    glNormal3dv(a.faces()[i].normalC);
                    glVertex3dv(&a.vertices()[f.v[0]]);
                    glVertex3dv(&a.vertices()[f.v[1]]);
                    glVertex3dv(&a.vertices()[f.v[2]]);
                }
                // Otherwise we render the normals from each vertex.
                else{
                    glNormal3dv(&a.normals()[f.n[0]]);
                    glVertex3dv(&a.vertices()[f.v[0]]);

                    glNormal3dv(&a.normals()[f.n[1]]);
                    glVertex3dv(&a.vertices()[f.v[1]]);

                    glNormal3dv(&a.normals()[f.n[2]]);
                    glVertex3dv(&a.vertices()[f.v[2]]);
                }
            }
        glEnd();
    glPopMatrix();
}

void Display_Floor(GLfloat x, GLfloat z){
    GLfloat blue[] = {0.0,0.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blue);
        // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat*) &Materials[f.mat].shininess);
    // TOP
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(x/2,0,-z/2);
        glVertex3f(x/2,0,z/2);
        glVertex3f(-x/2,0,z/2);
        glVertex3f(-x/2,0,-z/2);
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
    // Display();
}

int main(int argc, char **argv) {
    glutInit (&argc, argv);

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0]+400, INIT_WINDOW_POSITION[1]-50);
    glutInitWindowSize( WindowSize[0], WindowSize[1] );
    glutCreateWindow( "IDI: Examen1" );

    // Load the model
    m.load("legoman.obj");


    // Refreshing routines
    glutReshapeFunc(Resize_Window);
    glutKeyboardFunc(Keyboard_Press);
    glutSpecialFunc(NonASCIIKeyboard_Press);
    glutDisplayFunc(Display);

    glEnable(GL_DEPTH_TEST);
    // Set_Lights();

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
    glutMainLoop();

    return 0;
}