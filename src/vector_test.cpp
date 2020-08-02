#include "vector.h"

int main(){
    vector<string> v;
    cout << v.empty() << endl;
    v.push_back("one");
    v.push_back("two");
    v.push_back("three");
    v.clear();
    cout << v.size() << endl;
    v.push_back("four");
    v.push_back("five");
    v.push_back("six");
    v.push_back("seven");
    v.print_all_elem();

    cout << v.max_size() << endl;
    cout << v.front() << endl;
    cout << v.back() << endl;
    v.insert(v.start_ptr+2, "insert_1");
    v.insert(v.start_ptr+3, "insert_2");
    cout << "after insert elements..." << endl;
    v.print_all_elem();

    v.earse(v.start_ptr+2, v.start_ptr+4);
    cout << "after earse elements..." << endl;
    v.print_all_elem();
    
}
