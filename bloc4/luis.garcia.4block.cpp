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
GLint scene_camera_position = 0;
const GLfloat LIGHT_AMBIENT[]       = { 0.001, 0.001, 0.001, 1.0};
const GLfloat LIGHT_DIFFUSE[]       = { 1.0, 1.0, 1.0, 1.0};
const GLfloat LIGHT_SPECULAR[]      = { 0.8, 0.8, 0.8, 1.0};

// Scene light positions.
const GLfloat LIGHT_1_POSITION_1[]  = {0.5, 0.01, 0.5, 1};
const GLfloat LIGHT_1_POSITION_2[]  = {0.5, 0.01, -0.5, 1};
const GLfloat LIGHT_1_POSITION_3[]  = {-0.5, 0.01, -0.5, 1};
const GLfloat LIGHT_1_POSITION_4[]  = {-0.5, 0.01, 0.5, 1};

Model m;

// Program modes variables.
bool scene_light = true, camera_light = false, help_menu = true, first = true, verbose = false;

// Functions declarations.
void Keyboard_Press(unsigned char pressedKey, int mouseX, int mouseY);
void NonASCIIKeyboard_Press(int pressedKey, int mouseX, int mouseY);
void Resize_Window(int w, int h);
void Help_Display();
void Display_Status();
void Set_Lights();
void Draw_Light(GLfloat x, GLfloat y, GLfloat z);
void Update_Light();
void Config_Camera();
void Display();
void Display_Model(Model a);
void Display_Floor();

void Keyboard_Press(unsigned char pressedKey, int mouseX, int mouseY){
    char pressedChar = char(pressedKey);
    switch(pressedKey){
        case 'h':
            help_menu = true;
            break;
        case 'c':
            // on/off luz de camara
            camera_light = !camera_light;
            if(verbose){
                cout << "Camera light: ";
                if (camera_light) cout << "enabled";
                else cout << "disabled";
                cout <<endl;
            }
            break;
        case 's':
            // cambia la posicion de la luz
            ++scene_camera_position;
            if (scene_camera_position >=4) scene_camera_position = 0;
            if (verbose) cout << "Camera position: " << scene_camera_position <<endl;
            break;
        case 'f':
            // on/off luz de escena
            scene_light = !scene_light;
            if (verbose){
                cout << "Scene light: ";
                if (scene_light) cout << "enabled";
                else cout << "disabled";
                cout <<endl;
            }
            break;

        case 27:
            if (verbose) cout << "Bye!" <<endl;
            exit(0);
            break;
        case 'q':
            if (verbose) cout << "Bye!" <<endl;
            exit(0);
            break;
        case 'V':
            verbose = !verbose;
            cout << "Verbose: ";
            if (verbose) cout << "enabled";
            else cout << "disabled";
            cout <<endl;
            break;
        case 'Z':
            if (ViewerDistance > 0.51)
                ViewerDistance -= 0.01;
            break;
        case 'z':
        if (ViewerDistance < 1)
            ViewerDistance += 0.01;
            break;
    }
    Display();
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

void Help_Display(){
    help_menu = false;
    cout << "-----------------ZOOM & INFO CONTROLS-----------------"<<endl;
    cout << "|'h' to show this menu.                              |"<<endl;
    cout << "|'q' or 'esc' to quit.                               |"<<endl;
    cout << "|'c' to toggle camera light.                         |"<<endl;
    cout << "|'f' to toggle scene light.                          |"<<endl;
    cout << "|'s' to change the position of the scene light.      |"<<endl;
    cout << "|----------------------------------------------------|"<<endl;
    cout << "|'V'     to toggle verbose mode (default off).       |"<<endl;
    cout << "|'up'    to orbit the camera up.                     |"<<endl;
    cout << "|'down'  to orbit the camera down.                   |"<<endl;
    cout << "|'right' to orbit the camera right.                  |"<<endl;
    cout << "|'left'  to orbit the camera left.                   |"<<endl;
    cout << "|'Z'     to zoom in.                                 |"<<endl;
    cout << "|'z'     to zoom out.                                |"<<endl;
    cout << "------------------------------------------------------"<<endl;
}

void Display_Status(){
    cout << "OBS:("<<OBS[0]<<','<<OBS[1]<<','<<OBS[2]<<')'<<endl;
    cout << "VRP:("<<VRP[0]<<','<<VRP[1]<<','<<VRP[2]<<')'<<endl;
    cout << "viewer_distance: "<<ViewerDistance;
    if (ViewerDistance <= 0.51) cout << "(min)";
    else if (ViewerDistance >= 0.99) cout << "(max)";
    cout << endl;
    cout << "azimuth: "<<viewerAzimuth<<endl;
    cout << "zenith: "<<viewerZenith<<endl;
    cout << "------------------------------------------------------"<<endl;
}

void Set_Lights(){
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT1, GL_AMBIENT,  LIGHT_AMBIENT);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  LIGHT_DIFFUSE);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
    glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION_1);
    Draw_Light(LIGHT_1_POSITION_1[0],LIGHT_1_POSITION_1[1],LIGHT_1_POSITION_1[2]);
}

void Draw_Light(GLfloat x, GLfloat y, GLfloat z){
    GLUquadricObj* quadro = gluNewQuadric();
    glPushMatrix();
        glTranslatef(x,y,z);
        gluSphere(quadro,0.01, 48, 48);
    glPopMatrix();
}

void Update_Light(){
    glPushMatrix();
        glLoadIdentity();
         
        switch (scene_camera_position){
            case 0:
                glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION_1);
                if(scene_light) Draw_Light(LIGHT_1_POSITION_1[0],LIGHT_1_POSITION_1[1],LIGHT_1_POSITION_1[2]);
            break;
            case 1:
                glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION_2);
                if(scene_light) Draw_Light(LIGHT_1_POSITION_2[0],LIGHT_1_POSITION_2[1],LIGHT_1_POSITION_2[2]);
            break;
            case 2:
                glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION_3);
                if(scene_light) Draw_Light(LIGHT_1_POSITION_3[0],LIGHT_1_POSITION_3[1],LIGHT_1_POSITION_3[2]);
            break;
            case 3:
                glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION_4);
                if(scene_light) Draw_Light(LIGHT_1_POSITION_4[0],LIGHT_1_POSITION_4[1],LIGHT_1_POSITION_4[2]);
            break;
        }
    glPopMatrix();
    
    if (camera_light){ 
        glPushMatrix();
            glLightfv(GL_LIGHT0, GL_POSITION, OBS);
            glEnable(GL_LIGHT0);
        glPopMatrix();
    }
    else glDisable(GL_LIGHT0);
    if (scene_light) glEnable(GL_LIGHT1);
    else glDisable(GL_LIGHT1);
}

void Config_Camera(){
    // Set up the properties of the viewing camera.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    OBS[0] = VRP[0] + ViewerDistance * sin(viewerZenith) * sin(viewerAzimuth);
    OBS[1] = VRP[1] + ViewerDistance * cos(viewerZenith);
    OBS[2] = VRP[2] + ViewerDistance * sin(viewerZenith) * cos(viewerAzimuth);
    // Position and orient viewer.
    gluLookAt(
        OBS[0], OBS[1], OBS[2],
        VRP[0], VRP[1], VRP[2],
        CR[0],CR[1],CR[2]);
    glMatrixMode(GL_MODELVIEW);
}

void Display(){
    if(help_menu) Help_Display();
    if(verbose) Display_Status();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    Config_Camera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render scene.
    Update_Light();
    Display_Floor();
    glPushMatrix();
        glTranslatef(0.0, 16.5, 0.0);
        Display_Model(m);
    glPopMatrix();
    if(first){
        glScalef( 0.005, 0.005, 0.005);
        first = !first;
    }

    glDepthMask(GL_TRUE);
    glutSwapBuffers();
    // glFlush();
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

void Display_Floor(){
    GLfloat blue[] = {0.0,0.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blue);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blue);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blue);
        // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat*) &Materials[f.mat].shininess);
    // TOP
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(100,0,-100);
        glVertex3f(100,0,100);
        glVertex3f(-100,0,100);
        glVertex3f(-100,0,-100);
    glEnd();
    // BOTTOM
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(100,-5,-100);
        glVertex3f(100,-5,100);
        glVertex3f(-100,-5,100);
        glVertex3f(-100,-5,-100);
    glEnd();
    // FRONT
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(100,0,100);
        glVertex3f(100,-5,100);
        glVertex3f(100,-5,-100);
        glVertex3f(100,0,-100);
    glEnd();
    // RIGHT
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(100,0,100);
        glVertex3f(-100,0,100);
        glVertex3f(-100,-5,100);
        glVertex3f(100,-5,100);
    glEnd();
    // LEFT
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(100,0,-100);
        glVertex3f(-100,0,-100);
        glVertex3f(-100,-5,-100);
        glVertex3f(100,-5,-100);
    glEnd();
    // BACK
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(-100,0,-100);
        glVertex3f(-100,0,100);
        glVertex3f(-100,-5,100);
        glVertex3f(-100,-5,-100);
    glEnd();
}

int main(int argc, char** argv){
    glutInit (&argc, argv);
    cout << "------------------------------------------------------"<<endl;
    cout << "|   Luis Garcia Estrades G:22 4th block submission.  |" << endl;

    // Set up the display window.
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0]+400, INIT_WINDOW_POSITION[1]-50);
    glutInitWindowSize( WindowSize[0], WindowSize[1] );
    glutCreateWindow( "IDI: 4th  - Luis Garcia Estrades" );

    // Load the model
    m.load("models/porsche.obj");

    // Specify the resizing and refreshing routines.
    glutReshapeFunc(Resize_Window);
    glutKeyboardFunc(Keyboard_Press);
    glutSpecialFunc(NonASCIIKeyboard_Press);
    glutDisplayFunc(Display);

    // Set up depth testing.
    glEnable(GL_DEPTH_TEST);
    // Configure the lights.
    Set_Lights();

    glEnable(GL_NORMALIZE);
    glutMainLoop();
    return 0;
}