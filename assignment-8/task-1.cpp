#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input
    for (int i = 0; i < n; i++) {
        cout << "Enter Process ID: ";
        cin >> p[i].pid;
        cout << "Enter Arrival Time: ";
        cin >> p[i].at;
        cout << "Enter Burst Time: ";
        cin >> p[i].bt;
        cout << "--------------------------\n";
    }

    // Sort by Arrival Time
    sort(p.begin(), p.end(), [](Process a, Process b){
        return a.at < b.at;
    });

    int current_time = 0;
    float total_tat = 0, total_wt = 0;

    // FCFS Scheduling
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            // CPU is idle
            current_time = p[i].at;
        }

        p[i].ct = current_time + p[i].bt;
        current_time = p[i].ct;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    // Output table
    cout << "\n--------------------------------------------------------------\n";
    cout << left << setw(10) << "PID" 
         << setw(10) << "AT" 
         << setw(10) << "BT" 
         << setw(10) << "CT" 
         << setw(10) << "TAT" 
         << setw(10) << "WT" << endl;

    cout << "--------------------------------------------------------------\n";

    for (auto &pr : p) {
        cout << left << setw(10) << pr.pid
             << setw(10) << pr.at
             << setw(10) << pr.bt
             << setw(10) << pr.ct
             << setw(10) << pr.tat
             << setw(10) << pr.wt << endl;
    }

    cout << "--------------------------------------------------------------\n";

    cout << "Total TAT = " << total_tat << endl;
    cout << "Total WT  = " << total_wt << endl;
    cout << "Average TAT = " << total_tat / n << endl;
    cout << "Average WT  = " << total_wt / n << endl;

    return 0;
}
