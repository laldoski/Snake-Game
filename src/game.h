#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <mutex>
#include <future>
#include <fstream>

class Game {
 public:
 
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore1() const;
  int GetScore2() const;
  //vector<int> GetScore2()const;
  int GetSize1() const;
  int GetSize2 () const;
  Snake snake;
  Snake snake2;

  std::ofstream filestream;
  
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score1 = 0;
  int score2 = 0;
  std::mutex  mtx;
  void UpdateSnake(std::promise <bool> &snakePromise, Snake &snake);
  void PlaceFood();
  void Update();
};

#endif