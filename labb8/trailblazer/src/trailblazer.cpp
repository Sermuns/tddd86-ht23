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

    start->visited = true;

    for (Vertex *neighbor: graph.getNeighbors(start)) {
        if (neighbor->visited) continue;

        std::vector<Vertex *> path = depthFirstSearch(graph, neighbor, end);

        if (!path.empty()) {
            // If a non-empty path is found, insert the current vertex at the beginning of the path
            path.insert(path.begin(), start);
            //unvisitNodes(path);
            return path;
        }
    }

    // If the function reaches here, it means no path was found, return an empty vector
    return {};
}

void unvisitNodes(const vector<Vertex *> &path) {
    for (Vertex *v: path) {
        v->visited = false;
    }
}

vector<Node *> breadthFirstSearch(BasicGraph &graph, Vertex *start, Vertex *end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex *> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph &graph, Vertex *start, Vertex *end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex *> path;
    return path;
}

vector<Node *> aStar(BasicGraph &graph, Vertex *start, Vertex *end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex *> path;
    return path;
}
