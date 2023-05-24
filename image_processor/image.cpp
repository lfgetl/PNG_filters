#include "image.h"

void Image::WriteImageFrom(std::string path) {
    std::ifstream file(path, std::ios::binary);
    file.read(reinterpret_cast<char *>(&file_header_), sizeof(FileHeader));
    file.read(reinterpret_cast<char *>(&info_header_), sizeof(InfoHeader));
    line_size_ = (info_header_.bits_per_pixel * abs(info_header_.width) + DIVIDE - 1) / DIVIDE * 4;
    for (size_t i = 0; i < abs(info_header_.height); ++i) {
        std::vector<uint8_t> line;
        line.resize(line_size_);
        pixels_.push_back({});
        file.read(reinterpret_cast<char *>(line.data()), static_cast<std::streamsize>(line_size_));
        for (size_t j = 0; j < line_size_; j += 3) {
            if (j + 2 < line_size_) {
                pixels_[i].push_back({line[j + 2], line[j + 1], line[j]});  // проверить порядок RGB
            }
        }
    }

    if (info_header_.height < 0) {
        std::reverse(pixels_.begin(), pixels_.end());
    }
}

void Image::WriteImageTo(std::string path) {
    std::ofstream file_out(path, std::ios::binary);
    file_out.write(reinterpret_cast<char *>(&file_header_), sizeof(FileHeader));
    file_out.write(reinterpret_cast<char *>(&info_header_), sizeof(InfoHeader));
    if (info_header_.height < 0) {
        std::reverse(pixels_.begin(), pixels_.end());
    }
    size_t offset_size = line_size_ - 3 * info_header_.width;
    std::vector<uint8_t> offset;
    offset.resize(offset_size, 0);
    for (size_t i = 0; i < abs(info_header_.height); ++i) {
        for (size_t j = 0; j < static_cast<size_t>(info_header_.width); ++j) {
            std::vector<uint8_t> pixel = pixels_[i][j].WritePixel();
            file_out.write(reinterpret_cast<char *>(pixel.data()), static_cast<std::streamsize>(pixel.size()));
        }
        file_out.write(reinterpret_cast<char *>(offset.data()), static_cast<std::streamsize>(offset_size));
    }
}
