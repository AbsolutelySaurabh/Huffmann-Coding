#ifndef INPUTNODE_H
#define INPUTNODE_H
#include<bits/stdc++.h>

template <typename T>
class InputNode{

    public:
        int frequency;
        T data;

    public:
        InputNode(T data, int frequency){
            this->data = data;
            this->frequency = frequency;
        }

};

#endif // INPUTNODE_H
