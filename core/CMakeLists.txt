
add_library(ngcore STATIC
  archive.cpp
  bitarray.cpp
  exception.cpp
  localheap.cpp
  logging.cpp
  flags.cpp
  paje_trace.cpp
  profiler.cpp
  table.cpp
  taskmanager.cpp
  utils.cpp
  version.cpp
  )

if(WIN32)
  list(APPEND NGBLA_COMPILE_OPTOINS /bigobj /MP /W1 /wd4068)
  get_WIN32_WINNT(ver)
  target_compile_definitions(ngcore PUBLIC _WIN32_WINNT=${ver} WNT WNT_WINDOW NOMINMAX MSVC_EXPRESS _CRT_SECURE_NO_WARNINGS HAVE_STRUCT_TIMESPEC)
  target_link_options(ngcore PUBLIC /ignore:4273 /ignore:4217 /ignore:4049)
endif(WIN32)

# target_compile_definitions(ngcore PRIVATE NGCORE_EXPORTS)
# target_include_directories(ngcore INTERFACE $<INSTALL_INTERFACE:${NG_INSTALL_DIR_INCLUDE}> $<INSTALL_INTERFACE:${NG_INSTALL_DIR_INCLUDE}/include>)
target_compile_options(ngcore PUBLIC ${NGBLA_COMPILE_OPTIONS})

if(CHECK_RANGE OR CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "DEBUG")
  target_compile_definitions(ngcore PUBLIC NETGEN_ENABLE_CHECK_RANGE)
endif(CHECK_RANGE OR CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "DEBUG")

target_link_libraries(ngcore PRIVATE ${CMAKE_THREAD_LIBS_INIT})
