#include "BST.h"
template<typename T>
class AVL : public BST<T> {
    public:
        BinNodePosi(T) insert ( const T& e );
        bool remove ( const T& e ); 
};

#define Balanced(x) (stature( (x)->lc ) == stature( (x)->rc ) )
#define BalFac(x) (stature( (x)->lc ) - stature( (x)->rc ) )
#define AvlBalanced(x) ( -2 < (BalFac(x)) && (BalFac(x)) < 2 )
#define tallerChild(x) (stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : \
                        (stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : \
                        (IsLChild(x) ? (x)->lc : (x)->rc) ) )
template<typename T>
BinNodePosi(T) AVL<T>::insert ( const T& e ){
    BinNodePosi(T)& x = this->search (e); if(x) return x;
    BinNodePosi(T) xx = x = new BinNode<T> (e, this->_hot); this->_size++;
    for( BinNodePosi(T) g = this->_hot; g; g = g->parent ){
        if( !AvlBalanced( g ) ){
            BinNodePosi(T) tmp = this->rotateAt ( tallerChild ( tallerChild ( g ) ) );      // some bugs
                                                                                         // g->parent会被改变。
            g = FromParentTo(g) =  tmp;
            break;
        }else
            this->updateHeight( g );
    }
    return xx;
}

template <typename T> bool AVL<T>::remove ( const T& e ){
    BinNodePosi(T) & x = this->search( e ); if(!x) return false;
    removeAt(x, this->_hot); this->_size--;
    for ( BinNodePosi(T) g = this->_hot; g; g->parent ){
        if( !AvlBalanced( g ) ) 
            g = FromParentTo( g ) = this->rotateAt ( tallerChild ( tallerChild ( g ) ) );
        this->updateHeight(g);
    }
    return true;
}

template <typename T> BinNodePosi(T) BST<T>::rotateAt ( BinNodePosi(T) v ){
    BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent;
    if( IsLChild (p) )  //  zig
        if ( IsLChild ( v ) ) {    // zig-zig 
            p->parent = g->parent;
            return connect34 ( v, p, g, v->lc, v->rc, p->rc, g->rc );
        } else {                      // zig-zag
            v->parent = g->parent;
            return connect34 ( p, v, g, p->lc, v->lc, v->rc, g->rc );
        } 
    else            // zag
        if ( IsRChild ( v ) ){   // zag-zag
            p->parent = g->parent;
            return connect34 ( g, p, v, g->lc, p->lc, v->lc, v->rc );
        } else {                // zag-zig
            v->parent = g->parent;
            return connect34 ( g, v, p, g->lc, v->lc, v->rc, p->rc );
        }
}

template<typename T>  BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
                        BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3 ){
    a->lc = T0; if ( T0 ) T0->parent = a;
    a->rc = T1; if ( T1 ) T1->parent = a; this->updateHeight ( a );
    c->lc = T2; if ( T2 ) T2->parent = c;
    c->rc = T3; if ( T3 ) T3->parent = c; this->updateHeight ( c );
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b; this->updateHeight ( b );
    return b;
}