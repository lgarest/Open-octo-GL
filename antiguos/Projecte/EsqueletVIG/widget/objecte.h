#ifndef _OBJECTE_H_
#define _OBJECTE_H_
#include <vector>
#include <stdio.h>
#include "point.h"
#include "model.h"
#include "box.h"


using namespace std;

class Objecte
{
 protected:
  std::string nom;
  int model;   // identificador del model
  Point pos;    // posicio sobre el terra
  float scale;	   // mida en unitats
  float orientation;  //orientació respecte Y
  float matrix[16]; //matriu de transformació
  Box boxO;
  Point ultimaPos;
  Material matObj;
  Material matAnt;
  int numLlum;
  
 public:
  Objecte(std::string nom, int idmod, Point p, float scl, float ori);
  ~Objecte(void);

  void Render(std::vector<Model> &, int selected , int colorFals);
  std::string getNom();
  int getModelId();
  Point getPosition();
  float getScale();
  void setScale(float s);
  float getOrientation();
  void setPosition(Point p);
  void setOrientation(float o);
  Box& getBox();
  void calcularMatriuTrans(std::vector<Model> &lmodels);
  void setUltimaPos(Point p);
  Point getUltimaPos();
  void setMaterialObj(const Material mat);
  void setMaterial(float k, int dsa, int rgb);
  Material& getMaterial();
  void setTransp(float t);
  void setNumLlum(int num);
  int getNumLlum();
  Material& getMaterialAnt();
  void setMaterialAnt(Material &m);
};

#endif
