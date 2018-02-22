/* csci4850/5850 hw3 : calculate PI using Monte Carlo method
 * Name: Tae-Hyuk (Ted) Ahn
 * Date: 02/14/2018
 */

# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <ctime>
# include <cmath>

using namespace std;

//****************************************************************************80
int main ( int argc, char *argv[] )
//****************************************************************************80
{
  int numIter;
  cout << "Pleae enter an integer iteration number: ";
  cin >> numIter;

  double x,y;   	// x,y value for the random coordinate
  int i;	    	// loop counter
  int count=0;  	// Count holds all the number of how many good coordinates
  double z;	    	// Used to check if x^2+y^2<=1
  double pi;		// holds approx value of pi

  clock_t begin = clock();

  // Complete your code for XXXXX
  for (i=0; i<numIter; i++) {
    x = (double)rand()/RAND_MAX;
    y = (double)rand()/RAND_MAX;
    z = x*x+y*y;
    if (z <= 1) count+=1;
  }

  pi = 4*((double)count/(double)numIter);

  clock_t end = clock();
  double elapsedTime = double(end - begin) / CLOCKS_PER_SEC;

  cout << "  " << setw(12) << "n"
       << "  " << setw(12) << "Pi"
       << "  " << setw(12) << "time" << endl;

  cout << "  " << setw(12) << numIter
       << "  " << setw(12) << pi
       << "  " << setw(12) << elapsedTime << endl;

  return 0;
}

