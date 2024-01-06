// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
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
        std::vector<Vertex *> path = depthFirstSearch(graph, neighbor, end);
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
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)

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

    // while the queue is not empty
    while (!pq.isEmpty()) {
        // dequeue the lowest cost node
        Vertex *current = pq.dequeue();
        current->setColor(YELLOW);
        // if the node is the end node, return the path
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
            return path;
        }
        // for each of the node's neighbors
        for (Vertex *neighbor: graph.getNeighbors(current)) {
            // if the neighbor has not been visited
            if (!neighbor->visited) {
                // calculate the cost to get to the neighbor
                double cost = current->cost + graph.getEdge(current, neighbor)->cost;
                // if the cost is less than the neighbor's cost
                if (cost < neighbor->cost) {
                    // set the neighbor's cost to the current cost
                    neighbor->cost = cost;
                    // set the neighbor's previous to the current node
                    neighbor->previous = current;
                    // enqueue the neighbor with the cost
                    pq.enqueue(neighbor, cost);
                }
            }
        }
        // mark the current node as visited
        current->visited = true;
    }
    return path;
}

vector<Node *> aStar(BasicGraph &graph, Vertex *start, Vertex *end) {
    vector<Vertex *> path;
    PriorityQueue<Vertex*> pq;
    //set up the queue
    for (Vertex *v: graph.getVertexSet()) {
        v->cost = POSITIVE_INFINITY;
    }
    start->cost = 0;
    pq.enqueue(start, 0);

    // while the queue is not empty
    while (!pq.isEmpty()) {
        // dequeue the lowest cost node first iteration = start node
        Vertex *current = pq.dequeue();
        current->setColor(YELLOW);
        // mark the current node as visited
        current->visited = true;
        // if the node is the end node, return the path
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
             // break out of the while loop, we found the path!
        }
        for (Vertex *neighbor: graph.getNeighbors(current)) {
            if (neighbor->visited) continue; // if wrong skip iteration

            // calculate the currentCost to get to the neighbor and update the costs to priority queue.
            double currentCost = current->cost + graph.getEdge(current, neighbor)->cost;

            // if the currentCost is less than the neighbor's currentCost
            if (currentCost < neighbor->cost) {
                neighbor->cost = currentCost;
                neighbor->previous = current;
                neighbor->setColor(YELLOW);
                pq.enqueue(neighbor, currentCost + neighbor->heuristic(end));
            }

        }

    }
    return path;
}
