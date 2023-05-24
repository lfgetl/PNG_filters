#include "pixelization.h"

Pixelize::Pixelize(std::vector<std::string> args) : Filter(args) {
    if (args.size() != 1) {
        throw BadArguments("pixelize");
    }
    try {
        radius_ = std::stoi(args[0]);
        if (radius_ <= 0) {
            throw BadArguments("pixelize");
        }
    } catch (const std::invalid_argument &) {
        throw BadArguments("pixelize");
    }
}

void Pixelize::Apply(Image &image) {
    std::vector<std::vector<Pixel>> pixels = *image.GetPixels();
    std::vector<std::vector<Pixel>> new_pixels = pixels;
    for (size_t i = radius_; i < abs(image.GetInfoHeader()->height); i += radius_) {
        for (size_t j = radius_; j < static_cast<size_t>(image.GetInfoHeader()->width); j += radius_) {
            size_t count = 0;
            Pixel new_pixel = Pixel(0, 0, 0);
            for (int di = -radius_; di <= radius_; ++di) {
                for (int dj = -radius_; dj <= radius_; ++dj) {
                    int new_i = di + static_cast<int>(i);
                    int new_j = dj + static_cast<int>(j);
                    if (new_i < 0 || new_i >= abs(image.GetInfoHeader()->height) || new_j < 0 ||
                        new_j >= image.GetInfoHeader()->width) {
                        continue;
                    }
                    ++count;
                    new_pixel += pixels[new_i][new_j];
                }
            }
            double coeff = 1.0 / static_cast<double>(count);
            new_pixel *= coeff;
            for (int di = -radius_; di <= radius_; ++di) {
                for (int dj = -radius_; dj <= radius_; ++dj) {
                    int new_i = di + static_cast<int>(i);
                    int new_j = dj + static_cast<int>(j);
                    if (new_i < 0 || new_i >= abs(image.GetInfoHeader()->height) || new_j < 0 ||
                        new_j >= image.GetInfoHeader()->width) {
                        continue;
                    }
                    new_pixels[new_i][new_j].Copy(new_pixel);
                }
            }
        }
    }
    *image.GetPixels() = new_pixels;
}
