#include<list>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    // list<int> L = list<int>{1, 2, 3, 4, 5};
    // list<int>:: iterator p = L.begin();
    // list<int>:: iterator q = L.end();
    // bool a = p > q;
    
    // system("pause");

}

int gcd(int a, int b){
    if(a%b == 0){
        return b;
    }
    else 
        return (gcd(b, a%b));
}
