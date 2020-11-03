#include <bla.hpp>

using namespace ngbla;

void MyMatMult (SliceMatrix<> a, SliceMatrix<> b, SliceMatrix<> c)
{
  // c = a*b;

  size_t n = c.Height();
  size_t m = c.Width();
  size_t w = a.Width();
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++)
      {
        double sum = 0;
        for (size_t k = 0; k < w; k++)
          sum += a(i,k)*b(k,j);
        c(i,j) = sum;
      }

  /*
  size_t n = c.Height();
  size_t m = c.Width();
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < m; j++)
      c(i,j) = InnerProduct(a.Row(i), b.Col(j));
  */
}


int main()
{
  for (size_t n = 10; n <= 1280; n *= 2)
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
        // c = a*b;
        MyMatMult (a, b, c);
      timer.Stop();

      timer.AddFlops (runs*n*n*n);
    }
  
  NgProfiler::Print (stdout);
}



/*
  // c = a*b
job 8179 calls        1, time 9.4917 sec, MFlops = 14140.55 MatMult 5120
job 8180 calls        1, time 1.1647 sec, MFlops = 14404.61 MatMult 2560
job 8181 calls        1, time 0.1421 sec, MFlops = 14760.17 MatMult 1280
job 8182 calls        1, time 0.0776 sec, MFlops = 13507.02 MatMult 640
job 8183 calls        1, time 0.0655 sec, MFlops = 15508.84 MatMult 320
job 8184 calls        1, time 0.0609 sec, MFlops = 16483.96 MatMult 160
job 8185 calls        1, time 0.0641 sec, MFlops = 15605.46 MatMult 80
job 8186 calls        1, time 0.0583 sec, MFlops = 17147.52 MatMult 40
job 8187 calls        1, time 0.0786 sec, MFlops = 12726.23 MatMult 20
job 8188 calls        1, time 0.1360 sec, MFlops = 7355.59 MatMult 10

three loops:
job 8181 calls        1, time 13.6004 sec, MFlops = 154.20 MatMult 1280
job 8182 calls        1, time 3.0866 sec, MFlops = 339.71 MatMult 640
job 8183 calls        1, time 1.1404 sec, MFlops = 890.73 MatMult 320
job 8184 calls        1, time 0.9859 sec, MFlops = 1017.92 MatMult 160
job 8185 calls        1, time 0.7783 sec, MFlops = 1285.36 MatMult 80
job 8186 calls        1, time 0.6704 sec, MFlops = 1491.70 MatMult 40
job 8187 calls        1, time 0.6436 sec, MFlops = 1553.68 MatMult 20
job 8188 calls        1, time 0.7171 sec, MFlops = 1394.58 MatMult 10
 */
