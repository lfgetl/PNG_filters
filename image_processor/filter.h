#pragma once

#include <vector>
#include "image.h"

class Filter {
public:
    explicit Filter(std::vector<std::string> args) {
    }

    virtual void Apply(Image &image);

    class BadArguments : public std::exception {
    public:
        explicit BadArguments(std::string filter_name) : filter_name_(filter_name) {
        }

        std::string FilterName() const {
            return filter_name_;
        }

    private:
        std::string filter_name_;
    };

protected:
    std::vector<std::vector<double>> matrix_;
};