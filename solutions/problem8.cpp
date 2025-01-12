#include "problem8.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

namespace solution8 {

template<class T1, class T2>
int upmin(T1& x, T2 v) {
    if (x <= v) return 0;
    x = v;
    return 1;
}

const int MAXN = 75;

string BearAndString::solve(istream& input) {
    ios::sync_with_stdio(0);
    
    int N;
    string seq;
    input >> N >> seq;
    
    vector<int> pos[256];
    int dp[MAXN + 1][MAXN + 1][MAXN + 1][2];
    
    // Process the sequence
    for (int i = 0; i < N; ++i) {
        if (seq[i] != 'V' && seq[i] != 'K') {
            seq[i] = '#';
        }
        pos[static_cast<int>(seq[i])].emplace_back(i);
    }
    
    // Initialize dp array
    memset(dp, 0x3f3f3f3f, sizeof(dp));
    dp[0][0][0][0] = 0;
    
    // Dynamic programming
    for (size_t i = 0; i <= pos[static_cast<int>('V')].size(); ++i) {
        for (size_t j = 0; j <= pos[static_cast<int>('K')].size(); ++j) {
            for (size_t k = 0; k <= pos[static_cast<int>('#')].size(); ++k) {
                for (int l = 0; l < 2; ++l) {
                    auto cost = [&](int x) {
                        int a = lower_bound(pos[static_cast<int>('V')].begin(), pos[static_cast<int>('V')].end(), x) - pos[static_cast<int>('V')].begin();
                        int b = lower_bound(pos[static_cast<int>('K')].begin(), pos[static_cast<int>('K')].end(), x) - pos[static_cast<int>('K')].begin();
                        int c = lower_bound(pos[static_cast<int>('#')].begin(), pos[static_cast<int>('#')].end(), x) - pos[static_cast<int>('#')].begin();
                        return max(0, static_cast<int>(a - i)) + max(0, static_cast<int>(b - j)) + max(0, static_cast<int>(c - k));
                    };
                    
                    if (i + 1 <= pos[static_cast<int>('V')].size()) {
                        upmin(dp[i + 1][j][k][1], dp[i][j][k][l] + cost(pos[static_cast<int>('V')][i]));
                    }
                    if (!l && j + 1 <= pos[static_cast<int>('K')].size()) {
                        upmin(dp[i][j + 1][k][0], dp[i][j][k][l] + cost(pos[static_cast<int>('K')][j]));
                    }
                    if (k + 1 <= pos[static_cast<int>('#')].size()) {
                        upmin(dp[i][j][k + 1][0], dp[i][j][k][l] + cost(pos[static_cast<int>('#')][k]));
                    }
                }
            }
        }
    }
    
    // Get the minimum result
    int result = min(
        dp[pos[static_cast<int>('V')].size()][pos[static_cast<int>('K')].size()][pos[static_cast<int>('#')].size()][0],
        dp[pos[static_cast<int>('V')].size()][pos[static_cast<int>('K')].size()][pos[static_cast<int>('#')].size()][1]
    );
    
    return to_string(result);
}

} // namespace solution8
