#ifndef _QUADTREE_HPP
#define _QUADTREE_HPP
#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdlib.h>
using namespace std;


//creamos un punto con coordenas x,y
struct Point {
  int x;
  int y;
  Point(){x=0; y=0;}//constructor
  Point(int cordenanda_x, int cordenanda_y){x=cordenanda_x; y = cordenanda_y}
};

//nodo con el cual va a funcionar el quadtree
template <typename T>
struct QuadNode {
  rectan perimetro;
  int capacidad = 5;
  Point *puntos = new vector<Point>;
  bool divided = false;
  
};

//crear el rectangulo donde funcionara el QuadTree
class rectan{
private:
  float c_x;
  float c_y;
  int altura;
  int ancho;
public:
  int get_altura(){return altura;}
  int get_ancho(){return ancho;}
  Point get_ubicacion(){return Point(c_x, c_y);}
  rectan(){altura=200;  ancho=200; c_x = 100; c_y = 100}
  rectan(int alt; int anch){altura = alt; ancho = anch; c_x = anch/2; c_y = alt/2;}
  ~rectan();
  friend void print_rec(rectan a);
};


//creamos la clase quadtree
template <typename T>
class QuadTree {
private:
  QuadNode<T> *root;
  void insert_point(Point t);
  void subdivide();
public:
  QuadTree();
  QuadTree(rectan perimetro, int capacidad);
  ~QuadTree();

  
};




void QuadTree::insert_point(Point t){
  if (root->puntos.size() < root->capacidad)
  {
    root->puntos.push_back(t)
  }else{
    subdivide{
    }
  }
}


void rectan::print_rec(rectan a){
    for(int i=0; i<a.ancho;i++){
      cout<<"*";
    }
    for (int i=0; i<a.altura; i++){
      cout<<endl;
      if (i==0 || i == a.altura-1){
        cout<<'*';
      }
    }
    for (int i=0; i<a.ancho; i++){
      cout<<'*';
    }
    cout<<endl;
   }



#endif
