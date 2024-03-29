#include <iomanip>
#include "extendedGraph2.h"

Graph::Graph(const std::vector<std::string>& vertices, const std::vector<Edge>& edges) {
    this->vertices = vertices;                                                                  //  definition of this->vertex through parameter vertices (type: std::vector<std::string>)
    this->adjacencyMatrix.resize(vertices.size(), std::vector<int>(this->vertices.size()));     //  creation of an NxN Matrix, based on the size of vertices

    for(const auto & edge : edges) {
        insertEdge(edge);                   //  edges are added one by one, utilizing the insertEdge()-Function
    }
}

/*  --  /
Function to insert a vertex into the Graph;
    - takes one argument of type std::string that represents a vertex
    - returns void
/   --  */
void Graph::insertVertex(const std::string& vertex) {  
    if(this->resolveVertex(vertex) != -1) {         /*  --  */
        std::cerr << "Vertex already in Graph!\n";  /*  Calls this->resolveVertex to check if a given vertex is already in the Graph. Returns with an error, if this is the case.   */
        return;                                     /*  --  */
    }
    this->vertices.push_back(vertex);               //  adds a vertetx via the push_back function provided by std::vector
    this->adjacencyMatrix.resize(this->vertices.size(), std::vector<int>(this->vertices.size()));   //  resizes the adjacencyMatrix to the new size
    for(int i = 0; i < (this->vertices.size()); i++) {        /*  --  */
        adjacencyMatrix[i].resize(this->vertices.size());   /*  resizes every "sub" vector of the matrix to the new size    */
    }                                                       /*  --  */
}

/*  --  /
Function to delete a vertex from the Graph;
    - takes one argument of type std::string that represents a vertex
    - returns void
/   --  */
void Graph::deleteVertex(const std::string& vertex) {
    int index = this->resolveVertex(vertex);
    if(index == -1) {                               /*  --  */
        std::cerr << "Vertex not found\n";          /*  Calls this->resolveVertex to check if a given vertex is already in the Graph. Returns with an error, if this is the case.   */
        return;                                     /*  --  */
    }
    this->vertices.erase(this->vertices.begin() + index);   //  erases the vertex at position "index" from this->vertices

    this->adjacencyMatrix.erase(this->adjacencyMatrix.begin() + index);             //  erases the entries from the adjacencyMatrix at "column" position "index"
    for(int i = 0; i < (this->adjacencyMatrix[0].size()); i ++) {                     /*  --  */
        this->adjacencyMatrix[i].erase(this->adjacencyMatrix[i].begin() + index);   /*  erases the entries from the adjacencyMatrix in every "row" */
    }                                                                               /*  --  */
}


/*  --  /
Function to insert an Edge
    - takes one argument of type Edge that represents an edge
    - returns void
/   --  */
void Graph::insertEdge(const Edge& edge) {
    int col = this->resolveVertex(edge.getSrc());        //  resolves the src of the edge to the index within the adjacencyMatrix
    int row = this->resolveVertex(edge.getDest());       //  resolves the dest of the edge to the index within the adjacencyMatrix
    if(col == -1 || row == -1) {                    /*  --  */
        std::cerr << "Vertex not found!\n";         /*  Calls this->resolveVertex to check if a given vertex is already in the Graph. Returns with an error, if this is the case.   */
        return;                                     /*  --  */
    }
    
    this->adjacencyMatrix[col][row]= edge.getDistance();   //  sets the value of the adjacencyMatrix at position [col][row] to the weight of the edge
  }

/*  --  /
Function to delete an Edge
    - takes one argument of type Edge that represents an edge
    - returns void
/   --  */
void Graph::deleteEdge(const Edge& edge) {                 
    int col = this->resolveVertex(edge.getSrc());        //  resolves the src of the edge to the index within the adjacencyMatrix
    int row = this->resolveVertex(edge.getDest());       //  resolves the dest of the edge to the index within the adjacencyMatrix
    if(col == -1 || row == -1) {                    /*  --  */
        std::cerr << "Vertex not found!\n";         /*  Calls this->resolveVertex to check if a given vertex is already in the Graph. Returns with an error, if this is the case.   */
        return;                                     /*  --  */
    }
    this->adjacencyMatrix[col][row]= 0;             //  sets the value of the adjacencyMatrix at position [col][row] to 0
}

/*  --  /
Function to check whether vertex v2 is adjacent to vertex v1
    - takes one argument of type Edge that represents an edge
    - returns void
/   --  */
bool Graph::adjacent(const std::string& vertex1, const std::string& vertex2) {
    int indexVertex1 = this->resolveVertex(vertex1);
    int indexVertex2 = this->resolveVertex(vertex2);
    if(indexVertex1 == -1 || indexVertex2 == -1) {
        std::cerr << "Vertex not found!\n";
        return false;
    }
    //  As adjacency is an equivalency relation, we need to check for a possible relation in both direction.
    //  This can be achieved by swapping the the position specifications of the adjacencyMatrix (from [indexVertex1][indexVertex2]
    //  to [indexVertex2][indexVertex1]).
    if(this->adjacencyMatrix[indexVertex1][indexVertex2] != 0 || this->adjacencyMatrix[indexVertex2][indexVertex1] != 0) {
        return true;    //  if a connection (in any direction) is found, return true
    } else {
        return false;   //  else, return false
    }
}

/*  --  /
Function that returns an std::vector of std::string representing the neighbouring vertices of the parameter std::string vertex.
Other than adjacent, neighbourhood is a directed relationship, which means that a vertex "A" can be the neighbour of "B", but
this does not automatically imply that "B" is the neighbour of "A".
    - takes one argument of type std::string that represents a vertex
    - returns a std::vector of std::string
/   --  */
std::vector<std::string> Graph::neighbours(const std::string& vertex) {
    int indexVertex = this->resolveVertex(vertex);                          //  resolves the vertex to the index within the adjacencyMatrix
    std::vector<std::string> resVector = {};                                //  initializes an empty std::vetor of std::string
    for(int i = 0; i < this->adjacencyMatrix[indexVertex].size(); i++) {    /*  Loops through all entries of the subvector of adjacencyMatrix[indexVertex] */
        if(this->adjacencyMatrix[indexVertex][i] != 0) {                    /*  and checks if  the entry at position [indexVertex][i] is not 0. */
            resVector.push_back(this->vertices[i]);                         /*  If the condition is fulfilled, add the vertex (name) to the result vector resVector */
        }
    }
    return resVector;
}

/*  --  /
Function that prints the current Graph's adjacencyMatrix.
    - prints the Graph by utilizing std::cout
    - returns void
/   --  */
void Graph::printGraph() {
    std::cout << "--------------------------------------------\n";
    std::cout << "\t\t";
    for(auto & vertice : this->vertices) {
        std::cout << std::left << std::setfill(' ') << std::setw(10) << vertice ;
    }
    std::cout << "\n";
    for(int i=0; i < this->vertices.size(); i++) {
        std::cout << std::left << std::setfill(' ') << std::setw(10) << this->vertices[i] << "-->\t";
        for (int j = 0; j < this->vertices.size(); j++) {
            std::cout << std::left << std::setfill(' ') << std::setw(10) << this->adjacencyMatrix[i][j] ;
        }
        std::cout << "\n";
    }
    std::cout << "--------------------------------------------\n";
}

/*  --  /
Function that resolves a parameter std::string name and returns it's index within the this->vertices vector;
between vertices of type std::string and the corresponding index (in the adjacencyMatrix) of type int.
    - takes one argument of type std::string that represents a vertex
    - returns an int representing the vertex's index in the adjacencyMatrix;
    - function returns -1 in case the resolution of the name is unsuccessful
/   --  */
int Graph::resolveVertex(const std::string& vertexName) {
    for(int i = 0; i < this->vertices.size(); i++) {
        if(this->vertices[i] == vertexName) {
            return i;
        }
    }
    return -1;
}

int Graph::miniDist(const int dist[], const bool sptSet[]){
    int min = INT_MAX;
    int min_index;

    for (int i = 0; i < this->vertices.size(); i++){
        if (!sptSet[i] && dist[i] <= min){
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void Graph::printPath(int parent[], int j, int dist[]){

    if (parent[j] == -1){
        return;
    }

    printPath(parent, parent[j], dist);
    std::cout << " -(" << dist[j]-dist[parent[j]] << ")-> " << vertices.at(j);
}

void Graph::performDijkstraPath(const std::string& sourceVertex, const std::string& targetVertex){

    auto src = this->resolveVertex(sourceVertex);
    auto dest = this->resolveVertex(targetVertex);
    int max_size = vertices.size();

    int dist[max_size];
    bool sptSet[max_size];
    int parent[max_size];

    for(int i = 0; i < max_size; i++){
        parent[i] = -1;
        sptSet[i] = false;
    }

    for (int i = 0; i < max_size; i++){
        dist[i] = INT_MAX;
    }

    dist[src] = 0;

    for (int count = 0; count < max_size - 1; count++) {
        int u = miniDist(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < max_size; v++){
            if (!sptSet[v] && adjacencyMatrix[u][v] && dist[u] + adjacencyMatrix[u][v] < dist[v]){
                parent[v] = u;
                dist[v] = dist[u] + adjacencyMatrix[u][v];
            }
        }
    }
    std::cout << vertices.at(src);
    printPath(parent, dest, dist);
    std::cout << "; Gesamter Zollbetrag: " << dist[dest] << std::endl;
}


void Graph::depthFirstSearch(std::string vertex)
{

    int i = this->resolveVertex(vertex);

    checkedNodes[i] = true;
    std::cout << "<" << this->vertices.at(i) << ">" << " -> ";
    std::vector<std::string> neighbours = this->neighbours(this->vertices.at(i));

    for(auto & neighbour : neighbours)
    {
        int a = this->resolveVertex(neighbour);
        if (!checkedNodes[a])
            depthFirstSearch(this->vertices.at(a));
    }
}


int Graph::getEdgeWeight(std::string sourceVertex, std::string targetVertex) {

    if(this->adjacent(sourceVertex,targetVertex)){
        return adjacencyMatrix[this->resolveVertex(sourceVertex)][this->resolveVertex(targetVertex)];
    }
    return 0;
}

void Graph::setEdgeWeight(std::string sourceVertex, std::string targetVertex, int weight) {
    if(getEdgeWeight(sourceVertex,targetVertex) == 0){
        auto edge = {sourceVertex,targetVertex};
        this->adjacencyMatrix[this->resolveVertex(sourceVertex)][this->resolveVertex(targetVertex)] = weight;
    }else{
        this->adjacencyMatrix[this->resolveVertex(sourceVertex)][this->resolveVertex(targetVertex)] = weight;
    }
}
