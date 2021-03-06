#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include <memory>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>

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
        MyIterator(Node<T>* node_ptr){
            this->iter = node_ptr;
        }
        MyIterator(const MyIterator<T>& obj){
            this->iter = obj.iter;
        }
        MyIterator operator ++(int){
            if(iter->next == nullptr){      // 允许访问尾节点
                throw std::runtime_error("Invalid memory reference");
            }
            MyIterator tmp = MyIterator(*this);
            this->iter  = this->iter->next;
            return tmp;
        }
        MyIterator operator --(int){
            if(iter->previous->previous == nullptr){    //不允许访问头节点
                throw std::runtime_error("Invalid memory reference");
            }
            MyIterator tmp = MyIterator(*this);
            // return MyIterator(iter->previous);
            this->iter = this->iter->previous;
            return tmp;
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
            return this->iter == i.iter;
        }
        bool operator != (const MyIterator<T> &i){
            return !(*(this)==i);
        }
        // bool operator < (const MyIterator<T> &i){
        //     return this->iter < i.iter;
        // }
        // bool operator > (const MyIterator<T> &i){
        //     return this->iter > i.iter;
        // }
        // bool operator >= (const MyIterator<T> &i){
        //     return this->iter >= i.iter;
        // }

        // bool operator <= (const MyIterator<T> &i){
        //     return this->iter <= i.iter;
        // }

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
        using iterator = MyIterator<T>;
    public:
       
        std::allocator<Node<value_type>> alloc;
        
    private:
        Node<T>* start_node;
        Node<T>* end_node;
        Node<T>* head;
        std::size_t num;
    public:
        list();
        list(const list<T> &obj);
        list(const initializer_list<T> &t);
        ~list();
        
        // void push_front(const value_type &new_elem);

        value_type front();
        value_type back();

        void push_back(const value_type &new_elem);
        void push_front(const value_type &new_elem);

        void pop_back();
        void pop_front();

        void insert(iterator i, const value_type &elem);
        void erase(iterator first, iterator last);
        iterator begin() const;
        iterator end() const;
        bool empty() const;
        std::size_t size() const;
        void clear();
    private:
        void free_memory(iterator start_iter, iterator end_iter);
        void initial_list();
};

template<typename T>
list<T>::list(){
    initial_list();
}

template<typename T>
list<T>::list(const list<T> &obj){
    if(!obj.empty()){
        initial_list();
        iterator p = obj.begin();
        iterator q = obj.end();
        Node<T>* tmp = head;
        // iterator tmp = 
        while(p!=q){
            Node<T>* new_node = new Node<T>(p.iter->obj);
            tmp->next = new_node;
            new_node->previous = tmp;
            p++;
            tmp = new_node;
        }
        tmp->next = end_node;
        end_node->previous = tmp;
        this->num = obj.num;
        this->start_node = this->head->next;
    }
    
}

template<typename T>
list<T>::list(const initializer_list<T> &t){
    initial_list();
    typename std::initializer_list<T>::iterator op = t.begin();
    typename std::initializer_list<T>::iterator ed = t.end();
    while(op != ed){
        push_back(*op);
        op ++;
    }

}

template<typename T>
list<T>::~list(){
    free_memory(begin(), end());
    alloc.deallocate(start_node, end_node - start_node);
}

template<typename T>
T list<T>::front(){
    if(empty()){
        throw std::runtime_error("empty list!");
    }
    return this->start_node->obj;
}

template<typename T>
T list<T>::back(){
    if(empty()){
        throw std::runtime_error("empty list!");
    }
    return this->end_node->previous->obj;
}

template<typename T>
void list<T>::push_back(const value_type &new_elem){
    Node<value_type> *new_node = new Node<value_type>(new_elem);
    this->end_node->previous->next = new_node;
    new_node->previous = this->end_node->previous;
    new_node->next = this->end_node;
    this->end_node->previous = new_node;
    if(this->start_node == this->end_node){
        this->start_node = new_node;
    }
    this->num++;
}

template<typename T>
void list<T>::push_front(const value_type &new_elem){
    Node<value_type> *new_node = new Node<value_type>(new_elem);
    // Node<value_type> * tmp = this->start_node->next;
    this->head->next = new_node;
    new_node->previous = this->head;
    new_node->next = this->start_node;
    this->start_node->previous = new_node;
    this->start_node = new_node;
    this->num++;
}

template<typename T>
void list<T>::pop_back(){
    if(empty()){
        throw std::runtime_error("empty list!");
    }
    Node<T>* tmp = end_node->previous;
    tmp->previous->next = end_node;
    end_node->previous = tmp->previous;
    alloc.destroy(tmp);
}

template<typename T>
void list<T>::pop_front(){
    if(empty()){
        throw std::runtime_error("empty list!");
    }
    head->next = start_node->next;
    start_node->next->previous = head;
    alloc.destroy(start_node);
    start_node = head->next;
}

template<typename T>
void list<T>::insert(iterator i, const value_type &elem){
    iterator pre;
    if(i.iter == start_node){
        pre = head;
    }
    else{
        pre = i-1;
    }
    Node<value_type>* new_node = new Node<value_type>(elem);
    pre.iter->next = new_node;
    new_node->previous = pre.iter;
    i.iter->previous = new_node;
    new_node->next = i.iter;
    if(pre.iter == head){
        start_node = new_node;
    }
}

template<typename T>
void list<T>::erase(iterator first, iterator last){
    iterator p = first--;
    // if(first < begin() || last > end()){
    //     throw std::runtime_error("out of range!");
    // }
    free_memory(first, last);
    p.iter->next = last.iter;
    last.iter->previous = p.iter;
    this->start_node = this->head->next;
}

template<typename T>
bool list<T>::empty() const{
    return start_node == end_node;
}

template<typename T>
std::size_t list<T>::size() const{
    return this->num;
}

template<typename T>
MyIterator<T> list<T>::begin() const{
    if(empty()){
        throw std::runtime_error("The list is empty.");
    }
    else{
        return MyIterator<T>(start_node);
    }
}

template<typename T>
MyIterator<T> list<T>::end() const{
    if(empty()){
        throw std::runtime_error("The list is empty.");
    }
    return MyIterator<T>(end_node);
}

template<typename T>
void list<T>::free_memory(iterator start_iter, iterator end_iter){
    // if(start_iter< begin() || end_iter > end()){
    //     throw std::runtime_error("out of range");
    // }
    for(auto p=start_iter; p!=end_iter; p++){
        alloc.destroy(p.iter);
    }
}

template<typename T>
void list<T>::clear(){
    free_memory(begin(), end());
    end_node = start_node;
    end_node->previous = head;
    start_node->next = nullptr;
    this->num = 0;
}

template<typename T>
void list<T>::initial_list(){
    head = new Node<T>;
    head->previous = nullptr;
    end_node = new Node<T>;
    head->next = end_node;
    start_node = end_node;
    end_node ->previous = head;
    this->num = 0;
}