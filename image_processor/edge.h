#include "grayscale.h"

class EdgeDetector : public Filter {
public:
    explicit EdgeDetector(std::vector<std::string> args);

    void Apply(Image &image) override;

private:
    double threshold_;
};