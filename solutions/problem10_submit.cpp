#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    string sequence;
    cin >> sequence;

    // Convert bombs to '3' for easier processing
    for (char& ch : sequence) {
        if (ch == '*') {
            ch = '3';
        }
    }

    // dp[i][j][k] - ways to fill first i cells, with j bombs in i-1 cell
    // and k bombs in i cell
    vector<vector<vector<int>>> dp(sequence.size() + 1, 
        vector<vector<int>>(4, vector<int>(4, 0)));

    dp[0][0][0] = 1;

    for (size_t i = 0; i < sequence.size(); ++i) {
        for (int prevBombs = 0; prevBombs <= 3; ++prevBombs) {
            for (int currentBombs = 0; currentBombs <= 3; ++currentBombs) {
                // Try all possible values for current cell
                int start = (sequence[i] == '?') ? 0 : sequence[i] - '0';
                int end = (sequence[i] == '?') ? 3 : sequence[i] - '0';
                for (int bombs = start; bombs <= end; ++bombs) {

                    // Count bombs in adjacent cells
                    int adjacentBombs = (prevBombs == 3) + (bombs == 3);

                    // Skip invalid states
                    if (i != 0 && currentBombs < 3 && currentBombs != adjacentBombs) continue;
                    if (i != 0 && bombs == 0 && currentBombs == 3) continue;

                    // Update dp state
                    dp[i + 1][currentBombs][bombs] = (dp[i + 1][currentBombs][bombs] + dp[i][prevBombs][currentBombs]) % MOD;
                }
            }
        }
    }

    // Calculate final answer
    int result = 0;
    for (int i = 0; i <= 3; ++i) {
        for (int j = 0; j <= 3; ++j) {
            if (j < 3 && (i == 3) != j) continue;
            result = (result + dp[sequence.size()][i][j]) % MOD;
        }
    }

    cout << result << "\n";
    return 0;
} 