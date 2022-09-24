#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <vector>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{740};
  constexpr std::size_t kScreenHeight{740};
  constexpr std::size_t kGridWidth{38};
  constexpr std::size_t kGridHeight{38};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";

 std::cout << "Score Player1: " << game.GetScore1() << "\n";
 std::cout << "Score Player2: " << game.GetScore2() <<"\n";
 //announce the winner
  if (game.GetScore1() > game.GetScore2())
   {std::cout << "Player1 is The WINNER!!!"<< "\n";}
  else if(game.GetScore2() > game.GetScore1())
   {std::cout << "Player2 is The WINNER!!!"<< "\n";}
  return 0;
}