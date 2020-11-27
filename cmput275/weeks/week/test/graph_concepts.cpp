// A template for the Graph Concepts Exercise in C++.

#include <iostream>
#include <stdio.h>
#include <queue>
#include <unordered_map>
#include <list>
#include "digraph.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;


Digraph* read_city_graph_undirected(char filename[]) {
	Digraph graph;
	string eachline;
	ifstream edmontonfile(filename);
	if (!file.is_open()){
		cout << "Please type in the correct name" << endl;
	}
	if (edmontonfile.is_open()){
		while(!edmontonfile.eof()){
			while(getline(edmontonfile, eachline)){
				if(eachline.substr(0, 1) == "V"){
					int ID = eachline[2];
					graph.addVertex(ID);
				}
				else if(eachline.substr(0,1)== "E"){
					graph.addEdge(line[2], eachline[4]);
				}
			}
		}
	}
	edmontonfile.close();
	return &graph;
}



int main(int argc, char *argv[]) {
	Digraph graph;
	read_city_graph_undirected(argv[1]);
	vector<int> vertices = graph.vertices();
  	for (auto v : vertices) {
    	cout << v << ':';
    }
	return 0;
}
