#include <iostream>
#include <vector>

class Solution 
{
public:
    std::vector<int> sumEvenAfterQueries(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
        auto ans = std::vector<int>();

        // Initialize sum of evens
        int evenSum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] % 2 == 0)
            {
                evenSum += nums[i];
            }
        }

        for (int i = 0; i < queries.size(); i++)
        {
            auto q = queries[i];
            int val = q[0];
            int index = q[1];

            int numsParity = std::abs(nums[index]) % 2;
            int valParity = std::abs(val) % 2;

            if (numsParity == 0 && valParity == 0)
            {
                evenSum += val;
            }
            else if (numsParity == 1 && valParity == 1)
            {
                evenSum += nums[index] + val;
            }
            else if (numsParity == 0 && valParity == 1)
            {
                evenSum -= nums[index];
            }
            else ;

            // Write to solution
            ans.push_back(evenSum); 
            
            // Update nums
            nums[index] += val;
        }

        return ans;
    }
};

int main()
{
    //std::vector<int> nums = {1,2,3,4};
    //std::vector<std::vector<int>> queries = {{1,0},{-3,1},{-4,0},{2,3}};

    std::vector<int> nums = {-10,2,-4,5,-3,3};
    std::vector<std::vector<int>> queries = {{-4,2},{9,0},{-8,1},{5,4},{1,4},{9,0}};

    Solution sol;
    sol.sumEvenAfterQueries(nums, queries);
}
