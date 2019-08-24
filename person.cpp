//
// Created by StackStomp on 2019-08-24.
//

#include <assert.h>
#include <vector>
#include <map>
#include <set>

class PersonSolution {
public:
    int FindThePersonIndex(int personNum, const std::vector<std::pair<int, int>>& trusts)
    {
        std::set<int> notTrustOthers;
        std::map<int, int> indexToTrustedNum;
        for (int i = 0; i < personNum; ++i) {
            notTrustOthers.insert(i + 1);
            indexToTrustedNum[i + 1] = 0;
        }

        for (const auto & trust : trusts) {
            notTrustOthers.erase(trust.first);
            indexToTrustedNum[trust.second] += 1;
        }

        int thePersonIndex = -1;
        for (const auto & notTrust : notTrustOthers) {
            if (indexToTrustedNum[notTrust] == personNum - 1) {
                if (thePersonIndex < 0) {
                    thePersonIndex = notTrust;
                } else {
                    return -1;
                }
            }
        }
        return thePersonIndex;
    }
};

void Test()
{
    PersonSolution s;

    std::vector<std::pair<int, int>> trust;
    trust.emplace_back(std::pair<int, int>(1, 2));

    assert(s.FindThePersonIndex(2, trust) == 2);

    trust.clear();
    trust.emplace_back(std::pair<int, int>(1, 3));
    trust.emplace_back(std::pair<int, int>(2, 3));
    assert(s.FindThePersonIndex(3, trust) == 3);


    trust.clear();
    trust.emplace_back(std::pair<int, int>(1, 3));
    trust.emplace_back(std::pair<int, int>(2, 3));
    trust.emplace_back(std::pair<int, int>(3, 1));
    assert(s.FindThePersonIndex(3, trust) == -1);

    trust.clear();
    trust.emplace_back(std::pair<int, int>(1, 2));
    trust.emplace_back(std::pair<int, int>(2, 3));
    assert(s.FindThePersonIndex(3, trust) == -1);

    trust.clear();
    trust.emplace_back(std::pair<int, int>(1, 3));
    trust.emplace_back(std::pair<int, int>(1, 4));
    trust.emplace_back(std::pair<int, int>(2, 3));
    trust.emplace_back(std::pair<int, int>(2, 4));
    trust.emplace_back(std::pair<int, int>(4, 3));
    assert(s.FindThePersonIndex(4, trust) == 3);

    trust.clear();
    assert(s.FindThePersonIndex(1, trust) == 1);
}