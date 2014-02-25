#ifndef _Scene_H_
#define _Scene_H_
#include "objecte.h"
#include "model.h"
#include <QtOpenGL/qgl.h>


class Scene
{
 private:
	
  // Tindrem un vector amb els models geomètrics dels objectes geomètrics
  // i un altre amb instàncies seves (instàncies o referències a objectes).
  std::vector<Model> lmodels;
  std::vector<Objecte> lobjectes;
  
  int current;
  
 public:
  static MaterialLib matlib;	  // col·lecció de materials

  Scene();

  void Init();
  void construirBase();
  void Render(std::vector<int> &selected );
  void AddModel(Model &);
  void AddObjecte(Objecte &);
  int getIdModel(const char* name);
  Model getModel(int id);
  void CalcularEsfera(double &radi, Point &centre);
  void changePos(char c, int inc, std::vector<int> &selected);
  void setPosOrigen(std::vector<int> &selected);
  void changeOri(char c, std::vector<int> &selected);
  bool foraDeBase(Point pos);
  Box & getBoxObj(int i);
  bool colisiona(std::vector<int> &selected);
  int sizeLObj();
  void RenderObj(int i, std::vector<int> &selected);
  void setCurrent(int curr);
  Point getPos(int c);
  void setPos(int c, Point pos);
  void setUltimaPosObj();
  void changeMaterial(float k, int dsa , int rgb, int obj);
  void initObjecte();
  Material& getMaterialObj();
  void borrarObj(std::vector<int> &selected);
  void totOpac();
  void setTransparent(int numObj);
  void Save();
  void setObjNumLlum(int num, int obj);
  void setMaterialObj(Material mat, std::vector<int> &selected);
  void setScaleObj(int o, float s);
  void setMaterialAnt(int o);
  void canviMaterialAnt(int o);
};

#endif

