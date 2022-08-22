#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake, Snake &snake2) const;

 private:
  void ChangeDirection1(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
                       
  void ChangeDirection2(Snake &snake2, Snake::Direction input,
                       Snake::Direction opposite) const;                     
};

#endif