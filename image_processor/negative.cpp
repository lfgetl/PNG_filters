#include "negative.h"

void Negative::Apply(Image &image) {
    std::vector<std::vector<Pixel>> new_pixels = *image.GetPixels();
    for (size_t i = 0; i < abs(image.GetInfoHeader()->height); ++i) {
        for (size_t j = 0; j < static_cast<size_t>(image.GetInfoHeader()->width); ++j) {
            Pixel &pixel = new_pixels[i][j];
            pixel.red_ = 1 - pixel.red_;
            pixel.green_ = 1 - pixel.green_;
            pixel.blue_ = 1 - pixel.blue_;
        }
    }
    *image.GetPixels() = new_pixels;
}
