#include "header.h"
#include <functional>   // std::greater
#include <algorithm>    // std::sort

#include "FF_AVL_Tree.h"

#include <iostream>
using namespace std;

void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
    free_space = {};
    int size = items.size();
    int bin_index;
    if (size > 0)
    {
        FF_AVL_Tree t;
        for(int i = 0; i < size; ++i)
        {
            if (t.is_fit_in_current_bins(items[i]))
            {
                bin_index = t.insert_item(items[i]);
            }else
            {
                bin_index = t.get_bin_cnt();
                t.insert(FF_Bin(bin_index, 1.0 - items[i], 1.0 - items[i]));
            }
            assignment[i] = bin_index;
        }
        t.get_free_space(free_space);
    }
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
    // hard copies items list and then reverse sorts it
    std::vector<double> sorted_items(items);
    std::sort(sorted_items.begin(), sorted_items.end() , std::greater<double>());
    first_fit(sorted_items, assignment, free_space);
}
