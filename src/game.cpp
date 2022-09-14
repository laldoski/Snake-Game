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

Game::Game(std::size_t grid_width, std::size_t grid_height)
      : snake(grid_width,grid_height,1), snake2 (grid_width, grid_height, 2),
     engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)){
  filestream.open("score.txt", std::ofstream ::out | std::ofstream ::trunc);  
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
  

   controller.HandleInput1(running,snake, snake2);
  
    Update();
   renderer.Render(snake, snake2, food);
   
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score1,score2, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
 //  player1.join();
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) || !snake2.SnakeCell(x, y)){
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if ((!snake.alive) || (!snake2.alive)) 
return;
  std::promise<bool> snake1Promise;
  std::future<bool> snake1Future = snake1Promise.get_future();
  
  std::thread snake1Thread(&Game::UpdateSnake, this, std::ref(snake1Promise), std::ref(snake));
  
  std::promise<bool> snake2Promise;
  std::future<bool> snake2Future = snake2Promise.get_future();
  
  std::thread snake2Thread(&Game::UpdateSnake, this, std::ref(snake2Promise), std::ref(snake2));

 if (snake1Future.get() == true)
 score1++;
if (snake2Future.get() == true)
 score2++;


    filestream << "first " <<  score1;     
    filestream << std::endl;
    filestream << "second " << score2;
  snake1Thread.join();
  snake2Thread.join();
}

void Game::UpdateSnake(std::promise <bool> &snakePromise, Snake &snake){
  snake.Update();
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  std::scoped_lock snakeMtx(mtx);
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
   snakePromise.set_value(true);
   // score1++;
    // Grow snake and increase speed.
    
    snake.GrowBody();
    snake.speed += 0.02;
    PlaceFood();
  }
  else snakePromise.set_value(false);

};

 int Game::GetScore1() const { 
  string line;
   string scoreString;
   string playerNum;
   int Score1=0;
   string player= "first";
   std::ifstream filestream("/home/workspace/CppND-Capstone-Snake-Game/score.txt"); 
  if (filestream.is_open())
   {
     while (std::getline(filestream, line))
     {
       std::istringstream linestream(line);
       linestream >> playerNum >> scoreString;
       if (playerNum.compare(player) == 0)
       { 
         Score1 = stoi(scoreString);
         return Score1;
       }
     }
 } 
 }

 int Game::GetScore2() const
 {
   string line;
   string scoreString;
   string playerNum;
   string player = "second";
   int Score2 = 0;
   std::ifstream filestream("/home/workspace/CppND-Capstone-Snake-Game/score.txt");
   if (filestream.is_open())
   {
     while (std::getline(filestream, line))
     {
       std::istringstream linestream(line);
       linestream >> playerNum >> scoreString;

       if (playerNum.compare(player) == 0)
       {
         Score2 = stoi(scoreString);
         return Score2;
       }
     }
   }
 }

int Game::GetSize1() const { return snake.size; }
int Game::GetSize2() const { return snake2.size; }
