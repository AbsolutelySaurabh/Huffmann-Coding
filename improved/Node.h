#ifndef NODE_H
#define NODE_H
///using above is not necessary, but can be to define something initially, to make it compilable.
///refer : http://www.cplusplus.com/doc/tutorial/preprocessor/

#include<bits/stdc++.h>
using namespace std;

///Taking a random 26, because while traversing the Huffmann tree, the codes can be of varying length, so taking 26, as the length might depend on the number of unique characters,
///I am assuming the alphabets only, and hence th max number of uniqueness is 26

///#define : handled by the pre-processor -> means much faster;
///typedef : handled by the compiler -> means things are declared at compile time.

///They're almost the same
///more at : https://stackoverflow.com/questions/1666353/are-typedef-and-define-the-same-in-c

#define M 8
typedef bitset<M> BYTE;

template <typename T>
class Node{

    public:
        //this weight is the code
        BYTE weight;
        int frequency;
        T data;
        Node *leftChild;
        Node *rightChild;

    Node(T data, BYTE weight, int frequency){

        this->data = data;
        this->weight = weight;
        this->leftChild = NULL;
        this->rightChild = NULL;
        this->frequency = frequency;
    }

    public: void addLeftChild(Node *leftChild){
        this->leftChild = leftChild;
    }

    public: void addRightChild(Node *rightChild){
        this->rightChild = rightChild;

    }
};
#endif
