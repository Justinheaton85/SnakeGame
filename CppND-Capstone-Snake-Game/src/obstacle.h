#ifndef OBST_H
#define OBST_H

#include <random>
#include <vector>
#include "SDL.h"
#include "renderer.h"
#include "snake.h"
#include <fstream>
#include <sstream>
#include <string>
#include <memory>


class Obstacle {
 public:

  // Public Member Functions
  Obstacle(int width, int height);
  void DrawObstacle();
  void ParseObstacle();
  std::vector<SDL_Point> getObstacle();
  void Collision(Snake &snake);
  bool ObstacleCell(int x, int y);
  
  

 private:
   
  // Private Members
  int _width;
  int _height;
  std::vector<SDL_Point> obstaclePoints;
  std::string path = "../Data/obstacle1.txt";
};

#endif