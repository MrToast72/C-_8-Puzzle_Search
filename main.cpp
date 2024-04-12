#include "functions.h"

int main() {
  int input[9];
  int temp;
  int choice;
  int heuristic;

  // Greating and instructions
  cout << "\nWelcome to the 8-puzzle solver program! \n";
  cout << "To start, please take a look at what a completed 8-puzzle looks "
          "like: \n";
  cout << "---------\n| 1 2 3 |\n| 8 0 4 |\n| 7 6 5 |\n---------\n";
  cout << "To enter your own 8-puzzle, please enter the numbers from left to "
          "right,\ntop to bottom, with a space between each number. \n";
  cout << "For example, the 8-puzzle above would be entered as : 1 2 3 8 0 4 7 "
          "6 5 \nWith the 0 representing the empty space. \n";
  cout << "Please enter your 8-puzzle : ";

  // ... (Get starting state from user) ...
  for (int i = 0; i < 9; ++i) {
    cin >> temp;
    input[i] = temp;
  }

  // ... (Create starting state) ...
  State userState;
  userState = State(input);

  // Check if the input is solvable
  if (!isSolvable(userState)) {
    cout << "The input is not solvable. Please try again. \n";
    return 0;
  }

  // Display the starting state
  cout << "\nStarting state: \n";
  printState(userState);

  do {

    cout << "\nNow, Please choose from the options below: \n";
    cout << "1. Depth First Search \n";
    cout << "2. Breadth First Search \n";
    cout << "3. Best-First Search \n";
    cout << "4. End program \n";

    while (true) {
      cout << endl << "Enter your choice using a number: ";
      cin >> choice;

      if (cin.fail() || choice == 0 || choice > 4) {         // If the input is not a number
        cin.clear();            // Clear the input buffer
        cin.ignore(1000, '\n'); // Ignore the rest of the input
        cout << "\nInvalid input. Please try again.\n";
        continue;
      } else {
        cin.ignore(1000, '\n');
        break;
      }
    }

    if (choice == 1) { // Depth First Search

      cout << "Solving with Depth First Search... \n";
      vector<State> dFSPath = depthFirstSearch(userState);
      int dFSNodes = dFSPath.size();

      cout << "Depth First Search completed! \n";
      cout << "Number of Nodes: " << dFSNodes << endl;
      cout << "Path from the intial state to the goal: \n";
      for (int i = 0; i < dFSPath.size(); i += 10) {                  // Print the path in groups of 10
          vector<State> states;
          for (int j = i; j < i + 10 && j < dFSPath.size(); ++j) {
              states.push_back(dFSPath[j]);
          }
          printStates(states);
      }

    } else if (choice == 2) { // Breadth First Search

      cout << "Solving with Breadth First Search... \n";
      vector<State> bFSPath = breadthFirstSearch(userState);
      int bFSNodes = bFSPath.size();

      cout << "Breadth First Search completed! \n";
      cout << "Number of Nodes: " << bFSNodes << endl;
      cout << "Path from the intial state to the goal: \n";
      for (int i = 0; i < bFSPath.size(); i += 10) {                  // Print the path in groups of 10
          vector<State> states;
          for (int j = i; j < i + 10 && j < bFSPath.size(); ++j) {
              states.push_back(bFSPath[j]);
          }
          printStates(states);
      }

    } else if (choice == 3) { // Best-First Search

      do {

        cout << "Please select a heuristic: \n";
        cout << "1. Number of misplaced tiles \n";
        cout << "2. Manhattan distance \n";
        cout << "3. The Heuristic H (H = totdist + 3*seq) \n";
        cout << "4. Go back \n";

        while (true) {
          cout << endl << "Enter your choice using a number: ";
          cin >> heuristic;

          if (cin.fail() || heuristic == 0 || heuristic > 4) {         // If the input is not a number
            cin.clear();            // Clear the input buffer
            cin.ignore(1000, '\n'); // Ignore the rest of the input
            cout << "\nInvalid input. Please try again.\n";
            continue;
          } else {
            cin.ignore(1000, '\n');
            break;
          }
        }

        if (heuristic == 1) { // Number of misplaced tiles

          cout << "Solving with Best-First Search, Heuristic 1... \n";
          vector<State> bestFSPath = bestFirstSearch(userState, heuristic);
          int bestFSNodes = bestFSPath.size();

          cout << "Best-First Search completed! \n";
          cout << "Number of Nodes: " << bestFSNodes << endl;
          cout << "Path from the intial state to the goal: \n";
          for (int i = 0; i < bestFSPath.size(); i += 10) {                  // Print the path in groups of 10
              vector<State> states;
              for (int j = i; j < i + 10 && j < bestFSPath.size(); ++j) {
                  states.push_back(bestFSPath[j]);
              }
              printStates(states);
          }

        } else if (heuristic == 2) { // Manhattan distance

          cout << "Solving with Best-First Search, Heuristic 2... \n";
          vector<State> bestFSPath = bestFirstSearch(userState, heuristic);
          int bestFSNodes = bestFSPath.size();

          cout << "Best-First Search completed! \n";
          cout << "Number of Nodes: " << bestFSNodes << endl;
          cout << "Path from the intial state to the goal: \n";
          for (int i = 0; i < bestFSPath.size(); i += 10) {                  // Print the path in groups of 10
              vector<State> states;
              for (int j = i; j < i + 10 && j < bestFSPath.size(); ++j) {
                  states.push_back(bestFSPath[j]);
              }
              printStates(states);
          }

        } else if (heuristic == 3) { // The Heuristic H (H = totdist + 3*seq

          cout << "Solving with Best-First Search, Heuristic 3... \n";
          vector<State> bestFSPath = bestFirstSearch(userState, heuristic); 
          int bestFSNodes = bestFSPath.size();

          cout << "Best-First Search completed! \n";
          cout << "Number of Nodes: " << bestFSNodes << endl;
          cout << "Path from the intial state to the goal: \n";
          for (int i = 0; i < bestFSPath.size(); i += 10) {                  // Print the path in groups of 10
              vector<State> states;
              for (int j = i; j < i + 10 && j < bestFSPath.size(); ++j) {
                  states.push_back(bestFSPath[j]);
              }
              printStates(states);
          }

        } else if (heuristic == 4) { // Go back
          break;
        } else {
          cout << "Invalid input. Please try again. \n";
        }

      } while (heuristic != 4);

    } else if (choice == 4) { // End program
      cout << "Goodbye! \n";
      return 0;
    } else {
      cout << "Invalid input. Please try again. \n";
    }

  } while (choice != 4);
}
