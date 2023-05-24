#include "edge.h"

EdgeDetector::EdgeDetector(std::vector<std::string> args) : Filter(args) {
    if (args.size() != 1) {
        throw BadArguments("edge");
    }
    try {
        threshold_ = std::stod(args[0]);
    } catch (const std::invalid_argument &) {
        throw BadArguments("edge");
    }
    matrix_ = {{0,  -1, 0},
               {-1, 4,  -1},
               {0,  -1, 0}};
}

void EdgeDetector::Apply(Image &image) {
    GrayScale gray_scale({});
    gray_scale.Apply(image);
    Filter::Apply(image);
    std::vector<std::vector<Pixel>> pixels = *image.GetPixels();
    for (size_t i = 0; i < abs(image.GetInfoHeader()->height); ++i) {
        for (size_t j = 0; j < static_cast<size_t>(image.GetInfoHeader()->width); ++j) {
            Pixel &pixel = pixels[i][j];
            if (pixel.red_ <= threshold_) {
                pixel.red_ = 0;
                pixel.green_ = 0;
                pixel.blue_ = 0;
            } else {
                pixel.red_ = 1;
                pixel.green_ = 1;
                pixel.blue_ = 1;
            }
        }
    }
    *image.GetPixels() = pixels;
}
