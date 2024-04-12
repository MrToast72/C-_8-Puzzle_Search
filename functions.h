// All functions needed for my 8-puzzle solver program are defined in this file.

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>

using namespace std;

// -------------- Global Variables --------------
const int goal[9] = {1, 2, 3, 8, 0, 4, 7, 6, 5};                          // Goal state of the 8-puzzle, 0 is the empty tile

// ------------- Function declarations -------------
struct State;
int findBlankIndex(const State& state);                                   // Helper function to find the index of the blank tile
int cHeuristicH(const State &state);                                      // Heuristic function H
int cManDist(const State &currentState);                                  // Manhattan Distance Calculator
int cTilesOutOfPlace(const State &currentState);                          // Number of tiles out of place
bool isSolvable(const State &state);                                      // Solvability Checker
int cSeqScore(const State &currentState);                                 // Sequence Score Calculator
vector<State> getPossibleMoves(const State &state);                       // Possible Moves Generator
vector<State> depthFirstSearch(const State &initialState);                // Depth-First Search Algorithm
vector<State> breadthFirstSearch(const State &initialState);              // Breadth-First Search Algorithm
vector<State> bestFirstSearch(const State &initialState);                 // Best-First Search Algorithm
void printState(const State &state);


struct State {                                                            // State representation of the 8-puzzle
  int board[9];                                                           // 1D array with 9 elements
  int blankX, blankY; 
  int g, h, f;                                                            // g: (depth) cost from start, h: heuristic estimate, f: g + h

  
  State(int tiles[9]) {                                                   // Constructor to initialize the state with a given board configuration
    for (int i = 0; i < 9; ++i) {
        board[i] = tiles[i];
    }
  }

  
  State() : blankX(0), blankY(0) {                                        // Default constructor
    for (int i = 0; i < 9; ++i) {
        board[i] = 0;
    }
  }

  
  void calculateHeuristic(int heuristicType) {                            // Function to calculate the heuristic value based on the heuristic type
    switch (heuristicType) {
      case 1:                                                             // number of tiles out of place
        h = cTilesOutOfPlace(*this);
        break;
      case 2:                                                             // minimum number of moves to reach the goal state
        h = cManDist(*this);
        break;
      case 3:                                                             // the heuristic H
        h = cHeuristicH(*this);
        break;
    }
    f = g + h;
  }

  bool operator<(const State &other) const {                              // Less than operator
    for (int i = 0; i < 9; ++i) {                                         // Compare each element of the board
      if (board[i] != other.board[i]) {                                   // If the elements do not match
        return board[i] < other.board[i];                                 // Compare the elements
      }
    }
    return false;
  }

  bool operator==(const State &other) const {
    for (int i = 0; i < 9; ++i) {                                         // Compare each element of the board
      if (board[i] != other.board[i]) {                                   // If any element does not match
        return false;                                                     // The states are not equal
      }
    }
    return true;                                                          // All elements match
  }

  bool operator!=(const State &other) const {                             // Inequality operator
    return !(*this == other);
  }
};

// Helper function to find the index of the blank tile
int findBlankIndex(const State& state) {
    for (int i = 0; i < 9; i++) {
        if (state.board[i] == 0) {
            return i; 
        }
    }
    return -1;                                                            // Error handling if blank not found
  } 

// Function to calculate heuristic H based off of H = totdist + 3*seq
int cHeuristicH(const State &state) { return cManDist(state) + 3 * cSeqScore(state); }

// Function to determine if a state is the goal state
bool isGoalState(const State &state) {
  for (int i = 0; i < 9; ++i) {
    if (state.board[i] != goal[i]) {
      return false;
    }
  }
  return true;
}

/**
* @title Manhattan Distance Calculator
* @brief This function calculates the total Manhattan distance from the
* current state to the goal state. The Manhattan distance is the sum of the
* absolute differences of the horizontal and vertical distances.
*
* @param currentState The current state of the 8-puzzle game.
* @return The total Manhattan distance.
*/
int cManDist(const State &currentState) {
  int totalDistance = 0;                                                  // Initialize the total Manhattan distance
  unordered_map<int, int> goalPositions;                                  // Mapping from tile values to their goal positions in the 1D array
  for (int i = 0; i < 9; i++) {
    int tile = goal[i];
    if (tile != 0)
      goalPositions[tile] = i;
  }

  for (int i = 0; i < 9; i++) {                                           // Iterate over the current state
    int tile = currentState.board[i];                                     // Get the tile value
    if (tile != 0) {                                                      // Ignore the blank tile 
      int goalIndex = goalPositions[tile];                                // Get the goal position of the tile
      int goalRow = goalIndex / 3;                                        // Calculate the row of the goal position
      int goalCol = goalIndex % 3;                                        // Calculate the column of the goal position
      int currentRow = i / 3;                                             // Calculate the row of the current position
      int currentCol = i % 3;                                             // Calculate the column of the current position

      int distance = abs(currentRow - goalRow) + abs(currentCol - goalCol); // Calculate the Manhattan distance
      totalDistance += distance;                                          // Add the distance to the total
    }
  }

  return totalDistance;                                                   // Return the total Manhattan distance
}

/**
 * @title Number of Tiles Out of Place
 * @brief This function calculates the number of tiles that are out of place
 * in the current state compared to the goal state. It counts the number of
 * tiles that are not in their correct position.
 *
 * @param currentState The current state of the 8-puzzle game.
 * @return The number of tiles out of place.
 */
int cTilesOutOfPlace(const State &currentState) {
  int count = 0;
  for (int i = 0; i < 9; ++i) {
    if (currentState.board[i] != goal[i] && currentState.board[i] != 0) {
      ++count;
    }
  }
  return count;
}

/**
 * @title Solvability Checker
 * @brief This function checks if a given state of the 8-puzzle game is
 * solvable. It calculates the number of inversions in the state and returns
 * true if the number is even, false otherwise.
 *
 * @param state The state of the 8-puzzle game to check.
 * @return true if the state is solvable, false otherwise.
 */
bool isSolvable(const State &state) {
  int inversions = 0;
  for (int i = 0; i < 9; ++i) {                                           // Iterate over the tiles
    for (int j = i + 1; j < 9; ++j) {                                     // Iterate over the tiles after the current tile
      int pos_i = find(goal, goal + 9, state.board[i]) - goal;            // Find the position of the current tile in the goal state
      int pos_j = find(goal, goal + 9, state.board[j]) - goal;            // Find the position of the next tile in the goal state
      if (state.board[i] != 0 && state.board[j] != 0 && pos_i > pos_j) {  // Check if the current tile is after the next tile in the goal state
        ++inversions;
      }
    }
  }
  return inversions % 2 == 0;                                             // Return true if the number of inversions is even
}

/**
 * @title Sequence Score Calculator
 * @brief This function calculates the sequence score of the current state,
 * which is the degree to which the tiles are already ordered. The sequence
 * score is calculated based on the position of the blank tile and the order
 * of the other tiles.
 *
 * @param currentState The current state of the 8-puzzle game.
 * @return The sequence score.
 */
int cSeqScore(const State &currentState) {
  int score = 0;
  const int centerIndex = 4;                                              // Index of the center tile

  if (currentState.board[centerIndex] != 0)                               // Check if the center tile is not the blank tile
    score += 1;

  int clockwiseOrder[] = {0, 1, 2, 5, 8, 7, 6, 3};                        // Clockwise indices
  for (int i = 0; i < 8; i++) {                                           // Start at index 0 to include center
    int tile = currentState.board[clockwiseOrder[i]];
    if (tile == 0) continue;                                              // Skip the blank tile

    int goalSuccessor = (tile == 8) ? 1 : tile + 1;                       // Get the goal successor of the tile
    int clockwiseNeighborIndex = (i + 1) % 8;                             // Wrap around for the next tile
    int clockwiseNeighbor = currentState.board[clockwiseOrder[clockwiseNeighborIndex]]; // Get the clockwise neighbor
    if (clockwiseNeighbor != goalSuccessor) {                             // Check if the neighbor is not the goal successor
      score += 2;                                                         // Increment the score if the neighbor is not the goal successor
    } 
  }
  return score;
}

/**
 * @title Possible Moves Generator
 * @brief This function generates the possible moves (children) from a given
 * state of the 8-puzzle game. It finds the blank tile and swaps it with its
 * neighboring tiles to generate new states.
 *
 * @param state The current state of the 8-puzzle game.
 * @param children A vector to store the possible states.
 * @param visited A set to keep track of visited states.
 * @return A vector of possible states.
 */
vector<State> getPossibleMoves(const State &state) {
  int blankIndex = findBlankIndex(state);                                 // Find the index of the blank tile (0)

  vector<int> moves = {-3, 3, -1, 1};                                     // Up, Down, Left, Right
  vector<State> possibleMoves;                                            // Vector to store the possible moves

  for (int move : moves) {                                                // Iterate over the moves
    int newIndex = blankIndex + move;                                     // Calculate the new index

    if (newIndex >= 0 && newIndex < 9) {                                  // Check if within bounds
      if ((move == -1 && blankIndex % 3 == 0) || (move == 1 && blankIndex % 3 == 2)) // Check if move is left or right, and if so, ensure it doesn't wrap around
        continue;

      State newState = state;                                             // Create a new state
      swap(newState.board[newIndex], newState.board[blankIndex]);         // Swap directly

      possibleMoves.push_back(newState);                                  // Add the new state to the possible moves
    }
  }

  return possibleMoves;                                                   // Return the possible moves
}

/**
 * @title Depth-First Search Algorithm
 * @brief This function performs a depth-first search from the initial state
 * to the goal state of the 8-puzzle game. It uses a stack to keep track of
 * the frontier and a set to keep track of visited states.
 *
 * @param initialState The initial state of the 8-puzzle game.
 * @return A pair consisting of the path from the initial state to the goal
 * state and the number of nodes expanded.
 */
vector<State> depthFirstSearch(const State &initialState) {
  stack<State> frontier;                                                  // Stack to keep track of the frontier
  set<State> visited;                                                     // Set to keep track of visited states
  map<State, State> cameFrom;                                             // Map to store the parent state
  State currentState;                                                     // Current state

  frontier.push(initialState);                                            // Add the initial state to the frontier

  while (!frontier.empty()) {
    currentState = frontier.top();                                        // Get the current state from the frontier
    frontier.pop();                                                       // Pop the current state from the frontier

    if (isGoalState(currentState)) {                                      // Check if the current state is the goal state
      vector<State> path;
      for (State state = currentState; state != initialState; state = cameFrom[state]) {
        path.push_back(state);                                            // Add the state to the path
      }
      path.push_back(initialState);                                       // Add the initial state
      reverse(path.begin(), path.end());                                  // reverse the path to start from the initial state
      return path;                                                        // Goal found!
    }

    if (visited.find(currentState) == visited.end()) {
      visited.insert(currentState);                                       // Mark the state as visited

      vector<State> children = getPossibleMoves(currentState);

      for (auto child : children) {
        if (visited.find(child) == visited.end()) {                       // Check if the child is not visited
          frontier.push(child);                                           // Add the child to the frontier
          cameFrom[child] = currentState;                                 // Record the parent state
        }
      }
    }
  }

  return vector<State>();                                                 // No solution found
}

/**
 * @title Breadth-First Search Algorithm
 * @brief This function performs a breadth-first search from the initial state
 * to the goal state of the 8-puzzle game. It uses a queue to keep track of
 * the frontier and a set to keep track of visited states.
 *
 * @param initialState The initial state of the 8-puzzle game.
 * @return A pair consisting of the path from the initial state to the goal
 * state and the number of nodes expanded.
 */
vector<State> breadthFirstSearch(const State &initialState) {
  queue<State> frontier;                                                  // Queue to keep track of the frontier
  set<State> visited;                                                     // Set to keep track of visited states
  map<State, State> cameFrom;                                             // Map to store the parent state
  State currentState;                                                     // Current state

  frontier.push(initialState);                                            // Add the initial state to the frontier

  while (!frontier.empty()) {
    currentState = frontier.front();                                      // Get the current state from the frontier
    frontier.pop();                                                       // Remove the current state from the frontier

    if (isGoalState(currentState)) {
      vector<State> path;
      for (State state = currentState; state != initialState; state = cameFrom[state]) {
        path.push_back(state);                                            // Add the state to the path
      }
      path.push_back(initialState);                                       // Add the initial state
      reverse(path.begin(), path.end());                                  // reverse the path to start from the initial state
      return path;                                                        // Goal found!
    }

    if (visited.find(currentState) == visited.end()) {
      visited.insert(currentState);                                       // Mark the state as visited

      vector<State> children = getPossibleMoves(currentState);

      for (auto child : children) {
        if (visited.find(child) == visited.end()) {                       // Check if the child is not visited
          frontier.push(child);                                           // Add the child to the frontier
          cameFrom[child] = currentState;                                 // Record the parent state
        }
      }
    }
  }

  return vector<State>();                                                 // No solution found
}

/**
 * @title Best-First Search Algorithm
 * @brief This function performs a best-first search from the initial state to
 * the goal state of the 8-puzzle game. It uses a priority queue to keep track
 * of the frontier, with states ordered by their heuristic value, and a set to
 * keep track of visited states.
 *
 * @details Function uses cManDist, cSeqScore, and cHeuristicH functions to
 * calculate the heuristic values.
 * @see cManDist, cSeqScore, cHeuristicH
 * @param initialState The initial state of the 8-puzzle game.
 * @return A pair consisting of the path from the initial state to the goal
 * state and the number of nodes expanded.
 */
vector<State> bestFirstSearch(const State &initialState, int heuristicType) {
  auto compare = [heuristicType](pair<State, vector<State>> a, pair<State, vector<State>> b) {  // Lambda function to compare states based on heuristic value
    switch (heuristicType) {                                                                    // Switch statement to determine the heuristic type
      case 1:                                                                                   // depth in the search space + number of tiles out of place
        return a.first.g + cTilesOutOfPlace(a.first) > b.first.g + cTilesOutOfPlace(b.first);   // Compare the heuristic values
      case 2:                                                                                   // depth in the search space + minimum number of moves to reach the goal state
        return a.first.g + cManDist(a.first) > b.first.g + cManDist(b.first);                   // Compare the heuristic values
      case 3:                                                                                   // depth in the search space + the heuristic H
        return a.first.g + cHeuristicH(a.first) > b.first.g + cHeuristicH(b.first);             // Compare the heuristic values
    }
    return false;                                                                               // Default return value to avoid compiler warning
  };
  priority_queue<pair<State, vector<State>>, vector<pair<State, vector<State>>>, decltype(compare)> frontier(compare);

  set<State> visited; 
  vector<State> path; 
  State currentState;

  frontier.push({initialState, {}});

  while (!frontier.empty()) {                                             // While the frontier is not empty
    tie(currentState, path) = frontier.top();                             // Get the current state and path from the frontier
    frontier.pop();                                                       // Remove the current state from the frontier

    if (isGoalState(currentState)) {
      path.push_back(currentState);                                       // Add the current state to the path
      return path;                                                        // Goal found! Return the path
    }

    if (visited.find(currentState) == visited.end()) {                    // Check if the state is not visited
      visited.insert(currentState);                                       // Mark the state as visited

      vector<State> children = getPossibleMoves(currentState);            // Get the possible moves from the current state

      for (auto child : children) {                                       // Iterate over the children
        if (visited.find(child) == visited.end()) {                       // Check if the child is not visited
          vector<State> newPath = path;                                   // Create a new path
          newPath.push_back(child);                                       // Add the child to the path
          frontier.push({child, newPath});                                // Add the child and path to the frontier
        }
      }
    }
  }

  return vector<State>();                                                 // No solution found  
}

// Function to print the state in human readable format, encasing the board in a
// box
void printState(const State &state) {
  cout << "---------\n";                                                  // Print the top border
  for (int i = 0; i < 9; i += 3) {                                        // Iterate over the rows
    cout << "| ";                                                         // Print the left border
    for (int j = i; j < i + 3; j++) {                                     // Iterate over the columns
      cout << state.board[j] << " ";                                      // Print the value of the tile
    }
    cout << "|\n";                                                        // Print the right border
  }
  cout << "---------\n";                                                  // Print the bottom border
}

// Function to print rows of states in human readable format
void printStates(const vector<State> &states) {
  vector<string> buffers(5, "");                                          // 5 lines for each board

  for (const auto &state : states) {
    buffers[0] += "---------  ";                                          // Top border
    for (int i = 0; i < 9; i += 3) {                                      // Iterate over the rows
      buffers[i / 3 + 1] += "| ";                                         // Left border
      for (int j = i; j < i + 3; j++) {                                   // Iterate over the columns
        buffers[i / 3 + 1] += to_string(state.board[j]) + " ";            // Print the value of the tile
      }
      buffers[i / 3 + 1] += "|  ";                                        // Right border
    }
    buffers[4] += "---------  ";                                          // Bottom border
  }

  // Print all lines
  for (const auto &line : buffers) {
    cout << line << '\n';
  }
}
