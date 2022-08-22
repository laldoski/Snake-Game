#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection1(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {


if (snake.direction != opposite ||  snake.size1 == 1)
   snake.direction = input;
  return;
  
}
void Controller::ChangeDirection2(Snake &snake2, Snake::Direction input,
                                 Snake::Direction opposite) const {


if (snake2.direction != opposite ||  snake2.size2 == 1)
   snake2.direction = input;
  return;
  
}




void Controller::HandleInput(bool &running, Snake &snake, Snake &snake2 ) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection1(snake,Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection1(snake,Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection1(snake,Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection1(snake,Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      
        case SDLK_s:
          ChangeDirection2(snake2, Snake::Direction::kL,
                          Snake::Direction::kR);
          break;
        case SDLK_d:
          ChangeDirection2(snake2,Snake::Direction::kD,
                          Snake::Direction::kU);
          break;
        case SDLK_f:
          ChangeDirection2(snake2,Snake::Direction::kR,
                          Snake::Direction::kL);
          break;
        case SDLK_e:
          ChangeDirection2(snake2, Snake::Direction::kU,
                          Snake::Direction::kD);
          break;
        
      }
      
    }
  }
}