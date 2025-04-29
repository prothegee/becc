cmake_minimum_required(VERSION 3.15...3.30)

project(test_becc)

include(CheckIncludeFileCXX)
include(CMakeDependentOption)
include(GenerateExportHeader)
include(FindPackageHandleStandardArgs)

# test_aes_openssl
add_executable(test_aes_openssl test_aes_openssl.cc)
target_link_libraries(test_aes_openssl PRIVATE becc)

# test_argon2
add_executable(test_argon2 test_argon2.cc)
target_link_libraries(test_argon2 PRIVATE becc)

# test_barcode_qrcode
add_executable(test_barcode_qrcode test_barcode_qrcode.cc)
target_link_libraries(test_barcode_qrcode PRIVATE becc)
# ## required
# if(NOT MSVC)
#     target_link_libraries(test_barcode_qrcode PRIVATE -lm)

#     if(BECC_COMPILER_GNU) # error gnu gcc 12.2
#         target_link_libraries(test_barcode_qrcode PRIVATE -lm) # somehow build not error
#     endif()
# endif()

# test_base64
add_executable(test_base64 test_base64.cc)
target_link_libraries(test_base64 PRIVATE becc)

# test_communication_smtps
add_executable(test_communication_smtps test_communication_smtps.cc)
target_link_libraries(test_communication_smtps PRIVATE becc Drogon::Drogon)

# test_date_and_time
add_executable(test_date_and_time test_date_and_time.cc)
target_link_libraries(test_date_and_time PRIVATE becc)

# test_file_enc_dec
add_executable(test_file_enc_dec test_file_enc_dec.cc)
target_link_libraries(test_file_enc_dec PRIVATE becc)