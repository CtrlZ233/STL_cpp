#include<stdlib.h>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p)? (p)->height :-1)
typedef enum {RB_RED, RB_BLACK} RBColor;

template <typename T>
class BinNode{
    public:
        T data;
        BinNodePosi(T) parent;
        BinNodePosi(T) lc;
        BinNodePosi(T) rc;
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

#define IsRoot(p) (!((p)->parent))
#define IsLChild(p) (!IsRoot(p) && (p)->parent->lc == (p))
#define IsRChild(p) (!IsRoot(p) && (p)->parent->rc == (p))
#define HasParent(p) (!IsRoot(p))
#define HasLChild(p) ((p)->lc)
#define HasRChild(p) ((p)->rc)
#define HasChild(p) (HasLChild(p) || HasRChild(p))
#define HasBothChild(p) (HasLChild(p) && HasRChild(p))
#define IsLeaf(p) (!HasChild(p))
#define sibling(p) (IsLChild(p) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(p) ( IsLChild((p)->parent) ? (p)->parent->parent->rc : (p)->parent->parent->lc)
#define FromParentTo(p) (IsRoot((p))? this->_root : (IsLChild(p))? (p)->parent->lc : (p)->parent->rc)

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
    switch (rand() % 4)
    {
    case 1: travIn_I1(this, visit); 
        break;
    case 2: travIn_I2(this, visit); 
        break;
    case 3: travIn_I3(this, visit); 
        break;
    
    default: travIn_R(this, visit);  //递归版
        break;
    }
}

template<typename T>
template <typename VST> void BinNode<T>::travPre (VST& visit){
    switch (rand() % 3)
    {
    case 1: travPre_I1(this, visit); 
        break;
    case 2: travPre_I2(this, visit); 
        break;
    default: travPre_R(this, visit);  //递归版
        break;
    }
}

template<typename T>
template <typename VST> void BinNode<T>::travPost (VST& visit){
    switch (rand() % 2)
    {
    case 1: travPost_I(this, visit); 
        break;
    default: travPost_R(this, visit);  //递归版
        break;
    }
}
template<typename T>
int BinNode<T>::size(){
    if(!HasChild(this)) return 1;
    if(!HasLChild(this)) return 1 + this->rc->size();
    if(!HasRChild(this)) return 1 + this->lc->size();
    return 1 + this->rc->size() + this->lc->size();
}
template<typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit ){
    if(!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}
template<typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit ){
    if(!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template<typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit ){
    if(!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}
template<typename T, typename VST>
void travPre_I1(BinNodePosi(T) x, VST& visit){
    std::stack<BinNodePosi(T)> s;
    if (x) s.push(x);
    while(!s.empty()){
        x = s.top(); s.pop(); visit(x->data);
        if(HasRChild(x)) s.push(x->rc); if(HasLChild(x)) s.push(x->lc);
    }
}

template<typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, stack<BinNodePosi(T)>& S){
    while(x){
        visit(x->data); S.push(x->rc); x = x->lc;
    }
}
template<typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST& visit){
    stack<BinNodePosi(T)> S;
    while(true){
        visitAlongLeftBranch(x, visit, S);
        if(S.empty())  break;
        x = S.top(); S.pop();
    }
}

template<typename T>
void goAlongLeftBranch(BinNodePosi(T) x, stack<BinNodePosi(T)>& S){
    while(x) {
        S.push(x); x = x->lc;
    }
}
template<typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST& visit){
    stack<BinNodePosi(T)> S;
    while(true){
        goAlongLeftBranch(x, S);
        if(S.empty()) break;
        x = S.top(); S.pop(); visit(x->data);
        x = x->rc;
    }
}
template<typename T>
BinNodePosi(T) BinNode<T>::succ(){
    BinNodePosi(T) s = this;
    if(rc){
        s = rc;
        while(HasLChild(s)) s = s->lc;
    }
    else{
        while(IsRChild(s)) s = s->parent;
        s = s->parent; 
    }
    return s;
}
template<typename T, typename VST>
void travIn_I2(BinNodePosi(T) x, VST& visit){
    stack<BinNodePosi(T)> S;
    while(true){
        if(x){ S.push(x); x = x->lc; }
        else if(!S.empty())
        { x = S.top(); S.pop(); visit(x->data); x = x->rc; }
        else break;
    }
}
template<typename T, typename VST>
void travIn_I3(BinNodePosi(T) x, VST& visit){
    bool backtrack = false;
    while(true){
        if(!backtrack && HasLChild(x))   // 若有左子树且不是刚刚回溯
            x = x->lc;                  // 深入变量左子树
        else{                           // 无左子树或刚刚回溯
            visit(x->data);             // 访问该节点
            if(HasRChild(x)){           // 若右子树不为空
                x = x->rc; backtrack = false; //深入右子树
            }
            else{                       // 若右子树空
                if(!(x = x->succ())) break;  // 回溯
                backtrack = true;       // 设置回溯标志
            }
        }
    }
}

template<typename T>                    // 以S栈顶结点为根的子树中，找到最高左侧可见叶节点
static void gotoHLVFL(stack<BinNodePosi(T)>& S){
    while(BinNodePosi(T) x = S.top()){
        if(HasLChild(x)){
            if(HasRChild(x)) S.push(x->rc);
            S.push(x->lc);
        }
        else S.push(x->rc);
    }
    S.pop();                            // 退出循环时栈顶为空指针，需要弹出                
}

template<typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit){
    stack<BinNodePosi(T)> S;
    if(x) S.push(x);
    while(!S.empty()){
        if(S.top() != x->parent)     // 若当前栈顶不为x的父亲节点，则必为右兄弟节点（因为入栈顺序是如果有右兄弟节点，则先入栈）
            gotoHLVFL(S);
        x = S.top(); S.pop(); visit(x->data);
    }
}

template<typename T>
template<typename VST> void BinNode<T>::travLevel(VST& visit){
    queue<BinNodePosi(T)> Q;
    Q.push(this);
    while(!Q.empty()){
        BinNodePosi(T) x = Q.front(); Q.pop(); visit(x->data);
        if(HasLChild(x))    Q.push(x->lc);
        if(HasRChild(x))    Q.push(x->rc);
    }
}







