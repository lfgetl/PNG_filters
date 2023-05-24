#include "filter.h"

class Pixelize : public Filter {
public:
    explicit Pixelize(std::vector<std::string> args);

    void Apply(Image &image) override;

private:
    int radius_;
};
