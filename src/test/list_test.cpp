#include "../STL/list"
#include<stdlib.h>
using namespace std;
int main(){
    list<string> L = {"1", "2"};

    // L.push_front("zero");
    cout << "Is empty ?" << L.empty() << endl;
    L.push_back("one");
    L.insert(L.begin(), "insert");
    L.push_back("two");
    cout << "Is empty ?" << L.empty() << endl;
    L.push_back("three");
    // L.push_front("front");
    // L.clear();
    // L.push_back("one");
    // list<string> L2 = L;  // some bugs  // no bugs
    // cout << L2.size() << endl;
    // L.push_back("two");
    // cout << "hhh" <<endl;
    // cout<< L.start_node->obj << endl;
    L.pop_back();
    L.pop_front();
    list<string>::iterator a = L.begin();
    list<string>::iterator b = L.end();
    // L.erase(L.begin()+1, L.begin()+3);
    // if(L.head->previous== nullptr){
    //     cout << "sdsdsd" << endl;
    // }
    
    for(; a!=b; a ++ ){
        cout<< *(a) <<endl;
    }

    string m = L.front();
    string n = L.back();
    system("pause");
}



