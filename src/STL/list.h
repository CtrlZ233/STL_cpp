#include<stdio.h>
#include<stdlib.h>
#include <cstddef>
#include <stdexcept>
#include <memory>
#include <iterator>
#include<iostream>
#include<string>

using namespace std;

template<typename T>
class Node{
    public:
        T obj;
        Node<T> *previous;
        Node<T> *next;
    public:
        Node(const Node &node){
            this->obj = node->obj;
            this->next = node->next
            this->previous = node->previous;
        }
        Node(T &obj){
            this->obj = this->obj;
            this->next = nullptr;
            this->previous = nullptr; 
        }
};

template<typename T>
class iterator{
    public:
        Node<T> * iter;
    
    public:
        iterator() = default;
        iterator(const Node<T>* &node_ptr){
            this->iter = node_ptr;
        }
        iterator(const iterator<T> obj){
            this->iter = obj.iter;
        }
        iterator operator ++(){
            if(iter == nullptr){
                throw std::runtime_error("Invalid memory reference");
            }
            return iterator(iter->next);
        }
        iterator operator --(){
            if(iter->previous == nullptr){
                throw std::runtime_error("Invalid memory reference");
            }
            return iterator(iter->previous);
        }
        
}
;

template <typename T>
class list{
    public:
        using value_type = T;
        using iterator  = value_type *;
        using size_type = std::size_t;
    public:
        list() = default;
        list(const list<T> &obj);
        ~list();
        void push_front(const value_type &new_elem);
        void push_back(const value_type &new_elem);
 
};