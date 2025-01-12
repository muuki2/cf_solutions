#include "problem5.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

namespace solution5 {

CardsAndJoy::CardsAndJoy() : 
    card_count(MAXC),
    player_count(MAXC),
    dp(MAXN, vector<long long>(MAXN * MAXK, -1)) {
}

string CardsAndJoy::solve(istream& input) {
    // Read input
    input >> n >> k;
    
    // Read cards and count occurrences
    fill(card_count.begin(), card_count.end(), 0);
    for(int i = 0; i < n * k; i++) {
        int x;
        input >> x;
        card_count[x]++;
    }
    
    // Read favorite numbers and count players
    fill(player_count.begin(), player_count.end(), 0);
    for(int i = 0; i < n; i++) {
        int x;
        input >> x;
        player_count[x]++;
    }
    
    // Read joy values (0-based indexing)
    joy.resize(k + 1, 0);
    for(int i = 1; i <= k; i++) {
        input >> joy[i];
    }
    
    // Initialize dp array
    for(auto& row : dp) {
        fill(row.begin(), row.end(), -1);
    }
    dp[0][0] = 0;
    
    // For each player count
    for(int i = 0; i < n; i++) {
        // For each number of cards used so far
        for(int j = 0; j <= n * k; j++) {
            if(dp[i][j] == -1) continue;
            
            // Try giving different numbers of cards to the next player
            for(int cards = 0; cards <= min(k, j); cards++) {
                dp[i + 1][j] = max(dp[i + 1][j], 
                                 dp[i][j] + joy[cards]);
            }
        }
    }
    
    // Calculate final answer
    long long answer = 0;
    for(int num = 0; num < MAXC; num++) {
        if(player_count[num] > 0) {
            // For each number that appears as a favorite
            int available = min(card_count[num], player_count[num] * k);
            int players = player_count[num];
            
            // Try all possible ways to distribute these cards
            vector<vector<long long>> local_dp(players + 1, vector<long long>(available + 1, -1));
            local_dp[0][0] = 0;
            
            for(int p = 0; p < players; p++) {
                for(int used = 0; used <= available; used++) {
                    if(local_dp[p][used] == -1) continue;
                    
                    for(int take = 0; take <= min(k, available - used); take++) {
                        local_dp[p + 1][used + take] = max(local_dp[p + 1][used + take],
                                                         local_dp[p][used] + joy[take]);
                    }
                }
            }
            
            // Find maximum joy for this number
            long long max_joy = 0;
            for(int used = 0; used <= available; used++) {
                max_joy = max(max_joy, local_dp[players][used]);
            }
            answer += max_joy;
        }
    }
    
    return to_string(answer);
}

} // namespace solution5 