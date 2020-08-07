#include "../STL/vector.h"
#include<stdlib.h>
int main(){
    vector<string> v;
    cout << v.empty() << endl;
    v.push_back("one");
    cout << v.max_size() << endl;
    v.push_back("two");
    cout << v.max_size() << endl;
    v.push_back("three");
    cout << v.max_size() << endl;
    // v.clear();
    // cout << v.size() << endl;
    // v.push_back("four");
    // v.push_back("five");
    // v.push_back("six");
    // v.push_back("seven");
    // v.print_all_elem();

    // cout << v.max_size() << endl;
    // cout << v.front() << endl;
    // cout << v.back() << endl;
    // v.insert(v.start_ptr+2, "insert_1");
    // v.insert(v.start_ptr+3, "insert_2");
    // cout << "after insert elements..." << endl;
    // v.print_all_elem();

    v.erase(v.start_ptr+1, v.start_ptr+3);
    // cout << "after earse elements..." << endl;
    v.print_all_elem();
    cout << v.max_size() << endl;
    cout << v.size() << endl;
    v.push_back("four");
    v.push_back("five");
    v.push_back("six");
    v.push_back("seven");

    
    v.print_all_elem();
    cout << v.size() << endl;
    cout << v.max_size() << endl;

    // vector<int> v;
    // v.push_back(1);
    // v.push_back(2);
    // v.print_all_elem();
    // v[1] = 3;
    // v.print_all_elem();
    // vector<int> v1 = v;
    // v.print_all_elem();
    // v1.print_all_elem();
    // v.push_back(3);
    
    // v.print_all_elem();
    // v1.print_all_elem();
}
