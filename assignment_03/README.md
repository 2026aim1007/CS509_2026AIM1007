# CS509 Laboratory Repository

## Repository Overview
Individual Assignment Repository for **CS509 - PG Software Lab M.Tech AI 2026-27**: Minimum Spanning Tree (Kruskal and Prim Algorithms).

---

## Student / Pair Details
- **Roll Number:** 2026AIM1007
- **Name:** Ishtveer Singh Billing

---

## Language and Environment
- **Language:** C++
- **Compiler:** g++--14
- **Build System:** GNU Make

---

## Directory Structure

```plaintext
CS509_2026AIM1007/
|-- utility/
|   |-- csr.h
|   |-- csr.cpp
|   |-- testing_utils.h
|   `-- testing_utils.cpp
assignment_03/
|-- src/
|   |-- mst.h
|   |-- kruskal.cpp
|   `-- prim.cpp
|-- driver/
|   `-- driver.cpp
|-- tests/
|   |-- mst_10.txt
|   |-- mst_100.txt
|   |-- mst_10000.txt
|   |-- mst_50000.txt
|   `-- mst_100000.txt
|-- outputs/
|   |-- expected_mst_10.txt
|   |-- output_mst_10.txt
|   `-- ...
|-- generate_mst_tests.cpp
|-- Makefile
`-- README.md
```

---

## Common Wrapper / Driver: Build and Usage
The driver program loads weighted undirected graphs from adjacency list text files, converts them into Compressed Sparse Row (CSR) format, executes both Kruskal's and Prim's MST algorithms on the exact same graph representation, verifies total weight equivalence, and isolates algorithm execution time.

---

## Assignment 03 (Individual Task): Minimum Spanning Tree (Kruskal and Prim)

### Objective
Implement and benchmark two greedy Minimum Spanning Tree (MST) algorithms on weighted, undirected graphs using Compressed Sparse Row (CSR) format:

- **Kruskal's Algorithm:** Cycle detection and greedy edge selection via Disjoint Set Union (DSU) with Path Compression and Union by Rank.
- **Prim's Algorithm:** Tree growth via Min-Priority Queue starting deterministically from vertex 0.
- **Verification:** Verify that both implementations yield the exact same minimum total spanning tree weight for each input graph.

---

### Algorithm / Approach

#### Kruskal's Algorithm
1. Extracts unique undirected edges ($u < v$) directly from the CSR data arrays (`rowPtr`, `colIdx`, `values`) inside the timed algorithm routine.
2. Sorts all extracted edges in non-decreasing order of edge weight ($O(E \log E)$).
3. Iterates through the sorted edge list, using Disjoint Set Union (DSU) to check if endpoints belong to different components.
4. Connects disjoint sets and stops once exactly $V - 1$ edges are selected.

#### Prim's Algorithm
1. Starts growth deterministically at vertex $0$ for reproducible tree construction.
2. Utilizes a min-priority queue (`std::priority_queue` with `std::greater`) to greedily select the cheapest edge connecting an incorporated vertex to an unvisited vertex.
3. Maintains a boolean `inMST` array to prevent cycles and pushes newly exposed incident edges into the priority queue.
4. Terminates as soon as $V - 1$ edges are committed to the MST.

---

### Input Format

Input text files follow the Weighted Undirected Adjacency-List format:

```plaintext
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 neighbor2 weight2 ...
```

- **$V$**: Number of vertices.
- **$E$**: Number of undirected edges (each graph edge is counted once in $E$ even though it appears in both adjacency lists).
- **$u$**: Vertex whose adjacency list is being written.
- **`degree`**: Number of neighbors listed after vertex $u$.
- **`neighbor / weight`**: Destination vertex and the corresponding integer edge weight.

---

### Helper Functions / CSR Conversion
Adjacency lists are converted into CSR representation (`rowPtr`, `colIdx`, `values`) using the reusable `Csr` class from `utility/csr.cpp`. As mandated by benchmarking rules, the adjacency-list-to-CSR conversion is performed as preprocessing; its runtime is strictly excluded from reported algorithm execution times.

---

### File Structure Description
- `src/mst.h`: Edge data structure definition and algorithm declarations.
- `src/kruskal.cpp`: DSU implementation and Kruskal's MST algorithm logic.
- `src/prim.cpp`: Priority-queue-based Prim's MST algorithm logic.
- `utility/csr.h` / `utility/csr.cpp`: Adjacency list to CSR conversion utilities.
- `utility/testing_utils.h` / `utility/testing_utils.cpp`: Isolated benchmarking harness and metrics file comparator.
- `driver/driver.cpp`: Dedicated driver module for input validation, CSR setup, isolated execution timing, and output generation.
- `generate_mst_tests.cpp`: Deterministic graph generator ensuring connectedness, sparse density ($E \approx 3V$), and ground-truth output targets.

---

## Compilation & Execution

### Compilation
To compile all source files and generate the executable, run:

```bash
make
```

### Execution
To run across all graph sizes:

```bash
./driver_app ALL
```

To run in benchmark mode (averaging over 5 runs):

```bash
./driver_app ALL --test
```

---

## Test Cases and Result Table

| Algorithm | Test File | Vertices ($V$) | Edges ($E$) | Input Type | Expected Weight | Kruskal Weight | Prim Weight | Kruskal Time | Prim Time | Equal? | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| MST (Kruskal & Prim) | `mst_10.txt` | 10 | 30 | Weighted undirected CSR graph | 838 | 838 | 838 | 0.006 ms | 0.004 ms | Yes | **PASSED** |
| MST (Kruskal & Prim) | `mst_100.txt` | 100 | 300 | Weighted undirected CSR graph | 19428 | 19428 | 19428 | 0.017 ms | 0.014 ms | Yes | **PASSED** |
| MST (Kruskal & Prim) | `mst_10000.txt` | 10,000 | 30,000 | Weighted undirected CSR graph | 1983583 | 1983583 | 1983583 | 2.582 ms | 3.550 ms | Yes | **PASSED** |
| MST (Kruskal & Prim) | `mst_50000.txt` | 50,000 | 150,000 | Weighted undirected CSR graph | 9935673 | 9935673 | 9935673 | 14.660 ms | 29.199 ms | Yes | **PASSED** |
| MST (Kruskal & Prim) | `mst_100000.txt` | 100,000 | 300,000 | Weighted undirected CSR graph | 19825567 | 19825567 | 19825567 | 26.379 ms | 53.635 ms | Yes | **PASSED** |

---

## System Specification
- **Processor:** Intel(R) Core(TM) i3-8130U CPU @ 2.20GHz (2.21 GHz)
- **RAM:** 4 GB
- **Storage:** 1 TB

---

## Complexity Analysis

### Kruskal's Algorithm
- **Time Complexity:** $O(E \log E)$ or $O(E \log V)$
  - Extracting $E$ edges from CSR takes $O(V + E)$.
  - Sorting edges takes $O(E \log E)$.
  - DSU union-find operations with path compression and rank take $O(E \cdot \alpha(V))$, making edge sorting the dominant factor.
- **Space Complexity:** $O(V + E)$ auxiliary space to store the extracted edge array along with DSU parent and rank tracking vectors of size $O(V)$.

### Prim's Algorithm
- **Time Complexity:** $O(E \log E)$ or $O(E \log V)$ using a binary min-heap (`std::priority_queue`). Each vertex is visited once, and each edge is pushed into the priority queue at most once.
- **Space Complexity:** $O(V + E)$ auxiliary space to maintain the priority queue storing frontier edges along with the $O(V)$ boolean `inMST` visited array.
