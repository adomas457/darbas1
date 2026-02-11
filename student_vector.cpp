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
    cout << "Vardas: ";
    cin >> s.name;
    cout << "Pavardė: ";
    cin >> s.surname;

    int grade;
    while (true) {
        cout << "Namų darbų įvertinimai (-1 baigti): ";
        cin >> grade;
        if (grade == -1) {
            break;
        }
        else if (grade < 0 || grade > 10) {

            cout << "Įvertinimas turi būti tarp 0 ir 10" << endl;
        } else {
            s.homework.push_back(grade);
        }
    }

    while (true) {
        cout << "Egzamino įvertinimas: ";
        cin >> s.exam;
        if (s.exam >= 0 && s.exam <= 10) break;
        cout << "Įvertinimas turi būti tarp 0 ir 10" << endl;
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


void printStudent(Student stu, int comm) {
    if (comm == 1) {
        cout << std::left << std::setw(15) << stu.surname << std::setw(15) << stu.name << std::setw(10) << std::fixed << std::setprecision(2) << stu.mean << endl;
    } else if (comm == 2) {
        cout << std::left << std::setw(15) << stu.surname << std::setw(15) << stu.name << std::setw(10) << std::fixed << std::setprecision(2) << stu.median << endl;
    }

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
            cout << "Įrašyti dar vieną studentą? (y/n): ";
            cin >> comm;
            if (comm == 'y' || comm == 'n') {
                break;
            }
        }
    }

    int comm2;
    while (true) {
        cout << "Išvesti rezultatus vidurkio ar medianos pavidalu? (1 - vid., 2 - med.): ";
        cin >> comm2;
        if (comm2 == 1 || comm2 == 2 ) {
            break;
        }
    }

    cout << std::left << std::setw(15) << "Pavardė" << std::setw(15) << "Vardas" << std::setw(10) << "Galutinis" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (const auto &stu : students) {
            printStudent(stu, comm2);
    }
    return 0;
}
