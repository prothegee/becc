# unix
mkdir -p build/Debug;

cmake -G "Ninja" -B build/Debug -DBUILD_TOOLS=false -DBUILD_TESTS=true -DBUILD_SHARED_LIBS=false -DBUILD_VENDOR_SDL=true -DBUILD_VENDOR_STB=true -DBUILD_VENDOR_HARU=true -DBUILD_VENDOR_NANOSVG=true -DBUILD_VENDOR_ZXING_CPP=true -DBUILD_USE_VCPKG=false; # -DVCPKG_TRIPLET="" -DVCPKG_DEFAULT_TRIPLET="";

cmake --build build/Debug --target all;