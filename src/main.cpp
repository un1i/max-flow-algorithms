#include "../include/time_test.h"
#include <iostream>

int main(){
    time_test_few_edges();
    std::cout << "\nNext!\n";
    time_test_many_edges();
    std::cout << "\nNext!\n";
    time_test_complete_graph();
    std::cout << "\nNext!\n";
    time_test_increase_num_edges();
}