#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Graph::addVertex(string name){
    vertex* v = new vertex;
    v->name = name;
    vertices.push_back(v);
    
}

void Graph::addEdge(string v1, string v2){
    vertex* vertex1 = nullptr;
    vertex* vertex2 = nullptr;

    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i]->name == v1){
            vertex1 = vertices[i];
        }else if (vertices[i]->name == v2){
            vertex2 = vertices[i];
        }   
    }

    if (!vertex1 || !vertex2){
        return;
    }
    adjVertex av1;
    av1.v = vertex2;
    vertex1->adj.push_back(av1);

    adjVertex av2;
    av2.v = vertex1;
    vertex2->adj.push_back(av2);
}

void Graph::displayEdges(){
    for (int i = 0; i < vertices.size(); ++i) {
        cout << vertices[i]->name << " --> ";
        for (int j = 0; j < vertices[i]->adj.size(); ++j) {
            cout << vertices[i]->adj[j].v->name;
            if (j != vertices[i]->adj.size())
                cout << " ";
        }
        cout << endl;
    }
    
}

void Graph::breadthFirstTraverse(string sourceVertex){
    vertex* source = nullptr;

    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i]->name == sourceVertex) {
            source = vertices[i];
            break;
        }
    }

    if (!source) {
        cout << "Vertex " << sourceVertex << " not found in the graph." << endl;
        return;
    }

    queue<vertex*> q_vertices; 
    queue<int> q_distances; 

    source->visited = true;
    q_vertices.push(source);
    q_distances.push(0); 

    cout << "Starting vertex (root): " << source->name << "-> " ;

    while (!q_vertices.empty()) {
        vertex* v = q_vertices.front();
        int distance = q_distances.front();
        q_vertices.pop();
        q_distances.pop();
        if (v != source)
            cout << v->name << "(" << distance << ") ";

        for (int i = 0; i < v->adj.size(); ++i) {
            if (!v->adj[i].v->visited) {
                v->adj[i].v->visited = true;
                q_vertices.push(v->adj[i].v);
                q_distances.push(distance + 1); 
            }
        }
    }
    cout << endl << endl;
    for (int i = 0; i < vertices.size(); ++i) {
        vertices[i]->visited = false;
    }
}
void flipVectorOrder(std::vector<std::string>& vec) {
    int left = 0;
    int right = vec.size() - 1;

    while (left < right) {
        std::swap(vec[left], vec[right]);
        ++left;
        --right;
    }
}
/*
string::source : source vertex (starting city)
int::k : distance that you can travel from source city with remaining fuel
*/
vector<string> Graph::findReachableCitiesWithinDistanceK(string source, int k){
    vector<string> reachableCities;
    vertex* sourceVertex = nullptr;
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i]->name == source) {
            sourceVertex = vertices[i];
            break;
        }
    }

    if (!sourceVertex) {
        cout << "Vertex " << source << " not found in the graph." << endl;
        return reachableCities;
    }

    queue<vertex*> vertexQueue;
    queue<int> distanceQueue;

    sourceVertex->visited = true;
    vertexQueue.push(sourceVertex);
    distanceQueue.push(0);

    while (!vertexQueue.empty()) {
        vertex* v = vertexQueue.front();
        int distance = distanceQueue.front();
        vertexQueue.pop();
        distanceQueue.pop();
        if (distance == k && v->name != source) {
            reachableCities.push_back(v->name);
        }
        if (distance < k) {
            for (int i = 0; i < v->adj.size(); ++i) {
                if (!v->adj[i].v->visited) {
                    v->adj[i].v->visited = true;
                    vertexQueue.push(v->adj[i].v);
                    distanceQueue.push(distance + 1); 
                }
            }
        }
    }
    for (int i = 0; i < vertices.size(); ++i) {
        vertices[i]->visited = false;
    }
    for (int i = 0; i < reachableCities.size(); ++i) {
        if (reachableCities[i] == source) {
            reachableCities.erase(reachableCities.begin() + i);
            break;
        }
    }
    flipVectorOrder(reachableCities);
    return reachableCities;

}
