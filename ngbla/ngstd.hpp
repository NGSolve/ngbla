#ifndef FILE_NGSTD
#define FILE_NGSTD
#include "../core/ngcore.hpp"
#include "ngs_stdcpp_include.hpp"

namespace ngstd {
  using namespace ngcore;
  using namespace std;
}

#define NGS_DLL_HEADER

#include "ngs_utils.hpp"
#include "templates.hpp"

#include "simd.hpp"
#include "autodiff.hpp"
#include "autodiffdiff.hpp"
#include "simd_complex.hpp"

#endif // FILE_NGSTD
