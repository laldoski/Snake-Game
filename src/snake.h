#ifndef SNAKE_H
#define SNAKE_H
#include <iostream>
#include <vector>
#include "SDL.h"
using namespace std;

class Snake {
 public:
 enum class Direction { kUp, kDown, kLeft, kRight, kL, kD, kR, kU };
   //Snake(int grid_width, int grid_height): grid_width(grid_width), grid_height(grid_height), head_x(grid_width / 2), head_y(grid_height / 2) {}
  Snake(int grid_width, int grid_height, int snakePlayer) {
    grid_width = grid_width;
    grid_height = grid_height;
    if (snakePlayer == 1){
       head_x = (grid_width / 2);
       head_y = (grid_height / 2);
       
    }
    else if(snakePlayer == 2) {
       head_x2 = (grid_width / 3);
       head_y2 = (grid_height / 3);
       
    }
   }
 
  void Update(int snakePlayer);
  
  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x, head_y, head_x2, head_y2;
 
  
  std::vector<SDL_Point> body;
  std::vector<SDL_Point> body2; //snake2 vector body
 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell, int snakePlayer);

  bool growing{false};
  int grid_width;
  int grid_height;
  int snakePlayer;
};

#endif