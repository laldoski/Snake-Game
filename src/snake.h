#ifndef SNAKE_H
#define SNAKE_H
#include <iostream>
#include <vector>
#include "SDL.h"
using namespace std;

class Snake
{
public:
  enum class Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight
  };

  Snake(int grid_width, int grid_height, int snakePlayer);

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};

  bool alive{true};
  float head_x, head_y;

  std::vector<SDL_Point> body;

private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  int snakePlayer;
};

#endif