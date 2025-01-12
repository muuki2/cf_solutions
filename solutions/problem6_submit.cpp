#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read input
    int n, b;
    cin >> n >> b;
    
    vector<int> c(n);  // prices
    vector<int> d(n);  // discounts
    vector<int> x(n);  // dependencies
    
    // Read item details
    for (int i = 0; i < n; ++i) {
        cin >> c[i] >> d[i];
        if (i > 0) {
            cin >> x[i];
            x[i]--; // Convert to 0-based indexing
        }
    }
    
    // Build dependency graph
    vector<vector<int>> graph(n);
    for (int i = 1; i < n; ++i) {
        graph[x[i]].push_back(i);
    }
    
    // dp[state][node] stores vectors where:
    // state 0: without using current node's coupon
    // state 1: using current node's coupon
    // state 2: best result combining both states
    vector<vector<int>> dp[3];
    for (int i = 0; i < 3; ++i) {
        dp[i].resize(n);
    }
    
    // DFS function to process nodes
    function<void(int)> dfs = [&](int node) {
        // Initialize base cases
        dp[0][node] = {0, c[node]};  // Not using coupon
        dp[1][node] = {0x3f3f3f3f, c[node] - d[node]};  // Using coupon
        
        // Process all dependent items
        for (int child : graph[node]) {
            dfs(child);
            
            // Merge function to combine results
            auto merge = [](const vector<int>& a, const vector<int>& b) {
                vector<int> result(a.size() + b.size() - 1, 0x3f3f3f3f);
                for (size_t i = 0; i < a.size(); ++i) {
                    for (size_t j = 0; j < b.size(); ++j) {
                        result[i + j] = min(result[i + j], a[i] + b[j]);
                    }
                }
                return result;
            };
            
            // Merge results for both states
            dp[0][node] = merge(dp[0][node], dp[0][child]);
            dp[1][node] = merge(dp[1][node], dp[2][child]);
        }
        
        // Compute best result
        dp[2][node].resize(dp[0][node].size());
        for (int i = 0; i < dp[2][node].size(); ++i) {
            dp[2][node][i] = min(dp[0][node][i], dp[1][node][i]);
        }
    };
    
    // Start DFS from root (item 0)
    dfs(0);
    
    // Find maximum items that can be bought within budget
    auto& final_result = dp[2][0];
    for (int i = final_result.size() - 1; i >= 0; --i) {
        if (final_result[i] <= b) {
            cout << i << "\n";
            return 0;
        }
    }
    
    cout << "0\n";
    return 0;
} 