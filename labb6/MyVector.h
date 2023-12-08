// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
#include <iostream>

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;

private:
    T* storage;
    unsigned capacity = 1;
    unsigned numberOfElements = 0;
};

template<typename T>
MyVector<T>::MyVector(){
  storage = new T[capacity];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
     if(other == this) MYEXCEPTION("Self assignment");

    this->capacity = other.capacity;

    for(unsigned i = 0; i < other.numberOfElements; i++){
       *storage[i] = *other.storage[i];
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if(other == this) MYEXCEPTION("Self assignment");

    storage = new T[other.capacity];
    for(unsigned i = 0; i < other.numberOfElements; i++){
       *storage[i] = *other.storage[i];
    }

    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if(numberOfElements == capacity) {
    capacity = capacity * 2;
    T* tempStorage = new T[capacity];

    for(unsigned i = 0; i < numberOfElements; i++){
        tempStorage[i] = storage[i];
    }
    delete[] storage;
    storage = tempStorage;
    }

    storage[numberOfElements] = e;
    numberOfElements++;


}

template<typename T>
void MyVector<T>::pop_back(){
    numberOfElements--;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    delete[] storage;

    numberOfElements = 0;
    capacity = 1;
    storage = new T[capacity];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return storage;
}

template<typename T>
T* MyVector<T>::end(){
    return storage + numberOfElements;
}

#endif // MY_VECTOR_H
