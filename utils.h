#ifndef UTILS_H
#define UTILS_H

#include "student.h"
#include <string>
#include <vector>
#include <limits>
#include <iostream>

int getInt(const std::string &prompt, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());
int utf8_length(std::string s);

std::vector<Student> readFile(const std::string& filename);

void generateFile(const std::string &filename, int n, int nd);

bool rusiuoti(const Student& s1, const Student& s2);
void splitStudent(std::vector<Student> &stud, const std::string &geri, const std::string &blogi);

extern int rusiavimas;

#endif