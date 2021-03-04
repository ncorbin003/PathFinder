
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


void mapToGraph(matrix<char> *map);
bool isLegal(int i, int j);

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
    };


    void mapToGraph(Graph *g) {
        //70 vectors? Only add a vector if it is legal
        int graphSize = cols * rows;
        //adjacency matrix ex 70x70

        g->adjacencyMatrix = matrix<int> (graphSize, graphSize, 0);

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                //std::cout << i << " " << j << " \n";
                if (myMatrix[i][j] == 'O') {
                    if (isLegal(i+1, j)) {
                        //std::cout << i*10+j << " " << ((i+1)*10)+j << " \n";
                        g->adjacencyMatrix[i*10+j][((i+1)*10)+j] = 1;
                        //std::cout << ((i+1)*10)+j << " " << i*10+j << " \n";
                        g->adjacencyMatrix[((i+1)*10)+j][i*10+j] = 1;

                    }
                    if (isLegal(i, j+1)) {
                        //std::cout << i*10+j << " " << (i*10)+j+1 << " \n";
                        g->adjacencyMatrix[i*10+j][(i*10)+j+1] = 1;
                        //std::cout << (i*10)+j+1 << " " << i*10+j << " \n";
                        g->adjacencyMatrix[(i*10)+j+1][i*10+j] = 1;

                    }
                    if (isLegal(i-1, j)) {
                        //std::cout << i*10+j << " " << ((i-1)*10)+j << " \n";
                        g->adjacencyMatrix[i*10+j][((i-1)*10)+j] = 1;
                        //std::cout << ((i-1)*10)+j << " " << i*10+j << " \n";
                        g->adjacencyMatrix[((i-1)*10)+j][i*10+j] = 1;

                    }
                    if (isLegal(i, j-1)) {
                        //std::cout << i*10+j << " " << (i*10)+j-1 << " \n";
                        g->adjacencyMatrix[i*10+j][(i*10)+j-1] = 1;
                        //std::cout << (i*10)+j-1 << " " << i*10+j << " \n";
                        g->adjacencyMatrix[(i*10)+j-1][i*10+j] = 1;
                    }
                }

            }
        }

        for (int i = 0; i < graphSize; i++) {
            for (int j = 0; j < graphSize; j++) {
                std::cout << g->adjacencyMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
       //1 is true 0 is false

    }

private:
    int rows; // number of latitudes/rows in the map
    int cols; // number of longitudes/columns in the map
    matrix<bool> value;
    matrix<char> myMatrix;
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

    char spaceIndicator;
    int rows;
    int columns;

    std::cout << "Enter the text file you would like to read from:\n";
    std::cin >> fileName;
    readFile.open(fileName);

    if (readFile.is_open()) {
        std::cout << fileName + " is open\n";

        myMap = Map(readFile);
            //read the first 2 numbers from the file to create matrix

    } else {
        std::cout << "File not able to be opened.\n";
    }

    Map::Graph g;
    myMap.mapToGraph(&g);

    return 0;
}

/*void mapToGraph(matrix<char> *myMatrix) {
    graph<int> myGraph;
    int row = 0;
    int col = 0;

}*/




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

