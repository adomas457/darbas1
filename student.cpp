#include "student.h"
#include <algorithm>
#include <fstream>
#include <sstream>

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

void splitStudent(const std::string &filename, const std::string &geri, const std::string &blogi) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Failas nerastas.");

    std::ofstream fileGeri(geri);
    std::ofstream fileBlogi(blogi);

    std::string header;
    std::getline(file, header);
    fileGeri << header << "\n";
    fileBlogi << header << "\n";

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
            fileBlogi << line << "\n";
        } else {
            fileGeri << line << "\n";
        }
    }
}