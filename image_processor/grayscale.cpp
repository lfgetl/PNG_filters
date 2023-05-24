#include "grayscale.h"

const double RED_COEFF = 0.299;
const double GREEN_COEFF = 0.587;
const double BLUE_COEFF = 0.114;

void GrayScale::Apply(Image &image) {
    std::vector<std::vector<Pixel>> new_pixels = *image.GetPixels();
    for (size_t i = 0; i < abs(image.GetInfoHeader()->height); ++i) {
        for (size_t j = 0; j < static_cast<size_t>(image.GetInfoHeader()->width); ++j) {
            Pixel &pixel = new_pixels[i][j];
            pixel.red_ = RED_COEFF * pixel.red_ + GREEN_COEFF * pixel.green_ + BLUE_COEFF * pixel.blue_;
            pixel.green_ = pixel.red_;
            pixel.blue_ = pixel.red_;
        }
    }
    *image.GetPixels() = new_pixels;
}
