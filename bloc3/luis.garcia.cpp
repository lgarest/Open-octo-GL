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
#include "SolarSystemGlobals.h"
#include <iostream>
using namespace std;
// #include "model.h"
// Viewer positioning angles.
GLfloat viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
GLfloat viewerZenith  = INITIAL_VIEWER_ZENITH;
GLfloat VRP[] = { 0.0, 0.0, 0.0 };
GLfloat OBS[] = { 0.0, 0.0, 0.0 };
GLfloat CR[] = { 0.0, 1.0, 0.020 };

// Constants to draw the axis lines.
bool axis_bool = true, camera_mode = true;
float XO[3] = {-30,0,0}, YO[3] = {0,-30,0}, ZO[3] = {0,0,-30};
float XP[3] = {30,0,0} , YP[3] = {0,30,0} , ZP[3] = {0,0,30};

// Variables to keep track of current day status.
GLfloat CurrentEarthRotation = 0.00;
GLfloat EarthDaysTranspired  = 0.00;
GLfloat EarthDayIncrement    = 0.01;

// The initial window and viewport sizes (in pixels), set to ensure that
// the aspect ration for the viewport, will be a constant. If the window
// is resized, the viewport will be adjusted to preserve the aspect ratio.
GLint WindowSize[2]   = { 750, 750 / ASPECT_RATIO };
GLint ViewportSize[2] = { 750, 750 / ASPECT_RATIO };

GLfloat ViewerDistance = INITIAL_VIEWER_DISTANCE;

/***********************/
/* Function prototypes */
/***********************/
void KeyboardPress(unsigned char pressedKey, int mouseX, int mouseY);
void NonASCIIKeyboardPress(int pressedKey, int mouseX, int mouseY);
void TimerFunction(int value);
void Draw_Axis_Lines();
void ConfigCamera();
void Display();
void ResizeWindow(GLsizei w, GLsizei h);
void drawEarthAndMoon();
void drawSun();
void drawPlanets();
void drawPlanet(GLfloat inclination, GLfloat orbitDuration, GLfloat orbitRadius, GLfloat rotationDuration, GLfloat radius, float r, float g, float b) ;

/****************************/
/* Function implementations */
/****************************/

// The main function sets up the data and the   //
// environment to display the textured objects. //
int main(int argc, char** argv) {
    glutInit (&argc, argv);

    // Set up the display window.
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH );
    glutInitWindowPosition( INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1] );
    glutInitWindowSize( WindowSize[0], WindowSize[1] );
    glutCreateWindow( "IDI: Solar System 2.0" );

    // Specify the resizing and refreshing routines.
    glutReshapeFunc(ResizeWindow);
    glutKeyboardFunc(KeyboardPress);
    glutSpecialFunc(NonASCIIKeyboardPress);
    glutDisplayFunc(Display);
    glutTimerFunc(20, TimerFunction, 1);

    // Set up depth testing.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutMainLoop();
    return 0;
}

// Function to react to ASCII keyboard keys pressed by the user.   //
// +/- keys are used to accelerate/decelerate the animation, while //
// the z/Z keys are used to zoom in and out of the animation.      //
void KeyboardPress(unsigned char pressedKey, int mouseX, int mouseY){

    char pressedChar = char(pressedKey);
    switch(pressedKey){
        case 'h':
            cout << "'h' to show this menu." << endl;
            cout << "'+' to speed up the system"<< endl;
            cout << "'-' to slow down the system"<< endl;
            cout << "'Z' to zoom in to the VRP"<< endl;
            cout << "'z' to zoom out to the VRP"<< endl;
            cout << "'c' un/display axis lines"<< endl;
            cout << "'r' to reset the camera to default"<< endl << endl;
            break;
        case 'm':
            axis_bool = !axis_bool;
            break;
        case 'c':
            camera_mode = !camera_mode;
            break;
        case 'w':
            cout << "vrp: (" << VRP[0] <<","<< VRP[1]<<","<<VRP[2]<<")"<<endl;
            VRP[0] += (VRP[0] - OBS[0])*0.01;
            VRP[1] += (VRP[1] - OBS[1])*0.01;
            VRP[2] += (VRP[2] - OBS[2])*0.01;
            break; 
        case 's':
            cout << "vrp: (" << VRP[0] <<","<< VRP[1]<<","<<VRP[2]<<")"<<endl;
            VRP[0] -= (VRP[0] - OBS[0])*0.01;
            VRP[1] -= (VRP[1] - OBS[1])*0.01;
            VRP[2] -= (VRP[2] - OBS[2])*0.01;
            break;
        case 'a':
            // viewerZenith-=0.01;
            break;
        case 'd':
            // viewerZenith+=0.01;
            break;
        case '+':
            EarthDayIncrement *= 2.0;
            if (EarthDayIncrement > 10.0)
                EarthDayIncrement = 10.0;
            break;
        case '-':     
            EarthDayIncrement *= 0.5;
            if (EarthDayIncrement < 0.01)
                EarthDayIncrement = 0.01;
            break;
        case 'z':
            ViewerDistance -= VIEWER_DISTANCE_INCREMENT;
            if (ViewerDistance < MINIMUM_VIEWER_DISTANCE)
                ViewerDistance = MINIMUM_VIEWER_DISTANCE;
            break; 
        case 'Z':
            ViewerDistance += VIEWER_DISTANCE_INCREMENT;
            if (ViewerDistance > MAXIMUM_VIEWER_DISTANCE)
                ViewerDistance = MAXIMUM_VIEWER_DISTANCE;
            break; 
        case 'r':
            cout << "Camera reset!" << endl;
            VRP[3] = ( 0.0, 0.0, 0.0 );

            ViewportSize[2] = (750, 750 / ASPECT_RATIO);
            ViewerDistance = INITIAL_VIEWER_DISTANCE;
            viewerZenith  = INITIAL_VIEWER_ZENITH;
            viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
            break;

        case 27:
            exit(0);
            break;
        case 'q':
            exit(0);
            break;
    }
}

// Function to react to non-ASCII keyboard keys pressed by the user. //
// Used to alter spherical coordinates of the viewer's position.     //
void NonASCIIKeyboardPress(int pressedKey, int mouseX, int mouseY) {
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
}

// The EarthDayIncrement represents the fraction of an      //
// Earth day being added to the scene in one screen update. //
void TimerFunction(int value){
    CurrentEarthRotation += EarthDayIncrement;
    EarthDaysTranspired += EarthDayIncrement;
    if (EarthDaysTranspired == EARTH_ORBIT_DUR)
        EarthDaysTranspired = 0;
    glutPostRedisplay();
    glutTimerFunc(20, TimerFunction, 1);
}

void Draw_Axis_Lines(){
    glPushMatrix ();
       glLineWidth (0.5);
       glBegin (GL_LINES);
          glColor3f (1,0,0);  glVertex3fv (XO);  glVertex3fv (XP);    // X axis is red.
          glColor3f (0,1,0);  glVertex3fv (YO);  glVertex3fv (YP);    // Y axis is green.
          glColor3f (0,0,1);  glVertex3fv (ZO);  glVertex3fv (ZP);    // z axis is blue.
       glEnd();
 
   glPopMatrix ();
}

void ConfigCamera(){
    if (camera_mode){
        gluLookAt(
        OBS[0], OBS[1], OBS[2],
        VRP[0], VRP[1], VRP[2],
        CR[0],CR[1],CR[2]);
    }
    else{
        /*GLdouble left,
          GLdouble right,
          GLdouble bottom,
          GLdouble top,
          GLdouble zNear,
          GLdouble zFar*/
        glOrtho(0.0, WindowSize[0], WindowSize[1], 0.0, 0.2, 100.0);        
    }
}

// Principal display routine: sets up lighting,
// and camera properties, clears the frame buffer
void Display() {
    

    // Set up the properties of the viewing camera.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*GLdouble fovy,
     GLdouble aspect,
     GLdouble zNear,
     GLdouble zFar*/
    gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
    ConfigCamera();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Position and orient viewer.
    /*gluLookAt(
      GLdouble eyex,\
      GLdouble eyey, |> position of the camera
      GLdouble eyez,/

      GLdouble centerx,\
      GLdouble centery, |> VPR
      GLdouble centerz,/

      GLdouble upx,\
      GLdouble upy, |> rotation
      GLdouble upz /
    );*/
    OBS[0] = VRP[0] + ViewerDistance * sin(viewerZenith) * sin(viewerAzimuth);
    OBS[1] = VRP[1] + ViewerDistance * cos(viewerZenith);
    OBS[2] = VRP[2] + ViewerDistance * sin(viewerZenith) * cos(viewerAzimuth);


    // Render scene.
    drawEarthAndMoon();
    drawSun();
    drawPlanets();
    if (axis_bool) Draw_Axis_Lines();
    glDepthMask(GL_TRUE);
    glutSwapBuffers();
    glFlush();
}

//makes calls to the generic planet drawing function. took this out
//of the display function to enhance readability
void drawPlanets(){

    glColor3f(0,1.0,0); //green

    drawPlanet(MERCURY_INCLINATION, MERCURY_ORBIT_DUR, MERCURY_ORBIT_RADIUS, MERCURY_ROTATION_DUR, MERCURY_RADIUS, 1.0, 0, 0);

    drawPlanet(VENUS_INCLINATION, VENUS_ORBIT_DUR, VENUS_ORBIT_RADIUS,
            VENUS_ROTATION_DUR, VENUS_RADIUS, 0, 1.0, 0);

}

// Window-reshaping callback, adjusting the viewport to be as large
// as possible within the window, without changing its aspect ratio.
void ResizeWindow(int w, int h) {
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
    glLoadIdentity();
}


//Draws the texture-mapped earth and moon.
void drawEarthAndMoon() {
    GLfloat MoonRevolution = EarthDaysTranspired / LUNAR_CYCLE;
    GLUquadricObj* quadro = gluNewQuadric();                            
    gluQuadricNormals(quadro, GLU_SMOOTH);              
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glPushMatrix();
                // EARTH
                glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
                glRotatef( 360.0 * (EarthDaysTranspired/EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);
                glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0 );
                glRotatef( 360.0 * CurrentEarthRotation, 0.0, 1.0, 0.0 );
                //glRotatef( -90.0, 1.0, 0.0, 0.0 );
                glColor3f(0,0,0.8); //blue
                gluSphere(quadro, EARTH_RADIUS, 48, 48);
            glPopMatrix();
            // MOON
            glRotatef(EARTH_INCLINATION, 0.0, 0.0, 1.0);
            glRotatef( 360.0 * (EarthDaysTranspired/EARTH_ORBIT_DUR), 0.0, 1.0, 0.0);

            glTranslatef(EARTH_ORBIT_RADIUS, 0.0, 0.0 );
            glRotatef( 360.0 * MoonRevolution, 0.0, 1.0, 0.0 );
            glTranslatef( MOON_ORBIT_RADIUS  , 0.0, 0.0 );
            // gluSphere(quadro, MOON_RADIUS, 48, 48);
            glColor3f(1.0,1.0,1.0); //white
            // display_model(m); //WIP: display homer rotating
            gluSphere(quadro, MOON_RADIUS, 700, 700);
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quadro);
}

//Function to draw the sun at the origin
void drawSun() {
    glColor3f(1.0,1.0,0); //yellow
    GLUquadricObj* quadro = gluNewQuadric();                            
    gluQuadricNormals(quadro, GLU_SMOOTH);      
    gluQuadricTexture(quadro, GL_TRUE);         
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glPushMatrix();
                glRotatef( -90.0, 1.0, 0.0, 0.0 );
                gluSphere(quadro, SUN_RADIUS, 48, 48);
            glPopMatrix();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quadro);
}

//Given parameters about the planets dimension, orbit, radius etc, this function is used to draw everything except the sun, earth/moon. and saturns rings, as they are special cases of this function
void drawPlanet(GLfloat inclination, GLfloat orbitDuration,
        GLfloat orbitRadius, GLfloat rotationDuration, GLfloat radius, float r, float g, float b) {
    GLUquadricObj* quadro = gluNewQuadric();
    gluQuadricNormals(quadro, GLU_SMOOTH);
    glColor3f(r,g,b);
    glEnable(GL_TEXTURE_2D);
        glPushMatrix();
            glPushMatrix();
                glRotatef( inclination, 0.0, 0.0, 1.0);
                glRotatef( 360.0 * (EarthDaysTranspired/orbitDuration), 0.0, 1.0, 0.0);
                glTranslatef(orbitRadius, 0.0, 0.0 );
                glRotatef( 360.0 * (CurrentEarthRotation/rotationDuration), 0.0, 1.0, 0.0 );
                glRotatef( -90.0, 1.0, 0.0, 0.0 );
                gluSphere(quadro, radius, 48, 48);
            glPopMatrix();
        glPopMatrix();
    gluDeleteQuadric(quadro);
}