#ifndef QT_HPP
#define QT_HPP


#include <stdio.h> // Libreria estandar input output c/c++;
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <list>
#include <vector>
#include <stdlib.h>
#include <windows.h> //Libreria ecesaria para la visualizacion en windows se recomienda modificar hpp segun os;
#include <conio.h>
using namespace std;

unsigned int HEIGH = 22; // alto del rectangulo a imprimir en consola;
unsigned int WIDTH = 80; // ancho del rectangulo a imprimir en consola;
/* FUNCION gotoxy para windows, cumple la funcion de imprimir en pantalla lo que se desee por medio de coordenadas digitadas por el usuario */


void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
};


/* IMPLEMENTACION: gotoxy(x,y); print("%c", ascii); */

// Se crea el rectangulo donde funcionara el QuadTree;
class Rectan{
private:
    float ancho;
    float altura;
    int x;
    int y;

    void limites();
public:
    Rectan() : x(WIDTH), y(HEIGH), altura(HEIGH), ancho(WIDTH){}; //constructor de la clase rectangulo puesto en una consola "perfecta" de 80x22
    Rectan(int alt, int anch): altura(alt), ancho(anch){};
    Rectan(int x, int y, int alt, int anch ): x(x), y(y), altura(alt), ancho(anch){};
    int getWidth(){return ancho;}
    int getHeight(){return altura;}
    int get_X(){return x;}
    int get_Y(){return y;}
    //~Rectan();

    friend bool operator==(Rectan A, Rectan B);
};

bool operator==(Rectan A, Rectan B){
    if(A.get_X() == B.get_X() && A.get_Y() == B.get_Y() && A.getHeight() == B.getHeight() && A.getWidth() == B.getWidth()){
        return 1;
    }else{
        return 0;
    }
}

// Se crea el nodo con el cual va a funcionar el Quad Tree;
class QuadTree{
private:
  Rectan *node;
  int node_capa;
  int count;
  bool subdividirint;
  Rectan area; // Rectangulo que contiene el area que revisa el QT 
  QuadTree *root;

  vector<Rectan> array;
  vector<Rectan>::iterator it;

  QuadTree *NW; // apuntadores a arboles //Cuadraate 0
  QuadTree *NE; // apuntadores a arboles //Cuadraate 1
  QuadTree *SW; // apuntadores a arboles //Cuadraate 2
  QuadTree *SE; // apuntadores a arboles //Cuadraate 3

  
  int getIndex(Rectan objeto);
  void subdividir();

  vector<Rectan> hay_colision();

  bool contains(Rectan objeto);  // metodo para saber si un objeto esta contenido en el arreglo    int getIndex(Rectan objeto); // metodo para saber en que cuadrante se encuentra el objeto
  void ver_point();
  

public:
  /* Constructor del Quad Tree */
  QuadTree();
  QuadTree(Rectan pkey);
  ~QuadTree();
  //void subdividir(); // metodo para subdividir
  //int getIndex(Rectan objeto);

  bool insertObj(Rectan objeto); // metodo que inserta objetos
  void limpiar_objetos();
  
  void vector_(); // metodo para ver los objetos insertados
  void print_Rec();
  void ver_colision();
};

// Constructor
QuadTree::QuadTree(){
  node_capa = 4;
  count = 0;
  node = new Rectan[node_capa];
  //array = new Rectan[node_capa];
  Rectan area(); // Rectangulo que contiene el area que revisa el QT 
  root = nullptr;
  NW = nullptr;
  NE = nullptr;
  SE = nullptr;
  SW = nullptr;
} 

// Constructor
QuadTree::QuadTree(Rectan pArea) {
  node_capa = 4;
  //array = new Rectan[node_capa];
  node = new Rectan[node_capa];
  Rectan area = pArea;
  root = nullptr;
  NW = nullptr;
  NE = nullptr;
  SE = nullptr;
  SW = nullptr;
}

QuadTree::~QuadTree(){
  if(this->root != nullptr) delete this->root;
  if(this->NW != nullptr) delete this->NW;
  if(this->NE != nullptr) delete this->NE;
  if(this->SE != nullptr) delete this->SE;
  if(this->SW != nullptr) delete this->SW;

  delete[] node;
}
void QuadTree::subdividir(){
  this->subdividirint ==  true;

  this->NW = new QuadTree(Rectan(area.getHeight()/2, area.getWidth()));
  this->NE = new QuadTree(Rectan(area.getHeight()/2, area.getWidth()/2));
  this->SE = new QuadTree(Rectan(area.getHeight(), area.getWidth()/2));
  this->SW = new QuadTree(Rectan(area.getHeight(), area.getWidth()));
}

int QuadTree::getIndex(Rectan objeto){
  int index;

  int pntmid_v = area.getHeight()/2; // Punto medio en Y
  int pntmid_h = area.getWidth()/2;  // Punto medio en X 

  if(objeto.get_X() < pntmid_h){
    if(objeto.get_Y() < pntmid_v){
      index = 1;
    }else{//objeto.get_Y() > pntmid_v
      index = 2;
    }
  }else{ // objeto.get_X() > pntmid_h;
    if(objeto.get_Y() < pntmid_v){
      index = 0;
    }else{ // objeto.get_Y() > pntmid_h;
      index = 3;
    }
  }

  return index;
}

vector<Rectan> QuadTree::hay_colision(){
  vector<Rectan> colisiones;
  int Witdth = area.getWidth();
  int Heigh = area.getHeight();
  vector<Rectan> tmp;
  tmp = array;
  for (int i = 0; i < tmp.size(); i++){
    Rectan uno = tmp[i];
    int Witdth = uno.getWidth();
    int Heigh = uno.getHeight();
    int x = uno.get_X();
    int y = uno.get_Y();
    for (int i = 1; i < tmp.size(); i++){
      Rectan dos = tmp[i];
      int Witdth2 = dos.getWidth();
      int Heigh2 = dos.getHeight();
      int xx = dos.get_X();
      int yy = dos.get_Y();
      if ((Witdth/2+ Witdth2/2) > (xx+x)){
        vector<Rectan> ayuda = {uno,dos};
        colisiones = ayuda;
      }
      else if ((Heigh/2+ Heigh2/2) > (yy+y)){
        vector<Rectan> ayuda2 = {uno,dos};
        colisiones  = ayuda2;
      }
    }
  }
  return colisiones;
}

void QuadTree::ver_colision(){
  vector<Rectan> tmp;
  tmp = hay_colision();
  for(int i = 0; i < tmp.size(); i++){
    gotoxy(tmp[i].get_X(), tmp[i].get_Y()+4); printf("c", 178);
  }
}

bool QuadTree::contains(Rectan objeto){
  it = find (array.begin(), array.end(), objeto);
  return(it != array.end())?true:false;
}

// Se inserta un objeto en el arreglo
bool QuadTree::insertObj(Rectan objeto){
  //cout << "e" << endl;
  if(contains(objeto)){return false;}
  //cout << "n" << endl;
  if(this->NW == nullptr){this->subdividir();}
  //cout << "t" << endl;
  if(this->count < this->node_capa && this->NW != nullptr){
    array.push_back(objeto);
    this->node[this->count++] = objeto;
    return true;
  }
  //cout << "r" << endl;
  if(this->NW->insertObj(objeto)){/*cout << "cuadrante 1" << endl;*/ return true;}
  //cout << "a" << endl;
  if(this->NE->insertObj(objeto)){/*cout << "cuadrante 2" << endl;*/ return true;}
  //cout << "n" << endl;
  if(this->SE->insertObj(objeto)){/*cout << "cuadrante 3" << endl;*/ return true;}
  //cout << "d" << endl;
  if(this->SW->insertObj(objeto)){/*cout << "cuadrante 4" << endl;*/ return true;}
  //cout << "o" << endl;
  return false;
}

 
void QuadTree::vector_(){
  for(int i = 0; i < array.size(); i++){
    cout << array[i].get_X() << ", " << array[i].get_Y() << endl;
  }
  /*cout << "NW" << endl;*/ this->NW->vector_();
  /*cout << "NE" << endl;*/ this->NE->vector_();
  /*cout << "SE" << endl;*/ this->SE->vector_();
  /*cout << "SW" << endl;*/ this->SW->vector_();
}


void QuadTree::ver_point(){
  for(int i = 0; i < array.size(); i++){
    gotoxy(array[i].get_X(),array[i].get_Y()+4); printf("%c", 254);
  }
}

void QuadTree::print_Rec(){
  cout << endl;
  cout << endl;
  cout << endl;
  int L = area.getWidth();
  int l = area.getHeight();
    
  // Impresion de los bordes del Quad Tree;
  for(int i = 1; i <= L; i++){
    gotoxy(i,4); printf("%c", 196); // Linea de arriba;
    gotoxy(i,l+4); printf("%c", 196); // Linea de abajo;
  }
  for(int i = 1; i <= l; i++){
    gotoxy(0,i+4); printf("%c", 179); // Linea de izq;
    gotoxy(L,i+4); printf("%c", 179); // Linea de der;
  }
  if(this->NW != nullptr){
    this->NW->print_Rec();
    this->NE->print_Rec();
    this->SE->print_Rec();
    this->SW->print_Rec();
  }

  // Se imprimen los puntos que generan colisiones
  if(this->subdividirint == true){
    // Impresion de las lineas intermedias;
    for(int i = 0; i<= L; i++){
      gotoxy(i,l/2+4); printf("%c", 196);
    }
    for(int i = 0; i<= l; i++){
      gotoxy(L/2,i+4); printf("%c", 179);
    }
    
    // Impresion de la posicion punto medio usando los valores de la consola;
    gotoxy(L/2, l/2+4); printf("%c",197); // Implementado para ser mas visual;
  }
  ver_point();

  gotoxy(0,l/2+4); printf("%c", 195);
  gotoxy(L,l/2+4); printf("%c", 180);
  gotoxy(L/2,0+4); printf("%c", 194);
  gotoxy(L/2,l+4); printf("%c", 193);
    
  gotoxy(0,0+4); printf("%c", 218); // Esquina superior izq;
  gotoxy(L,0+4); printf("%c", 191); // Esquina superior der;
  gotoxy(L,l+4); printf("%c", 217); // Esquina inferior der;
  gotoxy(0,l+4); printf("%c", 192); // Esquina inferior izq;
}

#endif