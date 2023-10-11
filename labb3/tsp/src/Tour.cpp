// TDDD86 Lab 3 by Daniel Alchasov(Danal315) and Samuel Åkesson(samak519).
// Tour is a linked list of nodes that holds a point and a pointer to the next node that loops in a circular manner.
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
    if(firstNode == nullptr){
        // No problem, linked list already empty!
        return;
    }
    Node* current = firstNode->next;
    while(current != firstNode){
     Node* toBeDeleted = current;
     current = current->next;
     delete toBeDeleted;
    }
    delete firstNode;
}

void Tour::show()
{
    if(firstNode == nullptr) return;

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
    if(firstNode == nullptr) return;

    Node* currentNode = firstNode;
    while(currentNode->next != firstNode)
    {
        currentNode->point.draw(scene);
        currentNode->point.drawTo(currentNode->next->point, scene);
        currentNode = currentNode->next;
    }
    currentNode->point.drawTo(currentNode->next->point, scene);
}

int Tour::size()
{
    if(firstNode == nullptr) return 0;

    Node* currentNode = firstNode;
    int amountOfNodes = 1;
    while(currentNode->next != firstNode)
    {
      amountOfNodes++;
      currentNode = currentNode->next;
    }
    return amountOfNodes;
}

double Tour::distance()
{
    if(firstNode == nullptr) return 0;

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
    closest->next = new Node(p, closest->next);
}

void Tour::insertSmallest(Point p)
{
    if(firstNode == nullptr){
        firstNode = new Node(p);
        firstNode->next=firstNode;
        return;
    }
    Node* current = firstNode->next;
    Node* best = firstNode;
    Node* pNode = new Node(p);
    double bestDistanceIncrease = numeric_limits<double>::max();
    double previousTotalDistance = this->distance();
    double currentDistance = 0;
    while(current != firstNode)
    {


      // inserting node in front of current:
      pNode->next=current->next;
      current->next=pNode;

      // A--B
      // |  |-P
      // D--C
      // remove BC distance and add BP and CP distance!
      currentDistance = previousTotalDistance - current->point.distanceTo(pNode->next->point) +
              (pNode->point.distanceTo(current->point)+pNode->point.distanceTo(pNode->next->point)); // gets a numerical increase
      // check if this new distance is a lower increase then before.
      if(currentDistance < bestDistanceIncrease){
          bestDistanceIncrease = currentDistance;
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
