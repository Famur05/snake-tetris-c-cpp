#include <gtest/gtest.h>

#include "../brick_game/snake/model.h"

TEST(ModelTest, DefaultConstructor) {
  s21::Model model;
  auto state = model.updateCurrentState();

  EXPECT_EQ(state.score, 0);
  EXPECT_EQ(state.level, 1);
  EXPECT_EQ(state.speed, 200);
  EXPECT_EQ(state.pause, 1);
  EXPECT_EQ(state.game_status, GAME_IS_ON);
  EXPECT_EQ(state.snake_direction, s21::SnakeDirection::UP);
  EXPECT_FALSE(state.acceleration);
  EXPECT_EQ(state.snake_points.size(), kInitialSnakeLength);
}

TEST(ModelTest, UserInputBasicActions) {
  s21::Model model;

  model.UserInput('\n');  // Start
  EXPECT_EQ(model.updateCurrentState().enter, 1);

  model.UserInput(32);  // Pause
  EXPECT_EQ(model.updateCurrentState().pause, -1);

  model.UserInput(27);  // Terminate
  EXPECT_EQ(model.updateCurrentState().game_status, GAME_OVER);
}

TEST(ModelTest, SnakeDirectionInput) {
  s21::Model model;

  model.UserInput(KEY_LEFT);
  EXPECT_EQ(model.updateCurrentState().snake_direction,
            s21::SnakeDirection::LEFT);

  model.UserInput(KEY_UP);
  EXPECT_EQ(model.updateCurrentState().snake_direction,
            s21::SnakeDirection::UP);

  model.UserInput(KEY_RIGHT);
  EXPECT_EQ(model.updateCurrentState().snake_direction,
            s21::SnakeDirection::RIGHT);

  model.UserInput(KEY_DOWN);
  EXPECT_EQ(model.updateCurrentState().snake_direction,
            s21::SnakeDirection::DOWN);
}

TEST(ModelTest, AccelerationToggle) {
  s21::Model model;

  model.UserInput('w');  // Acceleration on
  EXPECT_TRUE(model.updateCurrentState().acceleration);

  model.UserInput('w');  // Acceleration off
  EXPECT_FALSE(model.updateCurrentState().acceleration);
}

TEST(ModelTest, AppleGeneration) {
  s21::Model model;
  model.GenerateApple();
  auto state = model.updateCurrentState();

  auto apple = state.apple_point;
  EXPECT_GE(apple.x, 0);
  EXPECT_LT(apple.x, WIDTH);
  EXPECT_GE(apple.y, 0);
  EXPECT_LT(apple.y, HEIGHT);

  bool apple_under_snake = false;
  for (const auto& point : state.snake_points) {
    if (apple.x == point.x && apple.y == point.y) {
      apple_under_snake = true;
      break;
    }
  }
  EXPECT_FALSE(apple_under_snake);
}

TEST(ModelTest, SnakeAppleEating) {
  s21::Model model;

  auto& state = model.GetAppleСoordinates();
  state.y = model.updateCurrentState().snake_points.front().y - 1;
  state.x = model.updateCurrentState().snake_points.front().x;

  model.Movement();

  EXPECT_GT(model.updateCurrentState().score, 0);

  EXPECT_EQ(model.updateCurrentState().snake_points.size(),
            kInitialSnakeLength + 1);
}

TEST(ModelTest, HighScoreHandling) {
  s21::Model model;

  model.SetHighScore(10);
  model.SaveHighScore();

  s21::Model model2;
  model2.LoadHighScore();
  EXPECT_EQ(model2.updateCurrentState().high_score, 10);
}
