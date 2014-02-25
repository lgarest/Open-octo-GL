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

static void RenderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");
    glutDisplayFunc(RenderSceneCB);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();
    return 0;
}