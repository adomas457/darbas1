#include <iostream>
#include <vector>
#include <string>
<<<<<<< HEAD
=======
#include <algorithm>
>>>>>>> a6aae34 (pridėta median funkcija)

using std::vector;
using std::cout;
using std::cin;
using std::string;
<<<<<<< HEAD
=======
using std::endl;
>>>>>>> a6aae34 (pridėta median funkcija)

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
<<<<<<< HEAD
    cout << "Enter homework grades (-1 to finish): ";
    while (grade != -1) {
        cin >> grade;
        if (grade < 0 || grade > 10) {
=======
    while (true) {
        cout << "Enter homework grades (-1 to finish): ";
        cin >> grade;
        if (grade == -1) {
            break;
        }
        else if (grade < 0 || grade > 10 && grade) {
>>>>>>> a6aae34 (pridėta median funkcija)
            cout << "Invalid grade, must be between 0 and 10" << endl;
        } else {
            s.homework.push_back(grade);
        }
    }

<<<<<<< HEAD
    cout << "Enter exam grade: ";
    while (true) {
=======
    while (true) {
        cout << "Enter exam grade: ";
>>>>>>> a6aae34 (pridėta median funkcija)
        cin >> s.exam;
        if (s.exam >= 0 && s.exam <= 10) break;
        cout << "Invalid grade, must be between 0 an 10" << endl;
    }

    return s;
}

double calculateMean(const vector<int> &hm, int exam) {
<<<<<<< HEAD
    if (hm.empty()) return exam;
=======
    if (hm.empty()) return exam*0.6;
>>>>>>> a6aae34 (pridėta median funkcija)
    double s = 0;
    for (int g : hm) {
        s += g;
    }
    s /= hm.size();
    return s * 0.4 + 0.6 * exam;
}

<<<<<<< HEAD
int main()
{

=======
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


int main()
{


>>>>>>> a6aae34 (pridėta median funkcija)
    return 0;
}
