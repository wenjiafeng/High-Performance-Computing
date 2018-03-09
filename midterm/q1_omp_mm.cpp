#include<iostream>
#include<stdio.h>  
#include<omp.h>
# include <ctime>
# include <iomanip>

using namespace std;  


int main(int argc,char **){  
    int numThreads;
    cout << "Pleae enter number of threads: ";
    cin >> numThreads;

    int N=1000;  
    static double A[1000][1000],B[1000][1000],C[1000][1000];
     
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            A[i][j]=1.0;
            B[i][j]=1.0;
            C[i][j]=0;
        }
    }
    int m,s,n;
    double time1 = omp_get_wtime();
// #pragma omp parallel for schedule (static) private (m,s,n) num_threads(numThreads)
 #pragma omp parallel for schedule (dynamic) private (m,s,n) num_threads(numThreads)
    for(m=0;m<N;m++){  
        for(s=0;s<N;s++){  
            C[m][s]=0;
            for(n=0;n<N;n++){  
                C[m][s]+=A[m][n]*B[n][s];  
            }  
        }  
    }  
//    for(m=0;m<N;m++){  
//        for(s=0;s<N;s++){  
//            cout<<C[m][s]<<"\t";  
//        }  
//       cout<<endl;  
//    }  
    double time2 = omp_get_wtime() - time1;
    double Speedup = 8.54/time2;
    double Efficiency = Speedup/numThreads;
    cout << "  " << setw(15) << "p"
         << "  " << setw(15) << "time" 
         << "  " << setw(15) << "Speedup"
         << "  " << setw(15) << "Efficiency" << endl;
    cout << "  " << setw(15) << numThreads
         << "  " << setw(15) << time2
         << "  " << setw(15) << Speedup 
         << "  " << setw(15) << Efficiency << endl;
  
    return 0;
  
}
