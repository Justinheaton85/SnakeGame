#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "obstacle.h"
#include <fstream>
#include <thread>



class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int getHighScore();
  void setHighScore(int &score);
  std::string getName();
  void setName(std::string &name);

 private:
  Snake snake;
  std::shared_ptr<Obstacle> obstacle;
  SDL_Point food;
  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  std::string scorePath = "../Data/score.txt";
  std::string namePath = "../Data/name.txt";

  void PlaceFood();
  //void PlaceFood(Obstacle &obstacle);
  void Update();
  //void Update(Obstacle &obstacle);
};

#endif