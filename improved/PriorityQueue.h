#ifndef PQ_NODE_H
#define PQ_NODE_H

#include<bits/stdc++.h>
#include "Node.h"

template <typename T>
class PriorityQueue{

    public:
        vector<Node<T>*> v;

    private: int getLeftChildIndex(int index){
        return 2*index + 1;
    }

    private: int getRightChildIndex(int index){
        return 2*index + 2;
    }

    private: int getParentIndex(int index){
        return (index-1)/2;
    }

    private: bool hasLeftChild(int index){
        int flag = false;
        if(getLeftChildIndex(index) < v.size()){
            flag = true;
        }
        return flag;
    }

    private: bool hasRightChild(int index){
        int flag = false;
        if(getRightChildIndex(index) < v.size()){
            flag = true;
        }
        return flag;
    }

    private: bool hasParentChild(int index){
        return true;
    }

    private: void swap(int index, int maxIndex){
        Node<T> *temp = v[index];
        v[index] = v[maxIndex];
        v[maxIndex] = temp;
    }

    private: void max_heapify(int index){

        int arr_size = v.size();
        //need to go from down to up, for max heapify
        int floor = (arr_size)/2 - 1;

        while(floor >= 0){

            int minIndex = floor;
            Node<T> *parent = v[minIndex];

            if(hasLeftChild(floor)){
                Node<T> *leftChild = v[getLeftChildIndex(floor)];
                if(leftChild !=NULL && parent!=NULL){

                    if(leftChild->frequency < v[minIndex]->frequency){
                        minIndex = getLeftChildIndex(floor);
                    }
                }
            }

            if(hasRightChild(floor)){
                Node<T> *rightChild = v[getRightChildIndex(floor)];
                if(rightChild != NULL && parent!=NULL){

                    if(rightChild->frequency < v[minIndex]->frequency){
                        minIndex = getRightChildIndex(floor);
                    }
               }
            }

            swap(floor, minIndex);
            floor--;

        }

    }

    public: Node<T>* getMin(){
        //here, v[0]->data returns char*, which is of pointer type, hence need to dereference it.
        return v[0];
    }

    public: void popMin(){

        Node<T> *popped = v[0];
        v.erase(v.begin() + 0);
        max_heapify(0);
        //cout<<"removed: data: "<<popped->data<<" priority: "<<popped->frequency<<endl;
        //return popped;
    }

    public: void insert(Node<T> *node){

        v.push_back(node);
        //run max_heapify after insertion
        max_heapify(0);
        cout<<"after heapify min: "<<endl;
        for(int i=0;i<v.size();i++){
            cout<<"data: "<<v[i]->data<<" priority: "<<v[i]->frequency<<endl;
        }
    }

    public: int getSize(){
        return v.size();
    }

    public: void printData(){
        cout<<"size: "<<v.size()<<endl;
        for(int i=0;i<v.size();i++){
            cout<<"pq data: "<<v[i]->data<<" pq frequency: "<<v[i]->frequency<<endl;
        }
    }

};
#endif // PQ_NODE_H
