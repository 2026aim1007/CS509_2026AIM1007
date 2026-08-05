# CS509 Individual Assignments Repo

## Repository Overview
This repository contains the implementation of Assignment 1 for CS509 Lab Work, focusing on General Matrix Multiplication (GEMM) algorithms in C++.

## Student Details
* **Student Name:** Ishtveer Singh Billing
* **Entry Number:** 2026AIM1007
* **Assignment Type:** Single (Individual)

## Language and Environment
* **Programming Language:** C++
* **Compiler:** `g++` 
* **Timing Method:** `std::chrono::high_resolution_clock`

## Directory Structure
```text
CS509_<EntryNumber>/
|-- README.md
|-- common_wrapper/
|   `-- wrapper.cpp
|-- assignment_01/
|   |-- src/
|   |   |-- gemm_simple.h
|   |   |-- gemm_simple.cpp
|   |   |-- gemm_blocking.h
|   |   `-- gemm_blocking.cpp
|   |-- driver/
|   |   `-- driver.cpp
|   |-- tests/
|   |   |-- test_01.txt
|   |   `-- ...
|   `-- outputs/
|       |-- output_01.txt
|       |-- expected_01.txt
|       `-- ...
```

## Common Wrapper: Build and Usage
The root `wrapper.cpp` serves as the repo-level interface. It launches the dedicated driver for Assignment 1.


### Execution
```bash
./wrapper
```

---

## Assignment 01: General Matrix Multiplication (GEMM)

### Objective
Implement and compare standard nested-loop GEMM (`Simple`) with cache-friendly tiled/blocked GEMM (`Blocking`).

### Algorithm / Approach
1. **GEMM Simple:** Standard 3-nested-loop matrix multiplication computing $C[i][j] = \sum A[i][k] \times B[k][j]$.
2. **GEMM Blocking:** Tile-based matrix multiplication using a block size ($B = 64$) to optimize cache spatial and temporal locality.

### Input Format
The matrix text file specifies $M$, $K$, and $N$ followed by elements of Matrix $A$ ($M \times K$) and Matrix $B$ ($K \times N$):
```text
M K N
<Row 0 A of>
...
<Row A M-1 of>
<Row 0 B of>
...
<Row B K-1 of>
```

### File Structure
* `gemm_simple.h` / `gemm_blocking.cpp`: `simpleMM` and `blockingMM` implementations.
* `driver.cpp`: Reads input files, triggers timed algorithm executions, writes output files, and verifies actual output against expected output.

### Compilation
```bash
mingw32-make
.\gemm_driver.exe
```

### Execution
Run the driver directly or through the common wrapper:
```bash
./assignment_01/driver/driver
```

### Test Cases and Result Table

| Mode | Test File | Input Type | Input Size / Dimensions | Expected Output | Actual Output | Simple Time | Blocking Time | Block Size | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Single | `test_01.txt` | Matrix input | $4 \times 4$ and $4 \times 4$ | Result matrix | Result matrix | 0 ms | 0 ms | 64 | PASSED |
| Single | `test_02.txt` | Matrix input | $16 \times 16$ and $16 \times 16$ | Result matrix | Result matrix | 0 ms | 0 ms | 64 | PASSED |
| Single | `test_03.txt` | Matrix input | $64 \times 64$ and $64 \times 64$ | Result matrix | Result matrix | 20 ms | 23 ms | 64 | PASSED |
| Single | `test_04.txt` | Matrix input | $256 \times 256$ and $256 \times 256$ | Result matrix | Result matrix | 700 ms | 455 ms | 64 | PASSED |
| Single | `test_05.txt` | Matrix input | $1024 \times 1024$ and $1024 \times 1024$ | Result matrix | Result matrix | 47907 ms | 28832 ms | 64 | PASSED |

System : Intel Core i3@2.20GHz
         4 GB Ram
         Intel UHD Graphics 128 MB
         64-bit OS, x64-based processor.
### Complexity
* **GEMM Simple:** Time Complexity: $\mathcal{O}(M \cdot K \cdot N)$, Auxiliary Space: $\mathcal{O}(M \cdot N)$
* **GEMM Blocking:** Time Complexity: $\mathcal{O}(M \cdot K \cdot N)$, Auxiliary Space: $\mathcal{O}(M \cdot N)$