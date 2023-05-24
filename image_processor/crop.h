#include "filter.h"

class Crop : public Filter {
public:
    explicit Crop(std::vector<std::string> args);

    void Apply(Image &image) override;

private:
    size_t width_;
    size_t height_;
};
