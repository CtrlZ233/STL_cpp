#include<list>
#include<iostream>
using namespace std;
int main(){
    list<int> L = list<int>{1, 2, 3, 4, 5};
    list<int>:: iterator p = L.begin();
    list<int>:: iterator q = L.end();
    // bool a = p > q;
}