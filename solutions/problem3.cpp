#include <iostream>
#include <vector>
#include "problem3.h"
using namespace std;

const int MOD = 1e9 + 7;

int solve(int r, int g) {
    // Find maximum possible height h where h(h+1)/2 <= r + g
    int h = 1;
    while ((long long)h * (h + 1) / 2 <= r + g) {
        h++;
    }
    h--; // Adjust back to valid height

    // dp[t][r] represents number of ways to build t levels using r red blocks
    vector<vector<int>> dp(2, vector<int>(r + 1, 0));
    dp[0][0] = 1; // Base case: 0 levels, 0 red blocks = 1 way

    for (int t = 0; t < h; t++) {
        vector<int>& curr = dp[t & 1];
        vector<int>& next = dp[(t + 1) & 1];
        fill(next.begin(), next.end(), 0);

        for (int used_r = 0; used_r <= r; used_r++) {
            if (curr[used_r] == 0) continue;

            // Calculate remaining green blocks
            int used_total = (t * (t + 1)) / 2;
            int used_g = used_total - used_r;
            int rem_g = g - used_g;

            // Try adding red blocks to next level
            if (used_r + (t + 1) <= r) {
                next[used_r + (t + 1)] = (next[used_r + (t + 1)] + curr[used_r]) % MOD;
            }

            // Try adding green blocks to next level
            if (rem_g >= (t + 1)) {
                next[used_r] = (next[used_r] + curr[used_r]) % MOD;
            }
        }
    }

    // Sum all possibilities for height h
    int result = 0;
    for (int used_r = 0; used_r <= r; used_r++) {
        result = (result + dp[h & 1][used_r]) % MOD;
    }

    return result;
}

#ifdef PROBLEM3_MAIN
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int r, g;
    cin >> r >> g;
    cout << solve(r, g) << endl;
    
    return 0;
}
#endif 