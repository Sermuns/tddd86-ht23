// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour(Point A, Point B, Point C, Point D)
{
    firstNode = new Node(A);
    Node *secondNode = new Node(B);
    Node *thirdNode = new Node(C);
    Node *fourthNode = new Node(D);

    firstNode->next = secondNode;
    secondNode->next = thirdNode;
    thirdNode->next = fourthNode;
    fourthNode->next = firstNode;

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

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
