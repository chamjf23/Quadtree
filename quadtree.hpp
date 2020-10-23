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
};

//nodo con el cual va a funcionar el quadtree
template <typename T>
struct QuadNode {
  Point pos;
  T data;
  QuadNode<T> *top_left;
  QuadNode<T> *close_left;
  QuadNode<T> *close_right;
  QuadNode<T> *top_right;
};

//crear el rectangulo donde funcionar el QuadTree
class rectan{
private:
  int altura;
  int ancho;
public:
  int get_altura();
  int get_ancho();
  rectan(){altura=10; int ancho=10;}
  void print_rec(rectan a);


};


//creamos la clase quadtree
template <typename T>
class QuadTree {
private:
  QuadNode<T> *root;
};


void rectan::print_rec(rectan a){
    for(int i=0; i<a.ancho;i++)
      cout<<"*";
   }



#endif
