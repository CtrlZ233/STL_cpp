#include "../STL/BST.h"

#include<iostream>
#include<stdlib.h>
int main(){
    BST<int> bst;
    bst.insert(2);
    bst.insert(1);
    
    bst.insert(6);
    bst.insert(3);
    bst.insert(7);
    bst.root()->travPre(print);
    cout << endl;
    bst.root()->travIn(print);
    cout << endl;
    bst.root()->travPost(print);
    cout << endl;
    bst.remove(6);
    bst.root()->travPre(print);
    cout << endl;
    bst.root()->travIn(print);
    cout << endl;
    bst.root()->travPost(print);

    system("pause");
}
