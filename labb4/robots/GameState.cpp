/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot = new Robot();
        while(!isEmpty(*robot)){
            //Teleports the robot with no location onto randomized cooridnate
            robot->teleport();
        }
        robots.push_back(robot);
    }
    teleportHero();
}
GameState::GameState(const GameState& otherGameState){
    hero = otherGameState.hero;
    robots = otherGameState.robots;
}

GameState::~GameState(){
 for(unsigned i=0; i < robots.size(); ++i)
     delete robots[i];
}

GameState& GameState::operator=(const GameState& otherGameState){
    //prevent self assignment
    if(this != &otherGameState){
        for(Robot* robot : robots){
            delete robot;
        }
        this->robots.clear();

        for(Robot* otherRobot : otherGameState.robots){
            robots.push_back(otherRobot->clone());
        }

        hero = otherGameState.hero;

    }

    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Robot* robot: robots)
        robot->draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Robot* robot: robots)
        robot->moveTowards(hero);
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < robots.size(); ++i){
        for(unsigned o=i+1; o < robots.size(); ++o){
            if(robots[i]->at(*robots[o])){
                robots[i]->doCrash();
                robots[o]->doCrash();
            }
        }
    }
}

int GameState::countJustCrashed()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->justCrashed())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < robots.size(); ++i){
        if (robots[i]->justCrashed()) {
            Junk* junk = new Junk(robots[i]->asPoint());
            delete robots[i];
            robots[i] = junk;
        }
    }
}

bool GameState::stillLiveRobots() const {
    for(unsigned i=0; i < robots.size(); ++i){
        if(robots[i]->canMove())
            return true;
    }
    return false;
}


bool GameState::heroDead() const {
    for(const Robot* robot: robots){
        if(hero.at(*robot)){
            return true;
        }
    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const Robot* robot: robots)
        if(robot->at(unit))
            return false;
    return true;
}

