#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include <memory>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include<vector>
// #include<deque>
using namespace std;


template<typename T, size_t elem_size>
class MyIterator{
    public:
        using value_type = T;
        using size_type = std::size_t;
    public:
        value_type* cur;
        value_type* first;
        value_type* last;
        value_type** map_node;
    
    public:
        MyIterator() = default;
        MyIterator(const value_type** map){
            set_map_node(map);
            cur = first;
        }
        MyIterator(const MyIterator<T, elem_size> &iter){
            this->cur = iter.cur;
            this->first = iter.first;
            this->last = iter.last;
            this->map_node = iter.map_node;
        }
        ~MyIterator() = default;
        void set_map_node(const value_type** new_map_node){
            map_node = new_map_node;
            first = *new_map_node;
            last = first + elem_size;
        }

        value_type operator * (){
            return *(cur);
        }
        MyIterator operator ++(){
            this->cur++;
            if(this->cur = this->last){ 
                set_map_node(map_node + 1);
                cur = first;
            }
            return *this;
        }

        MyIterator operator ++(int){
            MyIterator tmp = MyIterator(*this);
            ++(*this);
            return tmp;
        }

        MyIterator operator --(){
            
            if(this->cur = this->last){ 
                set_map_node(map_node - 1);
                cur = last;
            }
            this->cur -- ;
            return *this;
        }

        MyIterator operator --(int){
            MyIterator tmp = MyIterator(*this);
            
            --(*this);
            return tmp;
        }

        bool operator != (MyIterator iter){
            return this->cur != iter.cur;
        }
        
        bool operator == (MyIterator iter){
            return this->cur == iter.cur;
        }
        
};

template<typename T, size_t elem_size = 0>
class deque{
    public:
        using value_type = T;
        using iterator = MyIterator<T, elem_size>;
        using size_type = std::size_t;
        
    public:
        value_type * start_ptr;
        value_type * end_ptr;
        value_type** pointer_map;
        iterator start;
        iterator finish;
        size_type map_size;
        std::allocator<value_type> elem_alloc;
        std::allocator<value_type*> node_alloc;

    private:
        void alloc_memory(size_type alloc_size);
    public:
        deque();
        ~deque();
        iterator begin() const;
        iterator end() const;
};

template<typename T, size_t elem_size>
deque<T, elem_size>::deque(){
    alloc_memory(3);    // The first three memory areas
    this->start = iterator(this->pointer_map + 1);      // Start in the middle to make sure that both front and back can be inserted.
    this->finish = this->start;
}

template<typename T, size_t elem_size>
deque<T, elem_size>::~deque(){

}

template<typename T, size_t elem_size>
void deque<T, elem_size>::alloc_memory(size_type alloc_size){
    this->pointer_map = node_alloc.allocate(alloc_size);
    for(int i=0; i<alloc_size; i++){
        pointer_map[i] = elem_alloc.allocate(elem_size);
    }
    this->map_size = alloc_size;
}

template<typename T, size_t elem_size>
MyIterator<T, elem_size> deque<T, elem_size>::begin() const{
    return start;
}

template<typename T, size_t elem_size>
MyIterator<T, elem_size> deque<T, elem_size>::end() const{
    return finish;
}
