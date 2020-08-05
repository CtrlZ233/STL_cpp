#include "list.h"
#include<stdlib.h>
using namespace std;
int main(){
    list<string> L = list<string>();
    L.push_back("one");
    L.push_back("two");
    L.push_back("three");
    // cout << "hhh" <<endl;
    // cout<< L.start_node->obj << endl;
    for(auto a = L.begin(); !(a==L.end()); a ++ ){
        cout<< *(a) <<endl;
    }
    system("pause");
}


