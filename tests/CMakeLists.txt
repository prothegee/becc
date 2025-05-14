cmake_minimum_required(VERSION 3.15...3.30)

project(test_becc)

# test_aes_openssl
if(BECC_USING_OPENSSL)
    add_executable(test_aes_openssl test_aes_openssl.cc)
    target_link_libraries(test_aes_openssl PRIVATE becc becc_static)
    message(NOTICE "-- becc: adding test_aes_openssl")
endif()

# test_argon2
if(BECC_USING_ARGON2)
    add_executable(test_argon2 test_argon2.cc)
    target_link_libraries(test_argon2 PRIVATE becc becc_static)
    message(NOTICE "-- becc: adding test_argon2")
endif()

# test_barcode_qrcode
if(BECC_USING_STB AND BECC_USING_NANOSVG AND BECC_USING_ZXING_CPP)
    add_executable(test_barcode_qrcode test_barcode_qrcode.cc)
    target_link_libraries(test_barcode_qrcode PRIVATE becc becc_static)
    message(NOTICE "-- becc: adding test_barcode_qrcode")
endif()

# test_base64
add_executable(test_base64 test_base64.cc)
target_link_libraries(test_base64 PRIVATE becc becc_static)
message(NOTICE "-- becc: adding test_base64")

# test_communication_smtps
if(BECC_USING_CURL_EXECUTEABLE AND BECC_USING_DROGON)
    add_executable(test_communication_smtps test_communication_smtps.cc)
    target_link_libraries(test_communication_smtps PRIVATE becc becc_static Drogon::Drogon)
    message(NOTICE "-- becc: adding test_communication_smtps")
endif()

# test_date_and_time
add_executable(test_date_and_time test_date_and_time.cc)
target_link_libraries(test_date_and_time PRIVATE becc becc_static)
message(NOTICE "-- becc: adding test_date_and_time")

# test_database_scylla_rw
if(BECC_USING_SCYLLADB)
    add_executable(test_database_scylla_rw test_database_scylla_rw.cc)
    target_link_libraries(test_database_scylla_rw becc becc_static)
    message(NOTICE "-- becc: adding test_database_scylla_rw")
endif()

# test_file_enc_dec
if(BECC_USING_OPENSSL)
    add_executable(test_file_enc_dec test_file_enc_dec.cc)
    target_link_libraries(test_file_enc_dec PRIVATE becc becc_static)

    message(NOTICE "-- becc: adding test_file_enc_dec")
endif()

# test_sdl3_check_screen_resolutions
if(BECC_USING_SDL3)
    add_executable(test_sdl3_check_screen_resolutions test_sdl3_check_screen_resolutions.cc)
    target_link_libraries(test_sdl3_check_screen_resolutions PRIVATE becc becc_static)
    message(NOTICE "-- becc: adding test_sdl3_check_screen_resolutions")
endif()