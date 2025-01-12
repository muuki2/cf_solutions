#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 505;
const int MAXK = 11;
const int MAXC = 100005;

class CardsAndJoy {
private:
    int n, k;
    vector<int> card_count;
    vector<int> player_count;
    vector<int> joy;

public:
    CardsAndJoy() : 
        card_count(MAXC),
        player_count(MAXC) {
    }

    void solve() {
        cin >> n >> k;
        
        fill(card_count.begin(), card_count.end(), 0);
        for(int i = 0; i < n * k; i++) {
            int x;
            cin >> x;
            card_count[x]++;
        }
        
        fill(player_count.begin(), player_count.end(), 0);
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            player_count[x]++;
        }
        
        joy.resize(k + 1, 0);
        for(int i = 1; i <= k; i++) {
            cin >> joy[i];
        }
        
        long long answer = 0;
        for(int num = 0; num < MAXC; num++) {
            if(player_count[num] > 0) {
                // For each number that appears as a favorite
                int available = min(card_count[num], player_count[num] * k);
                int players = player_count[num];
                
                // Try all possible ways to distribute these cards
                vector<vector<long long>> dp(players + 1, vector<long long>(available + 1, -1));
                dp[0][0] = 0;
                
                for(int p = 0; p < players; p++) {
                    for(int used = 0; used <= available; used++) {
                        if(dp[p][used] == -1) continue;
                        
                        for(int take = 0; take <= min(k, available - used); take++) {
                            dp[p + 1][used + take] = max(dp[p + 1][used + take],
                                                       dp[p][used] + joy[take]);
                        }
                    }
                }
                
                // Find maximum joy for this number
                long long max_joy = 0;
                for(int used = 0; used <= available; used++) {
                    max_joy = max(max_joy, dp[players][used]);
                }
                answer += max_joy;
            }
        }
        
        cout << answer << "\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    CardsAndJoy solution;
    solution.solve();
    
    return 0;
} 