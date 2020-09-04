#include<list>
#include<stdlib.h>
#include<iostream>
using namespace std;
int main(){
    list<int> L;
    for(int i=1980; i<=2012; i++){
        L.push_back(i);
        cout << i <<endl;
    }
    for(int i=0; i<1980; i++){
        L.push_back(i);
        cout<<i<<endl;
    }
    system("pause");
}

