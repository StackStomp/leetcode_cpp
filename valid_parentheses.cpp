//
// Created by StackStomp on 2019-10-04.
//

#include <stack>
#include <string>

bool IsMatch(char a, char b) {
    if (a == '(' && b == ')') {
        return true;
    }
    if (a == '{' && b == '}') {
        return true;
    }
    if (a == '[' && b == ']') {
        return true;
    }
    return false;
}

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> parentheses;
        for (const auto & c : s) {
            if (c == '(' || c == '{' || c == '[') {
                parentheses.push(c);
                continue;
            }
            if (c == ')' || c == '}' || c == ']') {
                if (parentheses.empty()) {
                    return false;
                }
                char p = parentheses.top();
                parentheses.pop();
                if (!IsMatch(p, c)) {
                    return false;
                }
            }
        }

        return parentheses.empty();
    }
};


void Test() {

}