cmake_minimum_required(VERSION 3.22)
project(StudentManage)
# 设置库和可执行文件输出的位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 编译子文件的CmakeLists
add_subdirectory(src)