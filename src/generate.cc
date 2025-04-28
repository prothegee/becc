#include <becc/functions/generate.hh>
#include <becc/functions/utility.hh>

#if BECC_USING_STB
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif // STB_IMAGE_IMPLEMENTATION
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#endif // STB_IMAGE_WRITE_IMPLEMENTATION
#endif // BECC_USING_STB

#include <iostream>
#include <fstream>

namespace becc
{
namespace generate_functions
{

namespace image
{
#if BECC_USING_ZXING_CPP && BECC_USING_NANOSVG
int32_t matrix_to_svg(const std::string& file_output, const ZXing::BitMatrix& matrix, const int32_t& width, const int32_t& height, const int32_t& margin)
{
    if (!utility_functions::find::input_ends_with(file_output, FILE_EXTENSION_SVG_HINT) != 0)
    {
        std::cerr << "image::matrix_to_svg: file_output expecting .svg";
        return -1;
    }

    int32_t svgWidth = width + 2 * margin;
    int32_t svgHeight = height + 2 * margin;
    
    std::stringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"" << svgWidth << "\" height=\"" << svgHeight << "\">\n";

    ss << "<rect id=\"background\" width=\"" << svgWidth << "\" height=\"" << svgHeight << "\" fill=\"white\" />\n";
    
    for (int32_t y = 0; y < height; ++y)
    {
        for (int32_t x = 0; x < width; ++x)
        {
            if (matrix.get(x, y))
            {
                ss << "<rect x=\"" << (x + margin) << "\" y=\"" << (y + margin) << "\" width=\"1\" height=\"1\" fill=\"black\" />\n";
            }
        }
    }
    ss << "</svg>\n";

    std::ofstream file(file_output);

    try
    {
        if (!file.is_open())
        {
            std::cerr << "image::matrix_to_svg: fail to open " << file_output << "\n";
            return -2;
        }

        file << ss.str();
        file.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -69;
    }

    return 0;
}
#endif // BECC_USING_ZXING_CPP && BECC_USING_NANOSVG

#if BECC_USING_STB

int32_t buffer_to_png(const std::string& file_output, const buffer_t& buffer, const int32_t& width, const int32_t& height, const int32_t& stb_comp)
{
    if (!utility_functions::find::input_ends_with(file_output, FILE_EXTENSION_PNG_HINT) != 0)
    {
        return -1;
    }

    return stbi_write_png(file_output.c_str(), width, height, stb_comp, buffer.data(), (width * 4));
}

int32_t buffer_to_jpg(const std::string& file_output, const buffer_t& buffer, const int32_t& width, const int32_t& height, const int32_t& stb_comp)
{
    if (!utility_functions::find::input_ends_with(file_output, FILE_EXTENSION_JPG_HINT) != 0 || !utility_functions::find::input_ends_with(file_output, FILE_EXTENSION_JPEG_HINT) != 0)
    {
        return -1;
    }

    return stbi_write_jpg(file_output.c_str(), width, height, stb_comp, buffer.data(), (width * 4));
}
#endif // BECC_USING_STB
} // namespace image

// namespace rasterize
// {
// } // namespace rasterize

// namespace barqr
// {
// } // namespace barqr

} // namespace generate_functions
} // namespace becc
