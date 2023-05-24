#include "filter.h"

const double MID = 5;

class Sharp : public Filter {
public:
    explicit Sharp(std::vector<std::string> args) : Filter(args) {
        matrix_ = {{0,  -1,  0},
                   {-1, MID, -1},
                   {0,  -1,  0}};
    }
};