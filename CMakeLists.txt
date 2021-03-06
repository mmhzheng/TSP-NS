cmake_minimum_required( VERSION 2.8 )
set (CMAKE_CXX_STANDARD 17)

PROJECT(TSP_NS)
MESSAGE(STATUS "Project TSP-NS")

SET(CMAKE_BUILD_TYPE "Debug")
SET(LOG "OFF")        ## OFF

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O2 -Wall -g2 -ggdb")

## On-off log
if(LOG STREQUAL "OFF") 
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D _NO_LOG_")
endif()

# 头文件
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/skiplist/include
    ${PROJECT_SOURCE_DIR}/lib/ThreadPool
)
# 源文件
# 找到g3logger
find_package(g3logger CONFIG REQUIRED)

set(LIB_THREAD_POOL threadpool)
aux_source_directory(${PROJECT_SOURCE_DIR}/lib/ThreadPool/ THREAD_POOL_SRC)
add_library(${LIB_THREAD_POOL} STATIC ${THREAD_POOL_SRC})

set(LIB_SKIPLIST skiplist)
aux_source_directory(${PROJECT_SOURCE_DIR}/lib/skiplist/src/ SKIPLIST_SRC)
add_library(${LIB_SKIPLIST} STATIC ${SKIPLIST_SRC})

set(LIB_CORE_NAME TSP_NS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src CORE_SRC)
add_library(${PROJECT_NAME} STATIC ${CORE_SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_SKIPLIST} ${LIB_THREAD_POOL} pthread g3logger)
target_include_directories (${PROJECT_NAME} PUBLIC 
                            ${PROJECT_SOURCE_DIR}/include
                            ${PROJECT_SOURCE_DIR}/lib
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# 编译主函数，生成可执行文件
set(TEST_EXAMPLE test_example)
aux_source_directory(${PROJECT_SOURCE_DIR}/example TEST_SRC)
add_executable(${TEST_EXAMPLE} ${TEST_SRC})
# 把库链接起来
target_link_libraries(${TEST_EXAMPLE} ${LIB_CORE_NAME} ${LIB_SKIPLIST} ${LIB_THREAD_POOL} pthread g3logger)