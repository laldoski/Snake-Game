#include "game.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <thread>
#include <future>
#include <vector>
#include <thread>
#include <mutex>
#include "SDL.h"
using namespace std;
//starting up the game space
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake1(grid_width, grid_height, 1), snake2(grid_width, grid_height, 2),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1))
{

  PlaceFood();
}
//start running the main game loop of controller input, update, render
void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.

    controller.HandleInput(running, snake1, snake2);
    Update();
    renderer.Render(snake1, snake2, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(WriteScore1, WriteScore2, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}
// random placement of the food
void Game::PlaceFood()
{
  int x, y, a,b;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake1.SnakeCell(x, y) || !snake2.SnakeCell(x, y))
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update()
{
  if ((!snake1.alive) || (!snake2.alive))
    return;
  std::promise<bool> snake1Promise;
  std::future<bool> snake1Future = snake1Promise.get_future();

  std::thread snake1Thread(&Game::UpdateSnake, this, std::ref(snake1Promise), std::ref(snake1));

  std::promise<bool> snake2Promise;
  std::future<bool> snake2Future = snake2Promise.get_future();

  std::thread snake2Thread(&Game::UpdateSnake, this, std::ref(snake2Promise), std::ref(snake2));

  if (snake1Future.get() == true)
    WriteScore1++;

  if (snake2Future.get() == true)
    WriteScore2++;

  std::ofstream filestream;
  filestream.open( fileDirectory, std::ofstream ::out | std::ofstream ::trunc);
  filestream << "first " << WriteScore1;
  filestream << std::endl;
  filestream << "second " << WriteScore2;
  snake1Thread.join();
  snake2Thread.join();
  filestream.close();
}
//for each thread update the snake 
void Game::UpdateSnake(std::promise<bool> &snakePromise, Snake &snake)
{
  snake.Update();
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  
  std::scoped_lock snakeMtx(mtx);
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y )
  {
    snakePromise.set_value(true);
    snake.GrowBody();
    snake.speed += 0.02;
    PlaceFood();
  }
  else
    snakePromise.set_value(false);
};
// read the score1 from file 
int Game::GetScore1() const
{
  string line;
  string scoreString;
  string ReadPlayer;
  int ReadScore1 = 0;
  string PlayerNum = "first";
  std::ifstream filestream(fileDirectory);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> ReadPlayer >> scoreString;

      if (ReadPlayer.compare(PlayerNum) == 0)
      {
        ReadScore1 = stoi(scoreString);
        return ReadScore1;
      }
    }
  }
}

int Game::GetScore2() const
{
  string line;
  string scoreString;
  string ReadPlayer;
  string PlayerNum = "second";
  int ReadScore2 = 0;
  std::ifstream filestream(fileDirectory);
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> ReadPlayer >> scoreString;

      if (ReadPlayer.compare(PlayerNum) == 0)
      {
        ReadScore2 = stoi(scoreString);
        return ReadScore2;
      }
    }
  }
}

int Game::GetSize1() const { return snake1.size; }
int Game::GetSize2() const { return snake2.size; }
