#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

struct Student {
    std::string name;
    std::string surname;
    std::vector<int> homework;
    int exam;
    double mean;
    double median;
};

double calculateMean(const std::vector<int> &hm, int exam);
double calculateMedian(std::vector<int> hm, int);

extern std::vector<std::string> vardai;
extern std::vector<std::string> pavardes_vyr;
extern std::vector<std::string> pavardes_mot;


#endif