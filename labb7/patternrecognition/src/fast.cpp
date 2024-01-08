/* Lab 7 done by Samuel Åkesson och Daniel Alchasov.
 *
 *
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "Point.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene *scene, const vector<Point> &points) {
    for (const auto &point: points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene *scene, const Point &p1, const Point &p2) {
    p1.lineTo(scene, p2);
}

/**
 * @brief main, renders a line between points by getting slopes and connecting them.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input56.txt";
    ifstream input;
    input.open(filename);

    if (!input.is_open()) {
        cerr << "File '" << filename << "' not found." << endl;
        exit(EXIT_FAILURE);
    }

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Fast Sorting Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    // find all 4 (or more) points which lie on the same straight line
    // to do this, we iterate through all points p.
    // for each point p, we sort the other points by their slope to p.

    for (int i = 0; i < N; ++i) {
        Point &p = points[i];
        // map slope to vector of points with that slope
        unordered_map<double, vector<Point>> slope_map;
        // iterate through all points except p
        for (int j = 0; j < N; ++j) {
            if (i == j) continue; // skip self
            Point &q = points[j];
            double slope = p.slopeTo(q);
            // add q to vector of points with that slope
            slope_map[slope].push_back(q);
        }
        // iterate through all slopes
        for (auto &pair: slope_map) {
            // if there are 3 or more points with the same slope to p
            if (pair.second.size() >= 3) {
                // sort points by natural order
                sort(pair.second.begin(), pair.second.end());
                // render line segment from p to last point in vector
                Point& lastPoint = pair.second.back();
                render_line(scene, p, lastPoint);
            }
        }
    }


    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
