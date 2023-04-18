# rm -rf build
mkdir -p build
cd build
cmake .. "-DCMAKE_TOOLCHAIN_FILE=/home/ax/repos/vcpkg/scripts/buildsystems/vcpkg.cmake" && make -j axm && make -j axmc && cd .. && ./test.sh
