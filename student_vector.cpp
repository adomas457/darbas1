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
    "Laura", "Inga", "Edita", "Gabija", "Justina", "Daiva", "Rasa", "Jolita", "Asta", "Lina"};
vector<string> pavardes_vyr = {"Pavardenis1", "Pavardenis2", "Pavardenis3", "Pavardenis4", "Pavardenis5", 
    "Pavardenis6", "Pavardenis7", "Pavardenis8", "Pavardenis9", "Pavardenis10"
};
vector<string> pavardes_mot = {"Pavardenaite1", "Pavardenaite2", "Pavardenaite3", "Pavardenaite4", "Pavardenaite5",
    "Pavardenaite6", "Pavardenaite7", "Pavardenaite8", "Pavardenaite9", "Pavardenaite10"
};

struct Student {
    string name;
    string surname;
    vector<int> homework;
    int exam;
    double mean;
    double median;
};

int getInt(string prompt, int min = numeric_limits<int>::min(), int max= numeric_limits<int>::max()) {
    int num;

    while (true) {
        cout << prompt;
        if (cin >> num && num >= min && num <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Įveskite sveikąjį skaičių tarp " << min << " ir " << max << "." << endl;
    }

    return num;
}

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
                cout << "Įveskite sveikąjį skaičių tarp 0 ir 10: ";
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Įveskite sveikąjį skaičių tarp 0 ir 10: ";
        }
    }

    s.exam = getInt("Įveskite egzamino įvertinimą: ", 0, 10);

    return s;
}

Student enterStudent2() {
    Student s;
    cout << "Vardas: ";
    cin >> s.name;
    cout << "Pavardė: ";
    cin >> s.surname;

    int count = getInt("Atsitiktinai sugeneruotų namų darbų įvertinimų skaičius: ", 0);

    for (int i = 0; i < count; i++) {
        s.homework.push_back(rand() % 11);
    }

    s.exam = rand() % 11;

    return s;
}

Student enterStudent3(int count) {
    
    Student s;
    s.name = vardai[rand() % vardai.size()];
    if (s.name.back() == 's') {
        s.surname = pavardes_vyr[rand() % pavardes_vyr.size()];
    } else {
        s.surname = pavardes_mot[rand() % pavardes_mot.size()];
    }

    for (int j = 0; j < count; j++) {
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
        cout << left << setw(20) << stu.surname << setw(15) << left <<  stu.name << left <<  setw(10) << fixed << setprecision(2) << stu.mean << endl;
    } else if (comm == 2) {
        cout << left << setw(20) << stu.surname << setw(15) << left <<  stu.name << left <<  setw(10) << fixed << setprecision(2) << stu.median << endl;
    }

}

int main() {
    vector<Student> students;
    srand(time(nullptr));
    while (true) {
        cout << "1 - Įrašyti studentus ir pažymius ranka" << endl;
        cout << "2 - Generuoti random pažymius" << endl;
        cout << "3 - Generuoti random studentus ir pažymius" << endl;
        cout << "4 - Exit" << endl;
        int choice = getInt("Veiksmas: ", 1, 4);

        if (choice == 1 || choice == 2) {
            while (true) {
                Student s;
                if (choice == 1) s = enterStudent();
                else s = enterStudent2();
                s.mean = calculateMean(s.homework, s.exam);
                s.median = calculateMedian(s.homework, s.exam);
                students.push_back(s);
                string comm;
                cout << "Įrašyti dar vieną studentą? (y/n): ";
                cin >> comm;
                if (comm != "y") break;
            }

        } else if (choice == 3) {
            int student_count = getInt("Atsitiktinai sugeneruotų studentų skaičius: ", 1);
            int count = getInt("Atsitiktinai sugeneruotų namų darbų įvertinimų skaičius: ", 0);
            for (int i = 0; i < student_count; i++) {
                Student s = enterStudent3(count);
                s.mean = calculateMean(s.homework, s.exam);
                s.median = calculateMedian(s.homework, s.exam);
                students.push_back(s);
            }

        } else {
            break;
        } 

        int isvedimas = getInt("Išvesti rezultatus vidurkio ar medianos pavidalu? (1 - vid., 2 - med.): ", 1, 2);
        cout << left << setw(20) << "Pavardė" << left << setw(15) << "Vardas" << left << setw(10) << "Galutinis" << endl;
        cout << "-------------------------------------------------------------" << endl;
        for (const auto &stu : students) {
                printStudent(stu, isvedimas);
        }
        cout << "-------------------------------------------------------------" << endl;
        students.clear();

    }


    return 0;
}
