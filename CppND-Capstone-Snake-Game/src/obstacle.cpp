#include "obstacle.h"
#include <iostream>

// Constructor
Obstacle::Obstacle(int width, int height) : _width(width), _height(height){}


void Obstacle::ParseObstacle() {
    // Read coordinates from obstacle1.txt 
    SDL_Point point;
    std::ifstream filestream;
    filestream.open(path);
    if (filestream.is_open()) {
         std::string line, string_x, string_y;
        while (std::getline(filestream, line)) {
            std::stringstream linestream(line);
            linestream >> string_x >> string_y;
            point.x = std::stoi(string_x);
            point.y = std::stoi(string_y);
            // push SDL points to Obstacle vector
            obstaclePoints.emplace_back(point);
        }
        filestream.close();
    }
    return;
}

// Draw obstacle shape
void Obstacle::DrawObstacle() {
    for(int i = 0; i < _width/2; i++) {
        SDL_Point point;
        point.x = i;
        point.y =_height/3;
        obstaclePoints.emplace_back(point);
    }
}
// Getter
std::vector<SDL_Point> Obstacle::getObstacle() {
    return obstaclePoints;
    }

// Check if snake head collides with obstacle
void Obstacle::Collision(Snake &snake) {
    SDL_Point head_cell{
      static_cast<int>(snake.head_x),
      static_cast<int>(
          snake.head_y)};

    for (auto const &item : obstaclePoints) {
    if (head_cell.x == item.x && head_cell.y == item.y) {
       snake.alive = false;
    }
  }
  return;
}

// Check if cell belongs to obstacle
bool Obstacle::ObstacleCell(int x, int y) {
    for (auto const &item : obstaclePoints) {
        if (x == item.x && y == item.y) {
        return true;
        }
    }
    return false;
}
