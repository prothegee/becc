#ifndef BEHH_GENERATE_HH
#define BEHH_GENERATE_HH
#include "../pch.hh"

#include <behh/constants/file_const.hh>

#if BEHH_USING_ZXING_CPP
#include <ZXing/BarcodeFormat.h>
#include <ZXing/BitMatrix.h>
#include <ZXing/BitMatrixIO.h>
#include <ZXing/CharacterSet.h>
#include <ZXing/DecodeHints.h>
#include <ZXing/ImageView.h>
#include <ZXing/MultiFormatWriter.h>
#include <ZXing/ReadBarcode.h>
#include <ZXing/ReaderOptions.h>
#include <ZXing/TextUtfEncoding.h>

#if ZXING_EXPERIMENTAL_API
#include <ZXing/WriteBarcode.h>
#endif // ZXING_EXPERIMENTAL_API

using namespace ZXing;
#endif // BEHH_USING_ZXING_CPP

#if BEHH_USING_NANOSVG
#include <nanosvg/nanosvg.h>
#include <nanosvg/nanosvgrast.h>
#endif // BEHH_USING_NANOSVG

namespace behh {
namespace generate_functions {

namespace image {
#if BEHH_USING_ZXING_CPP && BEHH_USING_NANOSVG
/**
 * @brief generate svg from matrix
 *
 * @param file_output
 * @param matrix
 * @param width
 * @param height
 * @param margin
 * @return int32_t 1 mean ok
 */
int32_t matrix_to_svg(const std::string& file_output, const BitMatrix& matrix, const int32_t& width, const int32_t& height, const int32_t& margin);
#endif // BEHH_USING_ZXING_CPP && BEHH_USING_NANOSVG

#if BEHH_USING_STB
/**
 * @brief create png image from buffer
 *
 * @param file_output
 * @param buffer
 * @param width
 * @param height
 * @param stb_comp
 * @return int32_t 1 mean ok
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
 * @return int32_t 1 mean ok
 */
int32_t buffer_to_jpg(const std::string& file_output, const buffer_t& buffer, const int32_t& width, const int32_t& height, const int32_t& stb_comp = 4);
#endif // BEHH_USING_STB
} // namespace image

namespace rasterize {
#if BEHH_USING_NANOSVG
/**
 * @brief rasterize file_path of svg to output
 *
 * @param file_path
 * @param output
 * @param width
 * @param height
 * @return int32_t 1 mean ok
 */
int32_t from_svg(const std::string& file_path, std::vector<uint8_t>& output, int32_t& width, int32_t& height);
#endif // BEHH_USING_NANOSVG
} // namespace rasterize

namespace barqr {
#if BEHH_USING_ZXING_CPP && BEHH_USING_STB && BEHH_USING_NANOSVG
/**
 * @brief encode content to file_output
 *
 * @note important: size of width & height if less than 256 may cause a trouble
 * @note important: considering use std::thread or std::asyc is recomended, it can cause invalid pointer if the usage is more than once in the same implementation
 *
 * @param content
 * @param file_output
 * @param width
 * @param height
 * @param margin
 * @param format
 * @param channels
 * @return int32_t 1 mean ok
 */
int32_t encode(const std::string& content, const std::string& file_output, const int32_t& width, const int32_t& height, const int32_t& margin, const BarcodeFormat& format, const int32_t& channels = 4);

/**
 * @brief decode content to file_output
 *
 * @note important: size of width & height if less than 256 may cause a trouble
 * @note important: considering use std::thread or std::asyc is recomended, it can cause invalid pointer if the usage is more than once in the same implementation
 *
 * @param content
 * @param file_output
 * @param format
 * @param tryhard
 * @return int32_t 1 mean ok
 */
int32_t decode(const std::string& content, std::string& file_output, const BarcodeFormat& format, const bool& tryhard = true);
#endif // BEHH_USING_ZXING_CPP && BEHH_USING_STB && BEHH_USING_NANOSVG
} // namespace barqr

} // namespace generate_functions
} // namespace behh

#endif // BEHH_GENERATE_HH
