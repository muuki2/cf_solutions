CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

test_runner: src/test_runner.cpp solutions/problem1.cpp solutions/problem2.cpp solutions/problem3.cpp solutions/problem4.cpp solutions/problem5.cpp solutions/problem6.cpp solutions/problem7.cpp solutions/problem8.cpp solutions/problem9.cpp solutions/problem10.cpp
	$(CXX) $(CXXFLAGS) -o test_runner src/test_runner.cpp solutions/problem1.cpp solutions/problem2.cpp solutions/problem3.cpp solutions/problem4.cpp solutions/problem5.cpp solutions/problem6.cpp solutions/problem7.cpp solutions/problem8.cpp solutions/problem9.cpp solutions/problem10.cpp

clean:
	rm -f test_runner

.PHONY: all test clean