#include <iostream>
#include <cstring>
#include <cstdlib>
#include "binomial_heap.h"

using namespace std;

struct Task {
    int ID;
    int Priority;
    bool operator > (const Task &b) 
    { 
        if (Priority != b.Priority)
            return Priority > b.Priority; 
        else 
            return ID < b.ID;
    }
};

struct Computer {
    BinomialHeap<Task> Tasks;
};

int GetCommand(string &Input)
{
    static char* Command[] = {"assign", "merge", "execute"};
#if 0
    cout << sizeof(Command) / sizeof(*Command) << endl;
#endif

    for (unsigned int i = 0;
            i < sizeof(Command) / sizeof(*Command);
            i++)
    {
        if (strcmp(Input.c_str(), Command[i]) == 0)
            return i;
    }
    return -1;
}

int main()
{
    int ComputerNum, WorkloadLimit;
    cin >> ComputerNum >> WorkloadLimit;

    Computer *Computers = new Computer[ComputerNum];

    string Input;

    enum {_ASSIGN, _MERGE, _EXECUTE};

    while (cin >> Input)
    {
        switch(GetCommand(Input))
        {
            case _ASSIGN:
            {
                int ComputerID;
                Task t;

                cin >> ComputerID >> t.ID >> t.Priority;

                Computers[ComputerID].Tasks.insert(t);
                cout << "There are " << Computers[ComputerID].Tasks.size 
                     << " tasks on computer " << ComputerID << "." << endl;
            } break;

            case _MERGE:
            {
                int ToID, FromID;
                cin >> ToID >> FromID;
                if (Computers[FromID].Tasks.size < WorkloadLimit)
                {
                    cout << "Merging request failed." << endl;
                    break;
                }

                Computers[ToID].Tasks.merge(Computers[FromID].Tasks);
                cout << "The largest priority number is now " 
                     << Computers[ToID].Tasks.top().Priority
                     << " on " << ToID << "." << endl;

            } break;

            case _EXECUTE:
            {
                int ComputerID;
                cin >> ComputerID;

                int Top = Computers[ComputerID].Tasks.top().Priority;
                while (Computers[ComputerID].Tasks.size != 0 &&
                       Computers[ComputerID].Tasks.top().Priority == Top)
                cout << "Computer " << ComputerID << " executed task " 
                     << Computers[ComputerID].Tasks.pop().ID << "." << endl;
            } break;

            default:
            {
                exit(-1);
            } break;
        }
    }

    delete[] Computers;

    return 0;
}
