#include "header.h"
#include <functional>   // std::greater
#include <algorithm>    // std::sort

#include <iostream>
using namespace std;

void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
    free_space = {};
    int size = items.size();

    for(int i = 0; i < size; ++i)
    {
        int bin_index = 0;
        int bin_cnt = free_space.size();
        while(bin_index < bin_cnt && free_space[bin_index] < items[i])
        {
            ++bin_index;
        }

        if(bin_index == bin_cnt)
        {
            free_space.push_back(1.0);
        }
        free_space[bin_index] -= items[i];
        assignment[i] = bin_index;
    }
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
    // hard-copy items list
    std::vector<double> sorted_items(items);

    // sort it in descending order
    std::sort(sorted_items.begin(), sorted_items.end() , std::greater<double>());

    first_fit(sorted_items, assignment, free_space);
}
