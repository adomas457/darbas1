#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<string> vardai = {"Jonas", "Adomas", "Vytautas", "Juozas", "Matas", "Mantas", "Dominykas", "Algirdas", "Gediminas", "Mindaugas", 
    "Laura", "Eglė", "Edita", "Gabija", "Justina", "Aistė", "Rasa", "Gintarė", "Rūta", "Lina"};
vector<string> pavardes_vyr = {"Pavardenis1", "Pavardenis2", "Pavardenis3", "Pavardenis4", "Pavardenis5", 
    "Pavardenis6", "Pavardenis7", "Pavardenis8", "Pavardenis9", "Pavardenis10"
};
vector<string> pavardes_mot = {"Pavardenaitė1", "Pavardenaitė2", "Pavardenaitė3", "Pavardenaitė4", "Pavardenaitė5",
    "Pavardenaitė6", "Pavardenaitė7", "Pavardenaitė8", "Pavardenaitė9", "Pavardenaitė10"
};

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

Student enterStudent2() {
    Student s;
    cout << "Vardas: ";
    cin >> s.name;
    cout << "Pavardė: ";
    cin >> s.surname;

    int count;
    cout << "Atsitiktinai sugeneruotų namų darbų įvertinimų skaičius: ";
    while (true) {
        if (!(cin >> count)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Įvertinimų skaičius turi būti sveikasis skaičius ne mažesnis už 0: ";
        } else if (count < 0) {
            cout << "Įvertinimas turi būti sveikasis skaičius tarp 0 ir 10: ";
        } else {
            break;
        }
    }

    for (int i = 0; i < count; i++) {
        s.homework.push_back(rand() % 11);
    }

    s.exam = rand() % 11;

    return s;
}

Student enterStudent3(int hm_count) {
    
    Student s;
    s.name = vardai[rand() % vardai.size()];
    if (s.name.back() == 's') {
        s.surname = pavardes_vyr[rand() % pavardes_vyr.size()];
    } else {
        s.surname = pavardes_mot[rand() % pavardes_mot.size()];
    }

    for (int j = 0; j < hm_count; j++) {
        s.homework.push_back(rand() % 11);
    }

    s.exam = rand() % 11;

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
        cout << left << setw(25) << stu.surname << setw(20) << stu.name << setw(15) << fixed << setprecision(2) << stu.mean << endl;
    } else if (comm == 2) {
        cout << left << setw(25) << stu.surname << setw(120) << stu.name << setw(15) << fixed << setprecision(2) << stu.median << endl;
    }

}

int main() {
    vector<Student> students;
    int menu_choice;
    srand(time(nullptr));
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
        } else if (menu_choice == 2) {
            string comm = "y";
            while (comm == "y") {
                Student s = enterStudent2();
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
        } else if (menu_choice == 3) {
            int student_count;
            cout << "Atsitiktinai sugeneruotų studentų skaičius: ";
            while (true) {
                if (!(cin >> student_count)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Studentų skaičius turi būti sveikasis skaičius ne mažesnis už 1: ";
                } else if (student_count < 1) {
                    cout << "Studentų skaičius turi būti sveikasis skaičius ne mažesnis už 1: ";
                } else {
                    break;
                }
            }

            int hm_count;
            cout << "Atsitiktinai sugeneruotų namų darbų įvertinimų skaičius: ";
            while (true) {
                if (!(cin >> hm_count)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Įvertinimų skaičius turi būti sveikasis skaičius ne mažesnis už 0: ";
                } else if (hm_count < 0) {
                    cout << "Įvertinimų skaičius turi būti sveikasis skaičius ne mažesnis už 0: ";
                } else {
                    break;
                }
            }

            for (int i = 0; i < student_count; i++) {
                Student s = enterStudent3(hm_count);
                s.mean = calculateMean(s.homework, s.exam);
                s.median = calculateMedian(s.homework, s.exam);
                students.push_back(s);
            }

        } else {
            break;
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

        cout << left << setw(25) << "Pavardė" << setw(20) << "Vardas" << setw(15) << "Galutinis" << endl;
        cout << "-------------------------------------------------------------" << endl;
        for (const auto &stu : students) {
                printStudent(stu, isvedimas);
        }
        cout << "-------------------------------------------------------------" << endl;
        students.clear();

    }


    return 0;
}
