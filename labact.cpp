#include <iostream>
using namespace std;


int main()
{
    int processes;
    cout << "Input how many processes: "; cin >> processes;

    int at[processes], bt[processes];
    cout << "Input ARRIVAL TIME & BURST TIME in each processes: "; 
    cout << "\n==================================="<<endl;
    for (int i=0; i<processes; i++)
    {
        cout << "Process" << "[" << i << "]" ; //process header
        cout << "\nArrival Time" << "[" << i << "]" << ": "; cin >> at[i]; // Arrival Time
        cout << "Burst Time" << "[" << i << "]" << ": "; cin >> bt[i]; // Burst Time
        cout << "\n==================================="<<endl;
    }
    
    // int wt[0] = 0;
    // for (int i=1; i<n; i++)
    // {
    //     wt[i] = 0;
    //     for (int j=0; j<i; j++){
    //         wt[i] = wt[i] + bt[j];   //Waiting Time = Waiting Time + Burst Time
    //     }
    // }


    // Output
    cout << "Process\tArrival Time\tBurst Time";
    for (int i=0; i<processes; i++){
        cout << "\n" << i << "\t" << at[i] << "\t" << bt[i];
    }


}