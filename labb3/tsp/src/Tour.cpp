// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

}

Tour::~Tour()
{
    // TODO: write this member
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

//    Node nextNode = *(firstNode->next);
//    while(nextNode.toString() != firstNode->toString()){
//        cout << "hey" << endl;
//    }
    // TODO: write this member
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* currentNode = firstNode;
    while(currentNode->next != firstNode)
    {
        currentNode->point.drawTo(currentNode->next->point, scene);
    }
    currentNode->point.drawTo(currentNode->next->point, scene);
    // TODO: write this member
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
    // TODO: write this member
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
    // TODO: write this member
}

/**
 * @brief Tour::insertNearest
 * @param p
 */
void Tour::insertNearest(Point p)
{ //A->B ->C-> D | C
  //Problem with either 2nd iteration or further iterations.
    if(firstNode == nullptr){
        firstNode = new Node(p);
        return;
    }
    Node* currentNode = firstNode->next;
    Node* closestToP = firstNode; // guess that the first node is closest
    while(currentNode != firstNode)
    {
      if(currentNode->point.distanceTo(p) < closestToP->point.distanceTo(p)){
          closestToP = currentNode;
      }
      currentNode = currentNode->next;
      if(currentNode == nullptr){
          currentNode = firstNode;
      }
    }
    Node* pNode = new Node(p, closestToP->next);
    closestToP->next = pNode;

}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
