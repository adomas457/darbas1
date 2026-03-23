#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <chrono>


int rusiavimas = 2;

int getInt(const std::string &prompt, int min, int max) {
    int num;

    while (true) {
        try {
            std::cout << prompt;

            if (!(std::cin >> num) || (num < min || num > max)) throw std::runtime_error("Įveskite sveikąjį skaičių tarp " + std::to_string(min) + " ir " + std::to_string(max) + ".");
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return num;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Įveskite sveikąjį skaičių tarp " << min << " ir " << max << "." << std::endl;
        } catch (std::exception &e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << std::endl;
        }
        
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
    while (true) {
        try {
            std::cout << "Namų darbų įvertinimai (-1 baigti): ";

            if (!(std::cin >> grade) || ((grade < 0 && grade != -1) || grade > 10)) throw std::runtime_error("Įveskite sveikąjį skaičių tarp 0 ir 10.");

            if (grade == -1) {
                break;
            } else {
                s.homework.push_back(grade);
            } 
        } catch (std::exception &e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << std::endl;
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
        throw std::runtime_error("Failas nerastas.");
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


void generateFile(const std::string &filename, int n, int nd) {
    std::ofstream file(filename);

    file << std::left << std::setw(25) << "Vardas" << std::left << std::setw(25) << "Pavarde";
    for (int i = 1; i <= nd; i++) {
        file << std::left << std::setw(10) << ("ND" + std::to_string(i));
    }
    file << "Egz.\n";

    for (int i = 1; i <= n; i++) {
        file << std::left << std::setw(25) << ("Vardas" + std::to_string(i)) << std::left << std::setw(25) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j < nd; j++)file << std::left << std::setw(10) << (rand() % 11);

        file << std::left << std::setw(10) << (rand() % 11) << '\n';
    }
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

void printStudent(const Student& stu, std::ostream& out) {
    int surnameWidth = 30;
    int gradeWidth = 30;
    int nameWidth = 25;

    out << stu.surname << std::string(surnameWidth - utf8_length(stu.surname), ' ');
    out << stu.name << std::string(nameWidth - utf8_length(stu.name), ' ');
    out << std::left << std::setw(gradeWidth) << std::fixed << std::setprecision(2) << stu.mean;
    out << std::fixed << std::setprecision(2) << stu.median;
    out << '\n';
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


void splitStudent(std::vector<Student> &stud, const std::string &geri, const std::string &blogi) {

    auto start = std::chrono::high_resolution_clock::now();

    std::sort(stud.begin(), stud.end(), rusiuoti);

    std::vector<Student> geriStud;
    std::vector<Student> blogiStud;

    for (const auto &s : stud) {
        if (s.mean >= 5.0)
            geriStud.push_back(s);
        else
            blogiStud.push_back(s);
    }
    stud.clear();


    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Studentų rūšiavimo į dvi grupes laikas: " << std::chrono::duration<double>(end - start).count() << " s\n" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    std::ofstream fileGeri(geri);
    std::ofstream fileBlogi(blogi);

    fileGeri << std::left << std::setw(25) << "Vardas" << std::left << std::setw(25) << "Pavarde" << std::left << std::setw(25) << "Galutinis (Vid.)" << 
    "Galutinis (Med.)" << '\n';
    for (const auto &s : geriStud) {
        fileGeri << std::left << std::setw(25) << s.name << std::left << std::setw(25) << s.surname << std::left << std::setw(25) 
        << std::fixed << std::setprecision(2) << s.mean << std::fixed << std::setprecision(2) << s.median << '\n';
    }



    fileBlogi << std::left << std::setw(25) << "Vardas" << std::left << std::setw(25) << "Pavarde" << std::left << std::setw(25) << "Galutinis (Vid.)" << 
    "Galutinis (Med.)" << '\n';
    for (const auto &s : blogiStud) {
        fileBlogi << std::left << std::setw(25) << s.name << std::left << std::setw(25) << s.surname << std::left << std::setw(25) 
        << std::fixed << std::setprecision(2) << s.mean << std::fixed << std::setprecision(2) << s.median << '\n';
    }

    end = std::chrono::high_resolution_clock::now();
    std::cout << "Surūšiuotų studentų išvedimo į du failus laikas: " << std::chrono::duration<double>(end - start).count() << " s\n" << std::endl;

}
