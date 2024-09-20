#include <iostream>
using namespace std;


int main()
{
    int processes;
    cout << "Input how many processes: "; cin >> processes;

    int at[processes], bt[processes], wt[processes];
    cout << "Input ARRIVAL TIME & BURST TIME in each processes: "; 
    cout << "\n==================================="<<endl;
    for (int i=0; i<processes; i++)
    {
        cout << "Process" << "[" << i + 1 << "]" ; //process header
        cout << "\nArrival Time" << "[" << i + 1 << "]" << ": "; cin >> at[i]; // Arrival Time
        cout << "Burst Time" << "[" << i + 1<< "]" << ": "; cin >> bt[i]; // Burst Time
        cout << "\n==================================="<<endl;
    }
    

    // Computing for Waiting Time
    wt[0] = 0;
    for (int i=1; i<processes; i++){
        wt[i] = wt[i - 1] + bt[i - 1];  //Waiting Time = Constant Zero (0) + Burst Time
    }
    

    // Output Section
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time";
    for (int i=0; i<processes; i++){
        cout << "\n" << i << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << wt[i];
    }


}
