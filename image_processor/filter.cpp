#include "filter.h"

void Filter::Apply(Image &image) {
    std::vector<std::vector<Pixel>> pixels = *image.GetPixels();
    std::vector<std::vector<Pixel>> new_pixels = pixels;
    for (size_t i = 0; i < abs(image.GetInfoHeader()->height); ++i) {
        for (size_t j = 0; j < static_cast<size_t>(image.GetInfoHeader()->width); ++j) {
            int height = abs(image.GetInfoHeader()->height);
            int width = image.GetInfoHeader()->width;
            Pixel &pixel = new_pixels[i][j];
            Pixel current_pixel(0, 0, 0);
            for (int y = 2; y >= 0; --y) {
                for (int x = 0; x <= 2; ++x) {
                    int cur_x = static_cast<int>(j) + x - 1;
                    int cur_y = static_cast<int>(i) - y + 1;
                    cur_x = std::max(0, std::min(width - 1, cur_x));
                    cur_y = std::max(0, std::min(height - 1, cur_y));
                    Pixel add;
                    add.Copy(pixels[cur_y][cur_x]);
                    add *= matrix_[y][x];
                    current_pixel += add;
                }
            }
            pixel.red_ = std::min(1., std::max(0., current_pixel.red_));
            pixel.green_ = std::min(1., std::max(0., current_pixel.green_));
            pixel.blue_ = std::min(1., std::max(0., current_pixel.blue_));
        }
    }
    *image.GetPixels() = new_pixels;
}
