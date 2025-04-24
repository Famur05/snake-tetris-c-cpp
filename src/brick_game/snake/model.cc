#include "model.h"

namespace s21 {
/**
 * @brief Construct a new Model:: Model object
 *
 */
Model::Model() {
  CreateField();
  game_info_.score = 0;
  LoadHighScore();
  game_info_.level = 1;
  game_info_.speed = 200;
  game_info_.pause = 1;
  game_info_.game_status = GAME_IS_ON;
  game_info_.snake_direction = SnakeDirection::UP;
  game_info_.acceleration = false;
  std::srand(std::time(nullptr));
  InitializeSnake();
  GenerateApple();
}
/**
 * @brief Destroy the Model:: Model object
 *
 */
Model::~Model() {
  RemoveField();
  SaveHighScore();
}
/**
 * @brief создает поле, выделяя память
 *
 */
void Model::CreateField() {
  int flag = 0;
  game_info_.field = new int*[HEIGHT];
  if (game_info_.field != nullptr) {
    for (int i = 0; i < HEIGHT && !flag; i++) {
      game_info_.field[i] = new int[WIDTH];
      if (game_info_.field[i] == nullptr) {
        flag = 1;
      }
    }
  }
}
/**
 * @brief удалят поле, освобождая память
 *
 */
void Model::RemoveField() {
  if (game_info_.field != nullptr) {
    for (int i = 0; i < HEIGHT; i++) {
      if (game_info_.field[i] != nullptr) {
        delete[] game_info_.field[i];
      }
    }
    delete[] game_info_.field;
  }
}
/**
 * @brief обрабатывает действия пользователя
 *
 * @param action
 * @param hold
 */
void Model::userInput(UserAction_t action, bool hold) {
  UNUSED(hold);
  switch (action) {
    case Start:
      game_info_.enter = 1;
      break;
    case Pause:
      game_info_.pause *= -1;
      break;
    case Terminate:
      game_info_.game_status = GAME_OVER;
      break;
    case Left:
      if (game_info_.snake_direction != SnakeDirection::RIGHT)
        game_info_.snake_direction = SnakeDirection::LEFT;
      break;
    case Right:
      if (game_info_.snake_direction != SnakeDirection::LEFT)
        game_info_.snake_direction = SnakeDirection::RIGHT;
      break;
    case Up:
      if (game_info_.snake_direction != SnakeDirection::DOWN)
        game_info_.snake_direction = SnakeDirection::UP;
      break;
    case Down:
      if (game_info_.snake_direction != SnakeDirection::UP)
        game_info_.snake_direction = SnakeDirection::DOWN;
      break;
    case Action:
      game_info_.acceleration = !game_info_.acceleration;
      break;
    default:
      break;
  }
}
/**
 * @brief поддерживает актуальное состояние для отрисовки
 *
 * @return GameInfo_t
 */
GameInfo_t Model::updateCurrentState() {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      game_info_.field[y][x] = 0;
    }
  }

  for (const auto& point : game_info_.snake_points) {
    game_info_.field[point.y][point.x] = 1;
  }

  game_info_.field[game_info_.apple_point.y][game_info_.apple_point.x] = 2;
  return game_info_;
}
/**
 * @brief считывает действия пользователя
 *
 * @param input
 */
void Model::UserInput(int input) {
  switch (input) {
    case '\n':  // Enter
      userInput(Start, 1);
      break;
    case 32:  // Space
      userInput(Pause, 1);
      break;
    case 27:  // Esc
      userInput(Terminate, 1);
      break;
    case KEY_LEFT:
      userInput(Left, 1);
      break;
    case KEY_RIGHT:
      userInput(Right, 1);
      break;
    case KEY_UP:
      userInput(Up, 1);
      break;
    case KEY_DOWN:
      userInput(Down, 1);
      break;
    case 'w':  // ускорение
      userInput(Action, 1);
      break;
    default:
      break;
  }
}
/**
 * @brief проверяет, не находиться ли что-то под змеёй
 *
 * @param bit
 * @return true
 * @return false
 */
bool Model::CheckUnderSnake(const Point& bit) {
  bool flag = 0;
  for (const auto& point : game_info_.snake_points) {
    if (point.x == bit.x && point.y == bit.y) {
      flag = 1;
      break;
    }
  }
  return flag;
}
/**
 * @brief генерирует яблоко, прежде заполняя массив свободными ячейками
 *
 */
void Model::GenerateApple() {
  std::vector<Point> free_cells;

  // заполняем массив свободными ячейками
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      Point candidate(x, y);
      if (!CheckUnderSnake(candidate)) {
        free_cells.push_back(candidate);
      }
    }
  }
  // если на карте есть свободные ячейки, случайным образом ставим координаты
  // для яболка
  if (!free_cells.empty()) {
    int index = std::rand() % free_cells.size();
    game_info_.apple_point = free_cells[index];
  } else {
    game_info_.game_status = GAME_OVER;
  }
}
/**
 * @brief распологает змею на поле в начале игры
 *
 */
void Model::InitializeSnake() {
  for (int i = 0; i < kInitialSnakeLength; ++i) {
    game_info_.snake_points.emplace_back(WIDTH / 2, HEIGHT / 2 + i);
  }
}
/**
 * @brief проверяет столкновение
 *
 * @param new_head
 * @return true
 * @return false
 */
bool Model::CheckCollision(const Point& new_head) {
  bool flag = 0;
  if (new_head.x < 0 || new_head.x >= WIDTH || new_head.y < 0 ||
      new_head.y >= HEIGHT) {
    game_info_.game_status = GAME_OVER;
    flag = 1;
  }
  if (CheckUnderSnake(new_head)) {
    game_info_.game_status = GAME_OVER;
    flag = 1;
  }
  return flag;
}
/**
 * @brief проверяет, не съела ли змея яблоко, если съела то подсчитываются
 * количество очков и уровень
 *
 * @param new_head
 * @return true
 * @return false
 */
bool Model::CheckAppleEating(const Point& new_head) {
  bool flag = 0;
  if (new_head.x == game_info_.apple_point.x &&
      new_head.y == game_info_.apple_point.y) {
    game_info_.score++;
    if (game_info_.high_score < game_info_.score)
      game_info_.high_score = game_info_.score;
    if (game_info_.level < 10) game_info_.level = game_info_.score / 5 + 1;

    if (game_info_.snake_points.size() >= kMaxSnakeLength) {
      game_info_.game_status = GAME_OVER;
    } else {
      GenerateApple();
    }
    flag = 1;
  }
  return flag;
}
/**
 * @brief отвечает за догику движения змеи
 *
 * @param direction
 */
void Model::MoveSnake(const Point& direction) {
  Point new_head(game_info_.snake_points.front().x + direction.x,
                 game_info_.snake_points.front().y + direction.y);
  if (!CheckCollision(new_head)) game_info_.snake_points.push_front(new_head);

  if (!CheckAppleEating(new_head)) game_info_.snake_points.pop_back();
}
/**
 * @brief отвечает за движение змеи
 *
 */
void Model::Movement() {
  switch (game_info_.snake_direction) {
    case SnakeDirection::LEFT:
      MoveSnake(Point(-1, 0));
      break;
    case SnakeDirection::RIGHT:
      MoveSnake(Point(1, 0));
      break;
    case SnakeDirection::UP:
      MoveSnake(Point(0, -1));
      break;
    case SnakeDirection::DOWN:
      MoveSnake(Point(0, 1));
      break;
    default:
      break;
  }
}
/**
 * @brief загружает максимальное количество очков
 *
 */
void Model::LoadHighScore() {
  std::ifstream infile(score_file_);
  if (infile.is_open()) {
    infile >> game_info_.high_score;
    infile.close();
  } else {
    game_info_.high_score = 0;
  }
}
/**
 * @brief выгружает максимальное количество очков
 *
 */
void Model::SaveHighScore() {
  std::ofstream outfile(score_file_);
  if (outfile.is_open()) {
    outfile << game_info_.high_score;
    outfile.close();
  } else {
    std::cerr << "Ошибка: невозможно сохранить рекорд в файл!" << std::endl;
  }
}
/**
 * @brief гетттер на статус игры
 *
 * @return true
 * @return false
 */
bool Model::GetGameStatus() { return game_info_.game_status; }
/**
 * @brief геттер на получение актуальной скорости
 *
 * @return int
 */
int Model::GetSpeed() {
  return game_info_.acceleration ? 90
                                 : game_info_.speed - game_info_.level * 10;
}
/**
 * @brief получаем доступ к координатам яблоки, для тестов
 *
 */
Point& Model::GetAppleСoordinates() { return game_info_.apple_point; }
/**
 * @brief сеттер для изменения количества очков
 *
 * @param score
 */
void Model::SetHighScore(int score) { game_info_.high_score = score; }

}  // namespace s21
