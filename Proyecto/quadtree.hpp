#ifndef _QUADTREE_HPP
#define _QUADTREE_HPP

#include <stdio.h> // libreria estandar input output c/c++
#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdlib.h>
#include "conio.h" // necesario para visualizacion (no se encuentra en linux por esto mismo se anexa al los archivos del proyecto) 
using namespace std;

int INITIAL_CAPACITY = 5;//Capacidad inicial

//creamos un punto con coordenas x,y SIEMPRE van a ser enteros 
struct Point {
  int x;
  int y;
  Point():x(0), y(0){}//constructor
  Point(int cordenanda_x, int cordenanda_y):x(cordenanda_x),y(cordenanda_y){};
  
};

//crear el rectangulo donde funcionara el QuadTree
class rectan{
private:
  float c_x; //cordenanda x del rectangulo
  float c_y; //cordenanda y del rectangulo
  int altura; 
  int ancho;
public:
  rectan() : altura(22), ancho(80), c_x(12), c_y(41){};
  rectan(int alt, int anch): altura(alt), ancho(anch), c_x(anch/2), c_y(alt/2){};
  //rectan(int alt; int anch, float equis, float ye ){altura = alt; ancho = anch; c_x = equis; c_y = ye;}
  //~rectan();

  int get_altura(){return altura;}
  int get_ancho(){return ancho;}
  float get_x(){return c_x;}
  float get_y(){return c_y;}

  Point get_ubicacion(){return Point(c_x, c_y);}
  void print_rec(rectan a); //funcion que imprime un rectangulo
  void print_point();
};

//nodo con el cual va a funcionar el quadtree
template <typename T>
struct QuadNode{
  T key;
  QuadNode<T> *hijo;
  bool divided = false;
};

//creamos la clase quadtree
template <typename T>
class QuadTree{
private:
  QuadNode<T> *root;
  void insert_point(Point t);
  void subdivide();
public:
  QuadTree() : root(nullptr){};
  QuadTree(rectan perimetro, int capacidad);
  ~QuadTree();

  
};
template <typename T>
QuadTree<T>::QuadTree(rectan perimetroo, int capacidadd){
  root->perimetro = perimetroo;
  root->capacidad = capacidadd;
}

//funcion que inserta puntos a los nodos segun la cantidad, si ya paso la cantidad establecida se subdivide en 4
template <typename T>
void QuadTree<T>::insert_point(Point t){
  if(root->puntos.size() < root->capacidad){
    root->puntos.push_back(t);
  }else{
    if (!root.divided){
      //subdivide();
      root.divided = true;
    }
    root->hijo.insert(t);
  }
}

//funcion que imprime un cuadrado
void rectan::print_rec(rectan a){
  for(int i = 1; i <= a.ancho; i++){
    gotoxy(i,0); printf("%c", 196);
    gotoxy(i,22); printf("%c", 196);
  }
  for(int i=1; i <= a.altura; i++){
    gotoxy(0,i); printf("%c", 179);
    gotoxy(80,i); printf("%c", 179);
  }
  for(int i=1; i <=a.ancho; i++){
    gotoxy(11,i); printf("%c", 196);
  }
  for(int i=1; i <=a.altura; i++){
    gotoxy(i,44); printf("%c", 179);
  }

  gotoxy(0,0);   printf("%c", 218);
  gotoxy(80,0);  printf("%c", 191);
  gotoxy(0,22);  printf("%c", 192);
  gotoxy(80,22); printf("%c", 217);

  //posicion "(0,0)"

  //gotoxy(40,11); printf("%c",197); // DE MOMENTO NO 
  

}


#endif
