#include "header.h"
#include <algorithm>

#include <iostream>
using namespace std;
void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
    free_space = {};
    int size = items.size();
    for(int i = 0; i < size; ++i)
    {
        int bin_cnt = free_space.size();

        // assume the tightest bin is a new bin
        // and iterate all current bins to see there is other tighter bin.
        int final_index = bin_cnt;
        double min_space = 1.0;

        for(int bin_index = 0; bin_index < bin_cnt; ++bin_index)
        {
            if(free_space[bin_index] >= items[i] && free_space[bin_index] < min_space)
            {
                final_index = bin_index;
                min_space = free_space[bin_index];
            }
        }

        if(bin_cnt == final_index) // add the new bin if assumption is true
        {
            free_space.push_back(1.0);
        }
        assignment[i] = final_index;
        free_space[final_index] -= items[i];
    }
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
    // hard-copy items list
    std::vector<double> sorted_items(items);

    // sort it in descending order
    std::sort(sorted_items.begin(), sorted_items.end() , std::greater<double>());

    best_fit(sorted_items, assignment, free_space);
}