#include "std_solution.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <chrono>

namespace std_solution {

const int READ_BUFFER_SIZE = 1024 * 1024;  //  should it be global const?

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

static void process_data (
    char data[],
    int data_size,
    std::string &current_word,
    std::unordered_map<std::string, int> &unordered_map) 
{
    for (int i = 0; i < data_size + 1; i++) {
        char c;
        if (i < data_size) {
            c = data[i];
        } else {
            c = ' ';
        }

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

//  Insertion sort for 
void my_sort(std::vector<std::pair<std::string, int>> &vector) {
    std::sort(vector.begin(), vector.end(), 
            [](const auto& a, const auto& b) {
                return a.second > b.second
                    || a.second == b.second && a.first < b.first;
            });
    

}


void solution(
    std::string input_file, 
    std::string output_file) 
{
    std::cout << "std_unordered_map_solution::solution start\n";
    std::ifstream in(input_file);

    std::unordered_map<std::string, int> unordered_map;

    std::string current_word = "";
    std::unique_ptr<char[]> buffer(new char[READ_BUFFER_SIZE]);

    while (in) {
        in.read(buffer.get(), READ_BUFFER_SIZE);
        process_data(buffer.get(), in.gcount(), current_word, unordered_map);
    }

    std::vector<std::pair<std::string, int>> vector;
    for (const auto& pair: unordered_map) {
        //  here i tried std::move. But this didn't make visible profit
        //  i expected this, because words are normally short strings
        vector.push_back(pair);
    }

    std::cout << "std_unordered_map_solution::sort start\n";


    my_sort(vector);
    // std::sort(vector.begin(), vector.end(), 
    //         [](const auto& a, const auto& b) {
    //             return a.second > b.second
    //                 || a.second == b.second && a.first < b.first;
    //         });

    std::ofstream out(output_file, std::fstream::out | std::fstream::trunc);

    for (const auto& [word, count]: vector) {
        out << count << " " << word << "\n";
    }
    out.close();
    std::cout << "std_unordered_map_solution::solution end\n";
}

}  //  ns std_solution