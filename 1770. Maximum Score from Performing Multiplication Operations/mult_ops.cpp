#include <iostream>
#include <climits>
#include <vector>
#define M_size 1001

int M[M_size][M_size];
bool valid[M_size][M_size];

class Solution {
public:
    int maximumScore_tabulation(std::vector<int>& nums, std::vector<int>& multipliers) 
    {
        int n = nums.size();
        int m = multipliers.size();

        // i is the moves made so far
        // it is therefore the position in multipliers vector
        for (int i = m-1; i >= 0; i--)
        {
            for (int start = 0; start <= i; start++)
            {
                // end counts in reverse (end = 0 means the last position of nums)
                int end = i - start;
                int end_pos = std::max(n - 1 - end, start);

                int mult_start = multipliers[i] * nums[start];
                int mult_end = multipliers[i] * nums[end_pos];
                
                // On first iteration there is no recursion
                if (i == m-1) 
                {
                    M[start][end] = std::max(mult_start, mult_end);
                    continue;
                }

                // Off the diagonal, recurse freely
                mult_start += M[start+1][end];
                mult_end += M[start][end+1];
                
                M[start][end] = std::max(mult_start, mult_end);
            }
        }

        return M[0][0];
    }

    int maximumScore_memoization(std::vector<int>& nums, std::vector<int>& multipliers, int start = 0, int end = 0)
    {
        // Initialize bool array the first time
        if (start == 0 && end == 0)
        {
            for (int i = 0; i < M_size; i++)
                for (int j = 0; j < M_size; j++)
                    valid[i][j] = false;
        }
        
        int n = nums.size();
        int m = multipliers.size();
        int end_pos = n - 1 - end;

        // If it has been calculated return it
        if (valid[start][end])
        {
            return M[start][end];
        }

        // i can be inferred by the moves of start and end
        int i = start + end;
        
        // If we are at the last position of multipliers no recursion
        int start_sol = 0, end_sol = 0;
        if (i != m-1)
        {
            start_sol = maximumScore_memoization(nums, multipliers, start + 1, end);
            end_sol = maximumScore_memoization(nums, multipliers, start, end + 1);
        }

        M[start][end] = std::max(nums[start] * multipliers[i] + start_sol, nums[end_pos] * multipliers[i] + end_sol);
        valid[start][end] = true;
        return M[start][end];
    }
    void print(int m)
    {
        for (int i = 0; i < m-1; i++)
        {
            for (int j = 0; j < m-1; j++)
                std::cout << M[i][j] << " ";
            
            std::cout << std::endl;
        }
    }
};

int main() 
{
    std::vector<int> nums = {-854,-941,10,299,995,-346,294,-393,351,-76,210,897,-651,920,624,969,-629,985,-695,236,637,-901,-817,546,-69,192,-377,251,542,-316,-879,-764,-560,927,629,877,42,381,367,-549,602,139,-312,-281,105,690,-376,-705,-906,85,-608,639,752,770,-139,-601,341,61,969,276,176,-715,-545,471,-170,-126,596,-737,130};
    std::vector<int> multipliers = {83,315,-442,-714,461,920,-737,-93,-818,-760,558,-584,-358,-228,-220};

    //std::vector<int> nums = {1, 2, 3};
    //std::vector<int> multipliers = {3, 2, 1};
    
    Solution sol;
    std::cout << "Tabulation Matrix" << std::endl;
    std::cout << sol.maximumScore_tabulation(nums, multipliers) << std::endl;
    std::cout << std::endl;
    std::cout << "Memoization Matrix" << std::endl;
    std::cout << sol.maximumScore_memoization(nums, multipliers) << std::endl;
}