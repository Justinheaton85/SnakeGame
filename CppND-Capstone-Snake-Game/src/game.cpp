#include "game.h"
#include <iostream>
#include "SDL.h"
#include <fstream>
#include <future>
#include <string>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {

      // Create obstacle instance 
      obstacle = std::make_shared<Obstacle>(grid_width, grid_height);
      obstacle->ParseObstacle();

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
    controller.HandleInput(running, snake);
    obstacle->Collision(snake);
    Update();
    renderer.Render(snake, food, obstacle);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake or obstacle item before 
    // placing food.
    std::vector<std::future<bool>> frs;
    frs.emplace_back(std::async(&Snake::SnakeCell, snake, x,y));
    frs.emplace_back(std::async(&Obstacle::ObstacleCell, obstacle, x,y));
    if (!frs[0].get() && !frs[1].get()) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {

  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }

int Game::GetSize() const { return snake.size; }

// Read high score from score.txt
int Game::getHighScore() {
    int highScore = 0;
    std::ifstream fstream;
    fstream.open(scorePath);
    if (fstream.is_open()) {
         std::string line;
        while (std::getline(fstream, line)) {
            std::stringstream linestream(line);
            linestream >> highScore;
        }
    }
    return highScore;
}

// Set new high score
void Game::setHighScore(int &score) {
  std::ofstream outStream;
  outStream.open(scorePath);
  if (outStream.is_open()) {
    outStream << score;
    outStream.close();
  }
  else {
    std::cout << "Failed to open file" << std::endl;
  }
  return;
}


std::string Game::getName() {
    std::ifstream filestream;
    filestream.open(namePath);
    if (filestream.is_open()) {
         std::string line, name;
        while (std::getline(filestream, line)) {
            std::stringstream linestream(line);
            linestream >> name;
        }
      return name;
    }
    
}

void Game::setName(std::string &name) {
    std::ofstream outFile;
    outFile.open(namePath);
    if (outFile.is_open()) {
    outFile << name;
    outFile.close();
    }
    return;
}
