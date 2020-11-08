#include <bla.hpp>
using namespace ngbla;

int main()
{
  // the simd template class is a wrapper for AVX types
  SIMD<double,4> a(1,2,3,4);
  SIMD<double,4> b(10,11,12,13);

  SIMD<double,4> c = a+b;     
  cout << "a = " << a << ", b = " << b << ", c = " << c << endl;

  
  size_t n = 15; 
  Vector<double> va(n), vb(n);
  va = 1; vb = 5;
  double alpha = 7;

  // vector add using simds:
  size_t i;
  for (i = 0; i+SIMD<double>::Size() <= n; i+=SIMD<double>::Size())
    {
      SIMD<double> v = SIMD<double>(&va(i)) + alpha * SIMD<double>(&vb(i));
      v.Store (&va(i));
    }
  // the remainder
  for ( ; i < n; i++)
    va(i) += alpha*vb(i);
  
  cout << "va = " << va << endl;
}
