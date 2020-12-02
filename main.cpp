#include "quadtree.hpp"

int main(){
    QuadTree tree;

    Rectan A(55, 13, 3, 4);
    Rectan B(35, 13, 3, 4);
    Rectan C(1, 2, 3, 4);
    Rectan D(41, 1, 3, 4);
    Rectan E(45, 6, 3, 4);
    Rectan F(50, 10, 3, 4);
    Rectan G(43, 4, 3, 4);
    Rectan H(40, 2, 3, 4);
  
    tree.insertObj(A);
    tree.insertObj(B);
    tree.insertObj(C);
    tree.insertObj(D);
    
    tree.insertObj(E);
    tree.insertObj(F);
    tree.insertObj(G);

    tree.insertObj(H);

    
    //tree.vector();
    //tree.ver_point();
    tree.print_Rec();
    return 0;
}

