#include <iostream>
#include <vector>
using namespace std;


const int MAXS = 10000 + 10;
const int MOD = (int)1e9 + 7;

signed main() {
    ios::sync_with_stdio(0);
    
    int N;
    cin >> N;
    
    vector<int> A(N);
    for(int i = 0; i < N; ++i) {
        cin >> A[i];
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
            // Add current number
            dp[next_row][j + A[i]] = (dp[next_row][j + A[i]] + dp[current_row][j]) % MOD;
            // Subtract current number
            dp[next_row][j - A[i]] = (dp[next_row][j - A[i]] + dp[current_row][j]) % MOD;
        }
        
        // Add number of ways to get sum 0 at this step
        ans = (ans + dp[next_row][0]) % MOD;
        // Add option to start new subsequence from this position
        dp[next_row][0] = (dp[next_row][0] + 1) % MOD;
    }
    
    cout << ans << endl;
    return 0;
} 