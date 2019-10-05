//
// Created by StackStomp on 2019-10-05.
//
#include <assert.h>
#include <vector>
#include <map>
#include <queue>

struct SelectedIndex {
    size_t index1;
    size_t index2;
};

class Solution {
public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
        std::vector<std::vector<int>> result;
        int count = 0;

        if (nums1.empty() || nums2.empty()) {
            return result;
        }

        std::map<int, std::queue<SelectedIndex>> sumsToIndexes = Init(nums1, nums2);
        while (!sumsToIndexes.empty() && count++ < k) {
            auto smallest = sumsToIndexes.begin();
            SelectedIndex index = smallest->second.front();
            smallest->second.pop();

            std::vector<int> smallestIndexes;
            smallestIndexes.push_back(nums1[index.index1]);
            smallestIndexes.push_back(nums2[index.index2]);
            result.emplace_back(smallestIndexes);
            if (index.index2 + 1 < nums2.size()) {
                AddIndexes(sumsToIndexes, nums1[index.index1] + nums2[index.index2 + 1],
                        SelectedIndex{index.index1, index.index2 + 1});
            }

            if (smallest->second.empty()) {
                sumsToIndexes.erase(smallest);
            }
        }

        return result;
    }

    void AddIndexes(std::map<int, std::queue<SelectedIndex>>& sumsToIndexes, int sum, SelectedIndex indexes) {
        auto iter = sumsToIndexes.find(sum);
        if (iter == sumsToIndexes.end()) {
            sumsToIndexes[sum] = std::queue<SelectedIndex>();
        }
        sumsToIndexes[sum].push(indexes);
    }

    std::map<int, std::queue<SelectedIndex>> Init(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        std::map<int, std::queue<SelectedIndex>> sumsToIndexes;
        for (size_t i = 0; i < nums1.size(); ++i) {
            int sum = nums1[i] + nums2[0];
            AddIndexes(sumsToIndexes, sum, SelectedIndex{i, 0});
        }
        return sumsToIndexes;
    }
};

void Test()
{
    Solution s;
    std::vector<int> vec1{1,7,11};
    std::vector<int> vec2{2,4,6};
    auto ret = s.kSmallestPairs(vec1, vec2, 3);
    assert(ret.size() == 3);
}