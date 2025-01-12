#ifndef PROBLEM5_H
#define PROBLEM5_H

#include <vector>
#include <string>

namespace solution5 {
    using namespace std;
class CardsAndJoy {
private:
    static const int MAXN = 505;
    static const int MAXK = 11;
    static const int MAXC = 100005;
    
    int n, k;
    vector<int> card_count;
    vector<int> player_count;
    vector<int> joy;
    vector<vector<long long>> dp;

public:
    CardsAndJoy();
    string solve(istream& input);
};

} // namespace solution5

#endif // PROBLEM5_H 