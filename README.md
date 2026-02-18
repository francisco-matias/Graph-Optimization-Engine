# Word-Mutations-Graph-Solver
Efficient C implementation of a graph-based word mutation solver using shortest-path algorithms and adjacency lists.

# Features
- Graph-based modelling of word mutation problems
- Efficient dictionary handling with binary search over sorted word lists
- Dynamic adjacency list construction
- Full implementation of Dijkstra’s shortest path algorithm (priority-based exploration)
- Optimized build with `-O3` and strict warnings (`-Wall -std=c99`)
- Careful memory management and robustness for large inputs

# Algorithm & Implementation Notes
- The dictionary is loaded, sorted, and queried using binary search for fast lookups.
- Neighbor words are generated on demand by testing single-letter mutations instead of precomputing all edges, reducing memory usage.
- Each word is treated as a node, and valid single-letter mutations define the graph connections.
- The shortest transformation path is computed using Edsger W. Dijkstra’s algorithm, ensuring optimal paths while exploring only the necessary parts of the graph.
- The implementation focuses on performance, low memory overhead, and scalability for large dictionaries and multiple problem instances.
