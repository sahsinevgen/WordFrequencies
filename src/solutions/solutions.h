#ifndef SOLUTIONS
#define SOLUTIONS

#include <string>


#include "std_solution/std_solution.h"
#include "trie_solution/trie_solution.h"


typedef void (*t_solution_func)(std::string, std::string);


t_solution_func solutions[] =  {
    std_solution::solution,
    trie_solution::solution,
};

int solutions_count = (sizeof(solutions)/sizeof(*solutions));

#endif  // SOLUTIONS