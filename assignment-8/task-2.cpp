#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
    bool done = false;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time for P" << i + 1 << ": ";
        cin >> p[i].arrival;
        cout << "Enter Burst Time for P" << i + 1 << ": ";
        cin >> p[i].burst;
    }

    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;
    vector<int> ganttOrder;

    while (completed < n) {
        int idx = -1;
        int minBurst = 1e9;

        // Select eligible process with smallest burst
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= currentTime) {
                if (p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    idx = i;
                }
            }
        }

        // If no process has arrived yet → CPU Idle
        if (idx == -1) {
            currentTime++;
            continue;
        }

        // Process execution
        currentTime += p[idx].burst;
        p[idx].completion = currentTime;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;

        totalWT += p[idx].waiting;
        totalTAT += p[idx].turnaround;

        p[idx].done = true;
        completed++;

        ganttOrder.push_back(p[idx].pid);
    }

    cout << "\n-------------------------------------------------\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "-------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t"
             << p[i].arrival << "\t"
             << p[i].burst << "\t"
             << p[i].completion << "\t"
             << p[i].turnaround << "\t"
             << p[i].waiting << "\t"
             << "\n";
    }

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n;

    // Gantt Chart
    cout << "\n\nGantt Chart:\n| ";
    for (int id : ganttOrder) cout << "P" << id << " | ";
    cout << "\n";

    return 0;
}
