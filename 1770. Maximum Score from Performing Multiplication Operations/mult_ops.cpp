#include <iostream>
#include <climits>
#include <vector>
#define M_size 1001

long long int M[M_size][M_size];

class Solution {
public:
    int maximumScore(std::vector<int>& nums, std::vector<int>& multipliers) 
    {
        int n = nums.size();
        int m = multipliers.size();
        long long int ans = INT_MIN;

        // i is the moves made so far
        // it is therefore the position in multipliers vector
        for (int i = m-1; i >= 0; i--)
        {
            for (int start = 0; start <= i; start++)
            {
                int end = std::max(n - 1 - (i - start), start);

                long long int mult_start = multipliers[i] * nums[start];
                long long int mult_end = multipliers[i] * nums[end];
                
                // On the diagonal of first iteration there is no recursion
                if (i == m-1) 
                {
                    M[start][end] = std::max(mult_start, mult_end);
                    ans = std::max(ans, M[start][end]);
                    continue;
                }

                // Off the diagonal, recurse freely
                mult_start += M[start+1][end];
                mult_end += M[start][end-1];
                
                M[start][end] = std::max(mult_start, mult_end);
                ans = std::max(ans, M[start][end]);
            }
        }

        return ans;
    }
};

int main() 
{
    std::vector<int> nums = {-854,-941,10,299,995,-346,294,-393,351,-76,210,897,-651,920,624,969,-629,985,-695,236,637,-901,-817,546,-69,192,-377,251,542,-316,-879,-764,-560,927,629,877,42,381,367,-549,602,139,-312,-281,105,690,-376,-705,-906,85,-608,639,752,770,-139,-601,341,61,969,276,176,-715,-545,471,-170,-126,596,-737,130};
    std::vector<int> multipliers = {83,315,-442,-714,461,920,-737,-93,-818,-760,558,-584,-358,-228,-220};

    //std::vector<int> nums = {1, 2, 3, 4, 5};
    //std::vector<int> multipliers = {1, 2};
    
    Solution sol;
    sol.maximumScore(nums, multipliers);
}