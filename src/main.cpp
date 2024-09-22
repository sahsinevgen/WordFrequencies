#include <iostream>
#include <string>

#include "solutions/solutions.h"


void print_usage() {
    std::cout << "usage: ./freq [input_file] [output_file] [method_number]\n";
}

int main(int argc, char** argv) {
    if (argc != 4) {
        print_usage();
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    int method_number = std::stoi(argv[3]);

    solutions[method_number](input_file, output_file);
}