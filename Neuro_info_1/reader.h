#ifndef READER_H
#define READER_H
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

std::vector<std::vector<int>> readDataFromFile(const std::string& filename) {

    std::vector<std::vector<int>> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return data;
    }

    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c == '0' || c == '1') {
                row.push_back(c - '0');
            }
        }
        data.push_back(row);
    }

    file.close();
    return data;
}


void shuffle_data(std::vector<std::vector<int>>& data) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);
}

#endif // !READER_H