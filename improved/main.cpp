#include<bits/stdc++.h>
#include "Node.h"
#include "PriorityQueue.h"
#include "InputNode.h"
#include<string>

using namespace std;

vector<InputNode<char>*> v;
//vector to store the final data
vector<Node<char>*> v_huff;

vector<InputNode<char>*> calc_frequencies(string input){

    map<char, int> mp;
    map<char, int>::iterator it;

    for(int i=0;i<input.size();i++){

        if(mp.find(input[i])!=mp.end()){
            mp.insert(pair<char, int>(input[i], mp.find(input[i])->second++ ));
        }else{
            mp.insert(pair<char, int>(input[i], 1));
        }
    }

    //printing frequencies
    //store in vector from map, to make it easy for priority queue
    for(it=mp.begin();it!=mp.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
        InputNode<char> *node = new InputNode<char>(it->first, it->second);
        if(it->first != ' '){
            v.push_back(node);
        }
    }
    return v;

}

void print_pq(Node<char>* node){
    if(node == NULL){
        return;
    }
    print_pq(node->leftChild);
    print_pq(node->rightChild);
    cout<<"data: "<<node->data<<" frequency: "<<node->frequency<<endl;
}

void build_up_huffmann_tree(PriorityQueue<char> pq){

    cout<<endl;
    Node<char> *parentNode = NULL;
    while(pq.getSize() > 1){

        //PqNode needs template of pointer type, whereas PriorityQueue doesn't
        Node<char> *min_node_1 = pq.getMin();
        //as data is itself of pointer type, so need to dereference it too.
        pq.popMin();

        Node<char> *min_node_2 = pq.getMin();
        pq.popMin();

        Node<char> *leftChild = new Node<char>(min_node_1->data,'0', min_node_1->frequency);
        leftChild->leftChild = min_node_1->leftChild;
        leftChild->rightChild = min_node_1->rightChild;

        Node<char> *rightChild = new Node<char>(min_node_2->data,'0', min_node_2->frequency);
        rightChild->leftChild = min_node_2->leftChild;
        rightChild->rightChild = min_node_2->rightChild;

        //using ` as a sign, in parent data to detect it further.
        parentNode = new Node<char>('~', '0', min_node_1->frequency + min_node_2->frequency);
        parentNode->addLeftChild(leftChild);
        parentNode->addRightChild(rightChild);

        //do not need data value in the heap tree.
        pq.insert(parentNode);

    }
    v_huff.push_back(parentNode);
}

void traverse_huffmann_tree(Node<char> *node, string code){

    if(node->leftChild == NULL && node->rightChild == NULL && node->data != '~'){
        cout<<"code length: "<<code.length();
        bitset<8> b(code);
        node->weight = b;
        cout<<"data: "<<node->data<<"   :   priority: "<<node->frequency<<"   code: "<<code<<endl;
        cout<<"bitset: "<<node->weight<<"  :  "<<b<<endl;
        //reset the code
        code="";
        return;
    }
    traverse_huffmann_tree(node->leftChild, code+"0");
    traverse_huffmann_tree(node->rightChild, code+"1");

}

void calc_huffmann_codes(){

    ///traversing from the backward of v_huff, as the last node(toppest) is pushed lastly

   traverse_huffmann_tree(v_huff[v_huff.size()-1], "");

}

int main(){

    PriorityQueue<char> pq;

    cout<<"Enter string: "<<endl;
    string str;
    getline(cin, str);

    calc_frequencies(str);

    ///building priority queue
    for(int i=0;i<v.size();i++){
        Node<char> *node = new Node<char>(v[i]->data,'0', v[i]->frequency);
        pq.insert(node);
    }

    build_up_huffmann_tree(pq);

    ///now i have all the data in v_huff, now only need to traverse it to get the BYTE codes
    calc_huffmann_codes();

    return 0;
}
