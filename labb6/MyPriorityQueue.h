// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include <algorithm>
#include "MyVector.h"
#include <iostream>
#include "MyException.h"
#include <cmath>

template <typename T, typename C>
class MyPriorityQueue
{
    C strictly_larger_operator;

public:

    MyVector<T> vector_array;

    /**
     * @brief MyPriorityQueue, constructor for priority queue that initilizes the vector and comparable
     */
    MyPriorityQueue();

    /**
      * @brief Destructor of the priorty queue that deletes the array
      */
    ~MyPriorityQueue();

    /**
     * @brief push element t into the correct spot in the priority queue.
     * @param t element that is getting added.
     */
    void push(const T& t);
    /**
     * @brief top
     * @return the element with the highest priority.
     */
    T top()const;
    /**
     * @brief pop, pops the element with the highest priority and fixes the tree to follow the priorty structure.
     */
    void pop();

    /**
     * @brief empty, checks if array is empty.
     * @return true if array is empty.
     */
    bool empty()const;
    /**
   * @brief size, function to get the size of the array.
   * @return size of array
   */
  unsigned size() const;

private:
  bool isChild(int potentialChildIndex)
  { return  potentialChildIndex < vector_array.size(); }

  /**
   * @brief siftDown, given index gets sifted down in the tree into its "correct" spot depending on the comparable.
   * @param index of wanted element to go down tree.
   */
  void siftDown(int index){
      while(true)
    {
      int leftChildIndex = (2*index) +1;
      int rightChildIndex = leftChildIndex +1;
       if(isChild(leftChildIndex) && strictly_larger_operator(vector_array[index], vector_array[leftChildIndex])){
            swap(index, leftChildIndex);
            index = leftChildIndex;
       }
       else if(isChild(rightChildIndex) && strictly_larger_operator(vector_array[index], vector_array[rightChildIndex]) ){
           swap(index, rightChildIndex);
           index = rightChildIndex;
       }
       else{
           break;
       }

      }
  }
  /**
   * @brief siftUp, given index gets sifted up in the tree into its "correct" positon depending on the comparable.
   * @param index of wanted element to go up tree.
   */
  void siftUp(int index){
      while(true)
      {
          if(index == 0) break;

          int parentIndex = (index - 1)/2;

          if(strictly_larger_operator(vector_array[parentIndex], vector_array[index])){
              swap(index, parentIndex);
              index = parentIndex;
          }
          else{
              break;
          }
      }
  }
  /**
   * @brief swap, helper function to swap positon of 2 indexes.
   * @param index
   * @param indexTwo
   */
  void swap(int index, int indexTwo){
      auto tempHolder = vector_array[index];
      vector_array[index] = vector_array[indexTwo];
      vector_array[indexTwo] = tempHolder;
  }

};


template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
    vector_array = MyVector<T>();
    strictly_larger_operator =  C();
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){

}



template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    siftUp(vector_array.size() - 1);
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    swap(0, vector_array.size()-1);
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
