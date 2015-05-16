#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

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
    int ComputerNum, WorkloadUpperBound;
    cin >> ComputerNum >> WorkloadUpperBound;


    string Input;

    enum {_ASSIGN, _MERGE, _EXECUTE};

    while (cin >> Input)
    {
        switch(GetCommand(Input))
        {
            case _ASSIGN:
            {
                int ComputerID, TaskID, Priority;
                cin >> ComputerID >> TaskID >> Priority;
                cout << ComputerID << " " << TaskID << " " <<  Priority << endl;
            } break;

            case _MERGE:
            {
                int ToID, FromID;
                cin >> ToID >> FromID;
                cout << ToID << " " << FromID << endl;
            } break;

            case _EXECUTE:
            {
                int ComputerID;
                cin >> ComputerID;
                cout << ComputerID << endl;
            } break;

            default:
            {
                exit(-1);
            } break;
        }
    }

    return 0;
}
