#include "filter.h"
#include <map>
#include <cmath>

class Gauss : public Filter {
public:
    explicit Gauss(std::vector<std::string> args);

    void Apply(Image &image) override;

private:
    double sigma_;

    void MakeGaussWindow();

    std::map<int, double> gauss_window_;
    double front_coeff_;
    double gauss_sum_;
};
