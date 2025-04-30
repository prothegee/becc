# unix
mkdir -p build/Debug;

cmake -G "Ninja" -B build/Debug -DBUILD_TOOLS=false -DBUILD_TESTS=true -DBUILD_SHARED_LIBS=false -DBUILD_STATIC_LIBS=false -DBUILD_VENDOR_SDL3=true -DBUILD_VENDOR_STB=true -DBUILD_VENDOR_HARU=true -DBUILD_VENDOR_JSONCPP=true -DBUILD_VENDOR_OPENSSL=true -DBUILD_VENDOR_NANOSVG=true -DBUILD_VENDOR_ZXING_CPP=true;

cmake --build build/Debug --target all;