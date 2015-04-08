mkdir Build
cd Build
cmake .. -G "Visual Studio 14"
cmake --build .
ctest .