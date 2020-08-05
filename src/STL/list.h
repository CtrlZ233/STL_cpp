#include<stdio.h>
#include<stdlib.h>
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
        Node() = default;
        Node(const Node &node){
            this->obj = node->obj;
            this->next = node->next;
            this->previous = node->previous;
        }
        Node(T elem){
            this->obj = elem;
            this->next = nullptr;
            this->previous = nullptr; 
        }
};

template<typename T>
class MyIterator{
    public:
        Node<T> * iter;
    
    public:
        MyIterator() = default;
        MyIterator(Node<T>* &node_ptr){
            this->iter = node_ptr;
        }
        MyIterator(const MyIterator<T>& obj){
            this->iter = obj.iter;
        }
        MyIterator operator ++(int){
            if(iter->next == nullptr){      // 允许访问尾节点
                throw std::runtime_error("Invalid memory reference");
            }
            this->iter  = this->iter->next;
            return *this;
        }
        MyIterator operator --(int){
            if(iter->previous->previous == nullptr){    //不允许访问头节点
                throw std::runtime_error("Invalid memory reference");
            }
            // return MyIterator(iter->previous);
            this->iter = this->iter->previous;
            return *this;
        }
        MyIterator operator +(int i){
            Node<T>* tmp = iter;
            while(i>0){
                if(tmp->next == nullptr){
                    throw std::runtime_error("Invalid memory reference");
                }
                else{
                    tmp = tmp->next;
                }
                i--;
            }
            return MyIterator<T>(tmp);
        }
        MyIterator operator -(int i){
            Node<T>* tmp = this->iter;
            while(i>0){
                if(tmp->previous->previous == nullptr){
                    throw std::runtime_error("Invalid memory reference");
                }
                else{
                    tmp = tmp->previous;
                }
                i--;
            }
            return MyIterator<T>(tmp);
        }
        bool operator ==(const MyIterator<T> &i){
            return this->iter == i.iter ? true: false;
        }
        
        T operator *(){
            return this->iter->obj;
        }    
}
;

template <typename T>
class list{
    public:
        using value_type = T;;
        using size_type = std::size_t;
    public:
        Node<T>* start_node;
        Node<T>* end_node;
        size_type size;
        Node<T>* head;
        
    public:
        list();
        // list(const list<T> &obj);
        // ~list();
        // void push_front(const value_type &new_elem);
        void push_back(const value_type &new_elem);
        MyIterator<T> begin();
        MyIterator<T> end();
        bool empty();
};

template<typename T>
list<T>::list(){
    head = new Node<T>;
    start_node = head;
    end_node = new Node<T>;
    head->next = end_node;
    end_node ->previous = head;
}

// template<typename T>
// list<T>::list(const list<T> &obj){
//     this-
// }

template<typename T>
void list<T>::push_back(const value_type &new_elem){
    Node<T> *new_node = new Node<value_type>(new_elem);
    this->end_node->previous->next = new_node;
    new_node->previous = this->end_node->previous;
    new_node->next = this->end_node;
    this->end_node->previous = new_node;
    if(this->start_node == this->head){
        this->start_node = new_node;
    }
}

template<typename T>
bool list<T>::empty(){
    return start_node == head ? true:false;
}

template<typename T>
MyIterator<T> list<T>::begin(){
    if(empty()){
        throw std::runtime_error("The list is empty.");
    }
    else{
        return MyIterator<T>(start_node);
    }
}

template<typename T>
MyIterator<T> list<T>::end(){
    return MyIterator<T>(end_node);
}



