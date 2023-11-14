/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk(const Point& p): Robot(p){}

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;


    /**
     * @brief moveTowards, overrides moveTowards to do nothing;
     * @param u,
     */
    void moveTowards(const Unit& u) override;
    /**
     * @brief doCrash does nothing
     */
    void doCrash() override;

    /**
     * @brief justCrashed is always false
     * @return false
     */
    bool justCrashed() const override;

    /**
     * @brief canMove as junk cannot move
     * @return false
     */
    bool canMove() const override;
};

#endif // JUNK_H
