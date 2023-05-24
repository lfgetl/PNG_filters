#pragma once

#include "filter.h"

class GrayScale : public Filter {
public:
    explicit GrayScale(std::vector<std::string> args) : Filter(args) {
    }

    void Apply(Image &image) override;
};
