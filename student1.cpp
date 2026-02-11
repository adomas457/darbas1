#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using std::vector;
using std::cout;
using std::cin;
using std::string;
using std::endl;

struct Student {
    string name;
    string surname;
    vector<int> homework;
    int exam;
    double mean;
    double median;
};

Student enterStudent() {
    Student s;
    cout << "Enter name: ";
    cin >> s.name;
    cout << "Enter surname: ";
    cin >> s.surname;

    int grade;
    while (true) {
        cout << "Enter homework grades (-1 to finish): ";
        cin >> grade;
        if (grade == -1) {
            break;
        }
        else if (grade < 0 || grade > 10) {

            cout << "Invalid grade, must be between 0 and 10" << endl;
        } else {
            s.homework.push_back(grade);
        }
    }

    while (true) {
        cout << "Enter exam grade: ";
        cin >> s.exam;
        if (s.exam >= 0 && s.exam <= 10) break;
        cout << "Invalid grade, must be between 0 an 10" << endl;
    }

    return s;
}

double calculateMean(const vector<int> &hm, int exam) {
    if (hm.empty()) return exam*0.6;
    double s = 0;
    for (int g : hm) {
        s += g;
    }
    s /= hm.size();
    return s * 0.4 + 0.6 * exam;
}


double calculateMedian(vector<int> hm, int exam) {
    if (hm.empty()) return exam*0.6;

    sort(hm.begin(), hm.end());
    int pos = hm.size() / 2;
    if (hm.size() % 2 == 0) {
       return (hm[pos-1] + hm[pos]) / 2.0 * 0.4 + exam * 0.6;
    } else{
        return hm[pos] * 0.4 + exam * 0.6;
    }
}


void printStudent(Student stu) {
    cout << std::left << std::setw(15) << stu.surname << std::setw(15) << stu.name << std::setw(10) << std::fixed << std::setprecision(2) << stu.mean << endl;
}

int main() {
    vector<Student> students;
    char comm = 'y';
    while (comm == 'y') {
        Student s = enterStudent();
        s.mean = calculateMean(s.homework, s.exam);
        s.median = calculateMedian(s.homework, s.exam);
        students.push_back(s);
        while (true) {
            cout << "Enter another student? (y/n): ";
            cin >> comm;
            if (comm == 'y' || comm == 'n') {
                break;
            }
        }
    }
    cout << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(10) << "Galutinis (Vid.)" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (const auto &stu : students) {
            printStudent(stu);
    }
    return 0;
}
