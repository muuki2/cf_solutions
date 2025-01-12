#include <iostream>
#include <string>
using namespace std;

const int MAXN = 100;
const int MOD = (int)1e9 + 7;

signed main() {
    ios::sync_with_stdio(0);
    
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
    cin >> T;
    while (T--) {
        string seq;
        cin >> seq;
        int sum = 0;
        for (char c : seq) {
            sum += c - 'a';
        }
        cout << dp[seq.size()][sum] - 1 << "\n";
    }
    return 0;
} 