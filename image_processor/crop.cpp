#include "crop.h"

Crop::Crop(std::vector<std::string> args) : Filter(args) {
    if (args.size() != 2) {
        throw BadArguments("crop");
    }
    try {
        width_ = std::stoi(args[0]);
        height_ = std::stoi(args[1]);
        if (width_ <= 0 || height_ <= 0) {
            throw BadArguments("crop");
        }
    } catch (const std::invalid_argument &) {
        throw BadArguments("crop");
    }
}

void Crop::Apply(Image &image) {
    std::vector<std::vector<Pixel>> new_pixels;
    bool neg = false;
    std::vector<std::vector<Pixel>> pixels = *image.GetPixels();
    std::reverse(pixels.begin(), pixels.end());
    if (image.GetInfoHeader()->height < 0) {
        neg = true;
    }
    if (height_ > static_cast<size_t>(abs(image.GetInfoHeader()->height))) {
        height_ = abs(image.GetInfoHeader()->height);
    }
    if (width_ > static_cast<size_t>(image.GetInfoHeader()->width)) {
        width_ = image.GetInfoHeader()->width;
    }
    new_pixels.resize(height_);
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            new_pixels[i].push_back(pixels[i][j]);
        }
    }
    image.GetInfoHeader()->width = static_cast<int32_t>(width_);
    image.GetInfoHeader()->height = static_cast<int32_t>(height_);
    std::cout << new_pixels.size() << std::endl;
    if (neg) {
        image.GetInfoHeader()->height = -image.GetInfoHeader()->height;
    }
    std::reverse(new_pixels.begin(), new_pixels.end());
    *image.GetLineSize() =
            (image.GetInfoHeader()->bits_per_pixel * image.GetInfoHeader()->width + DIVIDE - 1) / DIVIDE * 4;
    image.GetInfoHeader()->image_data_size = *image.GetLineSize() * abs(image.GetInfoHeader()->height);
    *image.GetPixels() = new_pixels;
}
