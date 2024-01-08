// tddd86 lab 8 made my Samuel Åkesson och Daniel Alchasov. Simulates 4 different algorithms in a maze or terrains.

#include "costs.h"
#include <algorithm>
#include "trailblazer.h"
#include <cassert>
#include <iostream>
#include <pqueue.h>
#include <queue>

// TODO: include any other headers you need; remove this comment
using namespace std;

std::vector<Vertex *> depthFirstSearch(BasicGraph &graph, Vertex *start, Vertex *end) {
    if (start == end) {
        // base case: if the start is the same as the end, return a vector with only the start vertex
        return {start};
    }

    start->setColor(YELLOW);
    start->visited = true;

    for (Vertex *neighbor: graph.getNeighbors(start)) {
        if (neighbor->visited) continue; // skip visited neighbors
        vector<Vertex *> path = depthFirstSearch(graph, neighbor, end);
        if (path.empty()) continue; // skip empty paths

        // If a non-empty path is found, insert the current vertex at the beginning of the path
        path.insert(path.begin()    , start);
        start->setColor(GREEN);
        end->setColor(GREEN);
        graph.resetData(); // unvisit all nodes!
        return path;
    }

    // If the function reaches here, it means no path was found, return an empty vector
    start->setColor(GRAY);
    return {};
}


vector<Node *> breadthFirstSearch(BasicGraph &graph, Vertex *start, Vertex *end) {


    // perform breadth first search with a queue of nodes
    vector<Vertex *> path;
    queue<Vertex *> queue;

    // enqueue the start node
    queue.push(start);
    start->visited = true;

    while (!queue.empty()) {
        Vertex *current = queue.front();
        queue.pop();
        current->setColor(YELLOW);
        if (current == end) {
            // found the end node, return the path
            path.push_back(current);

            // backtrack to the start node
            while (current != start) {
                current->setColor(GREEN);
                current = current->previous;
                path.push_back(current);
            }
            start->setColor(GREEN);
            end->setColor(GREEN);
            reverse(path.begin(), path.end());
            graph.resetData(); // unvisit all nodes!
            return path;
        }

        for (Vertex *neighbor: graph.getNeighbors(current)) {
            if (!neighbor->visited) {
                neighbor->visited = true;
                neighbor->previous = current;
                queue.push(neighbor);
            }
        }
    }

    return {};
}

vector<Node *> dijkstrasAlgorithm(BasicGraph &graph, Vertex *start, Vertex *end) {
    vector<Vertex *> path;
    PriorityQueue<Vertex*> pq;
    // set all nodes to infinity
    for (Vertex *v: graph.getVertexSet()) {
        v->cost = POSITIVE_INFINITY;
    }
    // set start node to 0, enqueue it
    start->cost = 0;
    pq.enqueue(start, 0);

    while (!pq.isEmpty()) {
        // dequeue the lowest cost node
        Vertex *current = pq.dequeue();
        current->setColor(YELLOW);
        current->visited = true;

        if (current == end) {
            path.push_back(current);
            while (current != start) {
                current->setColor(GREEN);
                current = current->previous;
                path.push_back(current);
            }
            start->setColor(GREEN);
            end->setColor(GREEN);
            reverse(path.begin(), path.end());
            graph.resetData(); // unvisit all nodes!
            return path;
        }

        for (Vertex *neighbor: graph.getNeighbors(current)) {
            if (neighbor->visited) continue;
                // calculate the cost to get to the neighbor
                double cost = current->cost + graph.getEdge(current, neighbor)->cost;

                if (cost < neighbor->cost) {
                    neighbor->cost = cost;
                    neighbor->previous = current;
                    pq.enqueue(neighbor, cost);                      
            }
        }

    }
    return path;
}

vector<Node *> aStar(BasicGraph &graph, Vertex *start, Vertex *end) {
    vector<Vertex *> path;
    PriorityQueue<Vertex*> pq;
    //set up the heap value.
    for (Vertex *v: graph.getVertexSet()) {
        v->cost = POSITIVE_INFINITY;
    }
    start->cost = 0;
    pq.enqueue(start, 0);

    while (!pq.isEmpty()) {
        // dequeue the lowest cost node first iteration = start node
        Vertex *current = pq.dequeue();
        current->setColor(YELLOW);
        current->visited = true;

        if (current == end) {
            path.push_back(current);
            while (current != start) {
                current->setColor(GREEN);
                current = current->previous;
                path.push_back(current);
            }
            start->setColor(GREEN);
            end->setColor(GREEN);
            graph.resetData(); // unvisit all nodes!
            break; // break out of the while loop, we found the path!
        }
        for (Vertex *neighbor: graph.getNeighbors(current)) {
            if (neighbor->visited) continue; // if wrong skip iteration

            double currentCost = current->cost + graph.getEdge(current, neighbor)->cost;

            if (currentCost < neighbor->cost) {
                neighbor->cost = currentCost;
                neighbor->previous = current;
                neighbor->setColor(YELLOW);
                pq.enqueue(neighbor, currentCost + neighbor->heuristic(end));
            }

        }

    }
    reverse(path.begin(), path.end());
    return path;
}
