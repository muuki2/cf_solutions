#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 505;

// dp[l][r] represents minimum operations to clear substring s[l...r]
int dp[MAX_N][MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int string_length;
    string input_string;
    cin >> string_length >> input_string;

    // Initialize dp array with -1 (unvisited)
    memset(dp, -1, sizeof(dp));

    // Base cases
    // Empty substring needs 0 operations
    for (int i = 0; i <= string_length; i++) {
        for (int j = 0; j < i; j++) {
            dp[i][j] = 0;  // l > r case
        }
    }
    // Single character needs 1 operation
    for (int i = 0; i < string_length; i++) {
        dp[i][i] = 1;
    }

    // Fill dp table
    // For each length of substring
    for (int len = 2; len <= string_length; len++) {
        // For each starting position
        for (int left = 0; left + len - 1 < string_length; left++) {
            int right = left + len - 1;

            // Case 1: Delete first character separately
            dp[left][right] = 1 + dp[left + 1][right];

            // Case 2: Try matching first character with any other matching character
            for (int i = left + 1; i <= right; i++) {
                if (input_string[left] == input_string[i]) {
                    // We can either:
                    // 1. Delete characters between left+1 and i-1
                    // 2. Then handle the substring from i to right
                    dp[left][right] = min(dp[left][right], 
                                        dp[left + 1][i - 1] + dp[i][right]);
                }
            }
        }
    }

    // Output minimum operations needed for entire string
    cout << dp[0][string_length - 1] << endl;
    return 0;
} 