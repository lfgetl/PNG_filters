#include "gauss.h"

constexpr double pi = 3.14159265358979323846;

Gauss::Gauss(std::vector<std::string> args) : Filter(args) {
    if (args.size() != 1) {
        throw BadArguments("gauss");
    }
    try {
        sigma_ = std::stod(args[0]);
        if (sigma_ < 0) {
            throw BadArguments("gauss");
        }
    } catch (const std::invalid_argument &) {
        throw BadArguments("gauss");
    }
}

void Gauss::Apply(Image &image) {
    std::vector<std::vector<Pixel>> pixels = *image.GetPixels();
    std::vector<std::vector<Pixel>> new_image = pixels;
    MakeGaussWindow();
    for (size_t i = 0; i < abs(image.GetInfoHeader()->height); ++i) {
        for (size_t j = 0; j < static_cast<size_t>(image.GetInfoHeader()->width); ++j) {
            int width = image.GetInfoHeader()->width;
            double sum = 0;
            Pixel current(0, 0, 0);
            for (auto &[diff, coeff]: gauss_window_) {
                int new_x = static_cast<int>(j) + diff;
                if (new_x < 0 || new_x >= width) {
                    continue;
                }
                Pixel add;
                add.Copy(pixels[i][new_x]);
                add *= coeff;
                current += add;
                sum += coeff;
            }
            double coeff = 1 / (front_coeff_ * sum / gauss_sum_);
            current *= coeff;
            new_image[i][j].Copy(current);
        }
    }
    pixels = new_image;

    for (size_t i = 0; i < static_cast<size_t>(image.GetInfoHeader()->width); ++i) {
        for (size_t j = 0; j < abs(image.GetInfoHeader()->height); ++j) {
            int height = abs(image.GetInfoHeader()->height);
            double sum = 0;
            Pixel current(0, 0, 0);
            for (auto &[diff, coeff]: gauss_window_) {
                int new_y = static_cast<int>(j) + diff;
                if (new_y < 0 || new_y >= height) {
                    continue;
                }
                Pixel add;
                add.Copy(pixels[new_y][i]);
                add *= coeff;
                current += add;
                sum += coeff;
            }
            double coeff = 1 / (front_coeff_ * (sum / gauss_sum_));
            current *= coeff;
            new_image[j][i].Copy(current);
        }
    }
    pixels = new_image;
    *image.GetPixels() = pixels;
}

void Gauss::MakeGaussWindow() {
    int size = ceil(3 * sigma_);
    gauss_sum_ = 1;
    gauss_window_[0] = 1;
    front_coeff_ = sqrt(2 * pi * sigma_ * sigma_);
    for (int i = 1; i <= size; ++i) {
        gauss_window_[i] = exp((-i * i) / (2 * sigma_ * sigma_));
        gauss_window_[-i] = gauss_window_[i];
        gauss_sum_ += 2 * gauss_window_[i];
    }
}
