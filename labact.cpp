#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
using namespace std;

int fcfs(int processes){
    int at[processes], bt[processes], wt[processes];
    string processName[processes];
    cout << "Input ARRIVAL TIME & BURST TIME in each processes: "; 
    cout << "\n==================================="<<endl;
    for (int i=0; i<processes; i++)
    {
        processName[i] = "P" + to_string(i);
        cout << "Process" << "[" << i << "]" ; //process header
        cout << "\nArrival Time" << "[" << i << "]" << ": "; cin >> at[i]; // Arrival Time
        cout << "Burst Time" << "[" << i << "]" << ": "; cin >> bt[i]; // Burst Time
        cout << "\n==================================="<<endl;
    }

    // Initialize storage for sorted processes
    vector<tuple<int, int, string>> sortedATBT;
    for (int i = 0; i < processes; i++){
        sortedATBT.push_back(make_tuple(at[i], bt[i], processName[i]));
    }

    // Sort Processes by Arrival Time
    sort(sortedATBT.begin(), sortedATBT.end());

    // Update AT[] and BT[] with sorted values
    for (int i = 0; i < processes; i++){
        at[i] = get<0>(sortedATBT[i]);
        bt[i] = get<1>(sortedATBT[i]);
        processName[i] = get<2>(sortedATBT[i]);
    }

    // Computing for Waiting Time
    float wtTotal = 0;
    wt[0] = 0;
    for (int i=1; i<processes; i++){
        wt[i] = wt[i - 1] + bt[i - 1];  //Waiting Time = Constant Zero (0) + Burst Time
        wtTotal += wt[i];
    }

    // Output Section
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time";
    for (int i=0; i<processes; i++){
        cout << "\n" << processName[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << wt[i];
    }

    // Display Average Waiting Time
    cout << "\n\nAverage Waiting Time: (";
    for (int i = 0; i < processes - 1; i++){
        cout << wt[i] << " + ";
    }
    cout << wt[processes - 1] << ") / "<< processes <<" = " << wtTotal / processes;

    // Gantt Chart
    // cout << "\nGantt Chart for Schedule: "<< endl;
    // for (int i = 0; i < processes; i++){
    //     cout << " | " << processName[i] << "\t";
    // }
    // cout << "|\n ";
    // for (int i = 0; i < processes; i++){
    //     cout << wt[i] << "\t";
    // }
    
    cout << "\nGantt Chart for Schedule: " << endl;
    
    // Print top border
    for (int i = 0; i < processes; i++) {
        cout << "--------";
    }
    cout << "-" << endl;

    // Print process names
    cout << "|";
    for (int i = 0; i < processes; i++) {
        cout << " " << processName[i] << "\t|";
    }
    cout << endl;

    // Print bottom border
    for (int i = 0; i < processes; i++) {
        cout << "|-------";
    }
    cout << "|" << endl;

    // Print start times
    for (int i = 0; i < processes; i++) {
        cout << wt[i] << "\t";
    }
    cout << bt[processes - 1] + wt[processes - 1] << endl; // Print the last completion time
    
    return 0;
}

int sjf_non_preemptive(int processes){
    int at[processes], bt[processes], wt[processes], ct[processes];
    string processName[processes];
    
    cout << "Input ARRIVAL TIME & BURST TIME for each process:"; 
    cout << "\n===================================" << endl;
    for (int i = 0; i < processes; i++) {
        processName[i] = "P" + to_string(i + 1);
        cout << "Process [" << i + 1 << "]" << endl; // process header
        cout << "Arrival Time [" << i + 1 << "] : "; cin >> at[i]; // Arrival Time
        cout << "Burst Time [" << i + 1 << "] : "; cin >> bt[i]; // Burst Time
        cout << "===================================" << endl;
    }

    // Initialize storage for sorted processes
    vector<tuple<int, int, string>> sortedATBT;
    for (int i = 0; i < processes; i++) {
        sortedATBT.push_back(make_tuple(at[i], bt[i], processName[i]));
    }

    // Sort Processes by Arrival Time, then by Burst Time if Arrival Time is same
    sort(sortedATBT.begin(), sortedATBT.end(), [](tuple<int, int, string> a, tuple<int, int, string> b) {
        if (get<0>(a) == get<0>(b))
            return get<1>(a) < get<1>(b); // Sort by Burst Time if Arrival Time is same
        return get<0>(a) < get<0>(b); // Sort by Arrival Time
    });

    // Update AT[] and BT[] with sorted values
    for (int i = 0; i < processes; i++) {
        at[i] = get<0>(sortedATBT[i]);
        bt[i] = get<1>(sortedATBT[i]);
        processName[i] = get<2>(sortedATBT[i]);
    }

    int currentTime = 0; 
    float wtTotal = 0;
    vector<int> completed(processes, 0);
    vector<int> ganttChart;

    for (int completedProcesses = 0; completedProcesses < processes;) {
        int minIndex = -1;
        int minBurst = INT_MAX;

        // Find the process with the shortest burst time that has arrived and is not completed
        for (int i = 0; i < processes; i++) {
            if (at[i] <= currentTime && !completed[i] && bt[i] < minBurst) {
                minBurst = bt[i];
                minIndex = i;
            }
        }

        if (minIndex != -1) { // If a valid process is found
            wt[minIndex] = currentTime - at[minIndex];
            currentTime += bt[minIndex];
            ct[minIndex] = currentTime;
            completed[minIndex] = 1;
            ganttChart.push_back(currentTime);
            wtTotal += wt[minIndex];
            completedProcesses++;
        } else {
            currentTime++;
        }
    }

    // Output Section
    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time";
    for (int i = 0; i < processes; i++) {
        cout << "\n" << processName[i] << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << ct[i] << "\t\t" << wt[i];
    }

    // Display Average Waiting Time
    cout << "\n\nAverage Waiting Time: ("; 
    for (int i = 0; i < processes - 1; i++) {
        cout << wt[i] << " + ";
    }
    cout << wt[processes - 1] << ") / " << processes << " = " << wtTotal / processes;

    // Print Gantt Chart
    cout << "\nGantt Chart for Schedule: " << endl;
    // Print top border
    for (int i = 0; i < processes; i++) {
        cout << "--------";
    }
    cout << "-" << endl;
    // Print process names
    cout << "|";
    for (int i = 0; i < processes; i++) {
        cout << " " << processName[i] << "\t|";
    }
    cout << endl;
    // Print bottom border
    for (int i = 0; i < processes; i++) {
        cout << "|-------";
    }
    cout << "|" << endl;
    // Print Gantt Chart start times
    int startTime = 0;
    cout << startTime << "\t";
    for (int i = 0; i < processes; i++) {
        startTime += bt[i];
        cout << ganttChart[i] << "\t";
    }
    cout << endl;

    return 0;
}

int sjf_preemptive(int processes){
    return 0;
}

int main()
{
    int mode;
    // Select Mode Section "FCFS, SJF(non-preemp.), SJF(preemp.)"
    cout << "=====================================" <<endl;
    cout << "[1] - First Come First Serve"<<"\n[2] - SJF (non-preemptive)" << "\n[3] - SJF (preemptive)"<<endl;
    cout << "=====================================" <<endl;
    cout << "Select Mode of Choice: "; cin >> mode;
    cout << "=====================================" <<endl;
    if (mode == 1){ //FIRST COME FIRST SERVE
        int processes;
        cout << "Input how many processes: "; cin >> processes;
        fcfs(processes);
    }else if (mode == 2){   //SHORT JOB FIRST (non-preemptive)
        int processes;
        cout << "Input how many processes: "; cin >> processes; 
        sjf_non_preemptive(processes);
    }else if (mode == 3){   //SHORT JOB FIRST (preemptive)
        int processes;
        cout << "Input how many processes: "; cin >> processes; 
        sjf_preemptive(processes);
    }else   
        cout << "Please, Try Again!"; return mode;
    

        

    
}