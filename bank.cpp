#include <iostream>
#include <vector>

using namespace std;

const int NUMBER_OF_PROCESSES = 5;
const int NUMBER_OF_RESOURCES = 3;

vector<int> available(NUMBER_OF_RESOURCES);
vector<vector<int>> max_need(NUMBER_OF_PROCESSES, vector<int>(NUMBER_OF_RESOURCES));
vector<vector<int>> allocation(NUMBER_OF_PROCESSES, vector<int>(NUMBER_OF_RESOURCES));
vector<vector<int>> need(NUMBER_OF_PROCESSES, vector<int>(NUMBER_OF_RESOURCES));

bool is_safe_state(vector<bool> &finish)
{
    vector<int> work = available;
    vector<bool> temp_finish = finish;

    int count = 0;
    while (count < NUMBER_OF_PROCESSES)
    {
        bool found = false;
        for (int i = 0; i < NUMBER_OF_PROCESSES; ++i)
        {
            if (!temp_finish[i])
            {
                int j;
                for (j = 0; j < NUMBER_OF_RESOURCES; ++j)
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == NUMBER_OF_RESOURCES)
                {
                    for (int k = 0; k < NUMBER_OF_RESOURCES; ++k)
                        work[k] += allocation[i][k];
                    temp_finish[i] = true;
                    found = true;
                    ++count;
                }
            }
        }
        if (!found)
            break;
    }

    return count == NUMBER_OF_PROCESSES;
}

bool request_resources(int process_number, const vector<int> &request)
{
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        if (request[i] > need[process_number][i] || request[i] > available[i])
            return false;
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        available[i] -= request[i];
        allocation[process_number][i] += request[i];
        need[process_number][i] -= request[i];
    }

    vector<bool> finish(NUMBER_OF_PROCESSES, false);
    if (!is_safe_state(finish))
    {
        for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
        {
            available[i] += request[i];
            allocation[process_number][i] -= request[i];
            need[process_number][i] += request[i];
        }
        return false;
    }

    return true;
}

bool release_resources(int process_number, const vector<int> &release)
{
    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        cout << "release[i] :" << release[i] << "  allocation[process_number][i]: " << allocation[process_number][i] << endl;
        if (release[i] > allocation[process_number][i])
        {

            return false;
        }
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES; ++i)
    {
        available[i] += release[i];
        allocation[process_number][i] -= release[i];
        need[process_number][i] += release[i];
    }

    return true;
}

int main()
{
    available = {3, 3, 2};
    max_need = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}};
    allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}};

    for (int i = 0; i < NUMBER_OF_PROCESSES; ++i)
    { // 计算需求数量
        for (int j = 0; j < NUMBER_OF_RESOURCES; ++j)
        {
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

    int process_number = 1;//(2号进程)
    vector<int> request = {1, 0, 2}; 
    if (request_resources(process_number, request)) //allocation[1]->3,0,2
        cout << "Request granted." << endl;
    else
        cout << "Request denied." << endl;

    vector<int> release = {3, 0, 1}; // 释放一部分资源
    if (release_resources(process_number, release))
        cout << "Release granted." << endl;
    else
        cout << "Release denied." << endl;

    return 0;
}
