//
// Created by StackStomp on 2019-08-24.
//
#include <vector>

class TuningSolution {
public:
    int tuning(const std::vector<int>& signals)
    {
        if (signals.size() < 2) {
            return 0;
        }

        int stepOdd = turningEvenRecursively(signals, 0, signals[0], false);
        int stepEven = turningEvenRecursively(signals, 0, signals[0], true);
        return stepOdd < stepEven ? stepOdd : stepEven;
    }

private:
    // 不知道是否要求信号值大于0，假设不要求
    // 未考虑边界值
    int turningEvenRecursively(const std::vector<int>& signals, size_t currentIndex, int currentSignal, bool high)
    {
        if (currentIndex + 1 >= signals.size()) {
            return 0;
        }
        int currentIndexStep = 0;
        int nextValue = signals[currentIndex + 1];
        if (high) {
            if (currentSignal <= nextValue) {
                currentIndexStep = nextValue - currentSignal + 1;
            }
        } else {
            if (currentSignal >= nextValue) {
                currentIndexStep = currentSignal - nextValue + 1;
            }
        }

        if (currentIndexStep == 0) {
            return turningEvenRecursively(signals, currentIndex + 1, signals[currentIndex + 1], !high);
        }

        int minNextTotalSteps = 0;
        for (int step = 0; step < currentIndexStep; ++step) {
            if (high) {
                nextValue = signals[currentIndex + 1] - (currentIndexStep - step);
            } else {
                nextValue = signals[currentIndex + 1] + (currentIndexStep - step);
            }
            int totalNextSteps = turningEvenRecursively(signals, currentIndex + 1, nextValue, !high);
            if (step == 0) {
                minNextTotalSteps = totalNextSteps;
            } else {
                int totalSteps = step + totalNextSteps;
                if (minNextTotalSteps > totalSteps) {
                    minNextTotalSteps = totalSteps;
                }
            }
        }

        return minNextTotalSteps + currentIndexStep;
    }
};

void Test()
{
    TuningSolution s;

    std::vector<int> ss;
    ss.push_back(1);
    ss.push_back(2);
    ss.push_back(3);
    assert(2 == s.tuning(ss));

    ss.clear();
    ss.push_back(9);
    ss.push_back(6);
    ss.push_back(1);
    ss.push_back(6);
    ss.push_back(2);
    assert(4 == s.tuning(ss));
}