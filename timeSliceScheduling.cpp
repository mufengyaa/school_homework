#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task
{
    Task(string n, int at, int et) : name(n), arrival_time(at), execution_time(et), remaining_time(et) {}

    string name;
    int arrival_time;
    int execution_time;
    int remaining_time;
};

double timeSliceScheduling(vector<Task> &tasks, int time_slice)
{
    int current_time = 0;
    double total_turnaround_time = 0;

    for (auto &task : tasks)
    {
        while (task.remaining_time > 0)
        {
            if (task.remaining_time <= time_slice)
            {
                current_time += task.remaining_time;
                total_turnaround_time += current_time - task.arrival_time;
                task.remaining_time = 0;
            }
            else
            {
                current_time += time_slice;
                task.remaining_time -= time_slice;
            }
        }
    }

    double average_turnaround_time = total_turnaround_time / tasks.size();
    return average_turnaround_time;
}

int main()
{
    vector<Task> tasks = {
        Task("Task1", 0, 5),
        Task("Task2", 1, 3),
        Task("Task3", 2, 8)};

    int time_slice = 2;
    double average_turnaround_time = timeSliceScheduling(tasks, time_slice);
    cout << "Average Turnaround Time: " << average_turnaround_time << endl;

    return 0;
}
