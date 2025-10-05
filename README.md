# Prim’s Algorithm – Minimum Spanning Tree (MST)

## 📜 Overview
This project implements **Prim’s Algorithm** to find the **Minimum Spanning Tree (MST)** of a connected, undirected, weighted graph.  
The MST is a subset of edges that connects all vertices in the graph with the minimum possible total edge weight and without forming cycles.

This C++ implementation uses:
- **Adjacency list** representation for the graph  
- A **custom Min Heap** data structure for efficiently selecting the next minimum-weight edge  

## 🧠 Algorithm Summary
Prim’s Algorithm works by:
1. Starting from any vertex.
2. Repeatedly adding the smallest edge that connects a vertex in the MST to one outside it.
3. Continuing until all vertices are included.

The result is an MST with minimal total cost.

## ⚙️ Features
- Handles **undirected weighted graphs**.
- Uses **Min Heap** to achieve better performance (O(E log V)).
- Clean separation of graph and heap structures.
- Outputs the final MST edges and their weights.
