///THE PROBLEM NOW IS AS THE 0S AND 1S ARE STORED AS TRHE STRING DATA TYPES SO THEY ARE TAKING MUCH MEMORY INSPITE OF TAKING 1 BITS
#include <bits/stdc++.h>
#include<typeinfo>
#include<fstream>
#include<map>
#include<cstring>
#include<vector>
#include "Node.h"
//#include"compare.h"

using namespace std;

///NOTE:-

///In UNORDERED_MAP there is no order in which the elements will be stored,, so what to do to Decompress.

///In MAP elements are stored in ascending order.

///EveryTime you need to delete the older OUTPUT.TXT file otherwise it'll overwrite it.

///###DID PRE-ORDER TRAVERSAL FOR DECOMPRESSION.


struct compare
{
    bool operator()(Node* l, Node* r)
    {
        return (l->freq > r->freq);
    }
};


void CompressionRatio(int filesize)
{
    int newsize=0;
    ifstream f;
    f.open("output.txt");

   if(f.fail())
   {
       cout<<" File Not Found....."<<endl;
       exit(0);

   }

   char c;

   c=f.get();

    while(!f.eof())
    {
     if(sizeof(c)==1)
     {
      newsize+=1;
     }else
     if(sizeof(c)==4)
      {
       newsize+=4;

      }
      c=f.get();

    }

    cout<<endl<<"The size of the newfile is :"<<newsize<<"bytes"<<endl;

    float difference =(abs(filesize-newsize));

    float ratio=difference/filesize;

    cout<<ratio;

    cout<<"Compression ratio : "<<ratio*100<<"%"<<endl;
}


void Decompression(Node *root)
{
    ofstream myfile;


    myfile.open("decompress.txt",ios::app|ios::binary|ios::in);


    if(root==NULL)
    {
        return;


    }


    Decompression(root->left);
    if(root->data != '$')
    {
    cout<<root->data;
    myfile<<root->data;
    }


    Decompression(root->right);

}

void ArrayOutput(vector<bool>arr){

    vector<bool>::iterator it;

    for(it=arr.begin();it!=arr.end();it++){

        cout<<*it;

    }

    cout<<endl<<endl;


}

void PrintCodes(Node *root,string str)
{
    ofstream myfile;


    myfile.open("output.txt",ios::app|ios::binary|ios::in);

    if(!root)
    {
        return;
    }
    if(root->data!='$')
       {
           vector<bool>arr;

           cout<<root->data<<" "<<str<<endl;
           myfile<<str;

           //cout<<strlen(str);

           for(int i=0;i<strlen(str);i++){

                arr.push_back(str[i]);


           }

           ArrayOutput(arr);



           //myfile.close();
       }

    PrintCodes(root->left,str+"0");
    PrintCodes(root->right,str+"1");




}

Node* buildHuffmanTree(map<char,int>mp,int size)
{
    //ofstream myfile;
    //myfile.open("newd.jpg");
    priority_queue<Node*,vector<Node*>,compare>pq;///Its for making priority queue in increasing order

    map<char,int>::iterator it;
    for(it=mp.begin();it!=mp.end();it++)
    {

        pq.push(new Node(it->first,it->second));///Or we can even make the object first then insert it here.
    }

    Node* leftnode;
    Node* rightnode;
    Node* topnode;
   while(pq.size()!=1)
   {
    leftnode=pq.top();///If used queue in place of priority queue then use "front()" here.
    pq.pop();
    rightnode=pq.top();
    pq.pop();

    topnode=new Node('$',leftnode->freq+rightnode->freq);
    topnode->left=leftnode;
    topnode->right=rightnode;

    pq.push(topnode);

   }

   PrintCodes(pq.top(),"\0");///"\0" means NULL;

   return pq.top();
}


main()
{
   // Node* root;

   map<char,int>mp;
   map<char,int>::iterator it;
   int filesize=0;

   ifstream fin;
   char ch,fname[20];


   cout<<"Enter a file name: ";

   cin>>fname;

   fin.open(fname);

   if(fin.fail())
   {
       cout<<" File Not Found....."<<endl;
       exit(0);

   }




   ch=fin.get();
   while(!fin.eof())
   {

       //cout<<ch<<endl;
       it=mp.find(ch);
       if(it!=mp.end())
       {

           it->second++;
       }else
       {

           mp.insert(pair<char,int>(ch,1));
       }


       ///TYPEID returns type of expression t runtime so it cant be stored in any memory in code
       ///To get it stored in any memory place it needs to get returned at the compile time.

//       if(typeid(ch).name()=='c')
//       {
//           filesize+=1;
//
//       }else
//       if(typeid(ch).name()=='i')
//       {
//           filesize+=4;
//       }


       if(sizeof(ch)==1)
       {

           filesize+=1;
       }else

       /// No use of taking the size of INT because it's considering each letter as character.

       if(sizeof(ch)==4)
       {
           filesize+=4;
       }


       ch=fin.get();

   }
   cout<<endl;

    //ofstream myfile;
    //myfile.open("output.txt",ios::app|ios::binary|ios::in);


    cout<<endl<<"The size of the file is : "<<filesize<<"bytes"<<endl;

    cout<<"Do you want to compress or decompress !"<<endl;
    cout<<"1 : Compress \t 2 : Decompress"<<endl;

    Node *root=buildHuffmanTree(mp,mp.size());

    int response;
    cin>>response;


    switch(response)
    {

    case 1:
        cout<<"Let's Compress "<<endl;
        buildHuffmanTree(mp,mp.size());
        break;

    default:
        cout<<"Let's extract the codes "<<endl;
        Decompression(root);

    }


    CompressionRatio(filesize);


}
