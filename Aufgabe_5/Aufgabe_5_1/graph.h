#ifndef AUFGABE_5_1_GRAPH_H
#define AUFGABE_5_1_GRAPH_H

#include <vector>   /*  type vector  */
#include <string>   /*  type string  */
#include <iostream> /*  cout, cerr  */
#include <sstream>  /*  type stringstream to easily concat a result string  */
#include <limits.h> /*  INT_MAX */
#include <algorithm>

#include "edge.h"


#define V 10

void vectorToString(std::vector<std::string> vector);



/*  --  Class Graph --  */
class Graph {
    private:
        std::vector<std::string> vertices;                  //  vector connecting vertices with indicies; needed for name resolution
        void _letTheSalesmanTravel(const std::string& vertex, std::vector<bool>& visited, const std::string& startingPoint);
    public:



        Graph();                                            //  default constructor
        Graph(const std::vector<std::string>& vertices, const std::vector<Edge>& edges);  //  param. constructor
        std::vector<std::vector<int>> adjacencyMatrix;      //  vector of vectors containing integers (the adjacency matrix)
        
        /*  --
            Resolves a given string of a vertex and returns its position in the
            adjacencyMatrix (as integer). Returns -1 if name could not be resolved,
            which indicates the the name was not found. 
        --  */
        int resolveVertex(const std::string& name);
        void printGraph();    //  prints out the graph with vertices and the adjacencyMatrix

        /*  --
            Graph Manipulation Functions
        --  */
        void insertVertex(const std::string& vertex);                           //  inserts a new vertex; throws error, if vertex already exists in Graph
        void deleteVertex(const std::string& vertex);                           //  deletes a vertex from the Graph; throws an error, if vertex does not exist
        void insertEdge(const Edge& edge);                                      //  inserts a new edge; parameter can be {std::string, std::string} due to implicit cast...
                                                                                //  ...does not check if the edge already exists, nor notifies user/programmer
        void deleteEdge(const Edge& edge);                                      //  deletes an edge; parameter can be {std::string, std::string} due to implicit cast...
                                                                                //  ...does not check if edge exists
        bool adjacent(const std::string& vertex1, const std::string& vertex2);  //  checks if vertex1 and vertex2 are adjacent; returns boolean; adjacency indicates that...
                                                                                //  ...a direct connection between a <--> b (direction NOT important) exists
        std::vector<std::string> neighbours(const std::string& vertex);         //  returns a vector of strings, containing all neighbouring vertices of the parameter vertex...
                                                                                //  ...Neighbours are all vertices that a given vertex is connected to through OUTGOING edges
        
        int* performDijkstra(const std::string& sourceVertex);           //  Dijkstra algorithm implementation
        void letTheSalesmanTravel(const std::string& vertex);
        std::string getNearestNeighbour(const std::string& vertex, std::vector<bool>& visited);

        void printPath(int parent[], int j, int dist[]);
        void performPrimeMST(const std::string& sourceVertex, const std::string& targetVertex);
        int  miniDist(const int dist[], const bool sptSet[]);

    };

#endif //AUFGABE_5_1_GRAPH_H