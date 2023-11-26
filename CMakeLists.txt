CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

project(CefCMakeDemo LANGUAGES CXX VERSION 0.1.0)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置可执行文件的输出路径为bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
# 解决字符集问题
# ADD_COMPILE_OPTIONS("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
# ADD_COMPILE_OPTIONS("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_definitions(_UNICODE)
add_compile_definitions(NDEBUG)
# 控制项目所有编译单元_ITERATOR_DEBUG_LEVEL的值，
# 这里设置为和libcef_dll_wrapper.lib中的obj一致。
# ADD_COMPILE_DEFINITIONS($<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=0>)
# 由于项目仅release开发，使用的是cef的release库，针对cef设置一下NDEBUG宏
# add_definitions(-DUNICODE)
# add_definitions(-DNDEBUG)
# 设置编译时连接运行时的配置
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# 设置项目头文件的引入
include_directories("${CMAKE_SOURCE_DIR}/source")
# CEF相关头文件的引入
include_directories("${CMAKE_SOURCE_DIR}/cef_files")
include_directories("${CMAKE_SOURCE_DIR}/cef_files/include")
# 添加项目所有的文件
add_executable(${PROJECT_NAME}
        WIN32
        main.cpp
        source/resource.h
        source/simple_app.h
        source/simple_app.cpp
        source/simple_handler.h
        source/simple_handler.cpp
)
# 库链接
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        # 【CEF】cef相关静态库链接
        "${CMAKE_SOURCE_DIR}/cef_files/cef_sandbox.lib"
        "${CMAKE_SOURCE_DIR}/cef_files/libcef.lib"
        "${CMAKE_SOURCE_DIR}/cef_files/libcef_dll_wrapper.lib"
)