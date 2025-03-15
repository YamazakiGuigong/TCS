rm -rf ./build-win
mkdir build-win
cd build-win
cmake --toolchain "../CMakeToolchainWin.txt" ..
cmake --build .