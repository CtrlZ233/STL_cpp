#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p)? (p)->height :-1)
typedef enum {RB_RED, RB_BLACK} RBColor;
#include<stdlib.h>
template <typename T>
class BinNode{
    T data;
    BinNodePosi(T) parent, lc, rc;
    int height;
    int npl;
    RBColor color;
    BinNode():
        parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED){}
    BinNode(T e, BinNodePosi(T) p=nullptr, BinNodePosi(T) lc=nullptr, BinNodePosi(T) rc=nullptr,
            int h=0, int l=1, RBColor c=RB_RED):
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){}
    
    int size();  // 后代总数
    BinNodePosi(T) insertAsLC(T const & elem);
    BinNodePosi(T) insertAsRC(T const & elem);
    BinNodePosi(T) succ();
    template <typename VST> void travLevel (VST& visit);
    template <typename VST> void travPre (VST& visit);
    template <typename VST> void travIn (VST& visit);
    template <typename VST> void travPost (VST& visit);

    bool operator < (BinNode const &bn) { return data < bn.data; }
    bool operator == (BinNode const &bn) { return data == bn.data; }
    
};

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (x).parent->lc == (x))
#define IsRchild(x) (!IsRoot(x) && (x).parent->rc == (x))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p)) ? (p)->rc : (p)->lc)
#define uncle(p) ( IsLChild(*((p)->parent) ? (x)->parent->parent->rc : (x)->parent->parent->lc))
#define FromParentTo(p) (IsRoot(p)? _root : (IsLChild(p))? (p).parent->lc : (p).parent->rc)

template<typename T> 
BinNodePosi(T) BinNode<T>:: insertAsLC(T const & elem){
    return lc = new BinNode(elem, this);
}

template<typename T> 
BinNodePosi(T) BinNode<T>:: insertAsRC(T const & elem){
    return rc = new BinNode(elem, this);
}
template<typename T> 
template <typename VST> void BinNode<T>:: travIn (VST& visit){
    switch (rand() % 5)
    {
    case 1: travIn_I1(this, visit); 
        break;
    case 2: travIn_I2(this, visit); 
        break;
    case 3: travIn_I3(this, visit); 
        break;
    case 4: travIn_I4(this, visit); 
        break;
    
    default: travIn_R(this, visit);  //递归版
        break;
    }
}
template<typename T>
int BinNode<T>::size(){
    if(!HasChild(*this)) return 1;
    if(!HasLChild(*this)) return 1 + this->rc->size();
    if(!HasRChild(*this)) return 1 + this->lc->size();
    return 1 + this->rc->size() + this->lc->size();
}








