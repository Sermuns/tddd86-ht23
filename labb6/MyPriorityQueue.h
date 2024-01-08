

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include <algorithm>
#include "MyVector.h"
#include <iostream>
#include "MyException.h"
#include <cmath>

template<typename T, typename C>
class MyPriorityQueue {
    C strictly_larger_operator;

public:

    MyVector<T> vector_array;

    /**
     * @brief MyPriorityQueue, constructor for priority queue that initilizes the vector and comparable
     */
    MyPriorityQueue();

    /**
     * @brief push element t into the correct spot in the priority queue.
     * @param t element that is getting added.
     */
    void push(const T &t);

    /**
     * @brief top
     * @return the element with the highest priority.
     */
    T top() const;

    /**
     * @brief pop, pops the element with the highest priority and fixes the tree to follow the priorty structure.
     */
    void pop();

    /**
     * @brief empty, checks if array is empty.
     * @return true if array is empty.
     */
    bool empty() const;

    /**
   * @brief size, function to get the size of the array.
   * @return size of array
   */
    unsigned size() const;

private:
    /**
     * @brief isWithinRange, checks if the index is within the range of the array.
     * @param index  index that is being checked.
     * @return
     */
    bool isWithinRange(int index);

    /**
     * @brief siftDown, given index gets sifted down in the tree into its "correct" spot depending on the comparable.
     * @param index of wanted element to go down tree.
     */
    void siftDown(int index);

    /**
     * @brief siftUp, given index gets sifted up in the tree into its "correct" positon depending on the comparable.
     * @param index of wanted element to go up tree.
     */
    void siftUp(int index);

    /**
     * @brief swap, helper function to swap positon of 2 indexes.
     * @param index
     * @param indexTwo
     */
    void swap(int index, int indexTwo);


};

template<typename T, typename C>
bool MyPriorityQueue<T, C>::isWithinRange(int index) {
    return index < vector_array.size();
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::siftDown(int index) {
    while (index < vector_array.size()) {
        // Find the children
        int leftChildIndex = (index * 2) + 1;
        int rightChildIndex = (index * 2) + 2;

        int smallestChildIndex = index;

        // Check if left child is smaller than parent
        if (isWithinRange(leftChildIndex) &&
            strictly_larger_operator(vector_array[index], vector_array[leftChildIndex])) {
            // Assume left child is smallest
            smallestChildIndex = leftChildIndex;
        }

        // Check if right child is smaller than the smallest child
        if (isWithinRange(rightChildIndex) &&
            strictly_larger_operator(vector_array[smallestChildIndex], vector_array[rightChildIndex])) {
            // Right child is smaller than left child
            smallestChildIndex = rightChildIndex;
        }

        // If no children are smaller, then we are done
        if(smallestChildIndex == index){
            break;
        }

        // Swap the smallest child with the parent
        swap(index, smallestChildIndex);
        index = smallestChildIndex;
    }
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::swap(int index, int indexTwo) {
    T tempHolder = vector_array[index];
    vector_array[index] = vector_array[indexTwo];
    vector_array[indexTwo] = tempHolder;
}


template<typename T, typename C>
MyPriorityQueue<T, C>::MyPriorityQueue() {
    vector_array = MyVector<T>();
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::siftUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (strictly_larger_operator(vector_array[parentIndex], vector_array[index])) { // if parent is larger than child
            swap(parentIndex, index);
            index = parentIndex;
        } else {
            break; // if parent is smaller than child, then we are done
        }
    }
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::push(const T &t) {
    vector_array.push_back(t);
    siftUp(vector_array.size() - 1);
}

template<typename T, typename C>
T MyPriorityQueue<T, C>::top() const {
    return vector_array[0];
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::pop() {
    // Put last element at the top
    vector_array[0] = vector_array[vector_array.size() - 1];
    // Remove last element
    vector_array.pop_back();
    // Sift down the top element to its correct position
    siftDown(0);
}

template<typename T, typename C>
bool MyPriorityQueue<T, C>::empty() const {
    return vector_array.empty();
}

template<typename T, typename C>
unsigned MyPriorityQueue<T, C>::size() const {
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H
