
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


class Map
{
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

        myMatrix = matrix<char> (rows, cols, 0);

        for (int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                fin >> spaceIndicator;
                myMatrix[i][j] = spaceIndicator;
            }
        }

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                std::cout << myMatrix[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    };

    bool isLegal(int i, int j) {
        if (i < 0 || i >= rows) {
            return false;
        }
        else if (j < 0 || j >= cols){
            return false;
        }
        else if (myMatrix[i][j] == 'O') {
            return true;
        }
        else {
            return false;
        }
    }

    struct Graph {
        matrix<int> adjacencyMatrix;
        bool* seen;
    };


    void mapToGraph(Graph *g) {
        //70 vectors? Only add a vector if it is legal
        int graphSize = cols * rows;
        //adjacency matrix ex 70x70

        g->adjacencyMatrix = matrix<int> (graphSize, graphSize, 0);
        //initialize the boolean array

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                //std::cout << i << " " << j << " \n";
                if (myMatrix[i][j] == 'O') {
                    if (isLegal(i+1, j)) {
                        //std::cout << i*10+j << " " << ((i+1)*10)+j << " \n";
                        g->adjacencyMatrix[i*cols+j][((i+1)*cols)+j] = 1;
                        //std::cout << ((i+1)*10)+j << " " << i*10+j << " \n";
                        g->adjacencyMatrix[((i+1)*cols)+j][i*cols+j] = 1;

                    }
                    if (isLegal(i, j+1)) {
                        //std::cout << i*10+j << " " << (i*10)+j+1 << " \n";
                        g->adjacencyMatrix[i*cols+j][(i*cols)+j+1] = 1;
                        //std::cout << (i*10)+j+1 << " " << i*10+j << " \n";
                        g->adjacencyMatrix[(i*cols)+j+1][i*cols+j] = 1;

                    }
                    if (isLegal(i-1, j)) {
                        //std::cout << i*10+j << " " << ((i-1)*10)+j << " \n";
                        g->adjacencyMatrix[i*cols+j][((i-1)*cols)+j] = 1;
                        //std::cout << ((i-1)*10)+j << " " << i*10+j << " \n";
                        g->adjacencyMatrix[((i-1)*cols)+j][i*cols+j] = 1;

                    }
                    if (isLegal(i, j-1)) {
                        //std::cout << i*10+j << " " << (i*10)+j-1 << " \n";
                        g->adjacencyMatrix[i*cols+j][(i*cols)+j-1] = 1;
                        //std::cout << (i*10)+j-1 << " " << i*10+j << " \n";
                        g->adjacencyMatrix[(i*cols)+j-1][i*cols+j] = 1;
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

        for (int j = size-1; j > 0; j--) {
            int firstMove = path[j];
            //std::cout << "first move: " << path[j] << " ";
            int secondMove = path[j-1];
            //std::cout << "second move: " << path[j] << " ";
            int iConvertFirstMove = firstMove/cols;
            //std::cout << "row first move: " << iConvertFirstMove << " ";
            int jConvertFirstMove = firstMove%cols;
            //std::cout << "col first move: " << jConvertFirstMove << " ";
            int iConvertSecondMove = secondMove/cols;
            //std::cout << "row second move: " << iConvertSecondMove << " ";
            int jConvertSecondMove = secondMove%cols;
            //std::cout << "col second move: " << jConvertSecondMove << " ";

            print(iConvertFirstMove, jConvertFirstMove, rows, cols);
            //std::cout << "\n";

            if (iConvertSecondMove - iConvertFirstMove == 0) {
                if(jConvertSecondMove - jConvertFirstMove == 1) {
                    strcpy(directions[j], "Go Right, ");
                }
                else if(jConvertSecondMove-jConvertFirstMove == -1) {
                    strcpy(directions[j], "Go Left, ");
                }
            }
            else if(iConvertSecondMove - iConvertFirstMove == 1) {
                strcpy(directions[j], "Go Down, ");
            }
            else {
                strcpy(directions[j], "Go Up, ");
            }
            //std::cout << "\n";
        }
        for (int i = size-1; i > 0; i--) {
            std::cout << directions[i];
        }
        std::cout << "Done! \n";
    }

    void print(int rowCar, int colCar, int row, int col) {
        carPath = matrix<char> (rows, cols, 0);
        for (int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if (rowCar == i && colCar == j) {
                    carPath[i][j] = '+';
                }
                else if (myMatrix[i][j] == 'X'){
                    carPath[i][j] = 'X';
                }
                else if (myMatrix[i][j] == 'O') {
                    carPath[i][j] = ' ';
                }
            }
        }

        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
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

        //bool seen[rows*cols];

        int graphSize = rows * cols;
        int vertex = moves.top();
        if (vertex == graphSize-1) {
            printPath(moves);
            return true;
        }
        g.seen[vertex] = true;

            for (int i = vertex-cols; i < (vertex + cols + 1); i++) {
                if (g.adjacencyMatrix[vertex][i] == 1) {
                    moves.push(i);
                    if (g.seen[i] == false) {
                        //std::cout << "vertex: " << vertex << "\n";
                        //std::cout << "i: " << i << "\n";
                        g.seen[i] = true;
                        if (findPathRecursive(g, moves)) {
                            return true;
                        }
                        else {
                            moves.pop();
                        }
                    } else {
                        moves.pop();
                    }
                }

            }

        if (moves.empty()) {
            std::cout << "No path exists.\n";
            return false;
        }


            //find i and j from vertex for checking

    }

    /*DFS(Graph G, Vertex Vs) {
Mark all vertices as unvisited
        Initialize stack and push source vertex (Vs) into stack
Mark Vs as visited

while the stack is not empty {
set v = top; (vertex on the top of the stack);
if (vertex v has an unvisited adjacent vertex w) {
mark w as visited;
push w on the stack;
} else {
pop v from the stack;
}
}
}*/

private:
    int rows; // number of latitudes/rows in the map
    int cols; // number of longitudes/columns in the map
    bool* seen;
    matrix<bool> visited;
    matrix<char> myMatrix;
    matrix<char> carPath;
    matrix<int> mapping; // Mapping from latitude and longitude co-ordinates (i,j) values to node index values
    vector<int> reverseMapI; // Mapping from node index values to map latitude i value
    vector<int> reverseMapJ; // Mapping from node index values to map longitude j value
};

int main()
{
    ifstream readFile;
    std::string fileName;
    std::string input;
    Map myMap;
    Map::Graph g;
    std::stack<int> seenSpots;


    std::cout << "Enter the text file you would like to read from:\n";
    std::cin >> fileName;
    readFile.open(fileName);

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

    //find a recursive path using stack
    seenSpots.push(0);


    myMap.setUnseen(&g);

    if (myMap.findPathRecursive(g, seenSpots)) {
        std::cout << "FOUND IT!";
        //myMap.printPath(seenSpots);
        /*while (!seenSpots.empty()) {
            std::cout << seenSpots.top() << " ";
            seenSpots.pop();
        }
        std::cout << "\n";//print the stack*/
    }
    else {
        std::cout << "FAILED";
    }

    return 0;
}








