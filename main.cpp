
#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include <queue>
#include <vector>
#include <stack>
#include "graph.h"
//#include "d_graph.h"


class Map {
public:
    Map() {
        myMatrix;
    }

    Map(ifstream &fin) {
        std::string input;
        char spaceIndicator;

        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                fin >> input;
                rows = stoi(input);
            }
            if (i == 1) {
                fin >> input;
                cols = stoi(input);
            }
        }

        myMatrix = matrix<char>(rows, cols, 0);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fin >> spaceIndicator;
                myMatrix[i][j] = spaceIndicator;
            }
        }

        /*for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << myMatrix[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";*/
    };

    int numRows() { return rows; }

    int numCols() { return cols; }

    bool isLegal(int i, int j) {
        if (i < 0 || i >= rows) {
            return false;
        } else if (j < 0 || j >= cols) {
            return false;
        } else if (myMatrix[i][j] == 'O') {
            return true;
        } else {
            return false;
        }
    }

    struct Graph {
        matrix<int> adjacencyMatrix;
        bool *seen;
    };


    void mapToGraph(Graph *g) {
        //70 vectors? Only add a vector if it is legal
        int graphSize = cols * rows;
        //adjacency matrix ex 70x70

        g->adjacencyMatrix = matrix<int>(graphSize, graphSize, 0);
        //initialize the boolean array

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                //std::cout << i << " " << j << " \n";
                if (myMatrix[i][j] == 'O') {
                    if (isLegal(i + 1, j)) {
                        //std::cout << i*10+j << " " << ((i+1)*10)+j << " \n";
                        g->adjacencyMatrix[i * cols + j][((i + 1) * cols) +
                                                         j] = 1;
                        //std::cout << ((i+1)*10)+j << " " << i*10+j << " \n";
                        g->adjacencyMatrix[((i + 1) * cols) + j][i * cols +
                                                                 j] = 1;

                    }
                    if (isLegal(i, j + 1)) {
                        //std::cout << i*10+j << " " << (i*10)+j+1 << " \n";
                        g->adjacencyMatrix[i * cols + j][(i * cols) + j +
                                                         1] = 1;
                        //std::cout << (i*10)+j+1 << " " << i*10+j << " \n";
                        g->adjacencyMatrix[(i * cols) + j + 1][i * cols +
                                                               j] = 1;

                    }
                    if (isLegal(i - 1, j)) {
                        //std::cout << i*10+j << " " << ((i-1)*10)+j << " \n";
                        g->adjacencyMatrix[i * cols + j][((i - 1) * cols) +
                                                         j] = 1;
                        //std::cout << ((i-1)*10)+j << " " << i*10+j << " \n";
                        g->adjacencyMatrix[((i - 1) * cols) + j][i * cols +
                                                                 j] = 1;

                    }
                    if (isLegal(i, j - 1)) {
                        //std::cout << i*10+j << " " << (i*10)+j-1 << " \n";
                        g->adjacencyMatrix[i * cols + j][(i * cols) + j -
                                                         1] = 1;
                        //std::cout << (i*10)+j-1 << " " << i*10+j << " \n";
                        g->adjacencyMatrix[(i * cols) + j - 1][i * cols +
                                                               j] = 1;
                    }
                }

            }
        }
        //print the adjacency matrix

        //1 is true 0 is false

    }

    void printPath(stack<int> &s) {
        int size = s.size();
        int path[size];
        char directions[size][15];
        int i = 0;
        while (!s.empty()) {
            path[i] = s.top();
            s.pop();
            i++;
        }

        for (int j = size - 1; j > 0; j--) {
            int firstMove = path[j];
            //std::cout << "first move: " << path[j] << " ";
            int secondMove = path[j - 1];
            //std::cout << "second move: " << path[j] << " ";
            int iConvertFirstMove = firstMove / cols;
            //std::cout << "row first move: " << iConvertFirstMove << " ";
            int jConvertFirstMove = firstMove % cols;
            //std::cout << "col first move: " << jConvertFirstMove << " ";
            int iConvertSecondMove = secondMove / cols;
            //std::cout << "row second move: " << iConvertSecondMove << " ";
            int jConvertSecondMove = secondMove % cols;
            //std::cout << "col second move: " << jConvertSecondMove << " ";

            if (j == 1) {
                print(iConvertFirstMove, jConvertFirstMove, rows, cols);
                print(iConvertSecondMove, jConvertSecondMove, rows, cols);
            } else {
                print(iConvertFirstMove, jConvertFirstMove, rows, cols);
            }
            //std::cout << "\n";

            if (iConvertSecondMove - iConvertFirstMove == 0) {
                if (jConvertSecondMove - jConvertFirstMove == 1) {
                    strcpy(directions[j], "Go Right, ");
                } else if (jConvertSecondMove - jConvertFirstMove == -1) {
                    strcpy(directions[j], "Go Left, ");
                }
            } else if (iConvertSecondMove - iConvertFirstMove == 1) {
                strcpy(directions[j], "Go Down, ");
            } else {
                strcpy(directions[j], "Go Up, ");
            }
            //std::cout << "\n";
        }
        for (int i = size - 1; i > 0; i--) {
            std::cout << directions[i];
        }
        std::cout << "Done! \n";
    }

    void print(int rowCar, int colCar, int row, int col) {
        carPath = matrix<char>(rows, cols, 0);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (rowCar == i && colCar == j) {
                    carPath[i][j] = '+';
                } else if (myMatrix[i][j] == 'X') {
                    carPath[i][j] = 'X';
                } else if (myMatrix[i][j] == 'O') {
                    carPath[i][j] = ' ';
                }
            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                std::cout << carPath[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";

    }

    void setUnseen(Graph *g) {
        int graphSize = rows * cols;
        g->seen = new bool[graphSize];
        for (int i = 0; i < graphSize; i++) {
            g->seen[i] = false;
        }
    }

    bool findPathRecursive(Graph &g, stack<int> &moves) {
        int graphSize = rows * cols;
        int vertex = moves.top();
        if (vertex == graphSize - 1) {
            printPath(moves);
            return true;
        }
        //marks the vertex as seen
        g.seen[vertex] = true;

        for (int i = vertex - cols; i < (vertex + cols + 1); i++) {
            if (g.adjacencyMatrix[vertex][i] == 1) {
                //push the vertex into the stack if the vertex is adjacent
                moves.push(i);
                //if the vertex is unseen then mark it as true and recursively call
                //the function, otherwise it pops off and continues with the loop
                if (g.seen[i] == false) {
                    g.seen[i] = true;
                    if (findPathRecursive(g, moves)) {
                        return true;
                    } else {
                        moves.pop();
                    }
                } else {
                    moves.pop();
                }
            }

        }


        //std::cout << "No path exists.\n";
        return false;

    }

    bool findPathNonRecursive1(Graph &g, stack<int> &moves) {
        int graphSize = rows * cols;
        setUnseen(&g);
        moves.push(0);
        int vertex = moves.top();

        g.seen[vertex] = true;

        while (!moves.empty()) {
            vertex = moves.top();
            if (vertex == graphSize - 1) {
                printPath(moves);
                return true;
            }
            if (g.adjacencyMatrix[vertex][vertex + 1] == 1 &&
                g.seen[vertex + 1] == false) {
                g.seen[vertex + 1] = true;
                moves.push(vertex + 1);
            } else if (g.adjacencyMatrix[vertex][vertex - 1] == 1 &&
                       g.seen[vertex - 1] == false) {
                g.seen[vertex - 1] = true;
                moves.push(vertex - 1);
            } else if (g.adjacencyMatrix[vertex][vertex + cols] == 1 &&
                       g.seen[vertex + cols] == false) {
                g.seen[vertex + cols] = true;
                moves.push(vertex + cols);
            } else if (g.adjacencyMatrix[vertex][vertex - cols] == 1 &&
                       g.seen[vertex - cols] == false) {
                g.seen[vertex - cols] = true;
                moves.push(vertex - cols);
            } else {
                moves.pop();
            }
        }
        std::cout << "No path exists.\n";
        return false;
    }

    //Uses BFS to find path
    bool findPathNonRecursive2(Graph &g, queue<int> &moves) {
        int vertex;
        int graphSize = cols * rows;
        int *parents = new int[graphSize];
        std::stack<int> printQueue;
        vector<int> reverseParents;
        setUnseen(&g);
        vector<int> bfsPath;
        moves.push(0);
        g.seen[0] = true;

        //sets all parents to -1
        for (int i = 0; i < graphSize; i++) {
            parents[i] = -1;
        }

        while (!moves.empty()) {

            vertex = moves.front();
            //std::cout << "vertex: " << vertex << " ";
            if (vertex == graphSize - 1) {
                int index = graphSize - 1;
                int child;

                //takes the array of parents and children and finds the correct path
                //and adds it to the vector
                reverseParents.push_back(graphSize - 1);
                while (parents[index] != 0) {
                    child = parents[index];
                    reverseParents.push_back(parents[index]);
                    std::cout << "child: " << index << " parent: "
                              << parents[index] << "\n";
                    index = child;
                }
                reverseParents.push_back(parents[index]);

                //adds the vector to a stack to run through the printing function
                for (int i = reverseParents.size() - 1; i >= 0; i--) {
                    printQueue.push(reverseParents[i]);
                }

                printPath(printQueue);
                return true;
            }
            //goes through each adjacent vertex and if it is unseen it will add
            //the vertex to the queue and mark it seen and continue with the loop
            //pops the vertex from the last part of the queue for the next loop
            for (int i = vertex - cols; i < (vertex + cols + 1); i++) {
                if (g.adjacencyMatrix[vertex][i] == 1 && g.seen[i] == false) {
                    parents[i] = vertex;
                    moves.push(i);
                    g.seen[i] = true;
                }
            }
            moves.pop();

        }
        std::cout << "No path exists.\n";
        return false;
    }

    std::vector<int> findConnected(Graph g) {
        queue<int> myQueue;
        vector<int> bananas;

        setUnseen(&g);
        myQueue.push(0);
        int myVertex = myQueue.front();
        int i = 0;
        bananas.push_back(0);
        g.seen[0] = true;

        while (!myQueue.empty()) {
            //Look at the
            if (g.adjacencyMatrix[myVertex][myVertex + 1] == 1 &&
                g.seen[myVertex + 1] == false) {
                myQueue.push(myVertex + 1);
                g.seen[myVertex + 1] = true;
            }
            if (g.adjacencyMatrix[myVertex][myVertex - 1] == 1 &&
                g.seen[myVertex - 1] == false) {
                myQueue.push(myVertex - 1);
                g.seen[myVertex - 1] = true;
            }
            if (g.adjacencyMatrix[myVertex][myVertex + cols] == 1 &&
                g.seen[myVertex + cols] == false) {
                myQueue.push(myVertex + cols);
                g.seen[myVertex + cols] = true;
            }
            if (g.adjacencyMatrix[myVertex][myVertex - cols] == 1 &&
                g.seen[myVertex - cols] == false) {
                myQueue.push(myVertex - cols);
                g.seen[myVertex - cols] = true;
            }
            myQueue.pop();
            i++;
            if (!myQueue.empty()) {
                myVertex = myQueue.front();
                bananas.push_back(myVertex);
            }
            //std::cout << myVertex;

        }

        /*for (int i = 0; i < bananas.size(); i++) {
            std::cout << "banana: " << bananas[i] << "\n";
        }*/
        return bananas;
    }

    //uses Dijkstra algorithm
    bool findShortestPath1(Graph &g, stack<int> &bestMoves) {
        int graphSize = rows * cols;
        int *parents = new int[graphSize];
        int vertex;
        vector<int> findPath;
        vector<int> possibleMoves;
        int *SP = new int[graphSize];
        std::stack<int> printStack;
        int index = graphSize - 1;
        int child;
        //mark all vertices as unseen
        setUnseen(&g);

        //set SP all vertices to infinity
        //they are all infinity except for the first one
        SP[0] = 0;
        for (int i = 1; i < graphSize; i++) {
            SP[i] = std::numeric_limits<int>::max();// - graphSize;
            //std::cout << "placed in SP" << i << ": " << SP[i] << "\n";
        }

        //sets all parents to -1 so the child is the index and the parent is the value
        for (int i = 0; i < graphSize; i++) {
            parents[i] = -1;
        }

        //push all vertices into stack(pq?)?
//        for (int i = graphSize-1 ; i >= 0; i--) {
//            bestMoves.push(i);
//        }

        possibleMoves = findConnected(g);

        for (int i = possibleMoves.size() - 1; i >= 0; i--) {
            bestMoves.push(possibleMoves[i]);
        }
        setUnseen(&g);

        while (!bestMoves.empty()) {
            //pop vertex off the stack(pq?)
            vertex = bestMoves.top();
            //std::cout << "vertex: " << vertex << "\n";
            bestMoves.pop();
            //mark vertex as visited
            g.seen[vertex] = true;

            //for all unvisited neighbors i of vertex:
            for (int i = vertex - cols; i < (vertex + cols + 1); i++) {
                if (g.adjacencyMatrix[vertex][i] == 1 && g.seen[i] == false) {
                    if (SP[i] > SP[vertex] + 1) {
                        //std::cout << "Path of: " << i << ":  " << SP[i] << " Path of " << vertex << ": " << SP[vertex] << "\n";
                        //std::cout << "parent: " << vertex << " child: " << i << "\n";
                        SP[i] = SP[vertex] + 1;
                        //std::cout << "New path of " << i << ": " << SP[i] << "\n";
                        parents[i] = vertex;

                    }

                }
            }
        }
        if (parents[graphSize - 1] != -1) {
            //takes the array of parents and children and finds the correct path
            //and adds it to the vector
            findPath.push_back(graphSize - 1);
            while (parents[index] != 0) {
                child = parents[index];
                //std::cout << "parent: " << index << " child: " << parents[index] << "\n";
                findPath.push_back(parents[index]);
                index = child;
            }
            findPath.push_back(parents[index]);

            for (int i = findPath.size() - 1; i >= 0; i--) {
                printStack.push(findPath[i]);
            }

            printPath(printStack);
            return true;
        } else {
            std::cout << "No path exists.\n";
            return false;
        }

    }

    //Bellman Ford
    bool findShortestPath2(Graph &g, vector<int> &bestMoves) {
        int graphSize = rows * cols;
        int *SP = new int[graphSize];
        int *parents = new int[graphSize];
        std::stack<int> printStack;
        int sourceSP = 0;
        int sourceParent = 0;
        int index = graphSize - 1;
        int child;

        //set SP all vertices to infinity
        //they are all infinity except for the first one
        for (int i = 1; i < graphSize; i++) {
            SP[i] = std::numeric_limits<int>::max();
        }
        SP[sourceSP] = sourceSP;

        //sets all parents to -1 so the child is the index and the parent is the value
        for (int i = 0; i < graphSize; i++) {
            parents[i] = -1;
        }
        parents[sourceParent] = sourceParent;

        bestMoves = findConnected(g);
        int u;

        //For (i from 1 to |v| -1)
        for (int i = 0; i < bestMoves.size(); i++) {
            //For(u,v) in edges; for each edge (u,v) in g
            u = bestMoves[i];
            for (int v = u - cols; v < (u + cols + 1); v++) {
                if (g.adjacencyMatrix[u][v] == 1) {
                    if (SP[v] > SP[u] + 1) {
                        //std::cout << "vertex: " << u << " other vertex: " << v << "\n";
                        SP[v] = SP[u] + 1;
                        parents[v] = u;
                    }
                }

            }
        }

        vector<int> theVeryBestMoves;
        if (parents[graphSize - 1] != -1) {
            //takes the array of parents and children and finds the correct path
            //and adds it to the vector
            theVeryBestMoves.push_back(graphSize - 1);
            while (parents[index] != 0) {
                child = parents[index];
                theVeryBestMoves.push_back(parents[index]);
                index = child;
            }
            theVeryBestMoves.push_back(parents[index]);

            for (int i = theVeryBestMoves.size() - 1; i >= 0; i--) {
                printStack.push(theVeryBestMoves[i]);
            }

            printPath(printStack);
            return true;
        } else {
            std::cout << "No path exists.\n";
            return false;
        }

    }

private:
    int rows = 0; // number of latitudes/rows in the map
    int cols = 0; // number of longitudes/columns in the map
    bool *seen;
    matrix<int> parentChild;
    matrix<char> myMatrix;
    matrix<char> carPath;
    matrix<int> mapping; // Mapping from latitude and longitude co-ordinates (i,j) values to node index values
    vector<int> reverseMapI; // Mapping from node index values to map latitude i value
    vector<int> reverseMapJ; // Mapping from node index values to map longitude j value
};

int main() {
    ifstream readFile;
    std::string fileName;
    std::string input;
    Map myMap;
    Map::Graph g;
    std::stack<int> seenSpots;
    vector<int> bellmanVector;
    std::queue<int> visited;


    //std::cout << "Enter the text file you would like to read from:\n";
    //std::cin >> fileName;
    std::cout << "Map 1:\n";
    readFile.open("map1.txt");

    if (readFile.is_open()) {
        std::cout << fileName + " is open\n";

        myMap = Map(readFile);
        //read the first 2 numbers from the file to create matrix

    } else {
        std::cout << "File not able to be opened.\n";
        exit(0);
    }
    //create the graph from the map
    myMap.mapToGraph(&g);

    //find a recursive path using stack First push 0 onto the stack & set the map to unseen
    seenSpots.push(0);
    myMap.setUnseen(&g);

    std::cout << "Find path recursive: \n";
    myMap.findPathRecursive(g, seenSpots);
    std::cout << "Find path non-recursive 1: \n";
    myMap.findPathNonRecursive1(g, seenSpots);
    std::cout << "Find path non-recursive 2: \n";
    myMap.findPathNonRecursive2(g, visited);
    std::cout << "Find shortest path 1: \n";
    myMap.findShortestPath1(g, seenSpots);
    std::cout << "Find shortest path 2: \n";
    myMap.findShortestPath2(g, bellmanVector);

    readFile.close();

    std::cout << "Map 2:\n";
    readFile.open("map2.txt");

    if (readFile.is_open()) {
        std::cout << fileName + " is open\n";

        myMap = Map(readFile);
        //read the first 2 numbers from the file to create matrix

    } else {
        std::cout << "File not able to be opened.\n";
        exit(0);
    }
    //create the graph from the map
    myMap.mapToGraph(&g);

    //find a recursive path using stack First push 0 onto the stack & set the map to unseen
    seenSpots.push(0);
    myMap.setUnseen(&g);

    std::cout << "Find path recursive: \n";
    myMap.findPathRecursive(g, seenSpots);
    std::cout << "Find path non-recursive 1: \n";
    myMap.findPathNonRecursive1(g, seenSpots);
    std::cout << "Find path non-recursive 2: \n";
    myMap.findPathNonRecursive2(g, visited);
    std::cout << "Find shortest path 1: \n";
    myMap.findShortestPath1(g, seenSpots);
    std::cout << "Find shortest path 2: \n";
    myMap.findShortestPath2(g, bellmanVector);

    readFile.close();

    std::cout << "Map 3:\n";
    readFile.open("map3.txt");

    if (readFile.is_open()) {
        std::cout << "map3.txt is open\n";

        myMap = Map(readFile);
        //read the first 2 numbers from the file to create matrix

    } else {
        std::cout << "File not able to be opened.\n";
        exit(0);
    }
    //create the graph from the map
    myMap.mapToGraph(&g);

    //find a recursive path using stack First push 0 onto the stack & set the map to unseen
    seenSpots.push(0);
    myMap.setUnseen(&g);

    std::cout << "Find path recursive: \n";
    myMap.findPathRecursive(g, seenSpots);
    std::cout << "Find path non-recursive 1: \n";
    myMap.findPathNonRecursive1(g, seenSpots);
    std::cout << "Find path non-recursive 2: \n";
    myMap.findPathNonRecursive2(g, visited);
    std::cout << "Find shortest path 1: \n";
    myMap.findShortestPath1(g, seenSpots);
    std::cout << "Find shortest path 2: \n";
    myMap.findShortestPath2(g, bellmanVector);

    readFile.close();

    return 0;
}








