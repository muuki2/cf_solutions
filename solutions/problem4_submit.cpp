#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

// Constants for array sizes (100 for max string length + 2 for safety)
const int MAX_STRING_LENGTH = 100 + 2;
const int MAX_VIRUS_LENGTH = 100 + 2;

// Helper function to update maximum value
bool update_max(int &current_value, int new_value) {
    if (current_value < new_value) {
        current_value = new_value;
        return true;
    }
    return false;
}

// String lengths and input strings
int str1_length, str2_length, virus_length;
string str1, str2, virus;

// State structure to keep track of positions in dynamic programming
struct State {
    int pos_str1, pos_str2, pos_virus;  // Positions in str1, str2, and virus
    State() {}
    State(int s1, int s2, int v) : pos_str1(s1), pos_str2(s2), pos_virus(v) {}
};

// Dynamic programming table and previous state tracking
int dp[MAX_STRING_LENGTH][MAX_STRING_LENGTH][MAX_VIRUS_LENGTH];
State previous_state[MAX_STRING_LENGTH][MAX_STRING_LENGTH][MAX_VIRUS_LENGTH];

// Reconstruct the solution from the dp table
void reconstruct_solution(State current) {
    string result;
    // Build the solution by backtracking through previous states
    while (current.pos_str1 + current.pos_str2 + current.pos_virus > 0) {
        State prev = previous_state[current.pos_str1][current.pos_str2][current.pos_virus];
        // If we added a character in this step, add it to our result
        if (dp[prev.pos_str1][prev.pos_str2][prev.pos_virus] + 1 == 
            dp[current.pos_str1][current.pos_str2][current.pos_virus])
            result += str1[prev.pos_str1];
        current = prev;
    }
    // Reverse the result since we built it backwards
    reverse(result.begin(), result.end());
    cout << result << "\n";
}

void solve() {
    // Read input
    cin >> str1 >> str2 >> virus;
    
    // Initialize variables
    memset(dp, -1, sizeof(dp));
    str1_length = str1.size();
    str2_length = str2.size();
    virus_length = virus.size();
    dp[0][0][0] = 0;  // Base case: empty strings have length 0

    // Main dynamic programming loop
    for (int i = 0; i < str1_length; ++i)
        for (int j = 0; j < str2_length; ++j)
            for (int k = 0; k < virus_length; ++k) {
                if (dp[i][j][k] < 0) continue;  // Skip invalid states

                // If characters match in both strings
                if (str1[i] == str2[j]) {
                    if (str1[i] == virus[k]) {
                        // If current character matches virus position
                        if (update_max(dp[i + 1][j + 1][k + 1], dp[i][j][k] + 1))
                            previous_state[i + 1][j + 1][k + 1] = State(i, j, k);
                    } else {
                        // Check for virus pattern match
                        int new_k;
                        for (new_k = k; new_k >= 1; --new_k)
                            if (virus.substr(0, new_k) == virus.substr(k - new_k + 1, new_k - 1) + str1[i])
                                break;
                        if (update_max(dp[i + 1][j + 1][new_k], dp[i][j][k] + 1))
                            previous_state[i + 1][j + 1][new_k] = State(i, j, k);
                    }
                }

                // Try skipping characters
                // Skip in first string
                if (update_max(dp[i + 1][j][k], dp[i][j][k]))
                    previous_state[i + 1][j][k] = State(i, j, k);
                // Skip in second string
                if (update_max(dp[i][j + 1][k], dp[i][j][k]))
                    previous_state[i][j + 1][k] = State(i, j, k);
                // Skip in both strings
                if (update_max(dp[i + 1][j + 1][k], dp[i][j][k]))
                    previous_state[i + 1][j + 1][k] = State(i, j, k);
            }

    // Find the best solution
    State best_state;
    int max_length = 0;
    for (int i = 0; i <= str1_length; ++i)
        for (int j = 0; j <= str2_length; ++j)
            for (int k = 0; k < virus_length; ++k)
                if (update_max(max_length, dp[i][j][k]))
                    best_state = State(i, j, k);

    // Output the result
    if (max_length == 0) {
        cout << "0\n";
        return;
    }
    reconstruct_solution(best_state);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
} 