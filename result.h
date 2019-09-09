#include <vector>
#include <ostream>
class result {
    friend ostream& operator<<(ostream& o, const result& res) {
        o << result::N << "," << res.bins << "," << res.sum << "," << res.avg_free_space << "\n";
        return o;
    }
    public:
        static int N;
        int bins;
        double sum;
        double avg_free_space;
};