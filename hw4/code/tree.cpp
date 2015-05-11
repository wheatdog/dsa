#include <iostream>
#include <vector>

#include "dtree.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<RawData> Data;
    ReadRawData(Data, argv[1]);
    double Epsilon = stod(argv[2]);

    vector<RawData>::iterator start = Data.begin();
    vector<RawData>::iterator end = Data.end();

    DTree *Tree = new DTree;
    BuildTree(Tree, Epsilon, Data, start, end);

    cout << "int tree_predict(double *attr){" << endl;
    PrintCode(Tree, 1);
    cout << "}" << endl;

    FreeTree(Tree);

    return 0;
}
