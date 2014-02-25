#include "scene.h"
#include <math.h>
#include <fstream>

MaterialLib Scene::matlib;

Scene::Scene()
{}

void Scene::Init()
{
  current =-1;
  construirBase ();
}

void Scene::construirBase ()
{
  Model b("Base");

  // Construim el poligon base
  Vertex v1(Point(-5,0,-5));
  Vertex v2(Point(-5,0,5));
  Vertex v3(Point(5,0,5));
  Vertex v4(Point(5,0,-5));
  b.vertices.push_back(v1);
  b.vertices.push_back(v2);
  b.vertices.push_back(v3);
  b.vertices.push_back(v4);

  Face face(0,1,2,3);
  face.normal = Vector(0,1,0);
  face.material = 0;
  b.faces.push_back(face);

  AddModel(b);
  Objecte oref("Base", 0, Point(0,0,0), 1, 0);
  AddObjecte(oref);
}

void Scene::Render(std::vector<int> &selected)
{
  // Cal pintar tots els objectes de l'escena que es troben al vector

    for(int i = 0; i < lobjectes.size(); ++i){
    	lobjectes[i].calcularMatriuTrans(lmodels);
	
	int k = -1;
	for(int j = 0; j < selected.size(); ++j){
		
		if(selected[j] == i) k = i;
		
	}
        lobjectes[i].Render(lmodels, k, -1);
	
    }
    

}

void Scene::AddModel(Model &o)
{
  lmodels.push_back(o);
  //calcular les normals de les cares del model quan es guarda un de nou
  /*o.computeNormals();*/
}

void Scene::AddObjecte(Objecte &oref)
{
  lobjectes.push_back(oref);
}

int Scene::getIdModel(const char* name){

    for(unsigned int i = 0; i < lmodels.size(); ++i){
        if(lmodels[i].getName() == name) return i;
    }
    return -1;

}

Model Scene::getModel(int id){
        return lmodels[id];
}

Box& Scene::getBoxObj(int i){
        lobjectes[i].calcularMatriuTrans(lmodels);
        lmodels[1].calculaTransformedBox();
        
        return lobjectes[i].getBox();
}

void Scene::CalcularEsfera(double &radi, Point &centre){
	Box sceneBox(Point (0.0, 0.0, 0.0), Point (0.0, 0.0, 0.0));
	Box objBox;
	for(unsigned int i = 0; i < lobjectes.size(); ++i){
        lobjectes[i].calcularMatriuTrans(lmodels);
		objBox=lobjectes[i].getBox();
		sceneBox.update(objBox.maxb);
		sceneBox.update(objBox.minb); 		
	}
	centre=(sceneBox.minb + sceneBox.maxb)/2;
  	radi=(sceneBox.maxb - sceneBox.minb).length()/2;
}

void Scene::changePos(char c, int inc, std::vector<int> &selected){
	for(int i = 0; i < selected.size(); ++i){
		Point pos=lobjectes[selected[i]].getPosition();
		if(c=='x') pos.x+=inc;
		else pos.z+=inc;
		if(!foraDeBase(pos)){
			lobjectes[selected[i]].setPosition(pos);
		}
	}	
}

void Scene::setPosOrigen(std::vector<int> &selected){
	for(int i = 0; i < selected.size(); ++i){
		lobjectes[selected[i]].setPosition(lobjectes[selected[i]].getUltimaPos());
	}
}

bool Scene::foraDeBase(Point pos){
	Box bbox = lobjectes[0].getBox();
				
	if(pos.x-0.5 > bbox.minb.x and pos.z-0.5 > bbox.minb.z and 
		pos.x+0.5 < bbox.maxb.x and pos.z+0.5 < bbox.maxb.z){
		return 0;	
	}
	return 1;
}

void Scene::changeOri(char c, std::vector<int> &selected){
	for(int i = 0; i < selected.size(); ++i){
		float ori=lobjectes[selected[i]].getOrientation();
		if(c=='d') ori++;
		else ori--;
		lobjectes[selected[i]].setOrientation(ori);
	}
}

bool Scene::colisiona(std::vector<int> &selected){

    
    for(int j = 0; j < selected.size(); ++j){
    	for(unsigned int i = 1; i < lobjectes.size()-1; ++i){
    		if (selected[j] != i){
			Box bcmp = lobjectes[selected[j]].getBox();
			
        		Box b = lobjectes[i].getBox();
        		if(bcmp.maxb.x <= b.minb.x || bcmp.maxb.z <= b.minb.z||bcmp.minb.x >= b.maxb.x || bcmp.minb.z >= b.maxb.z
			|| bcmp.maxb.y <= b.minb.y|| bcmp.minb.y >= b.maxb.y);
    			else{
		
				Point posc = lobjectes[selected[j]].getPosition();
				posc.y += b.maxb.y-b.minb.y; 
				lobjectes[selected[j]].setPosition(posc);
				lobjectes[selected[j]].calcularMatriuTrans(lmodels);
				colisiona(selected);
			}
		}
    	}
    return false;
    }
}

int Scene::sizeLObj(){
	return lobjectes.size();
}
void Scene::RenderObj(int i, std::vector<int> &selected){
	lobjectes[i].Render(lmodels, -1, i);
}

void Scene::setCurrent(int curr){
	current = curr;
}

Point Scene::getPos(int c){
	return lobjectes[c].getPosition();
}
void Scene::setPos(int c, Point pos){
	lobjectes[c].setPosition(pos);
}

void Scene::setUltimaPosObj(){
	lobjectes[current].setUltimaPos(lobjectes[current].getPosition());
}
void Scene::changeMaterial(float k, int dsa , int rgb, int obj){
	lobjectes[obj].setMaterial(k, dsa, rgb);
}
void Scene::initObjecte(){
	lobjectes[current].setMaterialObj(lmodels[lobjectes[current].getModelId()].getMaterial());
	lobjectes[current].setNumLlum(-1);
}
void Scene::setMaterialObj(Material mat, std::vector<int> &selected){
	lobjectes[current].setMaterialObj(mat);
}
Material& Scene::getMaterialObj(){
	return lobjectes[current].getMaterial();
}

void Scene:: borrarObj(std::vector<int> &selected){
	for(int i = selected.size() - 1; i >= 0; --i){

		lobjectes[selected[i]] = lobjectes[lobjectes.size() - 1];
		selected.pop_back();
		lobjectes.pop_back();
	}
}

void Scene::totOpac(){
	for(int i = 0; i < lobjectes.size(); ++i) lobjectes[i].setTransp(1);
}
void Scene::setTransparent(int numObj){
	lobjectes[numObj].setTransp(0.5);
}

void Scene::Save(){
	/*cout << "save" << endl;
	char *cObj;
	char *cMod;
	ofstream file;
	file.open("fitch.txt", ofstream::out);
	cadena_lobj_lmod(cObj, cMod);
	file << cObj << endl;
	file << cMod << endl;
	file.close();*/
}
void Scene::setObjNumLlum(int num, int obj){
	lobjectes[obj].setNumLlum(num);
}

void Scene::setScaleObj(int o, float s){
	lobjectes[o].setScale(s);
}

void Scene::setMaterialAnt(int o){
	lobjectes[o].setMaterialAnt(getMaterialObj());
}
void Scene::canviMaterialAnt(int o){
	lobjectes[o].setMaterialObj(lobjectes[o].getMaterialAnt());
}
