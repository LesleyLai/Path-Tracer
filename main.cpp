#include <iostream>

#include "image.hpp"

int main()
try {
    Image image;
    image.saveto("test.ppm");
    return 0;
} catch (const Cannot_write_file& e) {
    std::cerr << "Cannot write to file: " << e.what() << '\n';
    return -1;
} catch (const Unsupported_image_extension& e) {
    std::cerr << "Unsupported image extension: " << e.what() << '\n';
    std::cerr << "Currently: only ppm output is supported\n";
    return -2;
}  catch (...) {
    std::cerr << "Unknown exception";
    return -255;
}

