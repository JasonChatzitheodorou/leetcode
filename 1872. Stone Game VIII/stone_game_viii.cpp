#include <iostream>
#include <vector>
#include <climits>

class Solution {
public:
    int stoneGameVIII(std::vector<int>& stones) {
        // The input is unimportant, overwrite it with prefix sums
        for (int i = 1; i < stones.size(); i++)
        {
            stones[i] += stones[i-1];
        }
        
        // Initialize diff so that the last move is always to take both stones (value equal to the whole sum)
        int diff = stones.back();

        // Iterate over possible states
        for (int start = stones.size()-3; start >= 0; start--)
        {
            /* 
                The only interesting moves for Alice are:
                1. The new available move (taking the first two stones)
                2. The optimal move as if we were on (start+1)

                Because all the other moves have already been considered by last iteration
             */
            diff = std::max(stones[start+1] - diff, diff);
        }

        // Return the difference over the whole sequence with Alice playing first
        return diff;
    }
    int stoneGameVIII_slow(std::vector<int>& stones) {
        int n = stones.size();

        // Table of differences, start is the location of the first stone
        int diff[n+1];
        
        // PrefixSums
        int prefixSum[n+1];

        // Calculate prefix sums
        prefixSum[0] = stones[0];
        for (int i = 1; i < n; i++)
        {
            prefixSum[i] = prefixSum[i-1] + stones[i];
        }

        // Initialize diff so that the last move is always to take both stones
        diff[n-2] = prefixSum[n-1];

        // Iterate over possible states
        for (int start = n-3; start >= 0; start--)
        {
            // If Alice plays try to maximize diff
            //? Must look at Bob's optimal moves to decide
            //? Bob's optimal moves lead to a diff that is the negative of Alice
            int alice = INT_MIN;
            for (int i = start+1; i < n; i++)
            {
                int temp = -diff[i] + prefixSum[i];
                if (alice < temp)
                {
                    alice = temp;
                }
            }
            diff[start] = alice;
        }

        // Return the difference over the whole sequence with Alice playing first
        return diff[0];
    }
};

int main() 
{
    //std::vector<int> stones = {-1,2,-3,4,-5};
    //std::vector<int> stones = {-10,-12};
    std::vector<int> stones = {7,-6,5,10,5,-2,-6};
    //std::vector<int> stones = {25,-35,-37,4,34,43,16,-33,0,-17,-31,-42,-42,38,12,-5,-43,-10,-37,12};
    
    Solution sol;
    std::cout << sol.stoneGameVIII(stones) << std::endl;
}