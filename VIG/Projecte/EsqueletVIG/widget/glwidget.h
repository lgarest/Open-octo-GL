#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFileDialog>
#include "point.h"
#include "scene.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);

protected:
    void initializeGL ();

    void paintGL ();
    void resizeGL (int width, int height);
    
    void camaraDefecte();

    virtual void mousePressEvent (QMouseEvent *e);
    virtual void mouseReleaseEvent (QMouseEvent *e);
    virtual void mouseMoveEvent (QMouseEvent *e);
    virtual void keyPressEvent (QKeyEvent *event);

    double dist, anterior, posterior, radi, angleX, angleY, anglecam, ra, fov, near, far;
    Point VRP, OBS, UP,centre;
    Scene scene;

    typedef  enum {NONE, ROTATE, ZOOM, PAN, MOV} InteractiveAction;
    InteractiveAction DoingInteractive;

    int   xClick, yClick;
    bool enMoviment, ortho;
    
    
    double  left, right, bottom, up; 
    
    bool bla, select;


    int current, tabMat, llumAct, llumAltres;
    
    Point multVectorial(Point a, Point b);
    
    struct llum {
    	GLfloat pos[4];
	float colorRGB[3];
	bool enabled;
	int numObj;
    }; llum llums[8];
    
    std::vector<int> selected;
    
 public slots:
     void LoadObject ();
     void resetCamara();
     void PolygonLine(bool b);
     void PolygonFill(bool b);
     void Ortho(bool b);

	void CanviMaterialR(int val);
	void CanviMaterialG(int val);
	void CanviMaterialB(int val);

	void CanviShininess(int s);
	void TabActual(QString s);
	
	void CanviLlumR(int val);
	void CanviLlumG(int val);
	void CanviLlumB(int val);
	
	void CanviLlumColor();
	void CanviLlumPos(int val);
	
	void ActivarDesactivarLlums(bool b);
	void ActivarDesactivarPartsAmagades(bool b);
	void inicializacionBarrasMat();
	
	void LoadCub();
	void LoadDoor();
	void LoadPrisma();
	void LoadPyramid();
	void LoadWindow();
	void LoadPeces(QString s, Point pos, float scale);
	void LoadModels();
	void guardaModel(QString model);
	
	void totOpac();
	void setTransparent();
	void Save();
	void iniLlums();
	void LlumSeleccionada(QString s);
	void LoadCubLlum();
	void CancelMaterial();
	void Scale(int s);
	
 signals:
 	void inicializacionBarrasMatDR(int k); 
	void inicializacionBarrasMatSR(int k);
	void inicializacionBarrasMatAR(int k);
	
	void inicializacionBarrasMatDG(int k); 
	void inicializacionBarrasMatSG(int k);
	void inicializacionBarrasMatAG(int k);
	
	void inicializacionBarrasMatDB(int k); 
	void inicializacionBarrasMatSB(int k);
	void inicializacionBarrasMatAB(int k);
	
	void inicializacionBarrasMatShi(int k);
	
	void inicializacionBarrasLlumR(int k); 
	void inicializacionBarrasLlumG(int k);
	void inicializacionBarrasLlumB(int k);
	
	void inicializacioActDes(bool b);
	
};
#endif
