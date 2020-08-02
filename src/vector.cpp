#include<stdio.h>
#include<stdlib.h>
#include <cstddef>
#include <stdexcept>
#include <memory>
#include <iterator>
#include<iostream>
#include<string>

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
        void insert(iterator iter, const value_type &new_elem);
        void earse(iterator start_itr, iterator end_iter);
        void print_all_elem();
    
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
;}


template <typename T> 
void vector<T>::pop_back()
{
    if(end_ptr - start_ptr>0){
        alloc.destroy(end_ptr);
        end_ptr --;
    }
}

template<typename T>
void vector<T>::insert(iterator iter, const value_type &new_elem){
    value_type now_elem = new_elem;
    while(iter < end_ptr){
        value_type tmp = *iter;
        alloc.construct(iter, now_elem);
        now_elem = tmp;
        iter ++;
    }
    push_back(now_elem);
}

template<typename T>
void vector<T>::earse(iterator start_iter, iterator end_iter){
    if(end_iter < end_ptr){
        iterator tmp1 = start_iter;
        iterator tmp2 = end_iter;
        while(tmp2 < end_ptr){
            alloc.construct(tmp1, * tmp2);
            tmp1 ++;
            tmp2 ++;
        }
        end_ptr = tmp1;
    }
}

template<typename T>
void vector<T>::print_all_elem(){
    vector<T>::iterator iter = start_ptr;
    while(iter!=end_ptr){
        std::cout<< *iter <<" ";
        iter++;
    }
    std::cout << endl;
}


int main(){
    vector<string> v;
    v.push_back("one");
    v.push_back("two");
    v.push_back("three");
    v.push_back("four");
    
    v.print_all_elem();

    v.insert(v.start_ptr+2, "insert_1");
    v.insert(v.start_ptr+3, "insert_2");
    cout << "after insert elements..." << endl;
    v.print_all_elem();

    v.earse(v.start_ptr+2, v.start_ptr+4);
    cout << "after earse elements..." << endl;
    v.print_all_elem();
    
}
