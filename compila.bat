mkdir build
cd build
conan install .. -g CMakeDeps -g CMakeToolchain --build=missing
cmake .. -DCMAKE_POLICY_DEFAULT_CMP0091="NEW" -DCMAKE_TOOLCHAIN_FILE="/generators/conan_toolchain.cmake" -G "Visual Studio 17 2022"
cmake --build . --config Release