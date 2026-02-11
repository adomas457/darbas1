#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

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
    cout << "Namų darbų įvertinimai (-1 baigti): ";
    while (true) {
        if (cin >> grade) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (grade == -1) {
                break;
            } else if (grade >= 0 && grade <= 10) {
                s.homework.push_back(grade);
                cout << "Namų darbų įvertinimai (-1 baigti): ";
            } else {
                cout << "Įvertinimas turi būti sveikasis skaičius tarp 0 ir 10: ";
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Įvertinimas turi būti sveikasis skaičius tarp 0 ir 10: ";
        }
    }
    cout << "Egzamino įvertinimas: ";
    while (true) {
        if (cin >> s.exam) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (s.exam >=0 && s.exam <= 10) {
                break;
            }
            cout << "Įvertinimas turi būti sveikasis skaičius tarp 0 ir 10: ";
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Įvertinimas turi būti sveikasis skaičius tarp 0 ir 10: ";
        }

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
        cout << left << setw(15) << stu.surname << setw(15) << stu.name << setw(10) << fixed << setprecision(2) << stu.mean << endl;
    } else if (comm == 2) {
        cout << left << setw(15) << stu.surname << setw(15) << stu.name << setw(10) << fixed << setprecision(2) << stu.median << endl;
    }

}

int main() {
    vector<Student> students;
    int menu_choice;
    while (true) {
        cout << "1 - Įrašyti studentus ir pažymius ranka" << endl;
        cout << "2 - Generuoti random pažymius" << endl;
        cout << "3 - Generuoti random studentus ir pažymius" << endl;
        cout << "4 - Exit" << endl;
        cout << "Veiksmas: ";

        if (!(cin >> menu_choice)) {        
            cin.clear();                 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Įveskite sveikąjį skaičių tarp 1 ir 4." << endl;
            continue;                     
        }

        if (menu_choice < 1 || menu_choice > 4) {  
            cout << "Įveskite sveikąjį skaičių tarp 1 ir 4." << endl;
            continue; 
        }

        if (menu_choice == 1) {
            string comm = "y";
            while (comm == "y") {
                Student s = enterStudent();
                s.mean = calculateMean(s.homework, s.exam);
                s.median = calculateMedian(s.homework, s.exam);
                students.push_back(s);
                while (true) {
                    cout << "Įrašyti dar vieną studentą? (y/n): ";
                    cin >> comm;
                    if (comm == "y" || comm == "n") {
                        break;
                    }
                }
            }
        } 


        int isvedimas;
        while (true) {
            cout << "Išvesti rezultatus vidurkio ar medianos pavidalu? (1 - vid., 2 - med.): ";
            if (cin>>isvedimas) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (isvedimas == 1 || isvedimas == 2 ) {
                    break;
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        
        }

        cout << left << setw(15) << "Pavardė" << setw(15) << "Vardas" << setw(10) << "Galutinis" << endl;
        cout << "-------------------------------------------------------------" << endl;
        for (const auto &stu : students) {
                printStudent(stu, isvedimas);
        }

        students.clear();

    }


    return 0;
}
