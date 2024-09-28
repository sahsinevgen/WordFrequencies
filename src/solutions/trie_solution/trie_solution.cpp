#include "trie_solution.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>


namespace trie_solution {


const int READ_BUFFER_SIZE = 1024 * 1024;


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


class trie_node {
public:
    trie_node() {
    }


    ~trie_node() {
        for (int i = 0; i < 26; i++) {
            if (children[i] != nullptr) {
                delete children[i];
            }
        }

        // for (auto [_, child]: children) {
        //     delete child;
        // }
    }


    trie_node* next(char c) {
        if (is_separator(c)) {
            return nullptr;
        }

        c = lower(c);

        if (children[c - 'a'] == nullptr) {
            children[c - 'a'] = new trie_node;
        }

        return children[c - 'a'];
    }
    

    int value = 0;
    trie_node* children[26] = {nullptr, };
    // std::unordered_map<int, trie_node*> children;
};


void trie_to_vector(
    trie_node* current_node, 
    std::string &current_str,
    std::vector<std::pair<std::string, int>> &vector
)
{
    if (current_node->value != 0) {
        vector.emplace_back(current_str, current_node->value);
    }

    for (int i = 0; i < 26; i++) {
        if (current_node->children[i] != nullptr) {
            current_str.push_back('a' + i);
            trie_to_vector(current_node->children[i], current_str, vector);
            current_str.pop_back();
        }
    }
}


static void process_data (
    char data[],
    int data_size,
    trie_node* &current_node,
    trie_node* trie_head)
{
    for (int i = 0; i < data_size; i++) {
        char c;
        if (i < data_size) {
            c = data[i];
        }

        trie_node* next_node = current_node->next(c);
        
        if (next_node == nullptr) {
            if (current_node != trie_head) {
                current_node->value++;
            }

            current_node = trie_head;
        } else {
            current_node = next_node;
        }
    }
}


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
    std::cout << "trie_solution::solution start\n";
    std::ifstream in(input_file);

    trie_node* trie_head = new trie_node;
    trie_node* current_node = trie_head;

    std::string current_word = "";
    std::unique_ptr<char[]> buffer(new char[READ_BUFFER_SIZE]);

    while (in) {
        in.read(buffer.get(), READ_BUFFER_SIZE);
        process_data(buffer.get(), in.gcount(), current_node, trie_head);
    }
    {
        char data[] = {" "};
        process_data(data, 1, current_node, trie_head);
    }

    std::vector<std::pair<std::string, int>> vector;
    {
        std::string str = "";
        trie_to_vector(trie_head, str, vector);
    }

    delete trie_head;

    std::cout << "trie_solution::sort start\n";

    my_sort(vector);

    std::ofstream out(output_file, std::fstream::out | std::fstream::trunc);

    for (const auto& [word, count]: vector) {
        out << count << " " << word << "\n";
    }
    out.close();
    std::cout << "trie_solution::solution end\n";
}

}  //  ns trie_solution