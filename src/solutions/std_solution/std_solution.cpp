#include "std_solution.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace std_solution {

static bool is_separator(char c) {
    return !('a' <= c && c <= 'z'
          || 'A' <= c && c <= 'Z');
}

static char lower(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A' + 'a';
    };

    return c;
}

static void process_data(
    std::string &data,
    std::string &current_word,
    std::unordered_map<std::string, int> &unordered_map) 
{
    for (char c: data) {
        if (is_separator(c)) {
            if (current_word != "") {
                unordered_map[current_word] += 1;
                current_word = "";
            }
            continue;
        }

        current_word += lower(c);
    }
}

void solution(
    std::string input_file, 
    std::string output_file) 
{
    std::cout << "std_unordered_map_solution::solution start\n";
    std::ifstream in(input_file);

    std::unordered_map<std::string, int> unordered_map;

    std::string current_word = "";
    // std::vector<char> buffer(1024, 0);
    std::string buffer;
    
    while (in >> buffer) {
        buffer += " ";
        process_data(buffer, current_word, unordered_map);
    }
    if (current_word != "") {
        unordered_map[current_word] += 1;
    }

    std::vector<std::pair<std::string, int>> vector;
    for (const auto& pair: unordered_map) {
        vector.push_back(pair);
    }

    std::sort(vector.begin(), vector.end(), 
            [](const auto& a, const auto& b) {
                return a.second > b.second
                    || a.second == b.second && a.first < b.first;
            });

    std::ofstream out(output_file, std::fstream::out | std::fstream::trunc);

    for (const auto& [word, count]: vector) {
        out << count << " " << word << "\n";
    }
    out.close();
    std::cout << "std_unordered_map_solution::solution end\n";
}

}  //  ns std_solution