#include<iostream>
#include<stdlib.h>
#include "../STL/AVL.h"
int main(){
    AVL<int> avlt;
    avlt.insert(1);
    avlt.insert(2);
    avlt.insert(3);
    // avlt.insert(4);
    avlt.root()->travPre(print);
    cout << endl;
    avlt.root()->travIn(print);
    cout << endl;
    avlt.root()->travPost(print);
    cout << endl;
    system("pause");
}