#include <iostream>
#include "dsf.h"

using namespace std;

int main()
{
    int friendNum, incidentNum;
    cin >> friendNum >> incidentNum;

    int price[friendNum];
    for (int count = 0; count < friendNum; count++)
    {
        cin >> price[count];
    }

    int type;
    while (cin >> type)
    {
        switch(type)
        {
            case 1:
            {
                int tediousID, interestID;
                cin >> tediousID >> interestID;
            } break;

            case 2:
            {
                int gameID;
                long long int money;
                cin >> gameID >> money;
            } break;
        }
    }

    return 0;
}

