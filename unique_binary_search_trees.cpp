//
// Created by StackStomp on 2019-08-22.
//
#include <iostream>
#include <map>

using namespace std;

class Solution {
public:

    int numTrees(int n)
    {
        if (n == 0) {
            return 0;
        }
        return ChoicesNumRecursively(n);
    }

    int ChoicesNumRecursively(int n)
    {
        auto iter = nodeNumToChoiceNum_.find(n);
        if (iter != nodeNumToChoiceNum_.end()) {
            return iter->second;
        }

        int num = 0, nodeNum;
        for (int i = 0; i < n; ++i) {
            nodeNum = i;
            int leftNum = nodeNum == 0 ? 1 : ChoicesNumRecursively(nodeNum);

            nodeNum = n - i - 1;
            int rightNum = nodeNum == 0 ? 1 : ChoicesNumRecursively(nodeNum);

            num += leftNum * rightNum;
        }
        nodeNumToChoiceNum_[n] = num;
        return num;
    }
private:
    map<int, int> nodeNumToChoiceNum_;
};

void Test()
{
    Solution s;
    for (int i = 0; i < 50; ++i) {
        cout << i << ": " << s.numTrees(i) << endl;
    }
}