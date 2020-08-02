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
        size_type max_size() const;
        value_type &operator[](size_type i) const;
        value_type &at(size_type i) const;
        value_type & front() const;
        value_type & back() const;
        void push_back(const value_type &new_elem);
        void pop_back();
        void insert(iterator iter, const value_type &new_elem);
        void earse(iterator start_iter, iterator end_iter);
        bool empty();
        void clear();
        void print_all_elem();
    
    public:
        iterator start_ptr = nullptr;
        iterator end_ptr = nullptr;
        iterator cap_ptr = nullptr;
        std::allocator<value_type> alloc;

    private:
        void check_cap();
        void free_memory(iterator start_iter, iterator end_iter);
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
    if(start_ptr==nullptr || end_ptr==nullptr){
        return 0;
    }
    return end_ptr - start_ptr;
}

template<typename T>
typename vector<T>:: size_type vector<T>::max_size() const{
    return cap_ptr - start_ptr;
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
typename vector<T>:: value_type &vector<T>::front() const {
    return *(start_ptr);
}

template<typename T>
typename vector<T>:: value_type &vector<T>::back() const{
    return *(end_ptr-1);
}

template<typename T>
vector<T>:: ~vector(){
    free();
}

template<typename T>
void vector<T>::free() {
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
    else{
        throw std::runtime_error("vector empty");
    }
}

template<typename T>
void vector<T>::insert(iterator iter, const value_type &new_elem){
    if(iter > end_ptr){
        throw std:: runtime_error("out of range");
    }
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
    if(start_iter < start_ptr || end_iter > end_ptr){
        throw std::runtime_error("out of range");
    }
    if(end_iter < end_ptr){
        iterator tmp1 = start_iter;
        iterator tmp2 = end_iter;
        while(tmp2 < end_ptr){
            alloc.construct(tmp1, * tmp2);
            tmp1 ++;
            tmp2 ++;
        }
        free_memory(tmp1, end_ptr);
        end_ptr = tmp1;
    }
}

template<typename T>
bool vector<T>::empty(){
    if(start_ptr == NULL ||start_ptr == end_ptr){
        return true;
    }
    return false;
}

template<typename T>
void vector<T>::clear(){
    if(start_ptr){
        free_memory(start_ptr, end_ptr);
        start_ptr = nullptr;
        end_ptr = nullptr;
        cap_ptr = nullptr;
    }
}

template<typename T>
void vector<T>::print_all_elem(){
    vector<T>::iterator iter = begin();
    while(iter!=end()){
        std::cout<< *iter <<" ";
        iter++;
    }
    std::cout << endl;
}

template<typename T>
void vector<T>::free_memory(iterator start_iter, iterator end_iter){
    if(start_iter<start_ptr || end_iter > end_ptr){
        throw std::runtime_error("out of range");
    }
    for(auto p=start_iter; p!=end_iter; p++){
        alloc.destroy(p);
    }
}