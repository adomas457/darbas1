#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include "utils.h"

int main() {
    std::vector<Student> students;
    std::srand(std::time(nullptr));

    while (true) {
        std::cout << "1 - Įrašyti studentus ir pažymius ranka" << std::endl;
        std::cout << "2 - Generuoti random pažymius" << std::endl;
        std::cout << "3 - Generuoti random studentus ir pažymius" << std::endl;
        std::cout << "4 - Nuskaityti iš failo" << std::endl;
        std::cout << "5 - Kurti failą" << std::endl;
        std::cout << "6 - Exit" << std::endl;

        int choice = getInt("Veiksmas: ", 1, 6);


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

            try {
               students = readFile(filename); 
            }
            catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }

        } else if (choice == 5) {
            int test = getInt("Įveskite įrašų skaičių: ", 1);
            auto start1 = std::chrono::high_resolution_clock::now();

            generateFile("studentai" + std::to_string(test) + ".txt", test, 10);

            auto end1 = std::chrono::high_resolution_clock::now();
            std::cout << "Failo su " << test << " įrašų kūrimo laikas: " << std::chrono::duration<double>(end1 - start1).count() << " s\n" << std::endl;

            std::cout << std::string(100, '-') << std::endl;

            auto start2 = std::chrono::high_resolution_clock::now();
            try {
                splitStudent("studentai" + std::to_string(test) + ".txt", "geri" + std::to_string(test) + ".txt", "blogi"+ std::to_string(test) + ".txt", test);
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }

             auto end2 = std::chrono::high_resolution_clock::now();
             std::cout << "Failo su " << test << " įrašų galutinis testavimo laikas: " << std::chrono::duration<double>(end2 - start2).count() << " s\n" << std::endl;
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

        } else if (choice == 1 || choice == 2 || choice == 3){
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