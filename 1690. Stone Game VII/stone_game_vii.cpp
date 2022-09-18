#include <iostream>
#include <vector>

#define n_max 1001

/*
    If start and end are the indices for the first 
    and last position in current array of stones
    then i is the size of this current array.

    On every move either the start or end element is picked,
    this recurrence can be solved by only keeping track of a 
    1-dimensional array with the results of the previous iteration, 
    which would be the diagonal of the 2-dimensional array 
    indexed by start and end.

    This array saves the running difference, therefore 
    Bob subtracts his score while Alice adds hers.
 */
int diff[n_max];

/*
    Sums are easy to keep track of by calculating all prefix sums
    
    sum[i:j] = prefixSum[j] - prefixSum[i-1]
 */
int prefixSum[n_max];

class Solution {
public:
    int stoneGameVII(std::vector<int>& stones) {
        int n = stones.size();

        // Fill prefixSums
        prefixSum[0] = stones[0];
        for (int i = 1; i < n; i++)
        {
            prefixSum[i] = prefixSum[i-1] + stones[i];
        }

        // Initialize diff (go until diff[n] because it will be accessed on the first move)
        for (int i = 0; i < n + 1; i++)
        {
            diff[i] = 0;
        }

        // Initialize player (odd n means last is Alice which is player 1 - true)
        bool player = (n % 2);
        
        /* 
            Start with arrays of size 1 and play the moves in reverse.

            The only thing needed is to flip the plus/minus (Alice/Bob)
            contribution to the difference.
         */
        for (int i = 0; i < n; i++)
        {
            // One move
            for (int j = 0; j < n - i; j++)
            {
                int start = j;
                int end = start + i;

                
                int stonesLeft;
                if (i > 0 && start > 0)
                {
                    stonesLeft = prefixSum[end-1] - prefixSum[start - 1];
                }
                else if (i > 0 && start == 0) 
                {
                    stonesLeft = prefixSum[end-1];
                }
                else 
                {
                    stonesLeft = 0;
                }
                
                int stonesRight = prefixSum[end] - prefixSum[start];
                diff[j] = player 
                            ? std::max(diff[j] + stonesLeft, diff[j+1] + stonesRight)
                            : std::min(diff[j] - stonesLeft, diff[j+1] - stonesRight);
            }

            player = !player;
        }

        // The single item of the last diagonal (position [0, n-1])
        return diff[0];
    }
};

int main() 
{
    //std::vector<int> stones = {1, 2, 3};
    //std::vector<int> stones = {5,3,1,4,2};
    std::vector<int> stones = {7,90,5,1,100,10,10,2};
    
    Solution sol;
    std::cout << sol.stoneGameVII(stones) << std::endl;
}