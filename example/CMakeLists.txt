cmake_minimum_required( VERSION 2.8 )
set (CMAKE_CXX_STANDARD 17)

PROJECT(test_simple_topo)
MESSAGE(STATUS "Project HSP-NS test_simple_topo")

SET(CMAKE_BUILD_TYPE "Debug")
SET(LOG "ON")        ## OFF

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O2 -Wall -g2 -ggdb")

## On-off log
if(LOG STREQUAL "OFF") 
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D _NO_LOG_")
endif()

# 头文件
include_directories(
    ${PROJECT_SOURCE_DIR}/../network/include/
    ${PROJECT_SOURCE_DIR}/
    ${PROJECT_SOURCE_DIR}/../lib/skiplist/include/
    ${PROJECT_SOURCE_DIR}/../lib/ThreadPool/
    ${PROJECT_SOURCE_DIR}/../core-parallel/include/
)

# 源文件
set(LIB_CORE_NAME nscore)
aux_source_directory(${PROJECT_SOURCE_DIR}/../core-parallel/src CORE_SRC)
add_library(${LIB_CORE_NAME} STATIC ${CORE_SRC})

set(LIB_NETWORK_NAME netwrok)
aux_source_directory(${PROJECT_SOURCE_DIR}/../network/src NETWORK_SRC)
add_library(${LIB_NETWORK_NAME} STATIC ${NETWORK_SRC})

set(LIB_THREAD_POOL threadpool)
aux_source_directory(${PROJECT_SOURCE_DIR}/../lib/ThreadPool/ THREAD_POOL_SRC)
add_library(${LIB_THREAD_POOL} STATIC ${THREAD_POOL_SRC})

set(LIB_SKIPLIST skiplist)
aux_source_directory(${PROJECT_SOURCE_DIR}/../lib/skiplist/src/ SKIPLIST_SRC)
add_library(${LIB_SKIPLIST} STATIC ${SKIPLIST_SRC})

# 找到g3logger
find_package(g3logger CONFIG REQUIRED)

# 编译主函数，生成可执行文件
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
aux_source_directory(${PROJECT_SOURCE_DIR}/ TEST_SRC)
add_executable(${PROJECT_NAME} ${TEST_SRC})

# 把库链接起来
target_link_libraries(${PROJECT_NAME} ${LIB_NETWORK_NAME} ${LIB_CORE_NAME} pthread g3logger ${LIB_THREAD_POOL} ${LIB_SKIPLIST}) 

