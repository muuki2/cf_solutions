#include "problem1.h"
#include <vector>
#include <iostream>

namespace solution1 {

const int MAXN = 100;
const int MOD = (int)1e9 + 7;

string Cipher::solve(istream& input) {
    int dp[MAXN + 1][25 * MAXN + 1] = {{0}};
    dp[0][0] = 1;
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j <= 25 * i; ++j) {
            for (int k = 0; k < 26; ++k) {
                (dp[i + 1][j + k] += dp[i][j]) %= MOD;
            }
        }
    }

    int T;
    input >> T;
    std::string result;
    for (int ti = 0; ti < T; ++ti) {
        std::string seq;
        input >> seq;
        int sum = 0;
        for (char c : seq) {
            sum += c - 'a';
        }
        result += std::to_string(dp[seq.size()][sum] - 1) + "\n";
    }
    return result;
}

} // namespace solution1 