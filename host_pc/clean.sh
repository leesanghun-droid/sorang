#!/bin/bash
#!/bin/bash
sudo rm -r CMakeFiles
sudo rm -r cmake_install.cmake
sudo rm -r CMakeCache.txt
sudo rm -r Makefile
sudo cmake CMakeLists.txt
sudo rm -r libuart.a