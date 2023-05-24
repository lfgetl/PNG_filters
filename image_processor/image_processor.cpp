#include "image_processor.h"

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cout
                << "TUTORIAL:"
                   "This is a BMP image_processor. Input must look like {path to input file} {path to output file} "
                   "{filter1 with arguments} {filter2 with arguments} ...\n"
                   "Example: input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5\n"
                   "List of filters:\n"
                   "-crop {args: width, height} - crops the image to the size width x height from the top-left angle.\n"
                   "-gs {args: none} - turns all the colors into shades of grey.\n"
                   "-sharp {args: none} - sharpens image.\n"
                   "-neg {args: none} - changes all the colors to their negative.\n"
                   "-edge {args: threshold} - finds edges. If pixel value is > threshold, it is colored white, "
                   "otherwise - black.\n"
                   "-blur {args: sigma} - Gaussian blur with sigma as its standard deviation.\n"
                   "-pixelize {args: radius} - turns image into a set of square blocks of the same colour. Radius sets the "
                   "size of each block. It does not change the resolution."
                << std::endl;
        return 0;
    }
    Image orig_image;
    Image new_image;
    try {
        orig_image = Image(argv[1]);
        new_image = Image(orig_image);
    } catch (const std::exception &) {
        std::cout << "Something wrong with the original file (maybe it's not BMP)";
        return 0;
    }
    if (argc == 2) {
        std::cout << "ERROR: No destination";
        return 0;
    }
    std::map<std::string, size_t> filters = {{"-crop",     2},
                                             {"-gs",       0},
                                             {"-neg",      0},
                                             {"-sharp",    0},
                                             {"-edge",     1},
                                             {"-blur",     1},
                                             {"-pixelize", 1}};
    std::string end_path = argv[2];
    for (int i = 3; i < argc; ++i) {
        std::string filter = argv[i];
        if (filters.find(filter) != filters.end()) {
            std::vector<std::string> args;
            for (size_t j = 0; j < filters[filter]; ++j) {
                ++i;
                if (i < argc) {
                    args.push_back(argv[i]);
                }
            }
            try {
                if (filter == "-crop") {
                    Crop crop(args);
                    crop.Apply(new_image);
                }
                if (filter == "-gs") {
                    GrayScale gs(args);
                    gs.Apply(new_image);
                }
                if (filter == "-neg") {
                    Negative neg(args);
                    neg.Apply(new_image);
                }
                if (filter == "-sharp") {
                    Sharp sharp(args);
                    sharp.Apply(new_image);
                }
                if (filter == "-edge") {
                    EdgeDetector edge(args);
                    edge.Apply(new_image);
                }
                if (filter == "-blur") {
                    Gauss gauss(args);
                    gauss.Apply(new_image);
                }
                if (filter == "-pixelize") {
                    Pixelize pixelize(args);
                    pixelize.Apply(new_image);
                }
            } catch (const Filter::BadArguments &bad_arguments) {
                std::cout << "Invalid argument in -" << bad_arguments.FilterName();
                return 0;
            }

        } else {
            std::cout << "No such filter: " << filter;
            return 0;
        }
    }
    new_image.WriteImageTo(end_path);
    return 0;
}
