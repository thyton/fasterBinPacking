#include "header.h"
#include <functional>   // std::greater
#include <algorithm>    // std::sort

#include "BF_AVL_Tree.h"

#include <iostream>


void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
    free_space = {};
    int size = items.size();
    int bin_index;
    if (size > 0)
    {
        pair<int,double> index_rc;
        BF_AVL_Tree t;
        for(int i = 0; i < size; ++i)
        {
            if (t.is_fit_in_current_bins(items[i]))
            {
                // search best bin and delete it from the data structure
                index_rc = t.search_best_bin(items[i]);
                bin_index  = index_rc.first;

                // readd it to the data structure with updated info
                t.insert(BF_Bin(index_rc.first, index_rc.second - items[i], index_rc.second - items[i]));
            }else
            {
                bin_index = t.get_bin_cnt();
                t.insert(BF_Bin(bin_index, 1.0 - items[i], 1.0 - items[i]));
            }
            assignment[i] = bin_index;
        }
        free_space = vector<double>(t.get_bin_cnt());
        t.get_free_space(free_space);
    }
        for(int i = 0; i < assignment.size(); ++i)
    {
        cout << assignment[i] << " ";
    }

    for(int i = 0; i < free_space.size(); ++i)
    {
        cout << fixed << i << " " << free_space[i] << " ";
    }
    cout << endl;
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
    // hard copies items list and then reverse sorts it
    std::vector<double> sorted_items(items);
    std::sort(sorted_items.begin(), sorted_items.end() , std::greater<double>());
    best_fit(sorted_items, assignment, free_space);
}
