/* Name: Nibras Alam & Al Hisham Anik
# ID: 1617818 & 1585385
# CMPUT 275, Winter 2020
#
# Assignment 2: Driving Route Finder Part 1
#
# Consulted C++ Documentation; Used Lecture Slides
*/
#include <iostream>
#include <string>
#include <fstream>  // to read data from files
#include <sstream>  // parsing individual lines from file
#include <cmath>  // for abs()
using namespace std;

#include <unordered_map>
#include <utility>  // for pair()
#include <list>  // for list()
#include "wdigraph.h"
#include "dijkstra.h"

// LL for brevity; Point stores vertex coords as 100000th of degree
typedef long long LL;
struct Point {
    LL lat;
    LL lon;
};

LL manhattan(const Point& pt1, const Point& pt2) {
    /*
        Calculates manhattan distance between 2 points: |x1-x2|+|y1-y2|

        Arguments:
            pt1 (const Point&): Pass by reference of Point obj pt1
            pt2 (const Point&): Pass by reference of Point obj pt2

        Returns:
            distance (LL): manhattan distance b/w points
    */
    LL result = abs(pt1.lat - pt2.lat) + abs(pt1.lon - pt2.lon);
    return result;
}

void readGraph(string filename, WDigraph& graph,
                    unordered_map<int, Point>& points) {
    /*
        Reads in graph vertices and edges from file to build weighted 
        graph and store points

        Arguments:
            filename (string): name of file
            graph (WDigraph&): Pass by reference of weighted graph
            points (unordered_map<int,Point>&): Pass by reference of pts hash

        Returns:
            void
    */
    ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }

    // reads file line by line
    string line, args[4];
    while (getline(inFile, line)) {
        // creates sstream to store each ','-delimited element
        stringstream ss(line);
        int i = 0;
        while (getline(ss, args[i], ',')) {
            i++;
        }

        // adds respective vertices or edges to weighted graph
        if (args[0] == "V") {
            int ID = stoi(args[1]);

            // converts lat/lon to 100000th of degree
            LL lat = static_cast<LL>(stod(args[2]) * 100000);
            LL lon = static_cast<LL>(stod(args[3]) * 100000);
            Point tempPoint = {lat, lon};

            // adds Point to points hash and graph
            points.insert({ID, tempPoint});
            graph.addVertex(ID);

        } else if (args[0] == "E") {
            int start = stoi(args[1]), end = stoi(args[2]);
            // string name = args[3];

            // find points and cost to add to graph
            auto pt1 = points.find(start), pt2 = points.find(end);
            LL edgeCost = manhattan((*pt1).second, (*pt2).second);
            graph.addEdge(start, end, edgeCost);
        }
    }
    inFile.close();
}

void waypointToClient(list<int>& path, unordered_map<int, Point>& points) {
    /*
        Server-client communication protocol where server sends waypoints'
        lats & lons waiting for acknowledgements in between

        Arguments:
            path (list<int>&): Pass by reference of waypoints in order
            points (unordered_map<int,Point>&): Pass by reference of pts hash

        Returns:
            void
    */
    // starts with stating number of waypoints
    cout << "N " << path.size() << endl;
    string clientResponse;

    // waits for "A" (acknowledgement) & displays each waypoint lat/lon
    for (auto it : path) {
        clientResponse = "\0";
        cin >> clientResponse;
        if (clientResponse == "A") {
            auto myPtItr = points.find(it);
            Point myPt = (*myPtItr).second;
            cout << "W " << myPt.lat << " " << myPt.lon << endl;
        }
    }

    // displays "E" for end after final "A"
    clientResponse = "\0";
    cin >> clientResponse;
    if (clientResponse == "A") {
        cout << "E" << endl;
    }
}

void processInput(WDigraph& graph, unordered_map<int, Point>& points) {
    /*
        Processes input request of the best cost path between 2 lat/lon's

        Arguments:
            graph (WDigraph&): Pass by reference of weighted graph
            points (unordered_map<int,Point>&): Pass by reference of pts hash

        Returns:
            void
    */
    // creates sstream to store each element of the input line
    string line, args[5];
    getline(cin, line);
    stringstream ss(line);
    int i = 0;
    while (getline(ss, args[i], ' ')) {
        i++;
    }

    // begins path-finding if valid "R" is used by client
    if (args[0] == "R") {
        // creates points for inputted lat/lon's
        LL lat1 = stoll(args[1]), lon1 = stoll(args[2]);
        LL lat2 = stoll(args[3]), lon2 = stoll(args[4]);
        Point tempPoint1 = {lat1, lon1}, tempPoint2 = {lat2, lon2};

        // finds closest vertices to inputted points; -1 for base comparison
        int startVertex, endVertex;
        LL startSmallest = -1, endSmallest = -1, temp;
        for (auto it : points) {
            temp = manhattan(it.second, tempPoint1);
            if (temp < startSmallest || startSmallest == -1) {
                startSmallest = temp;
                startVertex = it.first;
            }

            temp = manhattan(it.second, tempPoint2);
            if (temp < endSmallest || endSmallest == -1) {
                endSmallest = temp;
                endVertex = it.first;
            }
        }

        // uses dijkstra's algorithm to create tree of best cost paths
        unordered_map<int, PIL> searchTree;
        dijkstra(graph, startVertex, searchTree);

        // uses search tree to make list of waypoints to endVertex
        list<int> path;
        int stepping = endVertex;
        while (stepping != startVertex) {
            // crawl up the search tree one step
            path.push_front(stepping);
            stepping = searchTree[stepping].first;
        }
        path.push_front(startVertex);

        // displays waypoints through given protocol
        waypointToClient(path, points);
    }
}

int main(int argc, char *argv[]) {
    // creates weighted graph and points hash passed by reference
    WDigraph yegGraph;
    unordered_map<int, Point> yegPoints;
    readGraph(argv[1], yegGraph, yegPoints);

    processInput(yegGraph, yegPoints);

    return 0;
}
