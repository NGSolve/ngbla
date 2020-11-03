#include <bla.hpp>
using namespace ngbla;


// a FlatVector has a pointer and a sice
// no allocation/deallocation
// good for calling by value
void SetSubVec (FlatVector<double> sub, double val)
{
  sub = val;
}


// A SliceMatrix has a pointer, height, width and distance between rows
void SetSubMat (SliceMatrix<double> sub, double val)
{
  sub = val;
}


int main()
{
  Vector<double> x(5), y(5);
  Matrix<double> m(5,5);

  x = 0;
  SetSubVec (x.Range(2,4), 2.7);
  cout << "x = " << endl << x << endl;
  
  m = 0;
  SetSubMat (m.Rows(2,3), 1);
  SetSubMat (m.Cols(0,2), 3);
  cout << "m = " << endl << m << endl;
}

  
