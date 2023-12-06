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
    // Other private members?
};

template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
    vector_array = MyVector<T>();
    strictly_larger_operator =  C();
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
    // Temp solution
    vector_array.clear();
}

/**
 * @brief Inserts t into vector_array by finding its correct position using comperator.
 * @tparam T type of element
 * @tparam C comparator
 * @param t element to be pushed into order.
 */
template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    if(vector_array.empty()){
        vector_array.push_back(t);
    }else{
        unsigned i = 0;
        while(i < vector_array.size() && strictly_larger_operator(t, vector_array[i])){
            i++;
        }
        vector_array.push_back(t);
        for(unsigned j = vector_array.size()-1; j > i; j--){
            vector_array[j] = vector_array[j-1];
        }
        vector_array[i] = t;
    }

}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){

    for(unsigned i = 1; i < vector_array.size(); i++){
        vector_array[i-1] = vector_array[i];
    }
    vector_array.pop_back();
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
