#include "student.h"
#include <algorithm>

double calculateMean(const std::vector<int> &hm, int exam) {
    if (hm.empty()) return exam * 0.6;
    double s = 0;
    for (int g : hm) {
        s += g;
    }
    s /= hm.size();
    return s * 0.4 + 0.6 * exam;
}

double calculateMedian(std::vector<int> hm, int exam) {
    if (hm.empty()) return exam * 0.6;

    std::sort(hm.begin(), hm.end());
    int pos = hm.size() / 2;
    if (hm.size() % 2 == 0) {
        return (hm[pos - 1] + hm[pos]) / 2.0 * 0.4 + exam * 0.6;
    } else {
        return hm[pos] * 0.4 + exam * 0.6;
    }
}