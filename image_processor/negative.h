#include "filter.h"

class Negative : public Filter {
public:
    explicit Negative(std::vector<std::string> args) : Filter(args) {
    }

    void Apply(Image &image) override;
};