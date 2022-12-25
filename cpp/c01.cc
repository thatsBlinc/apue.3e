#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void printAdd(void* addr){
   printf("==> 0x%lx\n",(unsigned long)addr);
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

node* nodeFactory(void* addr, size_t size, int data,unsigned long next){
   printAdd(addr);
   if(addr==NULL){
      cout<<"[nodeFactory]: invalid addr"<<endl;
      return NULL;
   }
   if(size!=sizeof(node)){
      cout<<"[nodeFactory]:  wrong size"<<endl;
      return NULL;
   }
   node* ptr=(node*)addr;
   ptr->data=data;
   ptr->next=(node*)next;
   return ptr;
}

int main() {
   void* addr = malloc(sizeof(node));
   cout<<"[main] before casting!"<<endl;
   printAdd(addr);
   /*
   node* ptr=(node*)addr;
   ptr->data=123;
   ptr->next=(node*)0x123;
   cout<<"after casting!"<<endl;
   printAdd(addr);
   */

   cout<<"[main] factory mode:"<<endl;
   auto ptr = nodeFactory(addr,16,123,0x123);
   if(ptr!=NULL)
      ptr->show();   
   return 0;
}