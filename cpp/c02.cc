#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


/*
   dump object layout to file:
   g++ --fdump-class-hierarchy -c  src.cpp
*/

struct Node{
   int data;
   Node* next;
   
   virtual void show(){
      cout<<"show from Node"<<endl;
      cout<<this->data<<endl;
      cout<<this->next<<endl;
   }
   //virtual void sayHi()=0;
private: 
   Node(){}
public:
   Node(int d):data(d),next(NULL){}
};

struct BigNode:public Node{
   BigNode(int a):Node(a)
   {
      cout<<"BigNode"<<endl;
   }
   void show(){
      cout<<"show from BigNode"<<endl;
      Node::show(); //deviced class call base class func
   }
   void sayHi(){ //base class's pure virtual func impl

   }
};

//dynamic cast
void show(Node* n){
   if(n==NULL)
      return;
   if(BigNode* bn=dynamic_cast<BigNode*>(n))
      bn->show();
   else
      n->show();
}

//polymorphism
void show2(Node* n){
   if(n==NULL)
      return;
   n->show();
}

int main() {
   Node* bn=new BigNode(999);
   Node* n=new Node(123);
   cout<<"============1==========="<<endl;
   show(bn);
   show(NULL);
   cout<<"============2==========="<<endl;
   show2(bn);
   show2(n);
   return 0;
}