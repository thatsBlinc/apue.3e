#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void printAdd(void* addr){
   printf("==> 0x%x\n",(unsigned long)addr);
   return;
}

struct node{
   int data;
   node* next;
   
   void show(){
      cout<<this->data<<endl;
      cout<<this->next<<endl;
   }
private: 
   node(){}
   node(int d){}
};

node* nodeFactory(void* addr,int data,unsigned long next){
   printAdd(addr);
   if(addr==NULL)
      return NULL;
   node* ptr=(node*)addr;
   ptr->data=data;
   ptr->next=(node*)next;
   return ptr;
}

int main() {
   void* addr = malloc(sizeof(node));
   cout<<"before casting!"<<endl;
   printAdd(addr);
   /*
   node* ptr=(node*)addr;
   ptr->data=123;
   ptr->next=(node*)0x123;
   cout<<"after casting!"<<endl;
   printAdd(addr);
   */

   cout<<"factory mode:"<<endl;
   auto ptr = nodeFactory(addr,123,0x123);
   if(ptr!=NULL)
      ptr->show();   
   return 0;
}