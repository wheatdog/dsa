#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>    
#include <cstdlib> 

#include "dtree.h"

using namespace std;


void PrintVotingCode(int TreeNum)
{
    cout << "int TotalY = 0;" << endl;
    cout << "int TotalN = 0;" << endl;
    for (int i = 0; i < TreeNum; i++)
    {
        cout << "if(tree" << i+1 << "_predict(attr) == 1) ";
        cout << "TotalY = TotalY + 1;" << endl;
        cout << "else TotalN = TotalN + 1;" << endl;
    }
    cout << "if (TotalY > TotalN) return 1;" << endl;
    cout << "else if (TotalN > TotalY) return -1;" << endl;
    cout << "else { srand(time(NULL)); return (rand() % 2)? +1 : -1;}" << endl;

    return;

}

int main(int argc, char* argv[])
{
    vector<RawData> Data;
    ReadRawData(Data, argv[1]);
    int TreeNum = stod(argv[2]);

    DTree *Forest = new DTree[TreeNum];

    int TreeSize = Data.size() / 3;

    vector<RawData>::iterator start = Data.begin();
    vector<RawData>::iterator end = Data.begin() + TreeSize;


    cout << "#include <ctime>" << endl;
    cout << "#include <cstdlib>" << endl;

    for (int i = 0; i < TreeNum; i++)
    {
        random_shuffle(Data.begin(), Data.end());

        DTree *Tree = &Forest[i];
        BuildTree(Tree, 0, Data, start, end);

        cout << "int tree" << i+1 << "_predict(double *attr){" << endl;
        PrintCode(Tree, 1);
        cout << "}" << endl;
    }

    cout << "int forest_predict(double *attr){" << endl;
    PrintVotingCode(TreeNum);
    cout << "}" << endl;

    free(Forest);

    return 0;
}
