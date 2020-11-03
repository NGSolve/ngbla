#include <bla.hpp>
using namespace ngbla;


int main()
{
  Vector<double> x(5), y(5);
  Matrix<double> m(5,5);

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      m(i,j) = i+j;

  x = 1;   // set all entries
  
  cout << "size x = " << x.Size() << endl;
  cout << "size m = " << m.Height() << " x " << m.Width() << endl;
  
  y = m*x;    // matrix * vector 
  cout << "y = " << endl << y << endl;

  m.Rows(2,4).Cols(2,4) = 10;
  cout << "m = " << endl << m << endl;

  Vector<> z = m*x + y;
  cout << "z = " << endl << z << endl;
}
