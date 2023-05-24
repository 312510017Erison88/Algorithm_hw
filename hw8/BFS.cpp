#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>

using namespace std;

void enqueue(queue<int>& q, int vertex);
int dequeue(queue<int>& q);
void BFS(vector<vector<int> >& graph, int start);

struct Vertex {
    int color;
    int distance;
    int parent;
};

int main(){
    // Example usage
    vector<vector<int> > graph;
    graph.resize(5);
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(0);
    graph[2].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(1);
    graph[3].push_back(2);
    graph[3].push_back(4);
    graph[4].push_back(3);

    /*
    {
        {1, 2},     // Vertex 0 is connected to vertices 1 and 2
        {0, 2, 3},  // Vertex 1 is connected to vertices 0, 2, and 3
        {0, 1, 3},  // Vertex 2 is connected to vertices 0, 1, and 3
        {1, 2, 4},  // Vertex 3 is connected to vertices 1, 2, and 4
        {3}         // Vertex 4 is connected to vertex 3
    };
    */

    int startVertex = 0;  // Starting vertex for BFS

    BFS(graph, startVertex);
    
    return 0;
}

void enqueue(queue<int>& q, int vertex){
    q.push(vertex);
}

int dequeue(queue<int>& q){
    int vertex = q.front();
    q.pop();
    return vertex;
}

void BFS(vector<vector<int> >& graph, int start){
    int numVertices = graph.size();
    vector<Vertex> vertices(numVertices);

    for(int u = 0; u < numVertices; u++){
        vertices[u].color = 0;  // white
        vertices[u].distance = INT_MAX;
        vertices[u].parent = -1;  // NIL
    }

    vertices[start].color = 1;  // gray
    vertices[start].distance = 0;

    queue<int> queue;
    enqueue(queue, start);

    while(!queue.empty()){
        int u = dequeue(queue);

        for(vector<int>::iterator it = graph[u].begin(); it != graph[u].end(); it++){   // find nearest neighbor from that vertex
            int v = *it;
            if (vertices[v].color == 0){  // white
                vertices[v].color = 1;  // gray
                vertices[v].distance = vertices[u].distance + 1;
                vertices[v].parent = u;
                enqueue(queue, v);
            }
        }
        vertices[u].color = 2;  // black
    }

    // Printing the BFS traversal results
    for(int u = 0; u < numVertices; u++){
        cout << "Vertex " << u << ": ";
        cout << "Distance = " << vertices[u].distance << ", ";
        cout << "Parent = " << vertices[u].parent << endl;
    }
}
