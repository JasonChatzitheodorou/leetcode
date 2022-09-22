#include <string>
#include <stack>
class Solution {
public:
    std::string reverseWords(std::string s) {
        std::stack<char> reversedWord;
        int pos = 0;
        
        // Takes care of all spaces but not last word
        for (auto &c: s)
        {
            if (c == ' ')  
            {
                while(!reversedWord.empty())
                {
                    char curr = reversedWord.top();
                    s[pos++] = curr;
                    reversedWord.pop();
                }
                s[pos++] = ' ';
            }
            else
                reversedWord.push(c);
        }
        
        // Fixes last word
        while(!reversedWord.empty())
            {
                char curr = reversedWord.top();
                s[pos++] = curr;
                reversedWord.pop();
            }
        
        return s;
    }
};