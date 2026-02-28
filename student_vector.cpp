#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

std::vector<std::string> vardai = {"Jonas", "Adomas", "Vytautas", "Juozas", "Matas", "Mantas", "Dominykas", "Algirdas", "Gediminas", "Mindaugas", 
    "Laura", "Inga", "Edita", "Gabija", "Justina", "Daiva", "Rasa", "Jolita", "Asta", "Lina"};
std::vector<std::string> pavardes_vyr = {"Pavardenis1", "Pavardenis2", "Pavardenis3", "Pavardenis4", "Pavardenis5", 
    "Pavardenis6", "Pavardenis7", "Pavardenis8", "Pavardenis9", "Pavardenis10"};
std::vector<std::string> pavardes_mot = {"Pavardenaitė1", "Pavardenaitė2", "Pavardenaitė3", "Pavardenaitė4", "Pavardenaitė5",
    "Pavardenaitė6", "Pavardenaitė7", "Pavardenaitė8", "Pavardenaitė9", "Pavardenaitė10"};

struct Student {
    std::string name;
    std::string surname;
    std::vector<int> homework;
    int exam;
    double mean;
    double median;
};

int getInt(std::string prompt, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()) {
    int num;

    while (true) {
        std::cout << prompt;
        if (std::cin >> num && num >= min && num <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Įveskite sveikąjį skaičių tarp " << min << " ir " << max << "." << std::endl;
    }

    return num;
}

int utf8_length(std::string s) {
    int length = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) length++;
    }
    return length;
}

Student enterStudent() {
    Student s;
    std::cout << "Vardas: ";
    std::cin >> s.name;
    std::cout << "Pavardė: ";
    std::cin >> s.surname;

    int grade;
    std::cout << "Namų darbų įvertinimai (-1 baigti): ";
    while (true) {
        if (std::cin >> grade) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (grade == -1) {
                break;
            } else if (grade >= 0 && grade <= 10) {
                s.homework.push_back(grade);
                std::cout << "Namų darbų įvertinimai (-1 baigti): ";
            } else {
                std::cout << "Įveskite sveikąjį skaičių tarp 0 ir 10: ";
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Įveskite sveikąjį skaičių tarp 0 ir 10: ";
        }
    }

    s.exam = getInt("Įveskite egzamino įvertinimą: ", 0, 10);

    return s;
}

Student enterStudent2() {
    Student s;
    std::cout << "Vardas: ";
    std::cin >> s.name;
    std::cout << "Pavardė: ";
    std::cin >> s.surname;

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


double calculateMean(const std::vector<int> &hm, int exam) {
    if (hm.empty()) return exam * 0.6;
    double s = 0;
    for (int g : hm) {
        s += g;
    }
    s /= hm.size();
    return s * 0.4 + 0.6 * exam;
}

double calculateMedian(std::vector<int> hm, int exam) {
    if (hm.empty()) return exam * 0.6;

    std::sort(hm.begin(), hm.end());
    int pos = hm.size() / 2;
    if (hm.size() % 2 == 0) {
        return (hm[pos - 1] + hm[pos]) / 2.0 * 0.4 + exam * 0.6;
    } else {
        return hm[pos] * 0.4 + exam * 0.6;
    }
}

std::vector<Student> readFile(std::string filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Nepavyko atidaryti failo." << std::endl;
        return students;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Student s;

        ss >> s.name >> s.surname;
        
        int grade;
        std::vector<int> hm;
        while (ss >> grade) {
            hm.push_back(grade);
        }

        s.exam = hm.back();
        hm.pop_back();
        s.homework = hm;

        s.mean = calculateMean(s.homework, s.exam);
        s.median = calculateMedian(s.homework, s.exam);

        students.push_back(s);
    }

    return students;
}

void printStudent(const Student& stu, int comm) {
    int surnameWidth = 30;
    int nameWidth = 25;

    std::cout << stu.surname;
    std::cout << std::string(surnameWidth - utf8_length(stu.surname), ' ');

    std::cout << stu.name;
    std::cout << std::string(nameWidth - utf8_length(stu.name), ' ');

    if (comm == 1)
        std::cout << std::fixed << std::setprecision(2) << stu.mean;
    else
        std::cout << std::fixed << std::setprecision(2) << stu.median;

    std::cout << std::endl;
}

int main() {
    std::vector<Student> students;
    std::srand(std::time(nullptr));

    while (true) {
        std::cout << "1 - Įrašyti studentus ir pažymius ranka" << std::endl;
        std::cout << "2 - Generuoti random pažymius" << std::endl;
        std::cout << "3 - Generuoti random studentus ir pažymius" << std::endl;
        std::cout << "4 - Nuskaityti iš failo" << std::endl;
        std::cout << "5 - Exit" << std::endl;

        int choice = getInt("Veiksmas: ", 1, 5);

        if (choice == 1 || choice == 2) {
            while (true) {
                Student s;
                if (choice == 1) s = enterStudent();
                else s = enterStudent2();

                s.mean = calculateMean(s.homework, s.exam);
                s.median = calculateMedian(s.homework, s.exam);
                students.push_back(s);

                std::string comm;
                std::cout << "Įrašyti dar vieną studentą? (y/n): ";
                std::cin >> comm;
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

        } else if (choice == 4) {
            std::string filename;
            std::cout << "Įveskite failo pavadinimą: ";
            std::cin >> filename;

            students = readFile(filename);
        } 
        else {
            break;
        }

        int isvedimas = getInt("Išvesti rezultatus vidurkio ar medianos pavidalu? (1 - vid., 2 - med.): ", 1, 2);

        std::cout << "Pavardė";
        std::cout << std::string(30 - utf8_length("Pavardė"), ' ');

        std::cout << "Vardas";
        std::cout << std::string(25 - utf8_length("Vardas"), ' ');

        std::cout << "Galutinis" << std::endl;
        std::cout << std::string(70, '-') << std::endl;

        for (const auto &stu : students) {
            printStudent(stu, isvedimas);
        }

        std::cout << std::string(70, '-') << std::endl;
        students.clear();
    }

    return 0;
}