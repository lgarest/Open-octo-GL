#include "objecte.h"
#include "box.h"
#include <QtOpenGL/qgl.h>
#include "scene.h"

Objecte::Objecte(std::string n, int mod, Point p, float scl, float ori):
  nom(n), model(mod), pos(p), scale(scl), orientation(ori)
{}

Objecte::~Objecte(void)
{}

void Objecte::Render(std::vector<Model> &lmodels, int selected , int colorFals)
{
  // Cal pintar la geometria de l'objecte transformada de la forma adequada
  
  
  Model m=lmodels[this->model];
  
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glMultMatrixf(matrix);
  m.Render(colorFals, matObj);
  glPopMatrix();
	if(selected != -1){
  		glDisable(GL_LIGHTING);
  		boxO.Render();
		glEnable(GL_LIGHTING);
	}
  }



void Objecte::calcularMatriuTrans(std::vector<Model> &lmodels){

    //matrix[16];
    
    float sx, sy, sz;
    
    Model m=lmodels[this->model];
    m.updateBoundingBox();
    Box box=m.boundingBox();
  
    sx = box.maxb.x - box.minb.x;
    sy = box.maxb.y - box.minb.y;
    sz = box.maxb.z - box.minb.z;
    
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(orientation, 0, 1, 0);
    glScalef(1/scale, 1/scale, 1/scale);
    glTranslatef(-(box.maxb.x + box.minb.x)/2, -box.minb.y, -(box.maxb.z + box.minb.z)/2);
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    boxO=m.calculaTransformedBox();
    glPopMatrix();
}

std::string Objecte::getNom()
{
  return nom;
}

int Objecte::getModelId()
{
  return model;
}

Point Objecte::getPosition()
{
   return pos;
}

float Objecte::getScale()
{
   return scale;
}
void Objecte::setScale(float s){
	this->scale=s;
}

float Objecte::getOrientation()
{
   return orientation;
}
void Objecte::setPosition(Point p){
	this->pos=p;
}
void Objecte::setOrientation(float o){
	orientation=o;
}
Box& Objecte::getBox(){
    
	return boxO;
}

void Objecte::setUltimaPos(Point p){
	ultimaPos=p;
}
Point Objecte::getUltimaPos(){
	return ultimaPos;
}
void Objecte::setMaterialObj(const Material mat){
	this->matObj = mat;
}
void Objecte::setMaterial(float k, int dsa, int rgb){
	
	switch(dsa){
		case 0:
			switch(rgb){
				case 0:
					this->matObj.kd.r=k;
				break;
				case 1:
					this->matObj.kd.g=k;
				break;
				case 2:
					this->matObj.kd.b=k;
				break;
				default:
				break;
			}
		break;
		case 1:
			switch(rgb){
				case 0:
					this->matObj.ks.r=k;
				break;
				case 1:
					this->matObj.ks.g=k;
				break;
				case 2:
					this->matObj.ks.b=k;
				break;
				default:
				break;
			}
		break;
		case 2:
			switch(rgb){
				case 0:
					this->matObj.ka.r=k;
				break;
				case 1:
					this->matObj.ka.g=k;
				break;
				case 2:
					this->matObj.ka.b=k;
				break;
				default:
				break;
			}
		break;
		case 3:
			this->matObj.shininess=k;
		break;
		default:
		break;
	}
	
}

Material& Objecte::getMaterial(){
	return this->matObj;
}


void Objecte::setTransp(float t){
	this->matObj.kd.a = t;
	this->matObj.ks.a = t;
	this->matObj.ka.a = t;
}
void Objecte::setNumLlum(int num){
	this->numLlum = num;
}
int Objecte::getNumLlum(){
	return this->numLlum;
}


Material& Objecte::getMaterialAnt(){
	return this->matAnt;
}

void Objecte::setMaterialAnt(Material &m){
	this->matAnt=m;
}
