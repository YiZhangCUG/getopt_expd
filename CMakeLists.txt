# 设置所需的CMAKE的最低版本
cmake_minimum_required(VERSION 3.15.2)
# 设置cxx编译器 如果你使用别的编译器，请在这里修改
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++-9)
# 设置工程名称和语言
project(GETOPT_EXPD VERSION 1.0.0 LANGUAGES CXX)
# 设置安装地址 改用homebrew后此句不再使用
# set(CMAKE_INSTALL_PREFIX /usr/local)
# 添加源文件地址
add_subdirectory(src/)