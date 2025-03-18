# Project1: 8-puzzle
### Introduction
In this project we were prompted, given by Dr. Keogh, to solve an 8 puzzle, shown in **Figure 1**, using three different searches. The searches we needed to use was the Uniform Cost Search, A* with the Misplaced Tile heuristic, and A* with Manhattan Distance heuristic. For this project, I implemented my code in c++.

### Uniform Cost Search
The Uniform Cost Search is A* search algorithm where h(n) is hardcoded to equal zero. I implemented the Uniform Cost Search algorithm using the General search algorithm, **Figure 2**, that was provided in the project prompt.

I initialized the queue and used a while loop to check if the queue was not empty. If it was empty, the function terminated. I used a top() and pop(), which are predefined functions, to remove the front nodes. When the goal state is met, the results print and the code exits successfully. To expand the nodes I wrote a getNeighbors function to push valid nodes into the queue. For the queue I used a priority queue to order nodes based on cost, g(n), and heuristic, h(n).

### A* with the Misplaced Tile Heuristic
The A* with the Misplaced Tile heuristic evaluates the number of misplaced tiles, h(n). By evaluating the number of misplaced tiles in the puzzle we are able to estimate how far our current puzzle state is from the goal state. 

For my code, a counter was used to count the number of misplaced tiles and used for loops to iterate through rows and columns. If the tiles were not in the correct position, the counter would increment and it would return the total number of misplaced tiles.  


### A* with the Manhattan Distance Heuristic
The A* with the Manhattan Distance heuristic evaluates the number of spaces of the misplaced tiles, h(n). This allows us to know how far each tile is from its correct position by counting the number of moves (up, down, left, right) required to reach the goal state.

For my code, a variable, dist, was declared to store the Manhattan distance. For loops were used to iterate through the rows and columns and check if there were any misplaced tiles. If there were any misplaced tiles, the distance formula was used to add all the distances of the misplaced tiles and the sum of the misplaced distances would return.


### Algorithm Comparisons
We were provided with test cases by Dr. Keogh, from the project prompt. As shown in **Figure 3**, each test case had a different level of depth. The higher the depth gets, the more difficult the puzzle becomes.
/image

When running the code with each algorithm, there was no problem in the output for depths 0 to 4. The results came out pretty fast for all algorithms. However, for the Uniform Cost Search, starting from depth 8, the results started to get slower and longer than the other two algorithms.
The A* with the Misplaced Tile Heuristic and A* with the Manhattan Distance Heuristic had pretty much the same results for depth 8, but staring from depth 12, A* with the Misplaced Tile Heuristic started to get slower and longer. **Figure 4** shows the comparisons of the search algorithms for the total number of nodes expanded at each solution depth.
/image

Overall, A* Misplaced Tile and A* Manhattan Distance did not have much of a difference for the total number of nodded expanded. Starting from approximately depth 8, a difference can be seen among the two algorithms. But for Uniform Cost Search, a big difference in the number of nodes expanded can be seen from the start compared to the other two algorithms. A similar result can be seen in a different comparison in **Figure 5**, a comparison of the max queue size among the algorithms.
/image

The A* Misplaced Tile and A* Manhattan Distance did not have much of a difference for the max queue size, but from approximately depth 8, a difference can be seen among the two algorithms. For Uniform Cost Search, obvious differences for the max queue size can be seen starting from depth 2 compared to the other two algorithms.

### Conclusion
Based on the comparisons among the three algorithms, it can be concluded that the A* Manhattan Distance is best fit for solving the 8-puzzle. It has the smallest amount of nodes expanded, smallest amount of max queue size resulting in a fast output. On the other hand, the Uniform Cost Search comes last as it is the slowest because it expands all of its nodes causing a larger queue size and resulting in a slower output. It starts to get slow and at about depth 16 the program can crash because there are too many nodes, about 10,000 nodes. For the A* Misplaced Tiles, at about depth 20, the program tends to get slower as the node expands to about 2000, but it does not crash. Overall, the A* Manhattan Distance is best fit for solving the 8-puzzle as it is the fastest and there is no instance of the programming crashing when testing the puzzle with depth 24.
