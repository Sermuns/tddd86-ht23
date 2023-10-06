// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <limits>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

}

Tour::~Tour()
{
    // TODO: write this member
    if(firstNode == nullptr){
        return;
    }
    Node* currentNode = firstNode;
    while(currentNode->next == firstNode){
     Node* nextNode = currentNode->next;
     delete currentNode;
     currentNode = nextNode;
    }
    delete firstNode;
}

void Tour::show()
{
    Node* currentNode = firstNode;
    while(currentNode->next != firstNode)
    {
       cout << currentNode->point.toString() << endl;
       currentNode = currentNode->next;
    }
    cout << currentNode->point.toString() << endl;
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* currentNode = firstNode;
    while(currentNode->next != firstNode)
    {
        currentNode->point.drawTo(currentNode->next->point, scene);
        currentNode = currentNode->next;
    }
    currentNode->point.drawTo(currentNode->next->point, scene);
}

int Tour::size()
{

    Node* currentNode = firstNode;
    int amountOfNodes = 1;
    while(currentNode->next != firstNode)
    {
      amountOfNodes++;
      currentNode = currentNode->next;
    }
    return amountOfNodes;
}

/**
 * @brief Tour::distance
 * @return the total distance of the tour
 */
double Tour::distance()
{
    Node* currentNode = firstNode;
    double totalDistance = 0;
    while(currentNode->next != firstNode)
    {
      totalDistance += currentNode->point.distanceTo(currentNode->next->point);

      currentNode = currentNode->next;
    }
    totalDistance += currentNode->point.distanceTo(currentNode->next->point);
    return totalDistance;
}

/**
 * @brief Tour::insertNearest
 * @param p
 */
void Tour::insertNearest(Point p)
{
    if(firstNode == nullptr){
        firstNode = new Node(p);
        firstNode->next=firstNode;
        return;
    }
    Node* current = firstNode->next;
    Node* closest = firstNode; // guess that the first node is closest
    while(current != firstNode)
    {
      if(current->point.distanceTo(p) < closest->point.distanceTo(p)){
          closest = current;
      }
      current = current->next;
    }
    Node* pNode = new Node(p, closest->next);
    closest->next = pNode;
}

void Tour::insertSmallest(Point p)
{
    if(firstNode == nullptr){
        firstNode = new Node(p);
        firstNode->next=firstNode;
        return;
    }
    Node* current = firstNode->next;
    Node* best = firstNode; // guess that the first node is best place to insert after
    Node* pNode = new Node(p);
    // ANY OTHER INSERTION WILL RESULT IN BETTER DISTANCE!
    //TODO: Samuel i am not smart enough to understand these comments. Please reconsider...
    double smallestDistance = numeric_limits<double>::max();
    while(current != firstNode)
    {
      // test-inserting node in front of current:
      pNode->next=current->next;
      current->next=pNode;
      // * insert the node here, check if that distance is better. keep track!
      if(this->distance() < smallestDistance){
          smallestDistance = this->distance();
          best = current;
      }
      // removing pNode from linkedlist
      current->next = pNode->next;
      // next iteration
      current = current->next;
    }
    // insert pNode after best node
    pNode->next=best->next;
    best->next = pNode;
}
