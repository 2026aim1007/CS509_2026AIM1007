#ifndef TESTING_UTILS_H
#define TESTING_UTILS_H

#include <string>
#include <functional>

const std::string METRICS_ESCAPE_TOKEN = "===METRICS===";
bool compareFilesWithEscape(const std::string& p1, const std::string& p2);
double measureAverageExecutionTime(std::function<void()> algoCall, int iterations);

#endif