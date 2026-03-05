#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "utils.h"

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

            //auto start = std::chrono::high_resolution_clock::now();

            students = readFile(filename);

            //auto end = std::chrono::high_resolution_clock::now();
            //std::chrono::duration<double> diff = end - start;
            //std::cout << "Laikas: " << diff.count() << std::endl;
        } 
        else {
            break;
        }

        if (choice == 4) {
            rusiavimas = getInt("Surūšiuoti pagal: vardą (1); pavardę (2); pagal vidurkį (3); pagal medianą (4): ", 1, 4);
            std::sort(students.begin(), students.end(), rusiuoti);

            std::cout << "Pavardė";
            std::cout << std::string(30 - utf8_length("Pavardė"), ' ');

            std::cout << "Vardas";
            std::cout << std::string(25 - utf8_length("Vardas"), ' ');

            std::cout << "Galutinis (Vid.)";


            std::cout << std::string(30 - utf8_length("Galutinis (Vid.)"), ' ');
            std::cout << "Galutinis (Med.)" << std::endl;
            std::cout << std::string(100, '-') << std::endl;

        for (const auto &stu : students) {
            printStudent(stu);
        }

        } else {
            int isvedimas = getInt("Išvesti rezultatus vidurkio ar medianos pavidalu? (1 - vid., 2 - med.): ", 1, 2);

            std::cout << "Pavardė";
            std::cout << std::string(30 - utf8_length("Pavardė"), ' ');

            std::cout << "Vardas";
            std::cout << std::string(25 - utf8_length("Vardas"), ' ');

            if (isvedimas == 1) {
                std::cout << "Galutinis (Vid.)" << std::endl;
            } else {
                std::cout << "Galutinis (Med.)"  << std::endl;
            }
            
            std::cout << std::string(100, '-') << std::endl;

            for (const auto &stu : students) {
                printStudent(stu, isvedimas);
            }
        }

        std::cout << std::string(100, '-') << std::endl;
        students.clear();
    }

    return 0;
}