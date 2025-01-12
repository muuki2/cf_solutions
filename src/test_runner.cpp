#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <functional>
#include <filesystem>
#include "../solutions/problem1.h"
#include "../solutions/problem2.h"
#include "../solutions/problem3.h"
#include "../solutions/problem4.h"
#include "../solutions/problem5.h"
#include "../solutions/problem6.h"
#include "../solutions/problem7.h"
#include "../solutions/problem8.h"
#include "../solutions/problem9.h"
#include "../solutions/problem10.h"

using namespace std;
namespace fs = std::filesystem;

// Function to capture cout output
string capture_cout(function<void()> func) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    func();
    cout.rdbuf(old);
    return buffer.str();
}

// Function to read entire file content
string read_file_content(ifstream& file) {
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to trim whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos) return "";
    return str.substr(first, last - first + 1);
}

// Function to print test details
void print_test_details(const string& input, const string& expected, const string& actual, bool passed) {
    cout << "Input:\n" << input << "\n\n";
    cout << "Expected output:\n" << expected << "\n\n";
    cout << "Actual output:\n" << actual << "\n\n";
    cout << "Test " << (passed ? "PASSED" : "FAILED") << "\n";
    cout << "----------------------------------------\n";
}

bool run_test_case(int problem_num, int test_num, bool verbose) {
    string base_path = "tests/problem" + to_string(problem_num) + "/";
    string input_path = base_path + "input" + to_string(test_num) + ".txt";
    string output_path = base_path + "output" + to_string(test_num) + ".txt";
    
    // Check if both input and output files exist
    if (!fs::exists(input_path) || !fs::exists(output_path)) {
        return false;
    }
    
    ifstream input(input_path);
    ifstream output(output_path);
    
    string input_content = read_file_content(input);
    input.clear();
    input.seekg(0);
    
    streambuf* old_cin = cin.rdbuf(input.rdbuf());
    string expected = read_file_content(output);
    
    string result;
    switch (problem_num) {
        case 1: {
            solution1::Cipher solver;
            result = solver.solve(input);
            break;
        }
        case 2:
            result = capture_cout([]() { problem2::solve(); });
            break;
        case 3: {
            int r, g;
            input >> r >> g;
            result = to_string(solve(r, g));
            break;
        }
        case 4:
            result = capture_cout([]() { problem4::solve(); });
            break;
        case 5: {
            solution5::CardsAndJoy solver;
            result = solver.solve(input);
            break;
        }
        case 6: {
            solution6::SupermarketShopping solver;
            result = solver.solve(input);
            break;
        }
        case 7: {
            solution7::BeautifulNumber solver;
            result = solver.solve(input);
            break;
        }
        case 8: {
            solution8::BearAndString solver;
            result = solver.solve(input);
            break;
        }
        case 9: {
            solution9::Antimatter solver;
            result = solver.solve(input);
            break;
        }
        case 10: {
            solution10::Minesweeper1D solver;
            result = solver.solve(input);
            break;
        }
    }
    
    cin.rdbuf(old_cin);
    
    bool passed = trim(result) == trim(expected);
    if (verbose || !passed) {
        cout << "Test case " << test_num << ":\n";
        print_test_details(input_content, expected, result, passed);
    }
    if (!passed) {
        throw runtime_error("Problem " + to_string(problem_num) + " test " + to_string(test_num) + " failed!");
    }
    return true;  // Continue checking more test cases
}

void test_problem(int problem_num, bool verbose = false) {
    cout << "\nTesting Problem " << problem_num << ":\n";
    cout << "----------------------------------------\n";
    
    int test_num = 1;
    bool has_more_tests = true;
    bool any_tests = false;
    
    while (has_more_tests) {
        has_more_tests = run_test_case(problem_num, test_num, verbose);
        if (has_more_tests) any_tests = true;
        test_num++;
    }
    
    if (any_tests) {
        cout << "Problem " << problem_num << ": All tests passed!\n";
    } else {
        cout << "Problem " << problem_num << ": No tests found.\n";
    }
}

int main(int argc, char* argv[]) {
    bool verbose = false;
    int problem_number = 0;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-v" || arg == "--verbose") {
            verbose = true;
        } else if (arg == "-p" || arg == "--problem") {
            if (i + 1 < argc) {
                problem_number = stoi(argv[++i]);
            }
        }
    }
    
    try {
        if (problem_number == 0 || problem_number == 1) {
            test_problem(1, verbose);
        }
        if (problem_number == 0 || problem_number == 2) {
            test_problem(2, verbose);
        }
        if (problem_number == 0 || problem_number == 3) {
            test_problem(3, verbose);
        }
        if (problem_number == 0 || problem_number == 4) {
            test_problem(4, verbose);
        }
        if (problem_number == 0 || problem_number == 5) {
            test_problem(5, verbose);
        }
        if (problem_number == 0 || problem_number == 6) {
            test_problem(6, verbose);
        }
        if (problem_number == 0 || problem_number == 7) {
            test_problem(7, verbose);
        }
        if (problem_number == 0 || problem_number == 8) {
            test_problem(8, verbose);
        }
        if (problem_number == 0 || problem_number == 9) {
            test_problem(9, verbose);
        }
        if (problem_number == 0 || problem_number == 10) {
            test_problem(10, verbose);
        }
        cout << "\nAll specified tests passed!\n";
    } catch (const exception& e) {
        cerr << "\nTest failed: " << e.what() << endl;
        return 1;
    }
    
    return 0;
} 