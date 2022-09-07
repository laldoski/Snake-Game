#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:

 Controller(){};
 ~Controller(){};
  void HandleInput1 (bool &running, Snake &snake, Snake &snake2) const;
  

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
                       
                     
};

#endif