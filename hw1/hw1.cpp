#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>
using namespace std;


int main()
{
 cout << "Speedup(with p as row, n as column)" << endl;
 for(int a=1; a<=128; a*=2)
     cout << "\t" << a;
 cout << endl;
 for(int b=10; b<=320; b*=2){
     cout << b << "\t";
     for(int a=1; a<=128; a*=2){
         float Ts=b*b;
         float Tp=(b*b)/a+log(a)/log(2);
         float S=Ts/Tp;
         cout << setiosflags(ios::fixed) << setprecision(2) << S << "\t";
     }
     cout << endl;
 }
 cout << "Efficient(with p as row, n as column)" << endl;
 for(int a=1; a<=128; a*=2)
     cout << "\t" << a;
 cout << endl;
 for(int b=10; b<=320; b*=2){
     cout << b << "\t";
     for(int a=1; a<=128; a*=2){
         float Ts=b*b;
         float Tp=(b*b)/a+log(a)/log(2);
         float E=(Ts/Tp)/a;
         cout << setiosflags(ios::fixed) << setprecision(4) << E << "\t";
     }
     cout << endl;
 }

 return 0;
 }
