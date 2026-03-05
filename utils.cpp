#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstdlib>

std::vector<std::string> vardai = {"Jonas", "Adomas", "Vytautas", "Juozas", "Matas", "Mantas", "Dominykas", "Algirdas", "Gediminas", "Mindaugas", 
    "Laura", "Inga", "Edita", "Gabija", "Justina", "Daiva", "Rasa", "Jolita", "Asta", "Lina"};
std::vector<std::string> pavardes_vyr = {"Pavardenis1", "Pavardenis2", "Pavardenis3", "Pavardenis4", "Pavardenis5", 
    "Pavardenis6", "Pavardenis7", "Pavardenis8", "Pavardenis9", "Pavardenis10"};
std::vector<std::string> pavardes_mot = {"Pavardenaitė1", "Pavardenaitė2", "Pavardenaitė3", "Pavardenaitė4", "Pavardenaitė5",
    "Pavardenaitė6", "Pavardenaitė7", "Pavardenaitė8", "Pavardenaitė9", "Pavardenaitė10"};

int rusiavimas = 2;


int getInt(const std::string &prompt, int min, int max) {
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

std::vector<Student> readFile(const std::string &filename) {
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



/*void printStudent(const Student& stu, int comm) {
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
}*/

void printStudent(const Student& stu) {
    int surnameWidth = 30;
    int gradeWidth = 30;
    int nameWidth = 25;

    std::cout << stu.surname;
    std::cout << std::string(surnameWidth - utf8_length(stu.surname), ' ');

    std::cout << stu.name;
    std::cout << std::string(nameWidth - utf8_length(stu.name), ' ');

    std::cout << std::left << std::setw(gradeWidth) << std::fixed << std::setprecision(2) << stu.mean;

    std::cout << std::fixed << std::setprecision(2) << stu.median;

    std::cout << std::endl;
}

bool rusiuoti(const Student& s1, const Student& s2) {
    switch (rusiavimas) {
        case 1: return s1.name < s2.name;
        case 2: return s1.surname < s2.surname;
        case 3: return s1.mean < s2.mean;
        case 4: return s1.median < s2.median;
    }
    return false;
}
