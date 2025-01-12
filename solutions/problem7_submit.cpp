#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Helper function to update maximum value
// Returns 1 if the value was updated, 0 otherwise
template<class T1, class T2>
int updateMax(T1& current, T2 newValue) {
    if (current >= newValue) return 0;
    current = newValue;
    return 1;
}

const int MAX_LENGTH = (int)1e5;

string number;

// dp[pos][remainder] = maximum length of beautiful number ending at pos with remainder
int dp[MAX_LENGTH + 1][3];
// choice[pos][remainder] = whether we took the digit at pos-1 for this state
int choice[MAX_LENGTH + 1][3];

signed main() {
    ios::sync_with_stdio(0);
    
    // Read input
    cin >> number;
    
    // Initialize dp array with negative infinity
    for (size_t pos = 0; pos <= number.size(); ++pos) {
        for (int remainder = 0; remainder < 3; ++remainder) {
            dp[pos][remainder] = -(int)1e8;
        }
    }
    
    // Fill dp array
    for (size_t pos = 0; pos < number.size(); ++pos) {
        // Try using current digit as first digit (if it's not zero)
        if (number[pos] != '0' && updateMax(dp[pos + 1][(number[pos] - '0') % 3], 1)) {
            choice[pos + 1][(number[pos] - '0') % 3] = 1;
        }
        
        // For each previous remainder
        for (int remainder = 0; remainder < 3; ++remainder) {
            if (dp[pos][remainder] == -(int)1e8) continue;
            
            // Take current digit
            if (updateMax(dp[pos + 1][(remainder * 10 + number[pos] - '0') % 3], dp[pos][remainder] + 1)) {
                choice[pos + 1][(remainder * 10 + number[pos] - '0') % 3] = 1;
            }
            
            // Don't take current digit
            if (updateMax(dp[pos + 1][remainder], dp[pos][remainder])) {
                choice[pos + 1][remainder] = 0;
            }
        }
    }
    
    // Check if no beautiful number exists
    if (dp[number.size()][0] <= 0) {
        // Check if we can use single 0
        for (size_t i = 0; i < number.size(); ++i) {
            if (number[i] == '0') {
                cout << "0\n";
                exit(0);
            }
        }
        cout << -1 << "\n";
        exit(0);
    }
    
    // Reconstruct the answer
    string result;
    for (int pos = number.size(), remainder = 0; pos; --pos) {
        if (choice[pos][remainder]) {
            result += number[pos - 1];
            remainder = (remainder - number[pos - 1] + '0' + 33) % 3;
            (remainder *= 10) %= 3;
        }
    }
    
    reverse(result.begin(), result.end());
    cout << result << "\n";
    
    return 0;
} 