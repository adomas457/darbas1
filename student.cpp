#include "student.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <iostream>

std::vector<std::string> vardai = {"Jonas", "Adomas", "Vytautas", "Juozas", "Matas", "Mantas", "Dominykas", "Algirdas", "Gediminas", "Mindaugas", 
    "Laura", "Inga", "Edita", "Gabija", "Justina", "Daiva", "Rasa", "Jolita", "Asta", "Lina"};
std::vector<std::string> pavardes_vyr = {"Pavardenis1", "Pavardenis2", "Pavardenis3", "Pavardenis4", "Pavardenis5", 
    "Pavardenis6", "Pavardenis7", "Pavardenis8", "Pavardenis9", "Pavardenis10"};
std::vector<std::string> pavardes_mot = {"Pavardenaitė1", "Pavardenaitė2", "Pavardenaitė3", "Pavardenaitė4", "Pavardenaitė5",
    "Pavardenaitė6", "Pavardenaitė7", "Pavardenaitė8", "Pavardenaitė9", "Pavardenaitė10"};

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

bool rusiuotiPagalMean(const Student& s1, const Student& s2) {
    return s1.mean < s2.mean;
}

void splitStudent(const std::string &filename, const std::string &geri, const std::string &blogi, int test) {

    auto start1 = std::chrono::high_resolution_clock::now();

    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Failas nerastas.");

    std::string header;
    std::getline(file, header);
    std::vector<Student> geriStud;
    std::vector<Student> blogiStud;

    std::string line;
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
        
        if (s.mean < 5.0) {
            blogiStud.push_back(s);
        } else {
            geriStud.push_back(s);
        }

    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Failo su " << test << " įrašų nuskaitymo ir įvedimo į vectorius laikas: " << std::chrono::duration<double>(end1 - start1).count() << " s\n" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();

    std::sort(geriStud.begin(), geriStud.end(), rusiuotiPagalMean);
    std::sort(blogiStud.begin(), blogiStud.end(), rusiuotiPagalMean);

    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "Gerų ir blogų stud., kurie turi " << test << " įrašų rūšiavimo did. tvarka laikas: " << std::chrono::duration<double>(end2 - start2).count() << " s\n" <<  std::endl;

    std::ofstream fileGeri(geri);
    std::ofstream fileBlogi(blogi);

    auto start3 = std::chrono::high_resolution_clock::now();

    fileGeri << header << '\n';
    for (const auto &s : geriStud) {
        fileGeri << std::left << std::setw(15) << s.name << std::left << std::setw(15) << s.surname;
        for (int grade : s.homework) fileGeri << std::left << std::setw(10) << grade;
        fileGeri << std::left << std::setw(10) << s.exam << '\n';
    }

    auto end3 = std::chrono::high_resolution_clock::now();
    std::cout << "Gerųjų įrašymo į failą laikas (" << test << " įrašų testas): " << std::chrono::duration<double>(end3 - start3).count() << " s\n" << std::endl;

    auto start4 = std::chrono::high_resolution_clock::now();

    fileBlogi << header << '\n';
    for (const auto &s : blogiStud) {
        fileBlogi << std::left << std::setw(15) << s.name << std::left << std::setw(15) << s.surname;
        for (int grade : s.homework) fileBlogi << std::left << std::setw(10) << grade;
        fileBlogi << std::left << std::setw(10) << s.exam << '\n';
    }

    auto end4 = std::chrono::high_resolution_clock::now();
    std::cout << "Blogųjų įrašymo į failą laikas (" << test << " įrašų testas): " << std::chrono::duration<double>(end4 - start4).count() <<  " s\n" << std::endl;

}