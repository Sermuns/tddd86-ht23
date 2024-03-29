/*
 * TDDD86 Trailblazer
 * This file declares the functions you will write in this assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author: Marty Stepp
 * Slight modifications by Tommy Farnqvist
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include <vector>
#include "BasicGraph.h"

/**
 * Mark all nodes in the given path as un-visited.
 */
void unvisitNodes(const vector<Vertex*>& path);
/**
 * Given a graph, return a vector of pointers to the nodes along the path.
 * Use depth-first search to find a path between the given start and end nodes.
 */
vector<Node*> depthFirstSearch(BasicGraph& graph, Node* start, Node* end);
/**
 * Given a graph, return a vector of pointers to the nodes along the path.
 * Use breadth-first search to find a path between the given start and end nodes.
 */
vector<Node*> breadthFirstSearch(BasicGraph& graph, Node* start, Node* end);
/**
 * Given a graph, return a vector of pointers to the nodes along the path.
 * Use Dijkstra's algorithm to find a path between the given start and end nodes.
 */
vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end);
/**
 * Given a graph, return a vector of pointers to the nodes along the path.
 * Use A* search to find a path between the given start and end nodes.
 */
vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end);

#endif
