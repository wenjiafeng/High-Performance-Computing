# include <iostream>
# include <cstdlib> 
# include <ctime>
# include "mpi.h" 

int B[4][4]={};
int C[4]={};
int A[4]={};
int bsend[16]={};
int Bpart[4];
int Cpart;

using namespace std;

int main (int argc, char **argv) {
    MPI::Status status;
    
    MPI::Init(argc,argv);	//Initialize MPI
    int num_p = MPI::COMM_WORLD.Get_size(); // get number of processes
    int myid = MPI::COMM_WORLD.Get_rank(); // get this process's number 

    if (myid == 0) {
       for (int i=0; i<4; i++){
           C[i]=1;	//Initialize C
           for (int j=0; j<4; j++){
               B[j][i]=4*i+(j+1);	// Initialize B and transpose
           }
       }
       cout << "The transposed B is: " << endl;
       for(int i=0; i<4;i++){
          for(int j=0;j<4;j++){
             cout << B[i][j]<<"\t";
          }
          cout<<endl;
       }
       cout << "The vector C is:" << endl;
       for(int i=0;i<4;i++){
          cout << C[i] << "\t";
       }
       cout<<endl;

       for (int k=0; k<16; k++){
           bsend[k]=B[k/4][k%4];
       }
    }
    
    MPI::COMM_WORLD.Scatter(&C, 1, MPI::INT, &Cpart, 1, MPI::INT, 0);
    MPI::COMM_WORLD.Scatter(&bsend, 4, MPI::INT, &Bpart, 4, MPI::INT, 0);
    for (int i=0; i<4; i++){
        Bpart[i] = Bpart[i]*Cpart;
    }
    MPI::COMM_WORLD.Reduce(&Bpart, &A, 4, MPI::INT, MPI::SUM, 0);
    if (myid == 0){
       cout << "A = [";
       for (int i=0; i<4; i++){
           cout << A[i] << " ";
       }
    cout << "]" << endl;
    }
    MPI::Finalize();	//clean up for MPI
    return 0;
}  
 

