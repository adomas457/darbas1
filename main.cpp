#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include "utils.h"
#include <deque>
#include <list>

int main() {
    using Container = std::vector<Student>;
    //using Container = std::deque<Student>;
    //using Container = std::list<Student>;

    Container students;
    std::srand(std::time(nullptr));

    while (true) {
        std::cout << "1 - Generuoti failus (1 atvejis)" << std::endl;
        std::cout << "2 - Generuoti failus (2 atvejis)" << std::endl;
        std::cout << "3 - Exit" << std::endl;

        int choice = getInt("Veiksmas: ", 1, 3);

        if (choice == 1) {
            int test = getInt("Įveskite įrašų skaičių: ", 1);

            generateFile("studentai" + std::to_string(test) + ".txt", test, 10);

            
        } else if (choice == 2) {
            int test = getInt("Įveskite įrašų skaičių: ", 1);
            rusiavimas = getInt("Surūšiuoti pagal: vardą (1); pavardę (2); pagal vidurkį (3); pagal medianą (4): ", 1, 4);
            int pasirinkimas = getInt("Strategijos nr.: ", 1, 2);
            try {

                auto start = std::chrono::high_resolution_clock::now();

                students = readFile<Container>("studentai" + std::to_string(test) + ".txt");

                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Failo nuskaitymo laikas: " << std::chrono::duration<double>(end - start).count() << " s\n" << std::endl;

                if (pasirinkimas == 1) {
                    splitStudent<Container>(students, "geri" + std::to_string(test) + ".txt", "blogi"+ std::to_string(test) + ".txt");
                } else {
                    splitStudent2<Container>(students, "geri" + std::to_string(test) + ".txt", "blogi"+ std::to_string(test) + ".txt");
                }
                
                
                students.clear();
            } 
            catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        else {
            break;
        }

        std::cout << std::string(100, '-') << std::endl;
    }

    return 0;
}