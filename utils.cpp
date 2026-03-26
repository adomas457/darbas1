#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <chrono>
#include <list>

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


bool rusiuoti(const Student& s1, const Student& s2) {
    switch (rusiavimas) {
        case 1: return s1.name < s2.name;
        case 2: return s1.surname < s2.surname;
        case 3: return s1.mean < s2.mean;
        case 4: return s1.median < s2.median;
    }
    return false;
}

