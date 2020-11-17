#include <bla.hpp>
using namespace ngbla;

int main()
{
  int n = 100;

  Matrix<> A(n,n);
  Array<int> p(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      A(i,j) = rand() / double(RAND_MAX);

  Matrix<> Aorig = A;

  CalcLU (A, p);
  Matrix<> Ainv = A;
  InverseFromLU (Ainv,p);
  Matrix<> A_Ainv = Aorig * Ainv;
  cout << "error inverse = " << L2Norm(A_Ainv - Identity(n)) << endl;

  Vector<> x(n), y(n);
  for (int i = 0; i < n; i++)
    y(i) = rand() / double(RAND_MAX);

  x = y;
  SolveFromLU (A, p, FlatMatrix<double,ColMajor> (n, 1, &x(0)));

  cout << "||y-Ax|| = " << L2Norm(y-Aorig*x) << endl;
}
