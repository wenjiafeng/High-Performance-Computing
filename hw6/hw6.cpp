# include <iostream>
# include <cstdlib> 
# include "mpi.h" 
# define N 1000000

using namespace std;

int main (int argc, char **argv) {
    MPI::Status status;
    MPI::Init (argc, argv);
    int num_proc = MPI::COMM_WORLD.Get_size();
    int proc_id = MPI::COMM_WORLD.Get_rank();
    float x[N];
    float y[N];
    float xpart[N/num_proc+1];
    float ypart[N/num_proc+1];
    float dotpart;
    float sum;
    double stime;
    double etime;

    //initialize recieve part
    for(int i=0;i<(N/num_proc+1);i++){
        xpart[i]=0.0;
        ypart[i]=0.0;
    }
    stime = MPI::Wtime();
    if (proc_id == 0) {
       //initialize x[N],y[N]
       for(int i=0;i<N;i++){
          x[i]=1.0;
          y[i]=1.0;
       }    
    }
 
    //MPI_Scatter send and recv data    
    MPI::COMM_WORLD.Scatter(&x,(N/num_proc+1), MPI::FLOAT, &xpart, (N/num_proc+1), MPI::FLOAT, 0);
    MPI::COMM_WORLD.Scatter(&y,(N/num_proc+1), MPI::FLOAT, &ypart, (N/num_proc+1), MPI::FLOAT, 0);

    // count the dot product at each processor
    for(int i=0;i<N/num_proc+1;i++){
	dotpart+=xpart[i]*ypart[i];
    }
    // MPI_Reduce to recv data and count the sum dot product
    MPI::COMM_WORLD.Reduce(&dotpart, &sum, 1, MPI::FLOAT, MPI::SUM,0);

    if (proc_id == 0) {
       etime = MPI::Wtime();
       cout<<"N="<<N<<"\tProcess number="<<(num_proc)<<endl;
       cout<<"dot product = "<<sum<<"\tRuning time="<<(etime-stime)<<endl;
    }

    MPI::Finalize();
    return 0;
}
