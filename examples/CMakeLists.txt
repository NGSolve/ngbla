add_executable(matvec matvec.cpp)   
target_link_libraries(matvec ngcore)  
 
add_executable(submatvec submatvec.cpp)   
target_link_libraries(submatvec ngcore)  
 
# add_executable(time_ngbla_matmult time_ngbla_matmult.cpp)
# target_link_libraries(time_ngbla_matmult ngcore)

add_executable(demo_LU demo_LU.cpp)
target_link_libraries(demo_LU ngcore)

add_executable(demo_QR demo_QR.cpp)
target_link_libraries(demo_QR ngcore)

add_executable(time_simple_matmult time_simple_matmult.cpp) 
target_link_libraries(time_simple_matmult ngcore)

add_executable(demo_simd demo_simd.cpp)
target_link_libraries(demo_simd ngcore)


