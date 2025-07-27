#include <iostream>
#include <vector>
#include <climits>

using namespace std;

//Structure to represent an edge
struct Edge {
    int dest;
    int weight;
};

//Structure to represent a graph
class Graph {
public:
    int V; 
    vector<vector<Edge>> adj; //Adjacency list

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int src, int dest, int weight) {
        Edge edge1 = {dest, weight};
        Edge edge2 = {src, weight}; //since it is undirected
        adj[src].push_back(edge1);
        adj[dest].push_back(edge2);
    }
};

struct MinHeapNode {
    int v;     
    int key;    
};

class MinHeap {
public:
    int size;                   
    int capacity;               
    vector<int> pos;            
    vector<MinHeapNode> array;  

    MinHeap(int capacity);

    void minHeapify(int idx);
    bool isEmpty();
    MinHeapNode extractMin();
    void decreaseKey(int v, int key);
    bool isInMinHeap(int v);
};

MinHeap::MinHeap(int capacity) {
    this->pos.resize(capacity);
    this->size = 0;
    this->capacity = capacity;
    this->array.resize(capacity);
}

void MinHeap::minHeapify(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && array[left].key < array[smallest].key)
        smallest = left;

    if (right < size && array[right].key < array[smallest].key)
        smallest = right;

    if (smallest != idx) {
        //Swap positions
        MinHeapNode smallestNode = array[smallest];
        MinHeapNode idxNode = array[idx];

        pos[smallestNode.v] = idx;
        pos[idxNode.v] = smallest;

        //Swap nodes
        swap(array[smallest], array[idx]);

        minHeapify(smallest);
    }
}

bool MinHeap::isEmpty() {
    return size == 0;
}

MinHeapNode MinHeap::extractMin() {
    if (isEmpty())
        return { -1, -1 };

    MinHeapNode root = array[0];

    MinHeapNode lastNode = array[size - 1];
    array[0] = lastNode;

    pos[root.v] = size - 1;
    pos[lastNode.v] = 0;

    --size;
    minHeapify(0);

    return root;
}

void MinHeap::decreaseKey(int v, int key) {
    int i = pos[v];
    array[i].key = key;

    while (i && array[i].key < array[(i - 1) / 2].key) {
        pos[array[i].v] = (i - 1) / 2;
        pos[array[(i - 1) / 2].v] = i;
        swap(array[i], array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

bool MinHeap::isInMinHeap(int v) {
    return pos[v] < size;
}

void PrimMST(Graph& graph) {
    int V = graph.V;
    vector<int> parent(V);   //Array to store constructed MST
    vector<int> key(V);      //Key values to pick minimum weight edge
    MinHeap minHeap(V);

    for (int v = 0; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap.array[v] = { v, key[v] };
        minHeap.pos[v] = v;
    }

    key[0] = 0;
    minHeap.array[0].key = 0;
    minHeap.size = V;

    while (!minHeap.isEmpty()) {
        MinHeapNode minHeapNode = minHeap.extractMin();
        int u = minHeapNode.v;

        //Traverse through all adjacent vertices of u
        for (auto& edge : graph.adj[u]) {
            int v = edge.dest;

            //If v is still in min-heap and weight of u-v is less than key of v
            if (minHeap.isInMinHeap(v) && edge.weight < key[v]) {
                key[v] = edge.weight;
                parent[v] = u;
                minHeap.decreaseKey(v, key[v]);
            }
        }
    }

    cout << "Edge   Weight\n";
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << "    " << key[i] << endl;
}

int main() {
    int V = 9;
    Graph graph(V);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 7, 8);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 7, 11);
    graph.addEdge(2, 3, 7);
    graph.addEdge(2, 8, 2);
    graph.addEdge(2, 5, 4);
    graph.addEdge(3, 4, 9);
    graph.addEdge(3, 5, 14);
    graph.addEdge(4, 5, 10);
    graph.addEdge(5, 6, 2);
    graph.addEdge(6, 7, 1);
    graph.addEdge(6, 8, 6);
    graph.addEdge(7, 8, 7);

    PrimMST(graph);

    return 0;
}