//
// Created by StackStomp on 2019-10-04.
//
#include <iostream>
#include <assert.h>
#include <string>
#include <stack>

enum ElementType {NUMBER, OPERATOR, ELEMENT_TYPE_END};

struct Element {
    int type;
    int value;
};

class Solution {
public:
    int calculate(std::string s) {
        size_t index = 0;
        Element element;
        std::stack<int> numbers;
        std::stack<int> ops;
        while (index < s.size()) {
            index = GetNext(s, index, &element);
            if (element.type == NUMBER) {
                numbers.push(element.value);
            } else if (element.type == OPERATOR) {
                if (element.value == '+' || element.value == '-') {
                    if (!ops.empty() && ops.top() != '(') {
                        CalculateInStack(numbers, ops);
                    }
                    ops.push(element.value);
                } else if (element.value == '(') {
                    ops.push(element.value);
                } else if (element.value == ')') {
                    CalculateInStack(numbers, ops);
                    ops.pop(); // 公式正确，此时pop的一定是(，pop出前面的括号后，再做一次计算
                    CalculateInStack(numbers, ops);
                } else {
                    // 不可能的分支
                }
            } else {
                // 不可能的分支
            }
        }

        CalculateInStack(numbers, ops);
        return numbers.top();
    }

    size_t GetNext(const std::string& s, size_t index, Element * element) {
        element->type = ELEMENT_TYPE_END;
        element->value = 0;
        while (index < s.size()) {
            if (s[index] == ' ') {
                if (element->type == ELEMENT_TYPE_END) {
                    ++index;
                    continue;
                } else {
                    break;
                }
            }

            if (s[index] == '+'
                || s[index] == '-'
                || s[index] == '('
                || s[index] == ')') {
                if (element->type == ELEMENT_TYPE_END) {
                    element->type = OPERATOR;
                    element->value = s[index];
                    return index + 1;
                } else {
                    break;
                }
            }

            if (s[index] >= '0' && s[index] <= '9') {
                element->type = NUMBER;
                element->value = element->value * 10;
                element->value+= s[index] - '0';
                ++index;
                continue;
            }
        }
        return index;
    }

    void CalculateInStack(std::stack<int>& nums, std::stack<int>& operators) {
        int result = nums.top();
        nums.pop();
        while (!operators.empty()) {
            int op = operators.top();
            if (op == '(') {
                break;
            }
            operators.pop();

            int firstNum = nums.top();
            nums.pop();

            if (op == '+') {
                result = firstNum + result;
            } else if (op == '-') {
                result = firstNum - result;
            } else {
                // 不可能出现
            }
        }
        nums.push(result);
    }
};


void TestGetNext1() {
    Solution s;
    Element e;
    auto ret = s.GetNext("1", 0, &e);
    assert (ret == 1);
    assert (e.type == NUMBER);
    assert (e.value == 1);
}

void TestGetNext2() {
    Solution s;
    Element e;
    auto ret = s.GetNext(" 12 + 10", 0, &e);
    assert (ret == 3);
    assert (e.type == NUMBER);
    assert (e.value == 12);
}

void TestGetNext3() {
    Solution s;
    Element e;
    auto ret = s.GetNext(" 12 + 10-5", 3, &e);
    assert (ret == 5);
    assert (e.type == OPERATOR);
    assert (e.value == '+');
}

void TestGetNext4() {
    Solution s;
    Element e;
    auto ret = s.GetNext(" 12 + 10-5", 5, &e);
    assert (ret == 8);
    assert (e.type == NUMBER);
    assert (e.value == 10);
}

void TestGetNext5() {
    Solution s;
    Element e;
    auto ret = s.GetNext(" 12 + 10-5", 8, &e);
    assert (ret == 9);
    assert (e.type == OPERATOR);
    assert (e.value == '-');
}

void TestCalculateInStack1() {
    Solution s;
    std::stack<int> nums;
    std::stack<int> ops;

    nums.push(1);
    nums.push(2);
    ops.push('+');

    s.CalculateInStack(nums, ops);
    assert(nums.size() == 1);
    assert(ops.empty());
    assert(nums.top() == 3);
}

void TestCalculateInStack2() {
    Solution s;
    std::stack<int> nums;
    std::stack<int> ops;

    nums.push(1);
    nums.push(2);
    nums.push(5);
    ops.push('+');
    ops.push('+');

    s.CalculateInStack(nums, ops);
    assert(nums.size() == 1);
    assert(ops.empty());
    assert(nums.top() == 8);
}

void TestCalculateInStack3() {
    Solution s;
    std::stack<int> nums;
    std::stack<int> ops;

    nums.push(1);
    nums.push(2);
    nums.push(5);
    ops.push('+');
    ops.push('(');
    ops.push('+');

    s.CalculateInStack(nums, ops);
    assert(nums.size() == 2);
    assert(ops.size() == 2);

    assert(nums.top() == 7);
    nums.pop();
    assert(nums.top() == 1);

    assert(ops.top() == '(');
    ops.pop();
    assert(ops.top() == '+');
}

void TestCalculate() {
    Solution s;
    assert(s.calculate("1+1") == 2);
    assert(s.calculate("1 + 3 - 2") == 2);
    assert(s.calculate("(1 + 3) - 2") == 2);
    assert(s.calculate("(1+(4+5+2)-3)+(6+8)") == 23);
    assert(s.calculate("10+10") == 20);
}

void Test() {
    TestGetNext1();
    TestGetNext2();
    TestGetNext3();
    TestGetNext4();
    TestGetNext5();
    TestCalculateInStack1();
    TestCalculateInStack2();
    TestCalculateInStack3();

    TestCalculate();
}