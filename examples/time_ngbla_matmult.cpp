#include <bla.hpp>

using namespace ngbla;

int main()
{
  for (size_t n = 10; n <= 5120; n *= 2)
    {
      cout << "n = " << n << endl;
      
      Matrix<> a(n);
      Matrix<> b(n);
      Matrix<> c(n);
      
      // random init
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          {
            a(i,j) = rand();
            b(i,j) = rand();
          }
      
      Timer timer("MatMult "+to_string(n));
      
      c = a*b; // warmup
      
      int runs = 1+1e9 / (n*n*n);
      
      timer.Start();
      for (size_t i = 0; i < runs; i++)
        c = a*b;
      timer.Stop();

      timer.AddFlops (runs*n*n*n);
      double t = tmatmult.GetTime()/n_repetitions;
      double gflops = 1e-9*N*N*N/t;

      cout << "Needed " << t/1000 << " ms per Multiplication, GFlops: " << gflops << endl;
    }

  /*
  Timer tmatmult("MatMult");

  c = a*b; // warmup
  int n_repetitions = 100;
  tmatmult.Start();
  for(auto i : Range(n_repetitions))
    c = a*b;
  tmatmult.Stop();

  double t = tmatmult.GetTime()/n_repetitions;
  double gflops = 1e-9*N*N*N/t;

  cout << "Needed " << t*1000 << " ms per Multiplication, GFlops: " << gflops << endl;
  */
  // NgProfiler::Print (stdout);
}
