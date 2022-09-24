#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
//updating the direction of the snakes
void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const
{

  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}
// function to handle input keys with switch statment 
void Controller::HandleInput(bool &running, Snake &snake1, Snake &snake2) const
{

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {

      switch (e.key.keysym.sym)
      {

      case SDLK_UP:
        ChangeDirection(snake1, Snake::Direction::kUp,
                        Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(snake1, Snake::Direction::kDown,
                        Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(snake1, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake1, Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;
      case SDLK_s:
        ChangeDirection(snake2, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;
      case SDLK_d:
        ChangeDirection(snake2, Snake::Direction::kDown,
                        Snake::Direction::kUp);
        break;
      case SDLK_f:
        ChangeDirection(snake2, Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;
      case SDLK_e:
        ChangeDirection(snake2, Snake::Direction::kUp,
                        Snake::Direction::kDown);
        break;
      }
    }
  }
}
