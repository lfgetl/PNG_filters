#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "color.h"

#pragma pack(push)
#pragma pack(1)
struct FileHeader {
    char file_type[2];
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_bits;
};
#pragma pack(pop)
struct InfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes_count;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_data_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t color_used;
    uint32_t color_important;
};
const size_t DIVIDE = 32;

class Image {
public:
    Image() = default;

    explicit Image(std::string path) {
        WriteImageFrom(path);
    }

    Image(Image &other) {
        file_header_ = other.file_header_;
        info_header_ = other.info_header_;
        pixels_ = other.pixels_;
        line_size_ = other.line_size_;
    }

    std::vector<std::vector<Pixel>> *GetPixels() {
        return &pixels_;
    }

    InfoHeader *GetInfoHeader() {
        return &info_header_;
    }

    size_t *GetLineSize() {
        return &line_size_;
    }

    void WriteImageTo(std::string path);

private:
    FileHeader file_header_;
    InfoHeader info_header_;
    std::vector<std::vector<Pixel>> pixels_;

    void WriteImageFrom(std::string path);

    size_t line_size_;
};
