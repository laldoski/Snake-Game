#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update(int player) {
  if (player == 1){
  SDL_Point prev_cell{static_cast<int>(head_x),static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  
  UpdateHead();
  // Capture the head's cell after updating.
  SDL_Point current_cell{static_cast<int>(head_x),static_cast<int>(head_y)};  
  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell, player);}
  }
 else if (player == 2)
{
  //SDL_Point prev_cell{static_cast<int>(head_x),static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  SDL_Point prev_cell2{static_cast<int>(head_x2),static_cast<int>(head_y2)};
  UpdateHead();
  // Capture the head's cell after updating. 
 SDL_Point current_cell2 {static_cast<int>(head_x2),static_cast<int>(head_y2)};
  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell2.x != prev_cell2.x || current_cell2.y != prev_cell2.y){
    UpdateBody(current_cell2,prev_cell2, player);}
  }

}


  
  

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
     
      head_y -= speed;
       break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;

    case Direction::kU:
      head_y2 -= speed;
      break;

    case Direction::kD:
      head_y2 += speed;
      break;

    case Direction::kL:
      head_x2 -= speed;
      
      break;

    case Direction::kR:
      head_x2 += speed;
      break;


  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_x2 = fmod(head_x2 + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
  head_y2 = fmod(head_y2 + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell, int player) {
  // Add previous head location to vector
  if (player == 1)
  {
    body.push_back(prev_head_cell);

    if (!growing)
    {
      // Remove the tail from the vector.
      body.erase(body.begin());
    }
    else
    {
      growing = false;
      size1++;
    }
    // Check if the snake has died.
    for (auto const &item : body)
    {
      if (current_head_cell.x == item.x && current_head_cell.y == item.y)
      {
        alive = false;
      }
    }
  }

  else if (player == 2)
  {
    body2.push_back(prev_head_cell);

    if (!growing)
    {
      // Remove the tail from the vector.
      body2.erase(body2.begin());
    }
    else
    {
      growing = false;
      size2++;
    }
    // Check if the snake has died.
    for (auto const &item : body2)
    {
      if (current_head_cell.x == item.x && current_head_cell.y == item.y)
      {
        alive = false;
      }
    }
  }
}

void Snake::GrowBody() { growing = true; }
void Snake::GrowBody2() { growing2 = true; }
// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y) || x == static_cast<int>(head_x2) && y == static_cast<int>(head_y2)) {
    return true;
  }
  
  for (auto const &item : body) {
    if (x == item.x && y == item.y) 
      return true;
  }
 
  for (auto const &item : body2) {
    if (x == item.x && y == item.y) 
      return true;
    
  }
  return false;
}