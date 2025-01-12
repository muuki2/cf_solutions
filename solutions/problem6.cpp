#include "problem6.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

namespace solution6 {

string SupermarketShopping::solve(istream &input) {
    // Read input
    int numItems, budget;
    input >> numItems >> budget;
    
    vector<int> prices(numItems);
    vector<int> discounts(numItems);
    vector<int> dependencies(numItems);
    
    // Read item details
    for (int i = 0; i < numItems; ++i) {
        input >> prices[i] >> discounts[i];
        if (i > 0) {
            input >> dependencies[i];
            dependencies[i]--; // Convert to 0-based indexing
        }
    }
    
    // Build dependency graph
    vector<vector<int>> graph(numItems);
    for (int i = 1; i < numItems; ++i) {
        graph[dependencies[i]].push_back(i);
    }
    
    // dp[state][node] stores vectors where:
    // state 0: without using current node's coupon
    // state 1: using current node's coupon
    // state 2: best result combining both states
    vector<vector<int>> dp[3];
    for (int i = 0; i < 3; ++i) {
        dp[i].resize(numItems);
    }
    
    // DFS function to process nodes
    function<void(int)> dfs = [&](int node) {
        // Initialize base cases
        dp[0][node] = {0, prices[node]};  // Not using coupon
        dp[1][node] = {0x3f3f3f3f, prices[node] - discounts[node]};  // Using coupon
        
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
        for (size_t i = 0; i < dp[2][node].size(); ++i) {
            dp[2][node][i] = min(dp[0][node][i], dp[1][node][i]);
        }
    };
    
    // Start DFS from root (item 0)
    dfs(0);
    
    // Find maximum items that can be bought within budget
    auto& final_result = dp[2][0];
    for (int i = final_result.size() - 1; i >= 0; --i) {
        if (final_result[i] <= budget) {
            return to_string(i);
        }
    }
    
    return "0";
}

} // namespace solution6