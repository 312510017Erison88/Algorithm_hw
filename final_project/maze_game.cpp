#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>

using namespace std;

const int WALL = 0;
const int ROAD = 1;
const int TRAP = 2;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int xVal, int yVal) : x(xVal), y(yVal) {}
};

bool isValidMove(int x, int y, int numRows, int numCols) {
    return (x >= 0 && x < numRows && y >= 0 && y < numCols);
}

bool isRoad(vector<vector<int> >& maze, int x, int y) {
    return (maze[x][y] == ROAD || maze[x][y] == TRAP);
}

int shortestPath(vector<vector<int> >& maze, Point start, Point end) {
    int numRows = maze.size();
    int numCols = maze[0].size();

    vector<vector<int> > distance(numRows, vector<int>(numCols, numeric_limits<int>::max()));
    vector<vector<Point> > parent(numRows, vector<Point>(numCols, Point(-1, -1)));


    distance[start.x][start.y] = 0;

    queue<Point> q;
    q.push(start);

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        int x = current.x;
        int y = current.y;

        // Check if reached the destination
        if (x == end.x && y == end.y)
            break;

        // Possible moves: up, down, left, right
        int dx[4] = { -1, 1, 0, 0 };
        int dy[4] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValidMove(newX, newY, numRows, numCols) && isRoad(maze, newX, newY)) {
                int newDistance = distance[x][y] + 1;

                if (newDistance < distance[newX][newY]) {
                    distance[newX][newY] = newDistance;
                    parent[newX][newY].x = x;
					parent[newX][newY].y = y;
                    q.push(Point(newX, newY));
                }
            }
        }
    }

    // Backtrack to find the shortest path
    vector<Point> path;
    Point current = end;
    while (current.x != -1 && current.y != -1) {
        path.push_back(current);
        current = parent[current.x][current.y];
    }

    // Reverse the path
    reverse(path.begin(), path.end());

    // Write output to file
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cout << "Unable to open the output file." << endl;
        return 1;
    }

    // Write pattern number
    outputFile << "pattern 1" << endl;

        // Write step count
    int stepCount = path.size();
    outputFile << "step=" << stepCount << endl;

    // Write path coordinates
    for (vector<Point>::iterator it = path.begin(); it != path.end(); ++it) {
        outputFile << "(" << it->x << "," << it->y << ")" << endl;
    }

    outputFile.close();

    return 0;
}

int main() {
    // Read input from file
    ifstream inputFile("input.txt");
    if (inputFile){
    	cout << "read file success!" << endl;
	}
    if (!inputFile) {
        cout << "Unable to open the input file." << endl;
        return 1;
    }

    // Read maze dimensions
    int numRows, numCols;
    inputFile >> numRows >> numCols;

    // Read maze data
    vector<vector<int> > maze(numRows, vector<int>(numCols));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            inputFile >> maze[i][j];
        }
    }

    inputFile.close();

    // Define start and end points
    Point start;
    start.x = 0;
    start.y = 0;
    Point end;
    end.x = numRows - 1;
    end.y = numCols - 1;

    // Find the shortest path
    int shortest = shortestPath(maze, start, end);

    if (shortest == numeric_limits<int>::max()) {
        cout << "No path found to reach the destination." << endl;
    } else {
        cout << "Shortest path length: " << shortest << endl;
    }

    return 0;
}