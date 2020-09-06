#include "../STL/BinTree.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
int main(){
    BinTree<int> tree;
    tree.insertAsRoot(1);
    tree.insertAsLC(tree.root(), 2);
    tree.insertAsRC(tree.root(), 3);
    tree.insertAsLC(tree.root()->lc, 4);
    cout << tree.root()->height << endl;
    cout << tree.size() << endl;
    // tree.remove(tree.root()->rc);
    BinTree<int>* t = tree.secede(tree.root()->lc);
    cout << tree.root()->height << endl;
    cout << tree.size() << endl;

    tree.attachAsLC(tree.root(), t);

    cout << tree.root()->height << endl;
    cout << tree.size() << endl;
    cout << tree.root()->lc->lc->data << endl;
    system("pause");
}