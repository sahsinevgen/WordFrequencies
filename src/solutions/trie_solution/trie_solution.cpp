#include "trie_solution.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace trie_solution {


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


// class trie {
//     trie(): {
//         head = new trie_node;
//     }

//     ~trie(): {
//         delete head;
//     }
// private:
//     *trie_node head;
// }


static void process_data(
    std::string &data,
    trie_node* current_node,
    trie_node* trie_head) 
{
    for (char c: data) {
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


void solution(
    std::string input_file, 
    std::string output_file) 
{
    std::cout << "trie_solution::solution start\n";
    std::ifstream in(input_file);

    trie_node* trie_head = new trie_node;
    trie_node* current_node = trie_head;

    std::string current_word = "";
    // std::vector<char> buffer(1024, 0);
    std::string buffer;
    
    while (in >> buffer) {
        buffer += " ";
        process_data(buffer, current_node, trie_head);
    }
    if (current_node != trie_head) {
        current_node->value += 1;
    }


    std::vector<std::pair<std::string, int>> vector;
    {
        std::string str = "";
        trie_to_vector(trie_head, str, vector);
    }

    delete trie_head;

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
    std::cout << "trie_solution::solution end\n";
}

}  //  ns trie_solution