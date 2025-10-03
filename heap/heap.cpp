#include <iostream>

/*
In this exercise, we will implement heap as discussed in the class.
We need to implement the following functions.


ONLY THIS FILE MUST BE MODIFIED FOR SUBMISSION

You may edit main.cpp for writing more test cases.
But your code must continue to work with the original main.cpp


THERE IS ONLY ONE TEST CASE ONLY FOR YOUR UNDERSTANDING.

-- You may need to generate more random tests to get your tests right
-- Print will not work until you have a good printing function
*/


#include "heap.h"


int Heap::parent(int i) {
  return (i-1)/2; // dummy return
}

int Heap::left(int i) {
  return 2*i+1; // dummy return
}

int Heap::right(int i) {
  return 2*i+2; //dummy
}

int Heap::max() {
  return store[0]; //dummy
}

void Heap::swap(int i, int j) {
  int temp=store[i];
  store[i]=store[j];
  store[j]=temp;
  swap_count++;
}

void Heap::insert(int v) {
  store.push_back(v);
  int i=store.size()-1;
  while(store[i]>store[parent(i)] && i>0){
    swap(i,parent(i));
    i=parent(i);
  }
}

void Heap::heapify(int i,int n) {
  if(i<0) return;
  int largest=i;
  if(left(i)<n && store[left(i)]>store[largest]){
    largest=left(i);
  }
  if(right(i)<n && store[right(i)]>store[largest]){
    largest=right(i);
  }
  if(largest!=i){
    swap(i,largest);
    heapify(largest,n);
  }
}


void Heap::deleteMax() {
  if(store.empty()) return;
  swap(0,store.size()-1);
  store.pop_back();
  if (!store.empty()) {
      heapify(0,store.size());                          
  }
}

void Heap::buildHeap() {
  int n=store.size();
  for(int i=(n-1)/2;i>=0;i--){
    heapify(i,n);
  }
}

void Heap::heapSort() {
  int heapSize = store.size();  // logical size
  while (heapSize > 1) {
      swap(0, heapSize - 1);     // move max to end
      heapSize--;                // reduce heap size
      heapify(0,heapSize);      // heapify within heapSize
  }

}


