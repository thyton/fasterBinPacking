#include <vector>
#include <random>
#include <chrono>
#include <unordered_set>
using namespace std;

mt19937 get_mersenne_twister_generator_with_current_time_seed();

double rand_float(mt19937& mt, uniform_real_distribution<double>& dist);

int rand_int(mt19937& mt, uniform_int_distribution<int>& dist);

void get_random_weight_sequence(int N, int upto_decimal_place, vector<double>& seq , double& sum);

void get_random_weight_sequence(int N,  vector<double>& seq , double& sum);

void get_random_sequences(int N, int seq_nums, vector<vector<double>>& sequences, vector<double>& seq_sums);

void get_random_sequences(int N, int seq_nums, int upto_decimal_place, vector<vector<double>>& sequences, vector<double>& seq_sums);