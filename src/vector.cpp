#include<stdio.h>
#include<stdlib.h>
#include <cstddef>
#include <stdexcept>
#include <memory>
#include <iterator>
#include<iostream>
using namespace std;
template <typename T>
class vector
{
    public:
        using value_type = T;
        using iterator = value_type *;
        using size_type = std::size_t;
    
    public:
        vector() = default;
        ~vector();
        iterator begin() const;
        iterator end() const;
        size_type size() const;
        value_type &operator[](size_type i) const;
        value_type &at(size_type i) const;
        void push_back(const value_type &new_elem);
        void pop_back();
    
    public:
        iterator start_ptr = nullptr;
        iterator end_ptr = nullptr;
        iterator cap_ptr = nullptr;
        std::allocator<value_type> alloc;

    private:
        void check_cap();
        void free();
};

template <typename T>
typename vector<T>:: iterator vector<T>::begin() const{
    return start_ptr;
}

template<typename T>
typename vector<T>:: iterator vector<T>::end() const{
    return end_ptr;
}

template<typename T>
typename vector<T>:: size_type vector<T>::size() const{
    return end_ptr - start_ptr;
}


template <typename T>
typename vector<T>::value_type &vector<T>::operator[](size_type i) const
{
    return *(start_ptr + i);
}

template<typename T>
typename vector<T>:: value_type &vector<T>::at(size_type i) const{
    if (start_ptr + i > end_ptr){
        throw std::runtime_error("out of range");
    }
    return *(start_ptr + i);
}

template<typename T>
vector<T>:: ~vector(){
    free();
}

template<typename T>
void vector<T>::free(){
    if(start_ptr){
        for(auto p=start_ptr; p!=end_ptr; p++){
            alloc.destroy(p);
        }
        alloc.deallocate(start_ptr, end_ptr - start_ptr);
    }
}

template<typename T>
void vector<T>::check_cap(){
    if (end_ptr == cap_ptr){
        int new_size = size() ? size() <<1 :1;
        auto new_start_ptr = alloc.allocate(new_size);
        auto new_end_ptr = uninitialized_copy(std::make_move_iterator(start_ptr), 
                            std::make_move_iterator(end_ptr), new_start_ptr);
        free();
        start_ptr = new_start_ptr;
        end_ptr = new_end_ptr;
        cap_ptr = new_start_ptr + new_size;
    }
}

template<typename T>
void vector<T>:: push_back(const value_type & new_elem){
    check_cap();
    alloc.construct(end_ptr, new_elem);
    end_ptr ++ ;
}

template <typename T> 
void vector<T>::pop_back()
{
    if(end_ptr - start_ptr>0){
        alloc.destroy(end_ptr);
        end_ptr --;
    }
}

int main(){
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    vector<int>::iterator iter = v.start_ptr;
    while(iter!=v.end_ptr){
        cout << *iter << " ";
        iter ++;
    }

    cout << endl;
    system("pause");
    
}