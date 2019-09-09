#include "header.h"
#include "random.h"
#include "main_helper.h"

int result::N = 0;
int main(int argc , char *argv[])
{
    const int RUNS = 50;

    vector<vector<double>> sequences;
    vector<double> seq_sums;

    vector<result> results;

    ofstream o;
    // prepare random weight sequences
    result::N = atoi(argv[1]);

    // Uncomment this to run with
    get_random_sequences(result::N, RUNS, sequences, seq_sums);

    // Uncomment this to run with 10th decimal place, using to compare outputs of optimized and normal versio
    // get_random_sequences(result::N, RUNS, 10, sequences, seq_sums);

    print_title(result::N);

    // First Fit (FF)
    make_output_file_funcname("FF", o, result::N);
    experiment(sequences, seq_sums, results, first_fit);
    print(o, results, "FF");
    o.close();

    // First Fit Decreasing (FFD)
    make_output_file_funcname("FFD", o, result::N);
    experiment(sequences, seq_sums, results, first_fit_decreasing);
    print(o, results, "FFD");
    o.close();

    // Best Fit (BF)
    make_output_file_funcname("BF", o, result::N);
    experiment(sequences, seq_sums, results, best_fit);
    print(o, results, "BF");
    o.close();

    // Best Fit Decreasing (BFD)
    make_output_file_funcname("BFD", o, result::N);
    experiment(sequences, seq_sums, results, best_fit_decreasing);
    print(o, results, "BFD");
    o.close();

    return 0;
}
