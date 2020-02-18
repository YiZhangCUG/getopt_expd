# 设定源文件文件夹
aux_source_directory(lib/ GETOPT_EXPD_SRC)

# 以下部分为库的编译
# 注意目标名必须唯一 所以不能直接生成相同名称的动态库与静态库
# 注意此处不必为目标名称添加lib前缀和相应后缀，cmake会自行添加
add_library(getopt_expd SHARED ${GETOPT_EXPD_SRC})
# 首先添加静态库的生成命令
add_library(getopt_expd_static STATIC ${GETOPT_EXPD_SRC})
# 设置静态库的输出名称从而获得与动态库名称相同的静态库
set_target_properties(getopt_expd_static PROPERTIES OUTPUT_NAME "getopt_expd")
# 设置输出目标属性以同时输出动态库与静态库
set_target_properties(getopt_expd PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(getopt_expd_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
# 设置动态库的版本号
set_target_properties(getopt_expd PROPERTIES VERSION 1.0 SOVERSION 1.0)
# 设置库文件的输出地址
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# 库的安装命令
install(TARGETS getopt_expd getopt_expd_static
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
# 头文件安装命令
install(FILES lib/getopt_expd.h DESTINATION include)

# 以下部分为例子程序的编译
# 设置可执行文件的输出地址
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 添加可执行文件 命令行
add_executable(getopt_expd_sample sample/sample.cxx)
# 为安装文件添加动态库的搜索地址
set_target_properties(getopt_expd_sample PROPERTIES INSTALL_RPATH "/usr/local/lib")
# 链接动态库
target_link_libraries(getopt_expd_sample PUBLIC getopt_expd)