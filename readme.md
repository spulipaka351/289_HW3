# 🗺️ TSP 2-Opt Local Search Solver

This project implements the **2-Opt local search algorithm** to find near-optimal solutions for the Traveling Salesperson Problem (TSP). The current configuration is suitable for running tests on graphs up to **1000 nodes**.

---

## 🛠️ Compilation

To compile the C++ source files and create the executable, open your terminal or command prompt in the project directory and run the following command:

```bash
g++ .\main.cpp .\helper.cpp .\tsp.cpp .\2-opt.cpp -o main
```
## Run the code
### for windows

If you are running the executable on Windows, ensure that your input graph data file (e.g., rand.txt) and the compiled main.exe are located in the same folder.

Command Execution

```bash
./main.exe <filename>
```
note: ignore ./ .\ in filename

### Example 
```bash
./main.exe rand.txt
```
