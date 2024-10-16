# Компиляторы
CC=gcc
CC_FLAGS= -Wall -Werror -Wextra
GCOVFLAGS = --coverage
OBJECT_FILES= gui/cli/frontend.o game.o brick_game/tetris/backend.o 
TEST_FILES = test/test.o brick_game/tetris/backend.o gui/cli/frontend.o
GCOV_FILES = brick_game/tetris/backend.c test/test.c
DIST_DIR = s21_Tetris

UNAME_S = $(shell uname)

ifeq ($(UNAME_S),Darwin)
OPEN_CMD = open
endif

ifeq ($(UNAME_S),Linux)
OPEN_CMD = xdg-open
ADD_LDFLAGS = -lm
endif

LIB_NCURSES = -lncurses
LIB_LCHECK = -lcheck
OBJECT_NAME = tetris
TEST_NAME = test
GCOV_NAME = gcov_test

all: install

install: $(OBJECT_FILES)
	mkdir -p build
	$(CC) $(CC_FLAGS) $^ -o build/$(OBJECT_NAME) $(LIB_NCURSES)
	echo 0 > build/max_score.txt 

uninstall:
	rm -rf build

dvi:
	$(OPEN_CMD) Documentation.html

dist:
	mkdir -p $(DIST_DIR)
	cp -a brick_game $(DIST_DIR)
	cp -a gui $(DIST_DIR)
	cp -a test $(DIST_DIR)
	cp -a *.c $(DIST_DIR)
	cp -a *.h $(DIST_DIR)
	cp -a Documentation.html $(DIST_DIR)
	tar -czf s21_Tetris.tar.gz $(DIST_DIR)
	rm -rf $(DIST_DIR)
	
test: $(TEST_FILES)
	echo 0 > test/max_score.txt
	$(CC) $(CC_FLAGS) $^ -o test/$(TEST_NAME) $(LIB_LCHECK) $(LIB_NCURSES)
	cd test && ./$(TEST_NAME)

gcov_report:
	mkdir -p gcov
	echo 0 > gcov/max_score.txt
	$(CC) $(GCOVFLAGS) $(GCOV_FILES) -o ./gcov/$(GCOV_NAME) -lcheck
	cd gcov && ./$(GCOV_NAME)
	lcov -t "test" -o test_report.info -c -d . 
	genhtml -o report test_report.info
	$(OPEN_CMD) report/index.html
clean:
	rm -rf build *.gch *.gcno *.gcda *.info report *.o gui/cli/*.o brick_game/tetris/*.o brick_game/tetris/*.o test/*.o $(OBJECT_NAME) test/$(TEST_NAME) $(GCOV_NAME)
	rm -f s21_Tetris.tar.gz
	rm -rf gcov

clang_format:
	cp ../materials/linters/.clang-format ../../src
	clang-format -i *.c *.h
	clang-format -i brick_game/tetris/*.c brick_game/tetris/*.h
	clang-format -i gui/cli/*.c gui/cli/*.h
	clang-format -i test/*.c test/*.h
	rm -f .clang-format

check_clang_format:
	cp ../materials/linters/.clang-format ../../src
	clang-format -n *.c *.h
	clang-format -n brick_game/tetris/*.c brick_game/tetris/*.h
	clang-format -n gui/cli/*.c gui/cli/*.h
	clang-format -n test/*.c test/*.h
	rm -f .clang-format

