// Name: Al Hisham Anik
// ID: 1585385
// CMPUT275, Winter 2020
//
//Reference: template code from eclass and breadthfirst search algoirtm
//Exercise 5: Graph Concepts

//All C++ library used in this exercies
#include <iostream>
#include <queue>
#include <unordered_map>
#include <list>
#include "digraph.h"
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


//This function takes in three parameter and acts with the BFS graph search
//algorith to see if the start and end vertices connect and returns a counter 
// to keep track the number of connected graph components
int count_components(Digraph* graph, int startVertex, int endVertex) {
  static int counter = 0;
  unordered_map<int, int> searchTree; // map each vertex to its predecessor
  searchTree[startVertex] = -1;
  queue<int> q;
  q.push(startVertex);


  while (!q.empty()) {
    int v = q.front();
    q.pop();


    for (auto iter = graph->neighbours(v); iter != graph->endIterator(v); iter++) {
      if (searchTree.find(*iter) == searchTree.end()) {
        searchTree[*iter] = v;
        q.push(*iter);
      }
    }
  }


  list<int> path;
  if (searchTree.find(endVertex) == searchTree.end()) { //if the start vertex and end vertex are not connected
    return counter;
  }
  else { // if the startvertex and endvertex are connected
    int stepping = endVertex;
    while (stepping != startVertex) {
      path.push_front(stepping);
      stepping = searchTree[stepping]; // crawl up the search tree one step
    }
    path.push_front(startVertex);
    counter++;
  }
  return counter;
}

//This function parse through the CRSV entered from the command line
Digraph* read_city_graph_undirected(char filename[]) {
	Digraph graph;
	string eachline;
	ifstream edmontonfile(filename);

	//if the file name is correct then display the text for the user
	//to enter the correct file
	if (!edmontonfile.is_open()){
		cout << "Please type in the correct name" << endl;
	}

	//if the file name is correct then start reading through it
	if (edmontonfile.is_open()){
		while(!edmontonfile.eof()){ //while the file is open start parsing through it
			while(getline(edmontonfile, eachline)){
				//reading through each line if the first substring is V then fetch the ID number 
				//which is the second value and then use it to make vertices
				if(eachline.substr(0, 1) == "V"){
					int ID = eachline[2];
					graph.addVertex(ID);
				}
				//reading through each line if the first substring is E then fetch two ID number 
				//which is the second value and third value then use it to connect vertices
				else if(eachline.substr(0,1)== "E"){
					graph.addEdge(eachline[2], eachline[4]);
				}
			}
		}
	}
	//after reading the file close it
	edmontonfile.close();
	//return the graph created
	return &graph;
}


int main(int argc, char *argv[]) {
	Digraph graph;

	//seting up the nodes of the graph as we add vertices
	int nodes[] = {1, 2, 3, 4, 5, 6};
	for (auto v : nodes){
		graph.addVertex(v);
	}
	//connecting vertices with edges
	int edges[][2] = {{1, 2}, {3, 4}, {3, 5}, {4, 5}};
	for (auto e : edges) {
		graph.addEdge(e[0], e[1]);
		graph.addEdge(e[1], e[0]);
	}
	int connected_points =0;	
	int i = 1;
	int j = 2;
	//iterating through two vertex and looking to count numbers of connected components
	while(j !=7){//stops when 6 vertices are being iterated
		connected_points = count_components(&graph,i,j);
		j++;
	}
	cout << connected_points << endl;

	//adding more edges with vertices
	graph.addEdge(1, 4);
	graph.addEdge(4, 1);
	j = 2;

	//now iterating again with the new graph to count the number of connected components
	while(j !=7){
		connected_points = count_components(&graph,i,j);
		j++;
	}
	cout << connected_points << endl;

	//This is task two that calls a functions which calls a function that sends the
	//filename read from the command line argument 
	read_city_graph_undirected(argv[1]);
    return 0;
} 