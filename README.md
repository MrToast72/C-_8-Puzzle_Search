# 8-Puzzle Solver

## Project Description

This project implements a solver for the classic 8-puzzle game. The program takes an initial configuration and a search strategy as input and aims to find a path from the initial state to the goal state.

### User Input :
Initial configuration: A 3x3 representation of the starting state of the 8-puzzle (using 0 to represent the blank tile), as a string of numbers seperated by a space.

### Search strategy: Choose from the following :
Depth-first search (DFS)
Breadth-first search (BFS)
Best-first search (with three different heuristic options)

### Output :
Series of states (path): The sequence of board configurations from the initial state to the goal state.
Number of generated nodes (states): The total number of board states explored during the search.

### Search Strategies :
Depth-first search (DFS): Explores the search tree in a depth-wise manner.
Breadth-first search (BFS): Explores the search tree in a level-by-level manner.
Best-first search: Prioritizes exploration based on a heuristic evaluation. The following heuristics are implemented:
Heuristic 1: Depth in the search space + Number of tiles out of place.
Heuristic 2: Depth in the search space + Minimum number of moves to reach the goal state (often calculated using Manhattan distance).
Heuristic 3: Depth in the search space + H, where H is a custom heuristic defined below.

### Custom Heuristic (H)
H combines two measures:
totdist: The total Manhattan distance of tiles from their goal positions. Manhattan distance is the sum of horizontal and vertical distances between two positions.
seq: The sequence score, which measures how well tiles are ordered. Rules for calculation are provided in the detailed description.


## Example output :
```txt
Welcome to the 8-puzzle solver program! 
To start, please take a look at what a completed 8-puzzle looks like: 
---------
| 1 2 3 |
| 8 0 4 |
| 7 6 5 |
---------
To enter your own 8-puzzle, please enter the numbers from left to right,
top to bottom, with a space between each number. 
For example, the 8-puzzle above would be entered as : 1 2 3 8 0 4 7 6 5 
With the 0 representing the empty space. 
Please enter your 8-puzzle : 1 3 4 8 0 2 7 6 5

Starting state: 
---------
| 1 3 4 |
| 8 0 2 |
| 7 6 5 |
---------

Now, Please choose from the options below: 
1. Depth First Search 
2. Breadth First Search 
3. Best-First Search 
4. End program 

Enter your choice using a number: 2
Solving with Breadth First Search... 
--- Starting Breadth First Search--- 
Breadth First Search completed! 
Number of Nodes: 5
Path from the intial state to the goal: 
---------  ---------  ---------  ---------  ---------  
| 1 3 4 |  | 1 3 4 |  | 1 3 0 |  | 1 0 3 |  | 1 2 3 |  
| 8 0 2 |  | 8 2 0 |  | 8 2 4 |  | 8 2 4 |  | 8 0 4 |  
| 7 6 5 |  | 7 6 5 |  | 7 6 5 |  | 7 6 5 |  | 7 6 5 |  
---------  ---------  ---------  ---------  ---------  

Now, Please choose from the options below: 
1. Depth First Search 
2. Breadth First Search 
3. Best-First Search 
4. End program 

Enter your choice using a number: 3
Please select a heuristic: 
1. Number of misplaced tiles 
2. Manhattan distance 
3. The Heuristic H (H = totdist + 3*seq) 
4. Go back 

Enter your choice using a number: 1
Solving with Best-First Search, Heuristic 1... 
--- Starting Best First Search--- 
Best-First Search completed! 
Number of Nodes: 5
Path from the intial state to the goal: 
---------  ---------  ---------  ---------  ---------  
| 1 3 4 |  | 1 3 0 |  | 1 0 3 |  | 1 2 3 |  | 1 2 3 |  
| 8 2 0 |  | 8 2 4 |  | 8 2 4 |  | 8 0 4 |  | 8 0 4 |  
| 7 6 5 |  | 7 6 5 |  | 7 6 5 |  | 7 6 5 |  | 7 6 5 |  
---------  ---------  ---------  ---------  ---------  
Please select a heuristic: 
1. Number of misplaced tiles 
2. Manhattan distance 
3. The Heuristic H (H = totdist + 3*seq) 
4. Go back 

Enter your choice using a number: 4

Now, Please choose from the options below: 
1. Depth First Search 
2. Breadth First Search 
3. Best-First Search 
4. End program 

Enter your choice using a number: 4
Goodbye!
```
