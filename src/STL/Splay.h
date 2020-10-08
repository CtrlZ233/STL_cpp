#include "BST.h"
template<typename T>
class Splay : public BST<T> {
    protected:
        BinNodePosi(T) splay ( BinNodePosi(T) v );
    public:
        BinNodePosi(T) & search ( const T&  e );
        BinNodePosi(T) insert ( const T& e );
        bool remove ( const T& e );
};

template <typename NodePosi> inline
void attachAsLchild ( NodePosi p, NodePosi lc ) { p->lc = lc; if(lc) lc->parent = p; }

template <typename NodePosi> inline
void attachAsRchild ( NodePosi p, NodePosi rc ) { p->rc = rc; if(rc) rc->parent = p; }

template <typename T>
BinNodePosi(T) Splay<T>:: splay ( BinNodePosi(T) v ){
    if ( !v ) return nullptr; BinNodePosi(T) p; BinNodePosi(T) g;
    while ( ( p = v->parent ) && ( g = p->parent ) ) {
        BinNodePosi(T) gg = g->parent;
        if ( IsLChild ( v ) ) {
            if ( IsLChild ( p ) ) {       // zig-zig
                attachAsLchild ( g, p->rc ); attachAsLchild ( p, v->rc );
                attachAsRchild ( p, g );     attachAsRchild ( v, p );
            }
            else{                       // zig-zag
                attachAsLchild ( p, v->rc ); attachAsRchild ( g, v->lc );
                attachAsLchild ( v, g );     attachAsRchild ( v, p );
            }
        }
        else {
            if ( IsLChild (p) ) {       // zag-zig
                attachAsRchild ( p, v->lc ); attachAsLchild ( g, v->rc );
                attachAsRchild ( v, p );     attachAsLchild ( v, g );
            }       
            else{                       // zag-zag
                attachAsRchild ( g, p->lc ); attachAsRchild ( p, v->lc );
                attachAsLchild ( p, g );     attachAsLchild ( v, p );
            }    
        }
        if ( !gg ) v->parent = nullptr;
        else
            ( g == gg->lc ) ? attachAsLchild ( gg, v ) : attachAsRchild ( gg, v );
        this->updateHeight ( g ); this->updateHeight ( p ); this->updateHeight( v );
    }
    if ( p = v->parent ) {
        if ( IsLChild ( v ) ) { attachAsLchild ( p, v->rc ); attachAsRchild ( v, p ); }
        else                  { attachAsRchild ( p, v->lc ); attachAsLchild ( v, p ); }
        this->updateHeight ( p ); this->updateHeight ( v );
    }
    v->parent = nullptr; return v;
}

template <typename T>
BinNodePosi(T) & Splay<T>::search ( const T& e ){
    BinNodePosi(T) p = searchIn ( this->_root, e, this->_hot = nullptr );
    this->_root = splay ( ( p ? p : this->_hot) );
    return this->_root;
}

template <typename T>
BinNodePosi(T) Splay<T>::insert ( const T& e ) {
    if ( !this->_root ) { this->_size++; return this->_root = new BinNode<T> ( e ); }
    if ( e == search ( e )->data ) return this->_root;
    this->_size++; BinNodePosi(T) t = this->_root;
    if ( this->_root->data < e ) {   
        t->parent = this->_root = new BinNode<T> ( e, nullptr, t, t->rc );
        if ( HasRChild ( t ) ) { t->rc->parent = this->_root; t->rc = nullptr; }
    }else{
        t->parent = this->_root = new BinNode<T> ( e, nullptr, t->lc, t );
        if ( HasLChild ( t ) ) { t->lc->parent = this->_root; t->lc = nullptr; }
    }
    this->updateHeightAbove ( t );
    return this->_root; 
}

template <typename T> bool Splay<T>::remove ( const T& e ){
    if ( !this->_root || ( e != search ( e )->data ) ) return false;
    BinNodePosi(T) w = this->_root;
    if ( !HasLChild ( this->_root ) ) {
        this->_root = this->_root->rc; if( this->_root ) this->_root->parent = nullptr;
    } else if ( !HasRChild ( this->_root ) ){
        this->_root = this->_root->lc; if( this->_root ) this->_root->parent = nullptr;
    }else{
        BinNodePosi(T) lTree = this->_root->lc;
        lTree->parent = nullptr; this->_root->lc = nullptr;
        this->_root = this->_root->rc; this->_root->parent = nullptr;
        search( w->data );
        this->_root->lc = lTree; lTree->parent = this->_root;
    }
    delete( w ); this->_size--;
    if ( this->_root ) this->updateHeight ( this->_root );
    return true;
}