CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror
OS := $(shell uname)
TEST_FLAGS = -lgtest
GCOV_FLAGS = -L. --coverage -lgcov

all: clean test install

install: clean
	mkdir build
	cd View && qmake && make && make clean && rm Makefile && cd ../ && mv View/SmartCalc build
	build/SmartCalc

uninstall:
	rm -rf build

dist:
	rm -rf Archive_calc_v2.0/
	mkdir Archive_calc_v2.0
	cp ./build/SmartCalc Archive_calc_v2.0
	tar cvzf Archive_calc_v2.0.tgz Archive_calc_v2.0/
	rm -rf Archive_calc_v2.0/

dvi:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" ../materials/doc/html/files.html
else
	xdg-open ../materials/doc/html/files.html
endif

test:
	${CC} ${FLAGS} Test/s21_test.cpp Model/*.cpp ${TEST_FLAGS} -lgtest_main -o s21_test
	./s21_test

clean:
	rm -rf *.o *.a *.out *.info *.html *.g* main gcov_report s21_test report build build-SmartCalc-Desktop-Debug

gcov_report: clean
	${CC} Test/s21_test.cpp Model/*.cpp -lgtest -lgtest_main ${GCOV_FLAGS} ${FLAGS} -o gcov_report
	./gcov_report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

open_report:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/Model/index.html
else
	xdg-open report/Model/index.html
endif

clang:
	clang-format -n -style=google Test/*.cpp Model/*.cpp Model/*.h Controller/*.cpp Controller/*.h View/*.cpp View/*.h

clangI:
	clang-format -i -style=google Test/*.cpp Model/*.cpp Model/*.h Controller/*.cpp Controller/*.h View/*.cpp View/*.h

leak:
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./s21_test
else
	valgrind --leak-check=full -s --track-origins=yes ./s21_test
endif
	

rebuild: all
