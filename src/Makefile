CC = gcc
CFLAGS = -Wall -Werror -Wextra -lstdc++ -std=c++17
TESTFLAGS = -lgtest -pthread -lgtest_main
SOURCE = s21_matrix_oop.cc
TESTSOURCE = s21_matrix_oop_tests.cc
TESTAPP = s21_matrix_oop_tests

all: s21_matrix_oop.a test

s21_matrix_oop.a:
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar rc s21_matrix_oop.a s21_matrix_oop.o
	rm -rf *.o

test:
	$(CC) $(CFLAGS) $(TESTFLAGS) $(LCOV) $(TESTSOURCE) $(SOURCE) -o $(TESTAPP)
	leaks -atExit -- ./$(TESTAPP)

clean:
	rm $(TESTAPP)
	rm s21_matrix_oop.a