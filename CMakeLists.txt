if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING INTERNAL)
endif(NOT CMAKE_BUILD_TYPE)

cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0076 NEW)


option( USE_NATIVE_ARCH  "build for native cpu architecture" ON)

set(NG_COMPILE_FLAGS "" CACHE STRING "Additional compile flags")

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_modules")

if(APPLE)
  set(INSTALL_DIR_DEFAULT /Applications/Netgen.app)
else(APPLE)
  if(WIN32)
    set(INSTALL_DIR_DEFAULT "C:/netgen")
  else(WIN32)
    set(INSTALL_DIR_DEFAULT /opt/netgen)
  endif(WIN32)
endif(APPLE)

if(UNIX)
  message("Checking for write permissions in install directory...")
  execute_process(COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX})
  execute_process(COMMAND test -w ${CMAKE_INSTALL_PREFIX} RESULT_VARIABLE res)
  if(res)
    message(WARNING "No write access at install directory, please set correct permissions")
  endif()
endif(UNIX)

project(NGBla)
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${INSTALL_DIR_DEFAULT}" CACHE PATH "Install directory" FORCE)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Threads REQUIRED)

include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ngstd)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ngbla)

#######################################################################
# platform specific definitions and flags
macro(get_WIN32_WINNT version)
    if (WIN32 AND CMAKE_SYSTEM_VERSION)
        if("${CMAKE_SYSTEM_VERSION}" MATCHES "^([0-9]+)\\.([0-9]+)")
            math(EXPR ver "${CMAKE_MATCH_1}*100 + ${CMAKE_MATCH_2}")
        endif()
        set(${version} "0x${ver}")
    endif()
endmacro()

macro(get_dll_from_lib dll_path lib_path)
        get_filename_component(parent_lib_path ${lib} DIRECTORY)
        get_filename_component(lib_name ${lib} name)
endmacro()

set(CMAKE_CXX_STANDARD 17)

set(NGBLA_COMPILE_OPTIONS "")

#######################################################################
if(USE_NATIVE_ARCH)
    if(WIN32)
        include(CheckCXXSourceRuns)
        check_cxx_source_runs("
                #include <immintrin.h>
                int main()
                {
                    __m256d a{1.,2.,3.,4.};
                    __m256d b{2.,0.,3.,5.};
                    __m256d c = _mm256_mul_pd(a,b);
                    return 0;
                } " NG_HAVE_AVX)
        check_cxx_source_runs("
                #include <immintrin.h>
                int main()
                {
                    __m256i a{1,2,3,4};
                    __m256i b{2,0,3,5};
                    __m256i c = _mm256_cmpgt_epi64 (a,b);
                    return 0;
                } " NG_HAVE_AVX2)
        check_cxx_source_runs("
                #include <immintrin.h>
                int main()
                {
                    __m512d a{1.,2.,3.,4.};
                    __m512d b{5.,6.,7.,8.};
                    __m512d c = _mm512_mul_pd(a,b);
                    return 0;
                } " NG_HAVE_AVX512)

        if(NG_HAVE_AVX512)
            list(APPEND NGBLA_COMPILE_OPTIONS "/arch:AVX512")
            message(STATUS "Build for AVX512 CPU")
        elseif(NG_HAVE_AVX2)
            list(APPEND NGBLA_COMPILE_OPTIONS "/arch:AVX2")
            message(STATUS "Build for AVX2 CPU")
        elseif(NG_HAVE_AVX)
            list(APPEND NGBLA_COMPILE_OPTIONS "/arch:AVX")
            message(STATUS "Build for AVX CPU")
        else()
            message(STATUS "Build for generic CPU")
        endif()
    else()
        list(APPEND NGBLA_COMPILE_OPTIONS "-march=native")
    endif(WIN32)
    if(APPLE)
        # work-around for bug in Xcode 11.3: https://forums.developer.apple.com/thread/121887
        list(APPEND NGBLA_COMPILE_OPTIONS "-fno-stack-check")
    endif(APPLE)
endif(USE_NATIVE_ARCH)

add_subdirectory(core)
add_subdirectory(ngbla)
add_subdirectory(examples)

