#include <iostream>
#include <deque>
#include <string>
#include <simpio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_FOOD = 20;

const char kEmptyTile = ' ';
const char kWallTile = '#';
const char kFoodTile = '$';
const char kSnakeTile = '*';

const kWaitTime = 0.1;

const string kClearCommand = "clear";

struct pointT {
  int row, col;
};

struct gameT {
  vector<string> world;
  int numRows, numCols;

  deque<pointT> snake;
  int dx, dy;

  int numEaten;
};

string GetLine() {
  string result;
  getline(cin, result);
  return result;
}

void
openUserFile(ifstream& input) {
  while (true) {
    cout << "Enter filename: ";
    string fileName = GetLine();

    input.open(fileName.c_str());

    if (input.is_open()) {
      return;
    }
    else {
      cout << "Sorry, I can't find the file " << filename << endl;
      input.clear();
    }
  }
}

void
makePoint(int row, int col) {
  pointT result;
  result.row = row;
  result.col = col;

  return result;
}

void
loadWorld(gameT& game, ifstream& input) {
  input >> game.numRows >> game.numCols;
  game.world.resize(game.numRows);

  input >> game.dx >> game.dy;

  string dummy;
  getline(input, dummy); // to consume the newline character from previous extraction operator ">>"


  for (int row = 0; row < game.numRows; ++row) {
    getline(input, game.world[row]);

    int col = game.world[row].find(kSnakeTile);

    if (col != string::npos) {
      game.snake.push_back(makePoint(row, col));
    }
  }
  game.numEaten = 0;
}

void
initializeGame(gameT& game) {
  ifstream input;
  openUserFile(input);
  loadWorld(game, input);
}

void
pause() {
  clock_t startTime = clock(); // clock_t is a type wcich holds clock ticks

  // just a busy wait
  while (static_cast<double>(clock() - startTime)/ CLOCKS_PER_SEC < kWaitTime) {
  }
}

void
printWorld(gameT& game) {
  system(kClearCommand.c_str());
  for (int row = 0; row < game.numRows; ++row) {
    cout << game.world[row] << endl;
  }
  cout << "Food eaten: " << game.numEaten << endl;
}

void
displayResult(gameT& game) {
  printWorld(game);

  if(game.numEaten == kMaxFood) {
    cout << "The snake ate enough food and wins!" << endl;
  }
  else {
    cout << "Oh no! The snake crashed!" << endl;
  }
}

void
runSimulation(gameT& game) {
  /* Keep looping until we have eaten MAX_FOOD # of foods*/

  while (game.numEaten < kMaxFood) {
    printWorld(game);
    performAi(game);

    if (!moveSnake(game)) { // move the snake and break if crushed
      break;
    }

    pause();    // pause so that we can see whats going on
  }
  displayResult(game);
}

int main() {
  gameT game;
  initializeGame(game);
  runSimulation(game);

  return 0;
}