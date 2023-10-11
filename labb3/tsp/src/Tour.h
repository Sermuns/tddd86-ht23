#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"


class Tour {
public:

    Tour();
/**
 * @brief Tour::~Tour Deletes and removes used memory by looping through the linked list.
 */
    ~Tour();
    /**
     * @brief show Print all the points in the standard output
     */
    void show();
/**
 * @brief Tour::draw, draws to a scene using the built in function drawto from the header file.
 * @param scene
 */
    void draw(QGraphicsScene* scene);
/**
 * @brief Tour::size, loops through the linked list and adds 1 for each node it traverses.
 * @return size of linked list
 */
    int size();
/**
 * @brief Tour::distance, gets the distance of tour by looping through the linked list and addint the "distanceto()" from eact point.
 * @return the total distance of the tour
 */
    double distance();
/**
 * Insert point in front of the node in the tour which has closest euclidean distance to it.
 * @brief Tour::insertNearest
 * @param p
 */
    void insertNearest(Point p);
/**
 * Insert the point wherever the total distance increase of the tour is the smallest
 * @brief Tour::insertSmallest
 * @param p
 */
    void insertSmallest(Point p);

private:
    Node* firstNode = nullptr;
};

#endif // TOUR_H
