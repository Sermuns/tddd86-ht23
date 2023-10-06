// TDDD86 Lab 3 by Daniel Alchasov(Danal315) and Samuel Åkesson(samak519). Tour is a linked list of nodes that holds a point and a pointer to the next node that loops in a circular manner.
#include <iostream>
#include <limits>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

}
/**
 * @brief Tour::~Tour Deletes and removes used memory by looping through the linked list.
 */
Tour::~Tour()
{
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
/**
 * @brief Tour::show, shows the current nodes point in a string.
 */
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
/**
 * @brief Tour::draw, draws to a scene using the built in function drawto from the header file.
 * @param scene
 */
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
/**
 * @brief Tour::size, loops through the linked list and adds 1 for each node it traverses.
 * @return size of linked list
 */
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
 * @brief Tour::distance, gets the distance of tour by looping through the linked list and addint the "distanceto()" from eact point.
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
 * @brief Tour::insertNearest, Inserts a node at the point P where it leads to the tours smallest increase by looping through and seeing which point leads to smallest increase.
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
//    double smallestDistance = this->distance();
    double bestDistanceIncrease = numeric_limits<double>::max();
    double currentDistanceIncrease = 0;
    while(current != firstNode)
    {

      currentDistanceIncrease = this->distance();

      // test-inserting node in front of current:
      pNode->next=current->next;
      current->next=pNode;

      currentDistanceIncrease = this->distance() - currentDistanceIncrease; // gets a numerical increase
      //check if this new distance is a lower increase then before.
      if(currentDistanceIncrease < bestDistanceIncrease){
          bestDistanceIncrease = currentDistanceIncrease;
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
