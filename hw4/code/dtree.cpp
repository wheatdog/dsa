#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#include "dtree.h"

using namespace std;

double Confusion(int a, int b)
{
    double ans = (a + b == 0)? 
        1 : 1 - ((double) a / (a + b))*((double) a / (a + b)) - 
               ((double) b / (a + b))*((double) b / (a + b));
#if 0
    cout << "\tConfusion(" << a << ", " << b << "): " << ans << endl;
#endif
    return ans;
}

double TotalConfusion(int a, int b, int c, int d)
{
    double sum = a + b + c + d;
    double ans = (((a + b) / sum) * Confusion(a, b) + ((c + d) / sum) * Confusion(c, d));

#if 0
    cout << "\tConfusion(" << a << ", " << b << ", " << c <<", " << d <<"): " << ans << endl;
#endif

    return ans;
}

void ReadRawData(vector<RawData> &Data, char* FilePath)
{
    ifstream fin;
    fin.open(FilePath);

    string s;

    while (getline(fin, s))
    {
        RawData Buffer;

#if 0
        cout << s << endl;
#endif

        size_t found =  s.find(" "); 
        size_t last = 0;

        Buffer.Label = stoi(s.substr(last, found - last), 0);

        last = found;
        found = s.find(" ", found+1);

        while (found != string::npos)
        {
#if 0
            cout << s.substr(last, found - last) << endl;
#endif

            size_t colon =  s.find(":", last); 

            int ID = stoi(s.substr(last + 1, colon - last - 1), 0);

            Buffer.Feature[ID] = 
                stod(s.substr(colon + 1, found - colon - 1), 0);

            last = found;
            found = s.find(" ", found+1);
        }

        Data.push_back(Buffer);
    }

    fin.close();

#if 0
    // Note: Check if storage is correct.
    cout << "DataNum = " << Data.size() << endl;

    for (vector<RawData>::iterator it = Data.begin();
            it != Data.end();
            ++it)
    {
        cout << it->Label << endl;
        for (int j = 0; j < FEATURENUM; j++)
        {
            if (it->Feature[j] != 0)
                cout << "\t(" << j << ", " << it->Feature[j] << ")" << endl;
        }
    }
#endif

}

void FillThreshold(vector<double> &ThresholdSet,
                   vector<RawData>::iterator start,
                   vector<RawData>::iterator end,
                   int ID)
{
        set<double> ValueSet;
        for (vector<RawData>::iterator it = start;
             it != end;
             ++it)
        {
            ValueSet.insert(it->Feature[ID]);
        }

#if 0
        for (set<double>::iterator jt = ValueSet.begin();
                jt != ValueSet.end();
                ++jt)
        {
            cout << *jt << " ";
        }
        cout << endl;

        cout << "[" << ID << "]: " ;
        for (vector<RawData>::iterator it = start;
                it != end;
                ++it)
        {
            cout << it->Label << " ";
        }
        cout << endl;
#endif

        double last = *ValueSet.begin();
        for (set<double>::iterator jt = next(ValueSet.begin());
             jt != ValueSet.end(); ++jt)
        {
            ThresholdSet.push_back(last + (*jt - last)/2);
            last = *jt;
        }

        return;
}

BranchChoice FindBranchChoice(vector<RawData> &Data,
                              Label Total,
                              vector<RawData>::iterator start,
                              vector<RawData>::iterator end)
{

    BranchChoice Choice;
    Choice.BestFeature = -1;
    Choice.BestTotalConfusion = 1.5;
    Choice.BestThresholdID = -1;
    Choice.BestThreshold = -1;

    CompareByFeature Cmp;
    for (Cmp.ID = 0; Cmp.ID < FEATURENUM; Cmp.ID++)
    {
        sort(start, end, Cmp);

        vector<double> ThresholdSet;

        FillThreshold(ThresholdSet, start, end, Cmp.ID);

        if (ThresholdSet.size() == 0)
            continue;

        vector<Label> LabelSet(ThresholdSet.size());

        int ThresholdCount = 0;
        LabelSet[ThresholdCount].Y = 0;
        LabelSet[ThresholdCount].N = 0;

        for (vector<RawData>::iterator it = start;
             it != end;
             ++it)
        {
            if (it->Feature[Cmp.ID] > ThresholdSet.back())
                break;

            if (it->Feature[Cmp.ID] > ThresholdSet[ThresholdCount])
            {
                ThresholdCount++;
                if (it->Label == 1) 
                {
                    LabelSet[ThresholdCount].Y = LabelSet[ThresholdCount - 1].Y + 1;
                    LabelSet[ThresholdCount].N = LabelSet[ThresholdCount - 1].N;
                }
                else
                {
                    LabelSet[ThresholdCount].Y = LabelSet[ThresholdCount - 1].Y;
                    LabelSet[ThresholdCount].N = LabelSet[ThresholdCount - 1].N + 1;
                }
            }
            else
            {
                if (it->Label == 1) 
                {
                    LabelSet[ThresholdCount].Y += 1;
                }
                else
                {
                    LabelSet[ThresholdCount].N += 1;
                }
            }
        }

#if 0
        cout << "\t(";
        for (vector<double>::iterator it = ThresholdSet.begin();
             it != ThresholdSet.end();
             ++it)
        {
            cout << *it << " ";
        }
        cout << ")" << endl;
        for (unsigned int i = 0; i < LabelSet.size(); i++)
        {
            cout <<  "{" << ThresholdSet[i] << "}: "
                << LabelSet[i].Y << ", " << LabelSet[i].N << endl;
        }
#endif

        for (unsigned int i = 0; i < LabelSet.size(); i++)
        {
#if 0
            cout << LabelSet[i].Y << " " 
                 << LabelSet[i].N << " "
                 << Total.Y - LabelSet[i].Y << " "
                 << Total.N - LabelSet[i].N << ": ";
#endif
            double tmp = TotalConfusion(LabelSet[i].Y, 
                                        LabelSet[i].N,
                                        Total.Y - LabelSet[i].Y,
                                        Total.N - LabelSet[i].N);
#if 0
            cout << "\t" << tmp << endl;
#endif
            if (Choice.BestTotalConfusion > tmp)
            {
                Choice.BestFeature = Cmp.ID;
                Choice.BestThresholdID = i;
                Choice.BestThreshold = ThresholdSet[i];
                Choice.BestTotalConfusion = tmp;
            }
        }
#if 0
        cout << endl;
        cout << Choice.BestTotalConfusion << endl;
        cout << Cmp.ID << endl;
#endif
    }

    return Choice;
}

bool IsSame(vector<RawData> &Data, vector<RawData>::iterator start, 
                                   vector<RawData>::iterator end)
{
    RawData last = *start;
    for (vector<RawData>::iterator it = start; 
         it != end;
         ++it)
    {
        if (last != *it)
            return 0;
    }
    return 1;
}

void BuildTree(DTree *Tree, double Epsilon, vector<RawData> &Data,
               vector<RawData>::iterator start, vector<RawData>::iterator end)
{
    Label Total = {0};
    for (vector<RawData>::iterator it = start; 
         it != end;
         ++it)
    {
        if (it->Label == +1)
            Total.Y += 1;
        else
            Total.N += 1;
    }
    if (next(start) == end || Confusion(Total.Y,Total.N) <= Epsilon || IsSame(Data, start, end))
    {
        Tree->left = NULL;
        Tree->right = NULL;
        if (Total.Y > Total.N)
            Tree->Choice.BestFeature = YES;
        else if (Total.Y < Total.N)
            Tree->Choice.BestFeature = NO;
        else
        {
            srand(time(NULL));
            Tree->Choice.BestFeature = (rand() % 2)? YES : NO;
        }
        return;
    }
    else
    {
        Tree->Choice = FindBranchChoice(Data, Total, start, end);

#if 0
        cout << Total.Y << " " << Total.N << endl;
        cout << Tree->Choice.BestFeature << endl;
        cout << Tree->Choice.BestThreshold << endl;
        cout << Tree->Choice.BestThresholdID << endl;
        cout << Tree->Choice.BestTotalConfusion << endl;
#endif

        CompareByFeature Cmp;
        Cmp.ID = Tree->Choice.BestFeature;
        sort(start, end, Cmp);

        int Found = 0;
        vector<RawData>::iterator LeftEnd;

        for (vector<RawData>::iterator it = start; 
                it != end && !Found;
                ++it)
        {
            if (it->Feature[Tree->Choice.BestFeature] > Tree->Choice.BestThreshold)
            {
                Found = 1;
                LeftEnd = it;
            }
        }

#if 0
        cout << "*****************" << endl;
        for (vector<RawData>::iterator it = start; 
                it != LeftEnd;
                ++it)
        {
            cout << it->Feature[Tree->Choice.BestFeature] << " ";
        }
        cout << endl;
        cout << "*****************" << endl;
        for (vector<RawData>::iterator it = LeftEnd; 
                it != end;
                ++it)
        {
            cout << "\t" << it->Label << "\t";
            for (int i = 1; i < FEATURENUM; i++)
                cout << it->Feature[i] << " ";
            cout << endl;
        }
        cout << endl;
        cout << "*****************" << endl;
#endif

        DTree *left = new DTree;
        Tree->left = left;
        BuildTree(left, Epsilon, Data, start, LeftEnd);


        DTree *right = new DTree;
        Tree->right = right;
        BuildTree(right, Epsilon, Data, LeftEnd, end);
    }
}

void IndentPrint(int IndentNum)
{
    for (int i = 0; i < IndentNum; i++)
        cout << "  ";
    return;
}

void PrintCode(DTree *Tree, int IndentNum)
{
    if (Tree->left == NULL && Tree->right == NULL)
    {
        IndentPrint(IndentNum);
        cout << "return ";
        if (Tree->Choice.BestFeature == YES)
            cout << "+1;" << endl;
        else 
            cout << "-1;" << endl;

        return;
    }

    IndentPrint(IndentNum);
    cout << "if (attr[" << Tree->Choice.BestFeature << "] < " 
        << Tree->Choice.BestThreshold << "){" << endl;

    PrintCode(Tree->left, IndentNum + 1);

    IndentPrint(IndentNum); cout << "}" << endl;
    IndentPrint(IndentNum); cout << "else {" << endl;

    PrintCode(Tree->right, IndentNum + 1);

    IndentPrint(IndentNum); cout << "}" << endl;
    return;
}

void FreeTree(DTree *Tree)
{

    if (Tree->left != NULL)
        FreeTree(Tree->left);
    if (Tree->right != NULL)
        FreeTree(Tree->right);
    free(Tree);
    return;
}

