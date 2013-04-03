#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

struct V_Coords{
    int x;
    int y;
    int z;
};

V_Coords v1, v2, v3;
bool tmode, fmode;
int w_width, w_height;
double last_x, last_y;
int click_counter;
// double r,g,b,a;
// r = g = b = a = 0.0;

void refresh(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
    glutSwapBuffers();
}

void resize(int w, int h){
    w_width = w;
    w_height = h;
    if (w > h)
        glViewport(w/2-h/2, 0, h, h);
    else
        glViewport(0, h/2-w/2, w, w);
}

void keyboardeventhandler(unsigned char key, int x, int y){
    if (key == 't') {
        tmode = !tmode;
        fmode = false;
    }
    else if (key == 'f') {
        fmode = !fmode;
        tmode = false;
    }
    else if (key == 27){
        exit (0);
    }
    else if (key=='h'){
        cout << "help" << endl;
    }
}

void mouseeventhandler(int button, int event, int x, int y){
    if (tmode and button == GLUT_LEFT_BUTTON and event = GLUT_DOWN){
        // coger tres puntos
        ++click_counter;
    }
    else if (fmode){
        // colores
    }
}

void mousedrageventhandler(int x, int y){

}

int main(int argc, char const *argv[]){
    tmode = fmode = false;
    v1.x=1/2.0;
    v1.y=-1/3.0;
    v1.z=0;
    v2.x=-1.0/2.0;
    v2.y=-1.0/3.0;
    v2.z=0;
    v3.x=0;
    v3.y=2.0/3.0;
    v3.z=0;
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutCreateWindow("IDI:_Lab_1");

    // this function manages the display through the refresh func
    glutDisplayFunc(refresh);

    // this function manages the resize through the refresh func
    glutReshapeFunc(resize);

    glutMouseFunc(mouseeventhandler);
    glutMotionFunc(mousedrageventhandler);

    // // this function manages the keyboard input
    glutKeyboardFunc(keyboardeventhandler);
    glutMainLoop();
    return 0;
}




// #include <GL/gl.h>
// #include <GL/freeglut.h>
// #include <iostream>
// using namespace std;
// int anteriorX=-1;
// int anteriorY=-1;
// double r=0;
// double g=0;
// double b=0;
// double a=0;
// int contador=0;
// bool activaT=false;
// bool activaF=false;
// int anchura;
// int altura;
// float v1, v2, v3, v4, v5, v6, v7, v8, v9;
// void refresh(void)
// {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glBegin(GL_TRIANGLES);
//     glVertex3f(v1, v2, v3);
//     glVertex3f(v4, v5, v6);
//     glVertex3f(v7, v8, v9);
//     glEnd();
//     glutSwapBuffers();
// }
// void resize(int width, int height) {
//     anchura=width;
//     altura=height;
//     if (width > height) {
//         glViewport(width/2-height/2, 0, height, height);
//     }
//     else {
//         glViewport(0, height/2-width/2, width, width);
//     }
// }
// void ratonsimple(int button, int state, int x, int y) {
//     if (state == GLUT_DOWN) {
//         if(activaT) {
//             float xAux = x/(anchura/2.0)-1.0;
//             float yAux = (altura-(float)y)/(altura/2.0)-1.0;
//             cout << xAux << " "<< yAux << endl;
//             if (contador==0) {
//                 v1=xAux;
//                 v2=yAux;
//                 v3=0;
//                 contador++;
//             }
//             else if(contador==1) {
//                 v4=xAux;
//                 v5=yAux;
//                 v6=0;
//                 contador++;
//             }
//             else if(contador==2) {
//                 v7=xAux;
//                 v8=yAux;
//                 v9=0;
//                 contador=0;
//                 activaT=false;
//                 glutPostRedisplay();
//             }   
//         }
//     }
// }
// void ratonarrastrar(int x, int y) {
//     if(activaF and not activaT) {
//         if (x>anteriorX) {
//             if(a<1) a+=0.001;
//             if(g>0) g-=0.001;
//         }
//         if(x<anteriorX) {
//             if(g<1) g+=0.001;
//             if(a>0) a-=0.001;
//         }
//         if(y>anteriorY) {
//             if(b<1) b+=0.001;
//             if(r>0) r-=0.001;
//         }
//         if(y<anteriorY) {
//             if(r<1) r+=0.001;
//             if(b>0) b-=0.001;
//         }
//         glClearColor(r, g, b, a);
//         anteriorX=x;
//         anteriorY=y;
//         glutPostRedisplay();
//     }
// }
// void teclado(unsigned char tecla, int x, int y) {
//     switch(tecla) {
//         case 27: //escape
//             exit(0);
//             break;
//         case 'h':
//             cout << "help" << endl;
//             cout << "apretando t activas modo insertar nuevo triangulo" << endl;
//             cout << "tendras que hacer click 3 veces en la pantalla para capturar los 3 vertices nuevos "<<endl;
//             cout << "apretando f activas o desactivas modo color" << endl;
//             cout << "Arrastra el raton para cambiar color" << endl;
//             cout << "derecha +alpha - verde y viceversa con izquierda" <<endl;
//             cout << "abajo +azul -rojo y viceversa con arriba" << endl;
//             cout << "modo color desahibilitado momentaneamente mientras modo triangulo este activado" << endl;
            
//             break;
//         case 't':
//                 activaT = true;
//             break;
//         case 'f':
//                 activaF=not activaF;
//     }
// }
// int main(int argc, const char *argv[]) {
//     v1=1/2.0;
//     v2=-1/3.0;
//     v3=0;
//     v4=-1/2.0;
//     v5=-1/3.0;
//     v6=0;
//     v7=0;
//     v8=2/3.0;
//     v9=0;
//     glutInit(&argc, (char**)argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//     glutInitWindowSize(600, 600);
//     glutCreateWindow("IDI:Practiques OpenGl");
//     glutDisplayFunc(refresh);
//     glutReshapeFunc(resize);
//     glutMouseFunc(ratonsimple);
//     glutMotionFunc(ratonarrastrar);
//     glutKeyboardFunc(teclado);
//     glutMainLoop();
//     return 0;
// }