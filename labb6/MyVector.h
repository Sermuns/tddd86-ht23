// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
#include <ostream>
#include <istream>
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

    // private members?

    unsigned numberOfElements; // how much of the vector that is ACTUALLY full.
    unsigned capacity; //
    T* elements; //template

};

template<typename T>
MyVector<T>::MyVector(){

    capacity = 1;
    numberOfElements = 0;
    elements = new T[capacity]; // for fishes :D

}

template<typename T>
MyVector<T>::~MyVector(){
    //Delete all fishes :D
    delete[] elements;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    if(this == &other) return; // prevent self copy

    numberOfElements = other.numberOfElements;
    capacity = other.capacity;
    elements = new T[capacity];

    // Deep copy -_- zZzZzZ
    for(int i = 0; i < other.numberOfElements; i++){
        elements[i] = T(other.elements[i]);
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if(this != &other){
        numberOfElements = other.numberOfElements;
        capacity = other.capacity;
        elements = new T[capacity];

        // Deep copy -_- zZzZzZ
        for(int i = 0; i < other.numberOfElements; i++){
            elements[i] = other.elements[i];
        }
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if(numberOfElements > capacity) return;
    T* tempElements = new T[capacity+1];

    for(int i = 0; i < numberOfElements; i++){
        tempElements[i] = elements[i];
    }
    delete[] elements;
    elements = tempElements;

    elements[numberOfElements] = e; // last element
    numberOfElements += 1;
}

template<typename T>
void MyVector<T>::pop_back(){
    //element is still there :(( maybe ok? maybe not.... :/
    if(numberOfElements == 0) return;

    elements[numberOfElements - 1].~T();
    numberOfElements -= 1;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    if (i >= numberOfElements)
        MYEXCEPTION("OUT OF BOUNDS");

    return elements[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i) const {
    if (i >= numberOfElements)
        MYEXCEPTION("OUT OF BOUNDS");

    return elements[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    for(int i = 0; i < numberOfElements; i++) {
        elements[i] = nullptr;
    }
    numberOfElements = 0;
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return elements;
}

template<typename T>
T* MyVector<T>::end(){
    return elements + numberOfElements;
}

#endif // MY_VECTOR_H
