# Graph-Search-Engine

### Project Overview
This project is a from-scratch C++ implementation of a Directed Graph data structure. It features comprehensive search capabilities using both Breadth-First Search (BFS) and Depth-First Search (DFS) algorithms to navigate complex data relationships.

### Technical Highlights
* **Custom Adjacency List**: Engineered a directed graph using an array of linked lists, ensuring efficient representation of nodes and edges without relying on external libraries.
* **Algorithm Implementation**: Developed custom versions of BFS and DFS to demonstrate mastery of graph traversal and pathfinding logic.
* **Manual Memory Management**: Implemented the underlying data structures, including stacks and queues, to facilitate traversals while maintaining strict control over memory allocation and deallocation.
* **Search Flexibility**: The engine supports finding paths between any two nodes, handling both connected and disconnected components within the directed graph.

### Implementation Details
* **Language**: C++
* **Data Structures**: Adjacency List (Linked List based), Stack, Queue
* **Search Algorithms**: Breadth-First Search (BFS), Depth-First Search (DFS)
* **Graph Type**: Directed Graph

### How to Run

1. **Compile the source**:
   
   ```bash
   g++ main.cpp -o GraphSearch
   ```
 2.**Run the program**:

  Linux / macOS: ./GraphSearch

  Windows: GraphSearch.exe

3.**Usage**:

Follow the CLI prompts to build your graph by adding nodes and edges, then select a search method to find paths or traverse the structure.
