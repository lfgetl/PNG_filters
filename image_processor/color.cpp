#include "color.h"

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue) {
    red_ = static_cast<double>(red) / MAX_COLOR;
    green_ = static_cast<double>(green) / MAX_COLOR;
    blue_ = static_cast<double>(blue) / MAX_COLOR;
}

std::vector<uint8_t> Pixel::WritePixel() const {
    std::vector<uint8_t> result;
    result.resize(3);
    result[0] = static_cast<uint8_t>(blue_ * MAX_COLOR);
    result[1] = static_cast<uint8_t>(green_ * MAX_COLOR);
    result[2] = static_cast<uint8_t>(red_ * MAX_COLOR);
    return result;
}

void Pixel::operator+=(Pixel &other) {
    red_ += other.red_;
    green_ += other.green_;
    blue_ += other.blue_;
}

void Pixel::operator*=(double coeff) {
    red_ *= coeff;
    green_ *= coeff;
    blue_ *= coeff;
}

void Pixel::Copy(Pixel &other) {
    red_ = other.red_;
    green_ = other.green_;
    blue_ = other.blue_;
}
