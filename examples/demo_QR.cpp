#include <bla.hpp>
using namespace ngbla;

int main()
{
  size_t n = 10, m = 20;
  
  Matrix<> A(m,n);

  for (size_t i = 0; i < m; i++)
    for (size_t j = 0; j < n; j++)
      A(i,j) = rand() / double(RAND_MAX);

  Matrix<> Aorig = A;
  Matrix<> Q(m,m);
  QRFactorization (A, Q);

  if (n <= 20 && m <= 20)
    {
      cout << "R = " << Truncate(A) << endl;
      cout << "Q = " << Q << endl;
      cout << "Q^TQ = " << Truncate (Trans(Q)*Q) << endl;
      cout << "A - Q*R = " << Truncate (Aorig - Q*A) << endl;
    }
  NgProfiler::Print(stdout);  
}
