rm -rf build
mkdir build
cmake -S . -B build/ -DCMAKE_TOOLCHAIN_FILE=~/source/repos/HTMLQuery/lib/scripts/buildsystems/vcpkg.cmake