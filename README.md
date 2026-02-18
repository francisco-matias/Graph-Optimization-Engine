# Graph Optimization Engine

A performance-focused C implementation of shortest-path optimization over implicitly defined graphs, designed under strict time and memory constraints.

---

## Engineering Focus

This project demonstrates:

- Efficient modelling of large implicit graphs
- On-demand neighbor generation to reduce memory overhead
- Shortest-path optimization using priority-based exploration
- Non-linear edge cost modelling
- Careful dynamic memory management in C
- Scalable processing of multiple problem instances
- Robust file parsing and controlled program termination

---

## Algorithmic Design

Rather than materializing the full graph in memory, adjacency relationships are computed dynamically during exploration. This design choice reduces memory usage and improves scalability for large input spaces.

The optimization core relies on Dijkstra’s algorithm with a priority-based frontier expansion strategy, ensuring optimal path discovery while minimizing unnecessary exploration.

---

## Systems-Level Considerations

- Strict control of heap allocations
- Avoidance of memory leaks
- Efficient lookup structures
- Deterministic runtime behavior
- Makefile-based compilation with optimization flags

---

## Technologies

- C (C99)
- Graph Algorithms
- Shortest Path Optimization
- Systems Programming
