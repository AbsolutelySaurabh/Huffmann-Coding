class Node
{
public:

    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data,int freq)
    {
        this->data=data;
        this->freq=freq;
        left=right=NULL;

    }

};



