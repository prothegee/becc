#ifndef BECC_GENERATE_HH
#define BECC_GENERATE_HH
#include "../becc.hh"
#include "../constants/file_const.hh"

#if BECC_USING_ZXING_CPP
#include <ZXing/BarcodeFormat.h>
#include <ZXing/BitMatrix.h>
#include <ZXing/BitMatrixIO.h>
#include <ZXing/CharacterSet.h>
#include <ZXing/TextUtfEncoding.h>
#include <ZXing/MultiFormatWriter.h>
#include <ZXing/ReadBarcode.h>
#include <ZXing/ReaderOptions.h>
#include <ZXing/DecodeHints.h>
#include <ZXing/ImageView.h>

#if ZXING_EXPERIMENTAL_API
#include <ZXing/WriteBarcode.h>
#endif // ZXING_EXPERIMENTAL_API
#endif // BECC_USING_ZXING_CPP

#if BECC_USING_NANOSVG
#include <nanosvg/nanosvg.h>
#include <nanosvg/nanosvgrast.h>
#endif // BECC_USING_NANOSVG

namespace becc
{
namespace generate_functions
{

namespace image
{
#if BECC_USING_ZXING_CPP && BECC_USING_NANOSVG
/**
 * @brief generate svg from matrix
 * 
 * @param file_output 
 * @param matrix 
 * @param width 
 * @param height 
 * @param margin 
 * @return int32_t 0 mean ok
 */
int32_t matrix_to_svg(const std::string& file_output, const ZXing::BitMatrix& matrix, const int32_t& width, const int32_t& height, const int32_t& margin);
#endif // BECC_USING_ZXING_CPP && BECC_USING_NANOSVG

#if BECC_USING_STB
/**
 * @brief create png image from buffer
 * 
 * @param file_output 
 * @param buffer 
 * @param width 
 * @param height 
 * @param stb_comp 
 * @return int32_t 0 mean ok
 */
int32_t buffer_to_png(const std::string& file_output, const buffer_t& buffer, const int32_t& width, const int32_t& height, const int32_t& stb_comp = 4);

/**
 * @brief create jpg/jpeg image from buffer
 * 
 * @param file_output 
 * @param buffer 
 * @param width 
 * @param height 
 * @param stb_comp 
 * @return int32_t 0 mean ok
 */
int32_t buffer_to_jpg(const std::string& file_output, const buffer_t& buffer, const int32_t& width, const int32_t& height, const int32_t& stb_comp = 4);
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

#endif // BECC_GENERATE_HH
