# powershell
New-Item -Path "build/debug" -ItemType Directory -Force;

cmake -G "Ninja" -B build/debug -DCMAKE_BUILD_TYPE=Debug -DBECC_BUILD_TOOLS=true -DBECC_BUILD_TESTS=true -DBECC_BUILD_VENDOR_STB=true -DBECC_BUILD_VENDOR_SDL3=true -DBECC_BUILD_VENDOR_HARU=true -DBECC_BUILD_VENDOR_NANOSVG=true -DBECC_BUILD_VCPKG=true -DBECC_BUILD_VCPKG_TRIPLET="x64-window";

cmake --build build/debug --target all;