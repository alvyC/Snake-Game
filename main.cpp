#include <iostream>
#include <deque>
#include <string>
#include <simpio.h>

using namespace std;

const int MAX_FOOD = 20;

const char kEmptyTile = ' ';
const char kWallTile = '#';
const char kFoodTile = '$';
const char kSnakeTile = '*';

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

void
openUserFile(ifstream& input) {
  while (true) {
    cout << "Enter filename: ";
    string fileName = GetLine();

    input.open(fileName.c_str());

  }
}

void
makePpint(int row, int col) {
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
      game.snake.push_back(MakePoint(row, col));
    }
  }
}

void
initializeGame(gameT& game) {
  ifstream input;
  openUserFile(input);
  loadWorld(game, input);
}

int main() {
  gameT game;
  initializeGame(game);
  runSimulation(game);

  return 0;
}

/*
  string GetLine() {
    string result;
    getline(cin, result);
    return result;
  }
*/