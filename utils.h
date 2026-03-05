#ifndef UTILS_H
#define UTILS_H

#include "student.h"
#include <string>
#include <vector>
#include <limits>

int getInt(const std::string &prompt, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());
int utf8_length(std::string s);

Student enterStudent();
Student enterStudent2();
Student enterStudent3(int count);

std::vector<Student> readFile(const std::string& filename);
void printStudent(const Student &stu, int comm);
void printStudent(const Student& stu);

bool rusiuoti(const Student& s1, const Student& s2);

extern int rusiavimas;

#endif