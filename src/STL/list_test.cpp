#include "list.h"
#include<stdlib.h>
using namespace std;
int main(){
    list<string> L = list<string>();
    L.push_front("zero");
    cout << "Is empty ?" << L.empty() << endl;
    L.push_back("one");
    
    L.push_back("two");
    cout << "Is empty ?" << L.empty() << endl;
    L.push_back("three");
    L.push_front("front");
    L.clear();
    L.push_back("one");
    list<string> L2 = L;  // some bugs
    cout << L.size() << endl;
    // cout << "hhh" <<endl;
    // cout<< L.start_node->obj << endl;
    
    list<string>::iterator a = L.begin();
    list<string>::iterator b = L.end();
    for(; a!=b; a ++ ){
        cout<< *(a) <<endl;
    }
    system("pause");
}



