// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include <cmath>

template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

  unsigned size() const;

private:
  void siftDown(int index){
      while(true)
      {
          int leftChildIndex = 2*index +1;
          int rightChildIndex = leftChildIndex +1;
          if(leftChildIndex > vector_array.size()) break;


           if(strictly_larger_operator(vector_array[index], vector_array[leftChildIndex])){
                swap(index, leftChildIndex);
                index =leftChildIndex;
           }
           else if(strictly_larger_operator(vector_array[index], vector_array[rightChildIndex])){
               swap(index, rightChildIndex);
               index = rightChildIndex;
           }
           else{
               break;
           }

      }
  }
  void siftUp(int index){
      while(true)
      {
          int parentIndex = ceil(index/2);

          if(index == 0) break;

          if(strictly_larger_operator(vector_array[parentIndex], vector_array[index])){
              swap(index, parentIndex);
              index = parentIndex;
          }
          else{
              break;
          }
      }
  }
  void swap(int index, int indexTwo){
      const auto& tempHolder = vector_array[index];
      vector_array[index] = vector_array[indexTwo];
      vector_array[indexTwo] = tempHolder;
  }

};


template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
    vector_array = MyVector<T>();
    strictly_larger_operator = C();
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
    delete &vector_array;

}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    while(true){

    }
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    swap(0, *vector_array.end());
    vector_array.pop_back();
    siftDown(0);

}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H
