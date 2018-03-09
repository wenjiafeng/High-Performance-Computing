#include <iostream>
#include <cstdlib> // has exit(), etc.
#include <mpi.h>
#include <unistd.h>
# include <ctime>
# include <math.h>
# include <iomanip>
using namespace std;

int taskb(int task,int processor,int a){
    return (task/(processor-1))*(a-1);
}
int taske(int task,int processor,int a){//end i for array a processor get
    if(a==(processor-1)){
        return task;
    }else{
        return (task/(processor-1))*(a);
    }
}
int range(int task,int processor,int a){
    int b = taskb(task,processor,a);
    int e = taske(task,processor,a);
    return e-b;
}

int main(int argc, char **argv) {
  MPI::Status status;
  MPI::Init(argc, argv);
  int tag=1;
  int p = MPI::COMM_WORLD.Get_size();
  int myid = MPI::COMM_WORLD.Get_rank();
  int n=100;
  if (myid == 0) {
      double stime, etime;
      stime = MPI::Wtime();
      for(int i=1;i<p;i++){
          int task=range(n,p,i);
          MPI::COMM_WORLD.Send(&task, 1, MPI::INT, i, tag);
      }
      int count;
      long finalcount=0;
      long finalIter=10000000000;
      for(int i=1;i<p;i++){
          MPI::COMM_WORLD.Recv(&count, 1, MPI::INT, i, tag, status);
          finalcount+=count;
      }
      double pi = ((double)finalcount/(double)finalIter)*4.0;
      etime = MPI::Wtime();
      double Speedup = 2.92*100/(etime-stime);
      double Efficiency = Speedup/p;
      cout << "  " << setw(12) << "p"
           << "  " << setw(12) << "Pi"
           << "  " << setw(12) << "time"
           << "  " << setw(12) << "Speedup"
           << "  " << setw(12) << "Efficiency" << endl;
      cout << "  " << setw(12) << p
           << "  " << setw(12) << pi
           << "  " << setw(12) << etime-stime
           << "  " << setw(12) << Speedup
           << "  " << setw(12) << Efficiency << endl;
  
  }
  else{
      int task,count;
      double x,y,z;
      
      MPI::COMM_WORLD.Recv(&task, 1, MPI::INT, 0, tag, status);
      for (int i=0; i<task; i++) {
          
          for(int k=0;k<100000000;k++){
          
          x = (double)rand()/RAND_MAX;
          y = (double)rand()/RAND_MAX;
          z = x*x+y*x;
          if (z <= 1) count= count+1;}
        }
      MPI::COMM_WORLD.Send(&count, 1, MPI::INT, 0, tag);
  }
  MPI::Finalize();
  return EXIT_SUCCESS;
}
