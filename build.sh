rm -rf build
mkdir build
cmake -S . -B build/ -DCMAKE_TOOLCHAIN_FILE=lib/scripts/buildsystems/vcpkg.cmake