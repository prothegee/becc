# unix
mkdir -p build/debug;

cmake -G "Ninja" -B build/debug -DCMAKE_BUILD_TYPE=Debug -DBECC_BUILD_TOOLS=true -DBECC_BUILD_TESTS=true -DBECC_BUILD_VENDOR_STB=true -DBECC_BUILD_VENDOR_SDL3=true -DBECC_BUILD_VENDOR_HARU=true -DBECC_BUILD_VENDOR_NANOSVG=true;

cmake --build build/debug --target all;