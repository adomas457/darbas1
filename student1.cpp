#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cout;
using std::cin;
using std::string;

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
    cout << "Enter homework grades (-1 to finish): ";
    while (grade != -1) {
        cin >> grade;
        if (grade < 0 || grade > 10) {
            cout << "Invalid grade, must be between 0 and 10" << endl;
        } else {
            s.homework.push_back(grade);
        }
    }

    cout << "Enter exam grade: ";
    while (true) {
        cin >> s.exam;
        if (s.exam >= 0 && s.exam <= 10) break;
        cout << "Invalid grade, must be between 0 an 10" << endl;
    }

    return s;
}

double calculateMean(const vector<int> &hm, int exam) {
    if (hm.empty()) return exam;
    double s = 0;
    for (int g : hm) {
        s += g;
    }
    s /= hm.size();
    return s * 0.4 + 0.6 * exam;
}

int main()
{

    return 0;
}
