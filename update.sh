set -e

if [ "$#" -ne 1 ]; then
    echo "usage: $0 ngsolve_src_dir"
    exit 1
fi

cp $1/basiclinalg/LapackGEP.cpp ngbla/
cp $1/basiclinalg/LapackInterface.hpp ngbla/
cp $1/basiclinalg/avector.cpp ngbla/
cp $1/basiclinalg/avector.hpp ngbla/
cp $1/basiclinalg/bandmatrix.cpp ngbla/
cp $1/basiclinalg/bandmatrix.hpp ngbla/
cp $1/basiclinalg/bla.hpp ngbla/
cp $1/basiclinalg/calcinverse.cpp ngbla/
cp $1/basiclinalg/cholesky.cpp ngbla/
cp $1/basiclinalg/cholesky.hpp ngbla/
cp $1/basiclinalg/clapack.h ngbla/
cp $1/basiclinalg/eigensystem.cpp ngbla/
cp $1/basiclinalg/expr.hpp ngbla/
cp $1/basiclinalg/generate_mat_kernels.cpp ngbla/
cp $1/basiclinalg/matrix.hpp ngbla/
cp $1/basiclinalg/ng_lapack.hpp ngbla/
cp $1/basiclinalg/ngblas.cpp ngbla/
cp $1/basiclinalg/ngblas.hpp ngbla/
cp $1/basiclinalg/symmetricmatrix.hpp ngbla/
cp $1/basiclinalg/tensor.hpp ngbla/
cp $1/basiclinalg/vector.hpp ngbla/
cp $1/include/ngs_stdcpp_include.hpp ngbla/
cp $1/ngstd/autodiff.hpp ngbla/
cp $1/ngstd/autodiffdiff.hpp ngbla/
cp $1/ngstd/ngs_utils.hpp ngbla/
cp $1/ngstd/simd.hpp ngbla/
cp $1/ngstd/simd_complex.hpp ngbla/
cp $1/ngstd/templates.hpp ngbla/

cp $1/basiclinalg/triangular.hpp ngbla/
cp $1/basiclinalg/triangular.cpp ngbla/
cp $1/basiclinalg/LUdecomposition.cpp ngbla/
cp $1/basiclinalg/householder.hpp ngbla/
cp $1/basiclinalg/householder.cpp ngbla/

# cp $1/ngstd/ngstd.hpp ngbla/ too many changes, need to adapt manually!

patch -p1 < ngbla.patch
