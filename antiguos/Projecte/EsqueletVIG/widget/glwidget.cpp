#include "glwidget.h"
#include <math.h>
#include <iostream>

//#include "../formMaterials/formMaterials.h"
using namespace std;

const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void GLWidget::initializeGL()
{
  glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  
  
  scene.Init();
  
  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  camaraDefecte();
  
  enMoviment = false;
  ortho = false;
  bla = false;
  select = false;
  current =-1;
  tabMat = 0;
  iniLlums();
  LoadModels();
  
  
  for(unsigned int i = 0; i < selected.size(); ++i){
  	selected.pop_back();
  }
  

  
  llumAltres = 2;
  
}

void GLWidget::iniLlums(){

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  llumAct = 0;
  llums[0].enabled=true;
  llums[1].enabled=true;
  for(int i = 0; i < 8; ++i){
  	llums[i].colorRGB[RED] = 1;
  	llums[i].colorRGB[GREEN] = 1;
  	llums[i].colorRGB[BLUE] = 1;
	llums[i].numObj != -1;
  }
  llums[0].pos[0]= 0;
  llums[0].pos[1]=25;
  llums[0].pos[2]=0;
  llums[0].pos[3]=1;
  
  llums[1].pos[0]=0;
  llums[1].pos[1]=0;
  llums[1].pos[2]=0;
  llums[1].pos[3]=1;
  for(int i = 1; i < 8; ++i){
 
  	glLightfv(GL_LIGHT0 + i, GL_AMBIENT, llums[i].colorRGB);
  	glLightfv(GL_LIGHT0 + i, GL_SPECULAR, llums[i].colorRGB);
  	glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, llums[i].colorRGB);
  }

  for(int i = 2; i < 8; ++i){
  	llums[i].enabled = false;
  	llums[i].pos[0]=0;
  	llums[i].pos[1]=5;
  	llums[i].pos[2]=0;
  	llums[i].pos[3]=1;
  }
}

void GLWidget::resizeGL (int width, int height)
{

  glViewport (0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float rav =(float)width/height;
  double degArad = M_PI/180;
  double radAdeg = 180/M_PI;
  if(rav < 1){
  	anglecam = 2*atan(tan((fov/2)*degArad)/rav)*radAdeg; 
  }
  else anglecam = asin(radi/(2*radi))/M_PI*180*2;

}

void GLWidget::paintGL( void )
{

  // Esborrem els buffers
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  scene.CalcularEsfera(radi, centre);

    if(!ortho){
        //Tipus de camera: perspectiva
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(anglecam, (float)width()/height(), anterior, posterior);
   	
	
	glLightfv(GL_LIGHT0, GL_POSITION, llums[0].pos);
	for(int i = 2; i < 8; ++i){
		glLightfv(GL_LIGHT0 + i, GL_POSITION, llums[i].pos);
	}
        //Posició i orientació de la càmera
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	llums[1].pos[0]=0;
  	llums[1].pos[1]=0;
  	llums[1].pos[2]=0;
	glLightfv(GL_LIGHT1, GL_POSITION, llums[1].pos);
        glTranslatef(0,0,-dist);
        glRotatef(0,0,0,1);
        glRotatef(angleX,1,0,0);
        glRotatef(angleY,0,1,0);
        glTranslatef(-VRP.x, -VRP.y, -VRP.z);
	
	
	
	if(select){

		int numObj = -1;
        	glEnable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
        	glClearColor(0, 0, 0, 0);
        	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        	for(int i = 1; i < scene.sizeLObj(); ++i){
        		scene.RenderObj(i,selected);
    		}
        	GLfloat res;
		glReadPixels(xClick, height()-yClick, 1,1, GL_RED, GL_FLOAT, &res);
        	if (res!=0){
			numObj = res*255;
		}
		
		current = numObj;
		bool esta = false;
		for(unsigned int i = 0; i < selected.size(); ++i){
			
			if(current == selected[i]) esta = true;
		}
		if(current != -1 and not esta and current != 0){
			selected.push_back(current);
			
			scene.setCurrent(current);
			inicializacionBarrasMat();
			enMoviment = true;
		}
		select = false;
		glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
		glEnable(GL_LIGHTING);
		if(current != -1)scene.setMaterialAnt(current);
		
        	updateGL();
        
	  }
	
    }
    else{
    	float w = (float)width()/2;
	
	float aspRel = (float)w/height();
	
	//Primera meitat
	
	glViewport(0, 0, w, height());
	
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-10*aspRel,10*aspRel,-10,10, -10, 10);
	
	glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(90,1,0,0);
	scene.Render(selected);
	
	// dibuixar eixos aplicacio
  	glDisable(GL_LIGHTING);
  	glBegin(GL_LINES);
  	glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
  	glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
  	glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
  	glEnd();
	glEnable(GL_LIGHTING);
	
	
	//Segona meitat
	
	glViewport(w, 0, w, height());
	
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-10*aspRel,10*aspRel,-10,10, -10, 10);
	scene.Render(selected);
	
	// dibuixar eixos aplicacio
  	glDisable(GL_LIGHTING);
  	glBegin(GL_LINES);
  	glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
  	glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
  	glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
  	glEnd();
	glEnable(GL_LIGHTING);
  
	if(!bla){
		bla = true; 
		resetCamara();
	} else bla = false;
	
	
    }
  // dibuixar eixos aplicacio
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
  glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
  glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
  glEnd();
  glEnable(GL_LIGHTING);
  scene.Render(selected);
  
}

void GLWidget::mousePressEvent( QMouseEvent *e)
{

  if(!ortho){
  xClick = e->x();
  yClick = e->y();
  if (e->button()&Qt::LeftButton &&  e->modifiers() &Qt::ShiftModifier)
  {
  	if (e->modifiers() &Qt::AltModifier){
		if(enMoviment)DoingInteractive = MOV;
	}
    	else DoingInteractive = ZOOM;
  }
  else if (e->button()&Qt::LeftButton &&
      !(e->modifiers()&(Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
  else if (e->button()&Qt::LeftButton &&  e->modifiers() &Qt::ShiftModifier)
  {
    DoingInteractive = ZOOM;
  }
  else if (e->button()&Qt::LeftButton &&  e->modifiers() &Qt::ControlModifier)
  {
      DoingInteractive = PAN;
  }
  else if (e->button()&Qt::RightButton){
  	while(scene.colisiona(selected)){};
		enMoviment = false;
		scene.setUltimaPosObj();
		current = -1;
		scene.setCurrent(current);
		int size = selected.size();
		for(int i = 0; i < size; ++i){
  			selected.pop_back();
  		}
	
  }
  else if (e->button()&Qt::MidButton){
  	select = true;
	
	updateGL();
  }
  }
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
  switch (e->key())
  {
    case Qt::Key_F:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        updateGL();
        break;
    case Qt::Key_S:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        updateGL();
        break;

    case Qt::Key_D:
        if(enMoviment)scene.changeOri('d', selected);
        updateGL();
        break;
    case Qt::Key_E:
        if(enMoviment)scene.changeOri('e',selected);
        updateGL();
        break;
    case Qt::Key_Escape:
    	if(current!=-1){
    		scene.setPosOrigen(selected);
		updateGL();
	}
    	break;
    case Qt::Key_Delete:
	current = -1;
	scene.borrarObj(selected);
	updateGL();
	
    	break;
    default: e->ignore();
  }

    if((e->modifiers() & Qt::ShiftModifier) && e->key() == Qt::Key_X){
        if(enMoviment)scene.changePos('x', 1, selected);
        updateGL();
    }
    else if ((e->modifiers() & Qt::ShiftModifier) && e->key() == Qt::Key_Z){
        if(enMoviment)scene.changePos('z', 1, selected);
        updateGL();
    }
    else if (e->key() == Qt::Key_X){
        if(enMoviment)scene.changePos('x', -1, selected);
        updateGL();
    }
    else if (e->key() == Qt::Key_Z){
        if(enMoviment)scene.changePos('z', -1, selected);
        updateGL();
    }
    
}

void GLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{

  // Aqui cal que es calculi i s'apliqui la rotacio, el zoom o el pan
  // com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotacio
    
    angleY+= (e->x()-xClick)*0.5;
    angleX+= (e->y()-yClick)*0.5;

  }
  else if (DoingInteractive == ZOOM)
  {
    
    	if(yClick > e->y()){
    		anglecam+= (e->y()-yClick)*0.7;
		if(anglecam <10) anglecam = 10;
	}	
    	else if(yClick < e->y()){
    		anglecam+= e->y()-yClick;
		if(anglecam >170) anglecam = 170;
	}
    

  }
  else if (DoingInteractive==PAN)
  {
    // Fem el pan

	float m[16];
	
	float incx = xClick - e->x();
	float incy = yClick - e->y();

	glGetFloatv(GL_MODELVIEW_MATRIX, m);

	Point xobs = Point(m[0], m[4], m[8]);
	Point yobs = Point(m[1], m[5], m[9]);
	VRP = VRP + (incx*xobs + -incy*yobs)*0.04;
	//VRP.y= 0;
  }	
  else if (DoingInteractive==MOV){
 
	float incx = xClick - e->x();
	float incy = yClick - e->y();
	
	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	Point xobs = Point(m[0], m[4], m[8]);
	Point yobs = Point(m[1], m[5], m[9]);
	Point n = Point(0,1,0);
	Point u =  multVectorial(n, xobs);

	Point v =  multVectorial(yobs, n);

	
	
	for(unsigned int i = 0; i < selected.size(); ++i){
		Point pos = scene.getPos(selected[i]);
		pos = pos + (-incx*v + incy*u)*0.05;
		if(!scene.foraDeBase(pos)){
			scene.setPos(selected[i], pos);
			if(llums[llumAct].numObj == selected[i]){
				llums[llumAct].pos[0] = pos.x;
				llums[llumAct].pos[1] = pos.y + 1;
				llums[llumAct].pos[2] = pos.z;
			}
		}
	}
  }
  xClick = e->x();
  yClick = e->y();

  updateGL();
}

Point GLWidget:: multVectorial(Point a, Point b){

	Point res = Point(((a.y *b.z) - (b.y*a.z)),-((a.x *b.z) - (b.x*a.z)),((a.x *b.y)-(b.x*a.y)));
	return res;
}



void GLWidget::LoadObject()
{

  	QString model = QFileDialog::getOpenFileName(this, tr("Open File"), "../data", tr("Objectes (*.obj)"));
  	if (model != "")
  	{

    	// AquÃ­ cal fer el codi per a carregar el model escollit
   	const char* nom = model.toLatin1();
   	Box box;
   	int idmod = scene.getIdModel(nom);
   	if(idmod==-1){
   		Model m(nom);
   		m.updateBoundingBox();
	
		m.readObj(nom, Scene::matlib);
		scene.AddModel(m);
		idmod = scene.getIdModel(model.toLatin1());
		//miro si és el primer model carregat HOMER
    		//if(idmod == 1)scene.homers();
		box = m.boundingBox();
   	}
   	else{
   		box = scene.getModel(idmod).boundingBox();
   	}

  
    	float sx = box.maxb.x - box.minb.x;
    	float sy = box.maxb.y - box.minb.y;
    	float sz = box.maxb.z - box.minb.z;
    
    	float escala;
    	if(sx > sz) escala = sx;
    	else escala = sz;
	
   	/*if(idmod != 1){*/Objecte oref(nom, idmod, Point(0,0,0), escala, 0);
   
        	scene.AddObjecte(oref);
        //}
   	enMoviment = true;
   	current = scene.sizeLObj()-1;
	scene.setCurrent(current);
	scene.setUltimaPosObj();
	scene.initObjecte();
	scene.setMaterialAnt(current);
	if(current != -1)inicializacionBarrasMat();
  	}
}

void GLWidget::camaraDefecte(){

  scene.CalcularEsfera(radi, centre);
  VRP = Point(centre.x,centre.y,centre.z);  
  dist = 2*radi;
  posterior = 3*radi;
  anterior = radi;
  fov = asin(radi/(2*radi))/M_PI*180*2;
  anglecam =fov;
  angleX = 15;
  angleY = -30;
}

void GLWidget::resetCamara(){

    camaraDefecte();
    resizeGL(width(), height());
    updateGL();
}

void GLWidget::PolygonLine(bool b){
	if(b){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		updateGL();
	}
}
void GLWidget::PolygonFill(bool b){
	if(b){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		updateGL();
	}
}

void GLWidget::Ortho(bool b){

    if(b)ortho = true;
    else{
    	ortho = false;
	resetCamara();
    }
    updateGL();
}





//MATERIALS

void GLWidget::CanviMaterialR(int val){

	for(unsigned int i = 0; i < selected.size(); ++i){
    		scene.changeMaterial((float)val/255, tabMat , 0, selected[i]);
    		updateGL();
	}
}
void GLWidget::CanviMaterialG(int val){ 

	for(unsigned int i = 0; i < selected.size(); ++i){
    		if(current != -1)scene.changeMaterial((float)val/255, tabMat , 1, selected[i]);
    		updateGL();
	}
}
void GLWidget::CanviMaterialB(int val){ 
	
	for(unsigned int i = 0; i < selected.size(); ++i){
    		if(current != -1)scene.changeMaterial((float)val/255, tabMat , 2, selected[i]);
    		updateGL();
	}
}

void GLWidget::CanviShininess(int s){

     if(current != -1)scene.changeMaterial(s, 3 , -1, current);
     updateGL();
}

void GLWidget::TabActual(QString s){
	tabMat = 0;

	if(s == "Diffuse"){
		tabMat = 0;
	}
	if(s == "Specular"){
		tabMat = 1;
		}
	if(s == "Ambient"){
		tabMat = 2;
	}

	
	if(s == "Llum 0") llumAct = 0;
	if(s == "Llum1") llumAct = 1;
	if(s == "Altres") llumAct = llumAltres;
}

//LLUMS
void GLWidget::CanviLlumR(int val){

	llums[llumAct].colorRGB[RED]=(float)val/255;
	CanviLlumColor();
}
void GLWidget::CanviLlumG(int val){ 
	llums[llumAct].colorRGB[BLUE]=(float)val/255;
	CanviLlumColor();
}
void GLWidget::CanviLlumB(int val){ 
	llums[llumAct].colorRGB[GREEN]=(float)val/255;
	CanviLlumColor();
}

void GLWidget::CanviLlumColor(){

	float ambi[3];
	ambi[0]=llums[llumAct].colorRGB[RED]*0.05;
	ambi[1]=llums[llumAct].colorRGB[GREEN]*0.05;
	ambi[2]=llums[llumAct].colorRGB[BLUE]*0.05;

	glLightfv(GL_LIGHT0 + llumAct, GL_AMBIENT, ambi);
    	glLightfv(GL_LIGHT0 + llumAct, GL_SPECULAR, llums[llumAct].colorRGB);
    	glLightfv(GL_LIGHT0 + llumAct, GL_DIFFUSE, llums[llumAct].colorRGB);
	
        updateGL();
}
void GLWidget::CanviLlumPos(int val){ 
	llums[llumAct].pos[0]=llums[llumAct].pos[0];
	llums[llumAct].pos[1]= val;
	llums[llumAct].pos[2]=llums[llumAct].pos[2];
	llums[llumAct].pos[3]=1;
	glLightfv(GL_LIGHT0 + llumAct, GL_POSITION, llums[llumAct].pos);
	Point p = scene.getPos(current);
	p.y = llums[llumAct].pos[1]-1;
	scene.setPos(current, p);
	updateGL();
}

void GLWidget::ActivarDesactivarLlums(bool b){

	if(b){

		if(llumAct >= 0 and llumAct < 8){
			 glEnable(GL_LIGHT0 + llumAct);
		}

		if(llumAct >=2 and llumAct < 8 and not llums[llumAct].enabled)LoadCubLlum();
		llums[llumAct].enabled = true;
	}
	else{

		if(llumAct >= 0 and llumAct < 8){
			 glDisable(GL_LIGHT0 +llumAct);

		}
	
	}
	updateGL();
}

void GLWidget::ActivarDesactivarPartsAmagades(bool b){

	if(b){
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}
	else{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}
	updateGL();
}

void GLWidget::inicializacionBarrasMat(){
	Material mat = scene.getMaterialObj();
	emit inicializacionBarrasMatDR(mat.kd.r); 
	emit inicializacionBarrasMatSR(mat.ks.r);
	emit inicializacionBarrasMatAR(mat.ka.r);
	
	emit inicializacionBarrasMatDG(mat.kd.g); 
	emit inicializacionBarrasMatSG(mat.ks.g);
	emit inicializacionBarrasMatAG(mat.ka.g);
	
	emit inicializacionBarrasMatDB(mat.kd.b); 
	emit inicializacionBarrasMatSB(mat.ks.b);
	emit inicializacionBarrasMatAB(mat.ka.b);
	
	emit inicializacionBarrasMatShi(mat.shininess);
}


void GLWidget::guardaModel(QString model){

	const char* nom = model.toLatin1();
   	Model m(nom);
   	m.updateBoundingBox();
	m.readObj(nom, Scene::matlib);
	scene.AddModel(m);	
}

void GLWidget::LoadModels(){

	QString model = "../models/cub.obj";
	guardaModel(model);
	model = "../models/door.obj";
	guardaModel(model);
	model = "../models/prisma.obj";
	guardaModel(model);
	model = "../models/pyramid.obj";
	guardaModel(model);
	model = "../models/window.obj";
	guardaModel(model);
}
void GLWidget::LoadCubLlum()
{

  QString model = "../models/cub.obj";
  LoadPeces(model, Point(llums[llumAct].pos[0], llums[llumAct].pos[1]-1,
  llums[llumAct].pos[2]), 3);
  llums[llumAct].numObj = scene.sizeLObj() - 1;
  scene.setObjNumLlum(llumAct, llums[llumAct].numObj);
} 
void GLWidget::LoadCub()
{
  	QString model = "../models/cub.obj";
	LoadPeces(model, Point(0,0,0), 1);
	
	updateGL();
}
void GLWidget::LoadDoor()
{
  	QString model = "../models/door.obj";
	LoadPeces(model, Point(0,0,0), 1);
	updateGL();
}
void GLWidget::LoadPrisma()
{
  	QString model = "../models/prisma.obj";
	LoadPeces(model, Point(0,0,0), 1);
	updateGL();
}
void GLWidget::LoadPyramid()
{
  	QString model = "../models/pyramid.obj";
	LoadPeces(model, Point(0,0,0), 1);
	updateGL();
}
void GLWidget::LoadWindow()
{
  	QString model = "../models/window.obj";
	LoadPeces(model, Point(0,0,0), 1);
	updateGL();
}

void GLWidget::LoadPeces(QString model, Point pos, float scale)
{

  	if (model != "")
  	{

    	// AquÃ­ cal fer el codi per a carregar el model escollit
   	const char* nom = model.toLatin1();
   	Box box;
   	int idmod = scene.getIdModel(nom);
   	if(idmod==-1){
   		Model m(nom);
   		m.updateBoundingBox();
	
		m.readObj(nom, Scene::matlib);
		scene.AddModel(m);
		idmod = scene.getIdModel(model.toLatin1());
		box = m.boundingBox();
   	}
   	else{
   		box = scene.getModel(idmod).boundingBox();
   	}

  
    	float sx = box.maxb.x - box.minb.x;
    	float sy = box.maxb.y - box.minb.y;
    	float sz = box.maxb.z - box.minb.z;
    
	
   	Objecte oref(nom, idmod, pos, scale, 0);
   
        	scene.AddObjecte(oref);
   	enMoviment = true;
   	current = scene.sizeLObj()-1;
	scene.setCurrent(current);
	selected.push_back(current);
	scene.setUltimaPosObj();
	scene.initObjecte();
	scene.setMaterialAnt(current);
	
	if(current != -1)inicializacionBarrasMat();
  	}
}

void GLWidget::totOpac(){
	scene.totOpac();
}

void GLWidget::setTransparent(){

	for(unsigned int i = 0; i < selected.size();++i){
		scene.setTransparent(selected[i]);
	}
	updateGL();
}

void GLWidget::Save(){
	scene.Save();
}
void GLWidget::LlumSeleccionada(QString s){

	if(s =="Llum2") llumAct = 2;
	else if(s =="Llum3") llumAct = 3;
	else if(s =="Llum4") llumAct = 4;
	else if(s =="Llum5") llumAct = 5;
	else if(s =="Llum6") llumAct = 6;
	else if(s =="Llum7") llumAct = 7;
	llumAltres=llumAct;

	
	emit inicializacionBarrasLlumR(llums[llumAct].colorRGB[RED]); 
	emit inicializacionBarrasLlumG(llums[llumAct].colorRGB[GREEN]);
	emit inicializacionBarrasLlumB(llums[llumAct].colorRGB[BLUE]);
	emit inicializacioActDes(llums[llumAct].enabled);
}

void GLWidget::CancelMaterial(){
	if(not selected.empty()){
		for(unsigned int i = 0; i < selected.size();++i){
			scene.canviMaterialAnt(selected[i]);
			updateGL();
		}
	}
}
void GLWidget::Scale(int s){
	for(unsigned int i = 0; i < selected.size(); ++i){
		scene.setScaleObj(selected[i],(float)1/s);
	}
	updateGL();
}
