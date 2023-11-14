/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool crashed = false;

public:

    /**
     * @brief Robot uses unit superclass to create constructor.
     * @param p
     */
    Robot(const Point& p):Unit(p){};

    Robot():Unit(){};

    ~Robot();

    /**
     * @brief clone constructor
     * @return a robot with this robots coordinate.
     */
    Robot* clone();

    /*
     * did not crash yet
     */
    virtual bool canMove() const;

    /*
     * Crashes and remembers it
     */
    virtual void doCrash();

    /*
     * Return whether the robot crashed
     */
    virtual bool justCrashed() const;


    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    virtual void draw(QGraphicsScene* scene) const override;


};

#endif // ROBOT_H
