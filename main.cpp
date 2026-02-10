#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

//Fowzi Hindi 33587

// Simple linked list Node structure for adjacency list
struct Node {
    int vertex;
    Node* next;

    Node(int v) : vertex(v), next(nullptr) {} // init constructor
};

class Graph {
private:
    Node** adjacencyList; // array of pointers for adjacency lists
    int numVertices;
    bool* visited;

    // Gets the highest vertex ID in the file (used to size the graph)
    int getMaxVertex(const string& filename) {
        ifstream file(filename);
        int maxVertex = -1;
        string line;

        while (getline(file, line)) {
            istringstream iss(line);
            string v1Str, v2Str;
            int v1, v2;

            // Check if line has exactly two values, skip otherwise
            if (!(iss >> v1Str >> v2Str) || iss >> ws && iss.get() != EOF) {
                continue;
            }

            // Try to turn those values into integers
            try {
                v1 = stoi(v1Str);
                v2 = stoi(v2Str);
            }
            catch (...) {
                continue;
            }

            // Only consider non-negative values
            if (v1 >= 0 && v2 >= 0) {
                maxVertex = max(maxVertex, max(v1, v2));
            }
        }
        file.close();
        return maxVertex;
    }

    // Checks if an edge between source and dest already exists
    bool edgeExists(int source, int dest) {
        Node* current = adjacencyList[source];
        while (current != nullptr) {
            if (current->vertex == dest)
                return true;
            current = current->next;
        }
        return false;
    }

    // Insert node in a sorted order in the linked list for adjacency list
    void insertSorted(int source, int dest) {
        Node* newNode = new Node(dest);
        if (adjacencyList[source] == nullptr || adjacencyList[source]->vertex >= dest) {
            newNode->next = adjacencyList[source];
            adjacencyList[source] = newNode;
            return;
        }
        Node* current = adjacencyList[source];
        while (current->next != nullptr && current->next->vertex < dest) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

public:
    // Constructor reads from file and builds the graph
    Graph(const string& filename) {
        numVertices = getMaxVertex(filename) + 1;
        adjacencyList = new Node*[numVertices];
        visited = new bool[numVertices];

        for (int i = 0; i < numVertices; i++) {
            adjacencyList[i] = nullptr;
            visited[i] = false;
        }
        readFromFile(filename);
    }

    // Destructor to free up memory for nodes, adjacency list, and visited array
    ~Graph() {
        for (int i = 0; i < numVertices; i++) {
            Node* current = adjacencyList[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjacencyList;
        delete[] visited;
    }

    // Reads the edges from file and fills adjacency list
    void readFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        cout << "These edges are illegal or repeated:" << endl;

        while (getline(file, line)) {
            istringstream iss(line);
            string v1Str, v2Str;
            int v1, v2;

            if (!(iss >> v1Str >> v2Str) || iss >> ws && iss.get() != EOF) {
                cout << line << endl;
                continue;
            }

            try {
                v1 = stoi(v1Str);
                v2 = stoi(v2Str);
            }
            catch (...) {
                cout << line << endl;
                continue;
            }

            // Check for out-of-bounds vertices or repeat edges
            if (v1 < 0 || v2 < 0 || v1 >= numVertices || v2 >= numVertices) {
                cout << line << endl;
                continue;
            }

            if (edgeExists(v1, v2)) {
                cout << line << endl;
                continue;
            }
            insertSorted(v1, v2);
        }
        file.close();
    }

    // Print out the graph in adjacency list format
    void displayGraph() {
        cout << "The graph has this structure:" << endl;
        int actualMaxVertex = -1;

        for (int i = 0; i < numVertices; i++) {
            if (adjacencyList[i] != nullptr) {
                actualMaxVertex = i;
            }
        }

        for (int i = 0; i <= actualMaxVertex; i++) {
            cout << i << " ->";
            Node* current = adjacencyList[i];
            while (current != nullptr) {
                cout << " " << current->vertex;
                if (current->next != nullptr) cout << " ->";
                current = current->next;
            }
            cout << endl;
        }
    }

    // Add a new edge between nodes
    void addEdge(int source, int dest) {
        while (source < 0 || dest < 0 || source >= numVertices || dest >= numVertices) {
            cout << "The entered node IDs are out of range, Enter two other IDs:" << endl;
            cin >> source >> dest;
        }

        if (edgeExists(source, dest)) {
            cout << "The edge already exists!" << endl;
            return;
        }
        insertSorted(source, dest);
        cout << "The new edge is added." << endl;
    }

    // Remove an existing edge
    void removeEdge(int source, int dest) {
        while (true) {
            // Check range first
            if (source < 0 || dest < 0 || source >= numVertices || dest >= numVertices) {
                cout << "The entered node IDs are out or range, Enter two other IDs:" << endl;
                cin >> source >> dest;
            }
            else if (!edgeExists(source, dest)) {  // Check edge existence only if range is valid
                cout << "The entered edge does not exist in the graph! Enter two other node IDs:" << endl;
                cin >> source >> dest;
            }
            else {
                break;  // Valid input, proceed with removal
            }
        }

        // Remove the edge
        Node* current = adjacencyList[source];
        Node* prev = nullptr;

        while (current != nullptr && current->vertex != dest) {
            prev = current;
            current = current->next;
        }

        if (prev == nullptr) {
            adjacencyList[source] = current->next;
        }
        else {
            prev->next = current->next;
        }

        delete current;
        cout << "The entered edge is removed." << endl;
    }

    // Reset the visited status for all nodes (for traversal)
    void resetVisited() {
        for (int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }
    }

    // Breadth-First Search (BFS) from a given starting node
    void BFS(int startVertex) {
        while (startVertex < 0 || startVertex >= numVertices) {
            cout << "The entered node number is out of range, enter a valid one:" << endl;
            cin >> startVertex;
        }

        resetVisited();
        queue<int> q;

        cout << "\nBreadth-first search starting from node " << startVertex << ":" << endl;
        visited[startVertex] = true;
        cout << startVertex << " ";
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();

            Node* temp = adjacencyList[currentVertex];
            while (temp != nullptr) {
                int adjVertex = temp->vertex;
                if (!visited[adjVertex]) {
                    cout << adjVertex << " ";
                    visited[adjVertex] = true;
                    q.push(adjVertex);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

    // Depth-First Search (DFS) from a given starting node
    void DFS(int startVertex) {
        while (startVertex < 0 || startVertex >= numVertices) {
            cout << "The entered node number is out of range, enter a valid one:" << endl;
            cin >> startVertex;
        }

        resetVisited();
        stack<int> s;

        cout << "Depth-first search starting from node " << startVertex << ":" << endl;

        // Push initial vertex
        s.push(startVertex);

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();

            if (!visited[currentVertex]) {
                cout << currentVertex << " ";
                visited[currentVertex] = true;

                // Store adjacent vertices in reverse order
                Node* temp = adjacencyList[currentVertex];
                vector<int> adjacentVertices;

                // Collect all adjacent vertices
                while (temp != nullptr) {
                    adjacentVertices.push_back(temp->vertex);
                    temp = temp->next;
                }

                // Push vertices to stack in forward order
                for (int i = 0; i < adjacentVertices.size(); i++) {
                    if (!visited[adjacentVertices[i]]) {
                        s.push(adjacentVertices[i]);
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    string filename;
    cout << "Enter the input file name:" << endl;
    cin >> filename;

    ifstream file(filename);
    while (!file.is_open()) {
        cout << "Could not open the file " << filename << endl;
        cout << "Enter the input file name:" << endl;
        cin >> filename;
        file.open(filename);
    }
    file.close();

    Graph graph(filename);
    int choice;
    bool firstRun = true;

    while (true) {
        if (firstRun) {
            cout << "\n   (1) Add edge" << endl;
            cout << "   (2) Remove edge" << endl;
            cout << "   (3) Display graph" << endl;
            cout << "   (4) Depth-first search" << endl;
            cout << "   (5) Breadth-first search" << endl;
            cout << "   (6) Exit" << endl;
            cout << "Please enter a number (1-6):" << endl;
            firstRun = false;
        }

        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "The entered number is not valid! Make another choice:" << endl;
            continue;
        }

        if (choice == 6) {
            cout << "Program Exiting..." << endl;
            break;
        }

        int v1, v2;

        switch (choice) {
            case 1:
                cout << "Enter two nodes as two endings of the new edge" << endl;
                cin >> v1 >> v2;
                graph.addEdge(v1, v2);
                break;

            case 2:
                cout << "Enter two nodes as two endings of the edge" << endl;
                cin >> v1 >> v2;
                graph.removeEdge(v1, v2);
                break;

            case 3:
                graph.displayGraph();
                cout << "Press any key to continue..." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;

            case 4:
                cout << "Please enter starting node:" << endl;
                cin >> v1;
                graph.DFS(v1);
                break;

            case 5:
                cout << "Please enter starting node:" << endl;
                cin >> v1;
                graph.BFS(v1);
                break;
        }

        cout << "\n   (1) Add edge" << endl;
        cout << "   (2) Remove edge" << endl;
        cout << "   (3) Display graph" << endl;
        cout << "   (4) Depth-first search" << endl;
        cout << "   (5) Breadth-first search" << endl;
        cout << "   (6) Exit" << endl;
        cout << "Please enter a number (1-6):" << endl;
    }

    return 0;
}
