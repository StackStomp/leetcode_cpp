//
// Created by StackStomp on 2019-08-24.
//
#include <vector>
#include <set>
#include <map>


bool CompareChild(const std::pair<int, int>& c1, const std::pair<int, int>& c2)
{
    return c1.second - c2.second;
}

class ChildrenQueueSolution {
public:
    std::vector<std::pair<int, int>> Sort(const std::vector<std::pair<int, int>>& children)
    {
        std::map<int, std::vector<std::pair<int, int>>> weightsToChildren;
        for (const auto & child : children) {
            if (weightsToChildren.find(child.first) == weightsToChildren.end()) {
                weightsToChildren[child.first] = std::vector<std::pair<int, int>>();
            }
            weightsToChildren[child.first].push_back(child);
        }

        for (auto & iter : weightsToChildren) {
            std::sort(iter.second.begin(), iter.second.end(), CompareChild);
        }

        std::vector<std::pair<int, int>> sortedChildren;
        for (auto iter = weightsToChildren.rbegin(); iter != weightsToChildren.rend(); ++iter) {
            for (const auto & child : iter->second) {
                sortedChildren.insert(sortedChildren.begin() + child.second, child);
            }
        }

        return sortedChildren;
    }

};

void Test()
{
    ChildrenQueueSolution s;

    std::vector<std::pair<int, int>> cs;
    std::vector<std::pair<int, int>> expected_cs;

    cs.emplace_back(8, 0);
    cs.emplace_back(4, 4);
    cs.emplace_back(8, 1);
    cs.emplace_back(5, 0);
    cs.emplace_back(6, 1);
    cs.emplace_back(5, 2);

    expected_cs.emplace_back(5, 0);
    expected_cs.emplace_back(8, 0);
    expected_cs.emplace_back(5, 2);
    expected_cs.emplace_back(6, 1);
    expected_cs.emplace_back(4, 4);
    expected_cs.emplace_back(8, 1);

    auto ret = s.Sort(cs);
    assert(cs.size() == expected_cs.size());
    for (size_t i = 0; i < expected_cs.size(); ++i) {
        assert(cs[i] == expected_cs[i]);
    }
}