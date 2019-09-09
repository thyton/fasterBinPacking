#include <string>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <math.h>
#include "result.h"
using namespace std;

vector<int> get_sorted_vector(int n){
    vector<int> nums(n);
    int value = 0;
    for( int i=0; i<n; ++i){
        nums[i]=value;
        ++value;
    }
    return nums;
}

void make_output_file_funcname(string func_name, ofstream& outfile, int N){
    string file = "./result/" + func_name + "_" + to_string(N) + ".csv";
    outfile.open(file, ios::trunc);
    outfile << "funcname,n,bins,sum,avg_free_space\n";
}

void make_output_file(string perm_name, ofstream& outfile, int N){
    string file = "./" + perm_name + "_" + to_string(N) + ".csv";
    outfile.open(file, ios::trunc);
    outfile << "funcname,n,seconds\n";
}

void print(ofstream& o, const vector<result>& results, string func_name) {
    int size = results.size();
    for(int i = 0; i < size; ++i)
    {
        o << func_name << "," << results[i] << "\n";
    }
}

void print_title(int N)
{
    cout << "Running all bin packing algorithms on " << N << "\n";
}

double average(const vector<double>& floats)
{
    double result = 0.0;
    int size = floats.size();
    for(int i = 0; i < size; ++i)
    {
        result += floats[i]; 
    }
    return result / size;
}

bool isValid(const vector<double>& sequence, const vector<int>& assignment, int bin_cnt)
{
    vector<double> total_spaces(bin_cnt, 0.0);
    int size = assignment.size();
    for(int i = 0; i < size; ++i)
    {
        total_spaces[assignment[i]] += sequence[i];
    }
    
    for(int i = 0; i < bin_cnt; ++i)
    {
        if (total_spaces[i] > 1.0)
        {   
            cout << i << "  -  ";
            return false;
        }
    }
    return true;
}

void experiment(const vector<vector<double>>& sequences, const vector<double>& seq_sums, vector<result>& results, void (*f)(const vector<double>&, vector<int>& , vector<double>&))
{
    results = {};
    vector<int> assignment(sequences[0].size(), 0);
    vector<double> free_space;
    result res;
    int size = sequences.size();
    for(int i = 0; i < size; ++i)
    {
        f(sequences[i], assignment, free_space);
        res.avg_free_space = average(free_space);
        res.sum = seq_sums[i]; 
        res.bins = free_space.size();
        results.push_back(res);
    }
}

