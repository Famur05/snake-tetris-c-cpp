#ifndef MODEL_H
#define MODEL_H

#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define HEIGHT 20
#define WIDTH 10
#define GAME_OVER 0
#define GAME_IS_ON 1
#define UNUSED(x) (void)(x)
#define KEY_LEFT 0404
#define KEY_RIGHT 0405
#define KEY_DOWN 0402
#define KEY_UP 0403

constexpr int kInitialSnakeLength = 4;
constexpr int kMaxSnakeLength = 200;

namespace s21 {

enum UserAction_t {
  Start,
  Pause,
  Terminate,  // прекратить
  Left,
  Right,
  Up,
  Down,
  Action  // дейстивие - ускорение
};

enum class SnakeDirection { LEFT, RIGHT, UP, DOWN };

struct Point {
  int x;
  int y;

  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}
};

struct GameInfo_t {
  int** field;     //поле
  int** next;      // следующая фигура
  int score;       // счет
  int high_score;  // рекорд
  int level;       // уровень
  int speed;       // скорость
  int pause;       //пауза

  std::deque<Point> snake_points;
  Point apple_point;
  bool game_status;
  bool enter;
  bool acceleration;
  SnakeDirection snake_direction;
};
/**
 * @brief этот класс отвечает за бизнес логику игры
 *
 */
class Model {
 public:
  Model();
  ~Model();

  void userInput(UserAction_t action, bool hold);
  GameInfo_t updateCurrentState();
  void UserInput(int input);
  bool CheckUnderSnake(const Point& bit);
  void GenerateApple();
  void InitializeSnake();
  bool CheckCollision(const Point& new_head);
  bool CheckAppleEating(const Point& new_head);
  void MoveSnake(const Point& direction);
  void Movement();
  void LoadHighScore();
  void SaveHighScore();

  bool GetGameStatus();
  int GetSpeed();
  Point& GetAppleСoordinates();

  void SetHighScore(int score);

 private:
  GameInfo_t game_info_ = {};
  const std::string score_file_ = "high_score_snake.txt";

  void CreateField();
  void RemoveField();
};

}  // namespace s21

#endif  // MODEL_H
