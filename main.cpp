//HW4 by Dane Brazinski
//SU Net ID: dbbrazin SUID: 533140379
//HW4 Due: Friday March 6 at 11:59pm
#include <iostream>
#include <list>
#include <string>

using namespace std;
template <class T> class ThreeD {
public:
    T ht;
    T wid;
    T dep;
    ThreeD() :ht(0), wid(0), dep(0) {}
    ThreeD(T i, T j, T k) :ht(i), wid(j), dep(k) {}
    T getVol() const { return ht * wid * dep; }
    bool operator==(const ThreeD<T>& t) { return getVol() == t.getVol(); }
};

template <class T> class node {
public:
    T value;
    node<T>* next;
    node<T>* previous;
    node<T>() { next = nullptr; previous = nullptr; }
    node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
    bool operator==(const node<T>& t) const { return value == t.value; }
};

template <class T> class linked_list {
public:
    node<T>* head;
    node<T>* tail;
    linked_list() { head = tail = nullptr; }
    linked_list(const initializer_list<T>& V);
    void push_back(T t);
    bool operator==(const linked_list<T>& L) const;
    //Two linkes lists are equal if they have same number of nodes
    //and their respective node values are all equal

    linked_list(const linked_list<T>& L); //copy constructor
    linked_list(linked_list<T>&& L); //move constructor
    ~linked_list();//destructor
    void operator=(const linked_list<T>& L);//L-value operator=
    void operator=(linked_list<T>&& L);//R-value operator=
    template <class S> friend ostream& operator<<(ostream& s, const linked_list<S>& L);
};
template <class T> linked_list<T>::linked_list(const initializer_list<T>& V) : linked_list() {
    //Your implementation
    //head = nullptr;
    //tail = nullptr;
    auto it = V.end() - 1;
    while (it != V.begin() - 1) {
        node<T>* p = new node<T>(*it);
        p->next = head;
        head = p;
        if(p->next)
            p->next->previous = p;
        if(!tail)
            tail = p;
        it--;
    }
    cout << "LinkedList::Initializer_list" << endl;
}

template <class T> linked_list<T>::~linked_list() {  //destructor
    //Your implementation
    while(head){
        node<T>*p = head->next;
        delete head;
        head = p;
    }
    cout << "LinkedList::Destructor" << endl;
}

template <class T> linked_list<T>::linked_list(const linked_list<T>& L) : linked_list() { //copy constructor																			  																		  //num_nodes = 0;
    //Your implementation
    node<T>* p1 = L.tail;
    while (p1) {
        node<T>* p = new node<T>();
        p->next = head;
        head = p;
        if(p->next)
            p->next->previous = p;
        if(!tail)
            tail = p;
        p1 = p1->previous;
    }
    p1 = head;
    node<T>* p2 = L.head;
    while (p1) {
        p1->value = p2->value;
        p1 = p1->next;
        p2 = p2->next;
    }
    cout << "LinkedList::Copy Constructor" << endl;
}
template <class T> linked_list<T>::linked_list(linked_list<T>&& L) {//move constructor
    //Your implementation
    head = L.head;
    tail = L.tail;
    L.head = nullptr;
    L.tail = nullptr;
    cout << "LinkedList::Move constructor" << endl;
}

template <class T> void linked_list<T>::operator=(const linked_list<T>& L) { //L=value operator=
    //Your implementation
    while (head) {
        node<T>* p = head->next;
        delete head;
        head = p;
    }
    node<T>* p1 = L.tail;
    while (p1) {
        node<T>* p = new node<T>();
        p->next = head;
        head = p;
        if(p->next)
            p->next->previous = p;
        if(!tail)
            tail = p;
        p1 = p1->previous;
    }
    p1 = head;
    node<T>* p2 = L.head;
    while (p1) {
        p1->value = p2->value;
        p1 = p1->next;
        p2 = p2->next;
    }

    cout << "LinkedList::L value Operator=" << endl;
}

template<class T> void linked_list<T>::operator=(linked_list<T>&& L) {//R-value operator=
    //Your implementation
    while (head) {
        node<T>* p = head->next;
        delete head;
        head = p;
    }

    head = L.head;
    tail = L.tail;
    L.head = nullptr;
    L.tail = nullptr;
    cout << "LinkedList::R-value operator=" << endl;
}




template <class T> void linked_list<T>::push_back(T t)
{
    node<T>* p = new node<T>(t);
    if (head == nullptr) { head = tail = p; }

    else {
        p->previous = tail;
        tail->next = p;
        tail = p;
    }
}

template <class T> bool linked_list<T>::operator==(const linked_list<T>& L) const {
    //2 linked lists are equal if they have the same number of nodes and values of all nodes, repectively are equal
    //Your implementation
    node<T>* p1 = head;
    node<T>* p2 = L.head;
    while (p1 && p2) {
        if(!(p1->value == p2->value))
            return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return true;
}




template <class T> class Node {
public:
    T value;
    Node<T>* l_child;
    Node<T>* r_child;
    Node() : l_child(nullptr), r_child(nullptr){}
    Node(T i) :value(i), l_child(nullptr), r_child(nullptr) {}
    bool operator==(const Node<T>& n) const { return value == n.value; }
};

//For implementing the member functions of class Tree,
//you are allowed to create extra recursive member functions
//to be called by the member functions that you are required to implement


template <class T> class Tree { //an n-level full binary tree of 2^n - 1 nodes
public:
    Node<T>* root;
    Tree() : root(nullptr) {}
    Tree(const initializer_list<T>& I);
    Tree(const Tree<T>& t);//copy constructor
    ~Tree(); //destructor
    void operator=(const Tree<T>& t);//L-value operator=
    Tree<T> Three_Times();

    Tree(Tree<T>&& t); //move constructor
    void operator=(Tree<T>&& t);//R-value operator=

    Node<T>* makeTree(int n);
    Node<T>* find(Node<T>* p, const T& v);
    bool operator==(const Tree<T>& t);

    Node<T>* Tree_initializer(const initializer_list<T>& L, int* i, int s);
    void printTree(Node<T> *p, ostream& str) const;
    void destroyTree(Node<T>* tree);
    bool compare(const Node<T>& t1, const Node<T>& t2);
    Node<T>* makeCopy(const Node<T>* o);
    Node<T>* makeThreeTimes(const Node<T>* o);
};
template <class T> bool Tree<T>::operator==(const Tree<T>& t) {
    //Your implementation
    return compare(*root,*t.root);
}

template<class T> bool Tree<T>::compare(const Node<T>& t1, const Node<T>& t2){
    if((t1.l_child == nullptr && t2.l_child == nullptr) && (t1.r_child == nullptr && t2.r_child == nullptr))
        return true;
    else if((t1.l_child == nullptr ^ t2.l_child == nullptr) || (t1.r_child == nullptr ^ t2.r_child == nullptr))
        return false;
    else if(!(t1 == t2))
        return false;
    else
        return compare(*t1.l_child,*t2.l_child) && compare(*t1.r_child,*t2.r_child);
}

template <class T> Node<T>* Tree<T>::find(Node<T>* p, const T& v) {
    //Return the pointer to a node whose value is equal to v
    //Your implementation
    if(p == nullptr){
        return p;
    }
    else if(p->value == v){
        return p;
    }
    else {
        auto t1 = find(p->l_child, v);
        auto t2 = find(p->r_child, v);
        if(t1)
            return t1;
        else if(t2)
            return t2;
    }
    return nullptr;
}

template <class T> void Tree<T>::operator=(Tree<T>&& t) {
    //Your implementation
    destroyTree(root);
    root = t.root;
    t.root = nullptr;
    cout << "Tree::R-value operator=" << endl;
}

template <class T> Tree<T>::Tree(Tree<T>&& t) { //Move constructor
    //Your implementation
    root = t.root;
    t.root = nullptr;
    cout << "Tree::move constructor" << endl;
}


template <class T> Tree<T> Tree<T>::Three_Times() {
    //Return a tree which has the same number of nodes as the current tree and
    //all node values are three times of that of the current tree.

    //Your implementation
    Tree<T> tree;
    tree.root = makeThreeTimes(root);
    return tree;
}

template <class T> Node<T>* Tree<T>::makeThreeTimes(const Node<T>* o){
    if(o == nullptr){
        return nullptr;
    }
    Node<T>* p = new Node<T>(o->value*3);
    p->l_child = makeThreeTimes(o->l_child);
    p->r_child = makeThreeTimes(o->r_child);
    return p;
}



template <class T> Tree<T>::~Tree() { //destructor

    destroyTree(root);
    delete root;
    cout << "Tree::destructor" << endl;
}

template <class T> void Tree<T>::destroyTree(Node<T>* node) {
    if(node == nullptr) {
        delete node;
        return;
    }
    destroyTree(node->l_child);
    destroyTree(node->r_child);
    //delete node;


//    Node<T> l, r;
//    if(node->l_child != nullptr)
//        l = *node->l_child;
//    if(node->r_child != nullptr)
//        r = *node->r_child;
//    if(node->l_child != nullptr)
//        destroyTree(&l);
//    if(node->r_child != nullptr)
//        destroyTree(&r);
//    delete node;
}

template <class T> void Tree<T>::operator=(const Tree<T>& t) { //L-value operator=
    //Your implementation
    destroyTree(root);
    root = makeCopy(t.root);
    cout << "Tree::L-value Operator=" << endl;
}


template <class T> Tree<T>::Tree(const Tree<T>& t) {//copy constructor
    //Your implementation
    root = makeCopy(t.root);
    cout << "Tree::copy constructor" << endl;
}

template <class T> Node<T>* Tree<T>::makeCopy(const Node<T>* o){
    if(o == nullptr){
        return nullptr;
    }
    Node<T>* p = new Node<T>(o->value);
    p->l_child = makeCopy(o->l_child);
    p->r_child = makeCopy(o->r_child);
    return p;
}


template <class T> Tree<T>::Tree(const initializer_list<T>& L) :Tree() {
    //Your implementation
    int* i = new int{ 0 };
    root = nullptr ;
    if (L.size () > 0) root = Tree_initializer(L, i, L.size());
    cout << "Tree::initializer list" << endl;
}


template <class T> Node<T>* Tree<T>::Tree_initializer(const initializer_list<T>& L, int* i, int s) {
    //Create an n-level full binary tree without initial values
    //Your implementation
    Node<T>* p = new Node<T>();
    if (s && L.begin() + (*i) != L.end()) {
        p->l_child = Tree_initializer(L, i, s/2);
        p->value = *(L.begin() + (*i));
        *i = *i + 1;
        p->r_child = Tree_initializer(L, i, s/2);
        return p;
    }
    return nullptr ;
}


template <class T> Node<T>* Tree<T>::makeTree(int n) {
    //Create an n-level full binary tree without initial values
    //Your implementation
    Node<T>* p = new Node<T>();
    if (n == 1) return p;
    p->l_child = makeTree(n - 1);
    p->r_child = makeTree(n - 1);
    return p;
}


template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
    //Your implementation
    return str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
}

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L) {
    //Your implementation
    node<T>* p = L.head;
    str << "[";
    while (p) { str << p->value << (p->next?" ":""); p = p->next; }
    return str << "]";
}


//You can create extra recursive function, to be called by the following function.
template <class T> ostream& operator<<(ostream& str, const Tree<T>& t) { //in-order printing
    //Your implementation
    str << "{ ";
    t.printTree(t.root, str);
    return str << "}";

}

template <class T> void Tree<T>::printTree(Node<T>* p, ostream& str) const { //in-order printing
    if (p == nullptr) return;
    printTree(p->l_child, str);
    str << (p->value) << " ";
    printTree(p->r_child, str);
}


int main() {
//    linked_list<int> m {1,2,3,4};
//    linked_list<int> m2 = m;
//    linked_list<int> m3 {4,3,2,1};
//    cout<< ((m3 == m2) ? "Equal" : "Not equal" )<< endl;
//    m3 = m2;
//    cout << m3 << endl;
//    cout<< ((m3 == m2) ? "Equal" : "Not equal" )<< endl;

    Tree<int> T3{ 1,2,3, 4, 5, 6, 7 };
    cout << T3 << endl;

    Tree<int> T4{ T3 };
    cout << T4 << endl;
    Tree<int> T5;
    T5 = T4;
    cout << T5 << endl;
    Tree<int> T6;
    T6 = T3.Three_Times();
    cout << T6 << endl;
    ThreeD<int> t1{ 3,4,5 }, t2{ 7, 1, 4 }, t3{ 6, 7, 3 }, t4{ 8,4,2 },
            t5{ 1, 8, 8 }, t6{ 10,3,2 }, t7{ 9,5,4 }, t8{ 1,5,36 }, t9{ 8, 8, 2 }, t10{ 5,6,2 };
    Tree<linked_list<ThreeD<int>>> T7{ {{3,4,5},{7,1,4},{6,7,3}},{{8,4,2},{8,8,2}}, {{9,5,4},{10,3,2},{7,9,1},{2,2,3}} };
    cout << T7 << endl;
    linked_list<ThreeD<int>> L1{ {2,18,5},{10,3,2},{7,9,1},{3,1,4} };
    Node<linked_list<ThreeD<int>>>* p1 = T7.find(T7.root, L1);
    cout << p1->value << endl;

    Tree<linked_list<ThreeD<int>>> T8{ {{5,4,3},{7,2,2},{7,6,3}},{{8,4,2},{8,2,8}}, {{9,2,10},{10,3,2},{7,3,3},{2,2,3}} };
    if (T7 == T8) cout << "EQUAL" << endl;
    else cout << "NOT EQUQL" << endl;


    Tree<linked_list<ThreeD<int>>>* p2 = new Tree<linked_list<ThreeD<int>>>
            { {{3,4,5},{7,1,4},{6,7,3}},{{8,4,2},{8,8,2}}, {{9,5,4},{10,3,2},{7,9,1},{2,2,3}} };
    cout << *p2 << endl;
    delete p2;

    return 0;
}

/*
//Sample Screenshot

Tree::initializer list
{ 1 2 3 4 5 6 7 }
Tree::copy constructor
{ 1 2 3 4 5 6 7 }
Tree::L - value Operator =
{ 1 2 3 4 5 6 7 }
Tree::copy constructor
Tree::move constructor
Tree::destructor
Tree::R - value operator=
Tree::destructor
{ 3 6 9 12 15 18 21 }
Tree::initializer list
{ [(3, 4, 5) (7, 1, 4) (6, 7, 3)] [(8, 4, 2) (8, 8, 2)] [(9, 5, 4) (10, 3, 2) (7, 9, 1) (2, 2, 3)] }
[(9, 5, 4) (10, 3, 2) (7, 9, 1) (2, 2, 3)]
Tree::initializer list
EQUAL
Tree::initializer list
{ [(3, 4, 5) (7, 1, 4) (6, 7, 3)] [(8, 4, 2) (8, 8, 2)] [(9, 5, 4) (10, 3, 2) (7, 9, 1) (2, 2, 3)] }
Tree::destructor
Tree::destructor
Tree::destructor
Tree::destructor
Tree::destructor
Tree::destructor
Tree::destructor

*/
