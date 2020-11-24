include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/../ngstd)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(kernel_generator generate_mat_kernels.cpp)

target_compile_options(kernel_generator PUBLIC ${NGBLA_COMPILE_OPTIONS})

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/matkernel.hpp
  COMMAND kernel_generator
  DEPENDS kernel_generator
  )

add_custom_target(kernel_generated DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/matkernel.hpp)

target_sources(ngcore
  PRIVATE
  # add_library(ngbla STATIC
        bandmatrix.cpp calcinverse.cpp cholesky.cpp 
        eigensystem.cpp LapackGEP.cpp
        avector.cpp ngblas.cpp triangular.cpp householder.cpp LUdecomposition.cpp
        )

add_dependencies(ngcore kernel_generated)

target_include_directories(ngcore PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(ngcore PRIVATE ${NGSOLVE_COMPILE_DEFINITIONS_PRIVATE})

