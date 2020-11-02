#include <bla.hpp>

using namespace ngbla;

int main()
{
  int N = 500;
  cout << "Starting Matrix multiplication timing with N = " << N << endl;

  Matrix<> a(N);
  Matrix<> b(N);
  Matrix<> c(N);

  // random init
  for(auto i : Range(N))
    for(auto j : Range(N))
    {
      a(i,j) = rand();
      b(i,j) = rand();
    }

  Timer tmatmult("MatMult");

  c = a*b; // warmup
  int n_repetitions = 100;
  tmatmult.Start();
  for(auto i : Range(n_repetitions))
    c = a*b;
  tmatmult.Stop();

  double t = tmatmult.GetTime()/n_repetitions;
  double gflops = 1e-9*N*N*N/t;

  cout << "Needed " << t/1000 << " ms per Multiplication, GFlops: " << gflops << endl;
}
