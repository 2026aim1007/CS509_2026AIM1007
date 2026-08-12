#include "testing_utils.h"
#include <fstream>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

bool compareFilesWithEscape(const string& p1, const string& p2) {
    ifstream f1(p1), f2(p2);
    if (!f1.is_open() || !f2.is_open()) return false;
    string w1, w2;
    while (f1 >> w1) {
        if (w1 == METRICS_ESCAPE_TOKEN) {
            return true;
        }
        if (!(f2 >> w2) || w1 != w2) {
            return false;
        }
    }
    if (f2 >> w2 && w2 != METRICS_ESCAPE_TOKEN) return false;
    return true;
}

double measureAverageExecutionTime(std::function<void()> algoCall, int iterations) {
    double totalTime = 0.0;
    for (int i = 0; i < iterations; i++) {
        auto start = high_resolution_clock::now();
        algoCall();
        auto stop = high_resolution_clock::now();
        totalTime += duration<double, std::milli>(stop - start).count();
    }
    return totalTime / iterations;
}