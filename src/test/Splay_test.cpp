#include "../STL/Splay.h"
#include<iostream>
#include<stdlib.h>
int main(){
    Splay<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);

    s.root()->travPre(print);
    cout << endl;
    s.root()->travIn(print);
    cout << endl;
    s.root()->travPost(print);
    cout << endl;

    s.search(2);
    s.root()->travPre(print);
    cout << endl;
    s.root()->travIn(print);
    cout << endl;
    s.root()->travPost(print);
    cout << endl;

    s.search(3);
    s.root()->travPre(print);
    cout << endl;
    s.root()->travIn(print);
    cout << endl;
    s.root()->travPost(print);
    cout << endl;

    s.remove(4);
    s.root()->travPre(print);
    cout << endl;
    s.root()->travIn(print);
    cout << endl;
    s.root()->travPost(print);
    cout << endl;

    system("pause");
}