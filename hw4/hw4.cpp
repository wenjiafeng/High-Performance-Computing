#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <cmath>

 
using namespace std;

int main(int argc, char **argv) {
  MPI::Status status;
  MPI::Init(argc, argv);
  int N = 10000;
  int processor_num = MPI::COMM_WORLD.Get_size();
  float dot_product = 0.0;
  int myid = MPI::COMM_WORLD.Get_rank();
  double stime, etime;
  int tag=1;
  int desk=0;
  int preid;
  int chunk=N/processor_num;
  int evenblock;
  int noneven;
  int sizeblock=(int)ceil((float)N/processor_num);
  float x[N];
  float y[N];
  float result;

//master processor
  if (myid == 0) {
      stime = MPI::Wtime();
      for(int i=1; i<N;i++){
          x[i]=1.0;
          y[i]=1.0;
      }
      if(N % processor_num == 0){
        evenblock = chunk;
        for(myid=1; myid<processor_num; myid++){
           MPI::COMM_WORLD.Send(&evenblock, 1, MPI::INT, myid, tag);
           MPI::COMM_WORLD.Send(&x[evenblock], chunk, MPI::FLOAT, myid, tag);
           cout << "rank " << myid <<"sent x"<< endl;
           MPI::COMM_WORLD.Send(&y[evenblock], chunk, MPI::FLOAT, myid, tag); 
           cout << "rank " << myid <<"sent y"<< endl; 
           evenblock += chunk;
        }
        evenblock = 0;
        for(int i=0+evenblock*chunk; i<0+(evenblock+1)*chunk; i++){
           result += x[i]*y[i];
        }
        dot_product=result;

        for(int i=1;i<processor_num;i++){
           preid = i;
           MPI::COMM_WORLD.Recv(&result,1,MPI::INT,preid,tag);
           dot_product += result;
        }
        etime=MPI::Wtime();
        cout << "Dot product is: " << dot_product << endl;
        cout << "The elapsed time is: " << etime-stime << endl;
      }
      else{
        noneven = sizeblock;
        for(myid=1; myid<processor_num; myid++){

           cout << "rank " << myid << endl;
           MPI::COMM_WORLD.Send(&noneven, 1, MPI::INT, myid, 1);
           MPI::COMM_WORLD.Send(&x[noneven], sizeblock, MPI::FLOAT, myid, 1);
           cout << "rank " << myid <<"sent x"<< endl;
           MPI::COMM_WORLD.Send(&y[noneven], sizeblock, MPI::FLOAT, myid, 1);
           cout << "rank " << myid <<"sent y"<< endl;
           noneven += sizeblock;
        }
        noneven = 0;
        for(int i=0+noneven*sizeblock; i<min(N,0+(noneven+1)*sizeblock); i++){
           result += x[i]*y[i];
        }
        dot_product=result;
        for(int i=1;i<processor_num;i++){
           int preid = i;
           MPI::COMM_WORLD.Recv(&result,1,MPI::INT, preid,tag);
           dot_product += result;
        }
        etime=MPI::Wtime();
        cout << "Dot product is: " << dot_product << endl;
        cout << "The elapsed time is: " << etime-stime << endl;
      }
  }

//worker processor
  if (myid >0){
      preid = 0;
      if(N%processor_num==0){
         MPI::COMM_WORLD.Recv(&evenblock, 1, MPI::INT, preid,tag,status);
         MPI::COMM_WORLD.Recv(&x[evenblock], chunk, MPI::FLOAT,desk,tag,status);
         MPI::COMM_WORLD.Recv(&y[evenblock], chunk, MPI::FLOAT,desk,tag,status);
         for(int i=0+myid*(N/processor_num);i<0+(myid+1)*(N/processor_num);i++){
              result+=x[i]*y[i];
         }
         MPI::COMM_WORLD.Send(&result,1,MPI::FLOAT,0,tag);
      }
      else{
         MPI::COMM_WORLD.Recv(&noneven, 1, MPI::INT, preid,tag);
         MPI::COMM_WORLD.Recv(&x[noneven], sizeblock, MPI::FLOAT,0,tag);
         MPI::COMM_WORLD.Recv(&y[noneven], sizeblock, MPI::FLOAT,0,tag);
         if (myid == (processor_num-1)){
             for(int i=0+myid*sizeblock;i<N;i++){
                 result += x[i]+y[i];
             }
         }
         else{
             for(int i=0+myid*sizeblock;i<min(N,0+(myid+1)*sizeblock);i++ ){
                 result += x[i]+y[i];
             }
         }
         MPI::COMM_WORLD.Send(&result,1,MPI::FLOAT,0,tag);
      }
  }
    
  // clean up for MPI 
  MPI::Finalize();
 
  return EXIT_SUCCESS;
}
