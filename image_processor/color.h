#pragma once

#include <cstdint>
#include <vector>
#include <math.h>

const double MAX_COLOR = 255;

class Pixel {
public:
    double red_ = 0;
    double green_ = 0;
    double blue_ = 0;

    Pixel() {
    }

    Pixel(uint8_t red, uint8_t green, uint8_t blue);

    void Copy(Pixel &other);

    void operator+=(Pixel &other);

    void operator*=(double coeff);

    std::vector<unsigned char> WritePixel() const;
};