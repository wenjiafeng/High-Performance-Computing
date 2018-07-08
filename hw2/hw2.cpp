# include <iostream>
# include <stdio.h>
# include <omp.h>
# include <cmath>

using namespace std;

int main (int argc, char *argv[] )
{
  int i, n;
  int count =0 ;
  double time;
  time = omp_get_wtime ();
  cout << "Count of the prime number when n = 300000: " << endl;
//#pragma omp parallel for schedule ( static, 100 )
//#pragma omp parallel for reduction ( + : count ) schedule ( static, 100 )
//#pragma omp parallel for reduction ( + : count ) schedule ( dynamic, 100 )
//#pragma omp parallel for reduction ( + : count ) schedule ( guided, 100 )     
# pragma omp parallel for reduction ( + : count )  schedule ( static,100) private ( i, n )
//# pragma omp parallel for reduction ( + : count ) schedule ( dynamic ) private ( i, n )
//# pragma omp parallel for reduction ( + : count ) schedule ( guided ) private ( i, n )

  for (n = 2; n <= 300000; n++)
  {
   for (i = 2; i*i <= n; i++)
       if (n%i == 0)
           break;
   if (i*i>n)
      count += 1;
  }
  cout << count << endl;
  time = omp_get_wtime ()-time;
  cout << "The wall-clock time is: " << endl;
  cout << time << endl;
  return 0;
}
