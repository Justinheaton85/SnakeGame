#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "obstacle.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};


  

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  int score = game.GetScore();
  int highScore = game.getHighScore();
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Your Score: " << score << "\n";
  std::cout << "Snake Size: " << game.GetSize() << "\n";

  
  // Check if current score is greater than highest score
  if (score > highScore) {
    game.setHighScore(score);
    std::cout << "Congrats you achieved the high score " << std::endl;
    std::cout << "Enter your name for new high score:" << std::endl;
    std::string name;
    // set name for new high score
    std::cin >> name;
    game.setName(name);
  }
  
  std::cout << game.getName() << " has the High Score of: " << game.getHighScore() << std::endl;
  
  
  
  return 0;
}