#include <iostream>
#include <cstdlib>

#define N 1024

using namespace std;

__global__ void dotproduct(int *a, int *b, int *c)
{
        __shared__ int shareArray[N];
        shareArray[threadIdx.x] = a[threadIdx.x] * b[threadIdx.x];
        __syncthreads();

        if (0 == threadIdx.x) {
                int sum = 0;
                for (int i = 0; i < N; i++) {
                        sum += shareArray[i];
        }
        *c = sum;
    }
}

int main(int argx, char *argc[])
{
        int *A, *B, *Cone;
        int size=sizeof(int);
        A = (int*)malloc(N*size);
        B = (int*)malloc(N*size);
        Cone = (int*)malloc(size);

        int *devA, *devB, *devC;
        cudaMalloc((void**)&devA, N*size);
        cudaMalloc((void**)&devB, N*size);
        cudaMalloc((void**)&devC, size);

        //setup input values
        for (int i=0; i<N; i++){
                A[i] = 1;
                B[i] = 1;
        }
        printf("A:\n");
        for (int i = 0; i < N; i++) {
                printf("%5d", A[i]);
        }
        printf("\nB:\n");
        for (int i = 0; i < N; i++) {
                printf("%5d", B[i]);
        }
        printf("\n");

        //copy host value to device
        cudaMemcpy(devA, A, N*size, cudaMemcpyHostToDevice);
        cudaMemcpy(devB, B, N*size, cudaMemcpyHostToDevice);

        dotproduct<<<1,N>>>(devA, devB,devC);

        //copy result to host
        cudaMemcpy(Cone, devC, size, cudaMemcpyDeviceToHost);

        printf("C:\n");
        printf("%5d", *Cone);

        //Free the memory
        cudaFree(devA);
        cudaFree(devB);
        cudaFree(devC);

        free(A);
        free(B);
        free(Cone);

        return 0;

}
  
