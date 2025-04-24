#===========================================================================
CC = g++
FLAGS = -std=c++17 -pedantic -Wall -Werror -Wextra -lm
#===========================================================================
TARGET = snake.a
#===========================================================================
TEST_FLAGS = -lgtest -lgmock -pthread -lgtest_main
#===========================================================================
FILE_C_CC = brick_game/snake/*.cc gui/desktop/*.cc brick_game/tetris/*.c gui/cli/*.c
FILE_H = brick_game/snake/*.h gui/desktop/*.h brick_game/tetris/*.h gui/cli/*.h
FILE_CLI = brick_game/snake/*.cc brick_game/tetris/*.c gui/cli/*.c
#===========================================================================
all: install

install:
	$(CC) $(FLAGS) $(FILE_CLI) -lncurses -o tetris_snake

uninstall:
	rm -rf tetris_snake

install_desktop:
	cmake -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/
	./build/s21_Snake

uninstall_desktop:
	rm -rf build

$(TARGET):
	$(CC) $(FLAGS) -c brick_game/snake/model.cc
	ar rcs $(TARGET) *.o
	ranlib $(TARGET)
	rm -rf *.o

test: clean $(TARGET)
	$(CC) $(FLAGS) tests/tests.cc $(TARGET) $(TEST_FLAGS) -o test.out
	./test.out

gcov_report: clean
	$(CC) $(FLAGS) tests/tests.cc brick_game/snake/model.cc $(TEST_FLAGS) --coverage -o coverage.out
	./coverage.out
	lcov -c -d ./ -o coverage.info
	genhtml -o coverage_html coverage.info 
	xdg-open coverage_html/index.html

dvi:
	doxygen Doxyfile
	xdg-open html/index.html 

dist: clean
	mkdir archived_tetris_snake
	cp -r $(shell ls | grep -v archived_tetris_snake) archived_tetris_snake
	tar -czvf archived_tetris_snake.tar.gz archived_tetris_snake
	rm -rf archived_tetris_snake

valgrind: test
	valgrind --tool=memcheck --leak-check=yes  ./test.out

clang_i:
	clang-format -i -style=Google $(FILE_C_CC) $(FILE_H) tests/*.cc

clang_n:
	clang-format -n -style=Google $(FILE_C_CC) $(FILE_H) tests/*.cc

clean:
	rm -rf coverage_html html *.gcno *.gcda *.out *.info *.a *.o tetris_snake archived_tetris_snake.tar.gz high_score_snake.txt high_score_tetris.txt build

rebuild: clean all
#===========================================================================
