#include "random.h"

mt19937 get_mersenne_twister_generator_with_current_time_seed()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}

double rand_float(mt19937& mt, uniform_real_distribution<double>& dist)
{
    return dist(mt);
}
 
int rand_int(mt19937& mt, uniform_int_distribution<int>& dist)
{
    return dist(mt);
}

void get_random_weight_sequence(int N, int upto_decimal_place, vector<double>& seq , double& sum)
{
    mt19937 mt = get_mersenne_twister_generator_with_current_time_seed();
    uniform_int_distribution<int> dist(1, upto_decimal_place);
    
    seq = vector<double>(N);
    sum = 0.0;
    double dec_place = upto_decimal_place;
    for(int i = 0; i < N; ++i)
    {
        seq[i] = rand_int(mt, dist)/dec_place;
        sum += seq[i];
    }
}

void get_random_weight_sequence(int N,  vector<double>& seq , double& sum)
{
    mt19937 mt = get_mersenne_twister_generator_with_current_time_seed();
    uniform_real_distribution<double> dist(0.0, 1.0);
    
    seq = vector<double>(N);
    sum = 0.0;
    for(int i = 0; i < N; ++i)
    {
        seq[i] = rand_float(mt, dist);
        sum += seq[i];
    }
}

void get_random_sequences(int N, int seq_nums, vector<vector<double>>& sequences, vector<double>& seq_sums)
{
    sequences =  vector<vector<double>>(seq_nums);
    seq_sums = vector<double>(seq_nums);
    
    for(int i = 0; i < seq_nums; ++i){
        get_random_weight_sequence(N, sequences[i], seq_sums[i]);
    }
}

void get_random_sequences(int N, int seq_nums, int upto_decimal_place, vector<vector<double>>& sequences, vector<double>& seq_sums)
{
    sequences =  vector<vector<double>>(seq_nums);
    seq_sums = vector<double>(seq_nums);
    
    for(int i = 0; i < seq_nums; ++i){
        get_random_weight_sequence(N, upto_decimal_place, sequences[i], seq_sums[i]);
    }   
}