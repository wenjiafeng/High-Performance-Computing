#include<iostream>
#include<stdio.h>
#include <ctime>
#include <iomanip>

using namespace std;
int main(int argc,char **){
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
    clock_t begin = clock();
    for(m=0;m<N;m++){
        for(s=0;s<N;s++){
            C[m][s]=0;
            for(n=0;n<N;n++){
                C[m][s]+=A[m][n]*B[n][s];
            }
        }
    }
    clock_t end = clock();
    double elapsedTime = double(end - begin)/ CLOCKS_PER_SEC;
    cout << "  " << setw(15) << "time" << endl;
    cout << "  " << setw(15) << elapsedTime << endl;

    return 0;

}

