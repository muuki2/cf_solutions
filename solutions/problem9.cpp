#include "problem9.h"
#include <iostream>
#include <vector>

using namespace std;

namespace solution9 {

const int MAXS = 10000 + 10;
const int MOD = (int)1e9 + 7;

string Antimatter::solve(istream& input) {
    ios::sync_with_stdio(0);
    
    int N;
    input >> N;
    
    vector<int> A(N);
    for(int i = 0; i < N; ++i) {
        input >> A[i];
    }
    
    // DP array setup to handle negative indices
    vector<vector<int>> _dp(2, vector<int>(4 * MAXS));
    vector<int*> dp = {&_dp[0][2 * MAXS], &_dp[1][2 * MAXS]};
    
    int ans = 0;
    dp[0][0] = 1;
    
    for(int i = 0; i < N; ++i) {
        int current_row = i % 2;
        int next_row = (i + 1) % 2;
        
        // Clear the next row
        for(int j = -MAXS; j <= MAXS; ++j) {
            dp[next_row][j] = 0;
        }
        
        // Process all possible sums
        for(int j = -MAXS; j <= MAXS; ++j) {
            // Add current number (matter)
            dp[next_row][j + A[i]] = (dp[next_row][j + A[i]] + dp[current_row][j]) % MOD;
            // Subtract current number (antimatter)
            dp[next_row][j - A[i]] = (dp[next_row][j - A[i]] + dp[current_row][j]) % MOD;
        }
        
        // Add number of ways to get equal matter and antimatter at this step
        ans = (ans + dp[next_row][0]) % MOD;
        // Add option to start new subsequence from this position
        dp[next_row][0] = (dp[next_row][0] + 1) % MOD;
    }
    
    return to_string(ans);
}

} // namespace solution9 