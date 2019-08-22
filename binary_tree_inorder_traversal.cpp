//
// Created by StackStomp on 2019-08-22.
//
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<int> result;
        if (root != nullptr) {
            InorderTraversalLoop(root, result);
        }
        return result;
    }

private:
    void InorderTraversalRecursively(const TreeNode* node, vector<int>& vec)
    {
        if (node->left != nullptr) {
            InorderTraversalRecursively(node->left, vec);
        }
        vec.push_back(node->val);
        if (node->right != nullptr) {
            InorderTraversalRecursively(node->right, vec);
        }
    }

    void InorderTraversalLoop(const TreeNode* node, vector<int>& vec)
    {
        stack<const TreeNode*> nodes;
        const TreeNode* currentNode = node;
        bool leftLooped = false;
        while (currentNode != nullptr) {
            if (currentNode->left != nullptr && !leftLooped) {
                nodes.push(currentNode);
                currentNode = currentNode->left;
                leftLooped = false;
                continue;
            }

            vec.push_back(currentNode->val);

            if (currentNode->right != nullptr) {
                currentNode = currentNode->right;
                leftLooped = false;
                continue;
            }

            if (nodes.empty()) {
                currentNode = nullptr;
            } else {
                currentNode = nodes.top();
                nodes.pop();
                leftLooped = true;
            }
        }
    }
};



void Test()
{
    TreeNode n1(10), n2(9), n3(11), n4(8), n5(7);
    n1.right = &n3;
    n1.left = &n4;


    n4.left = &n5;
    n4.right = &n2;

    Solution s;
    auto result = s.inorderTraversal(&n1);

    for (int & iter : result) {
        cout << iter << ", ";
    }
}