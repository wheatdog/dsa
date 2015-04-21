#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>

#define MAXLINE 149639117
#define MAXUSER 23907637
#define MAXADID 22238287

using namespace std;

struct ProfitData
{
    int Click;
    int Impression;
    int UserID;

    bool operator < (const ProfitData& b) const
    {
        return (this->UserID < b.UserID);
    }
};

struct RawData
{
    int Click;
    int Impression;
    int AdID;
    long long unsigned int DisplayURL;
    int AdvertiserID;
    int KeywordID;
    int TitleID;
    int DescriptionID;
    int Depth;
    int Position;
    int QueryID;

};

struct UAKTD
{
    int AdID;
    long long unsigned int DisplayURL;
    int AdvertiserID;
    int KeywordID;
    int TitleID;
    int DescriptionID;
};

struct AdID_QueryID
{
    int AdID;
    int QueryID;
    bool operator < (const AdID_QueryID& b) const
    {
        if (AdID != b.AdID)
            return (AdID < b.AdID);
        else 
            return (QueryID < QueryID);
    }
};

bool CheckEqByADAKTD(UAKTD const &i, UAKTD const &j) 
{
    return ((i.AdID == j.AdID)
            && (i.DisplayURL == j.DisplayURL)
            && (i.AdvertiserID == j.AdvertiserID)
            && (i.KeywordID == j.KeywordID)
            && (i.TitleID == j.TitleID)
            && (i.DescriptionID == j.DescriptionID));
}

bool CompareByADAKTD(UAKTD const &i, UAKTD const &j) 
{
    if (i.AdID != j.AdID)
        return (i.AdID < j.AdID);
    else if (i.DisplayURL != j.DisplayURL)
        return (i.DisplayURL < j.DisplayURL);
    else if (i.AdvertiserID != j.AdvertiserID)
        return (i.AdvertiserID < j.AdvertiserID);
    else if (i.KeywordID != j.KeywordID)
        return (i.KeywordID < j.KeywordID);
    else if (i.TitleID != j.TitleID)
        return (i.TitleID < j.TitleID);
    else if (i.DescriptionID != j.DescriptionID)
        return (i.DescriptionID < j.DescriptionID);
    else
        return false;
}

bool CompareByADAKTDI(RawData* const &i, RawData* const &j) 
{
    if (i->AdID != j->AdID)
        return (i->AdID < j->AdID);
    else if (i->Impression != j->Impression)
        return (i->Impression > j->Impression);
    else if (i->DisplayURL != j->DisplayURL)
        return (i->DisplayURL < j->DisplayURL);
    else if (i->AdvertiserID != j->AdvertiserID)
        return (i->AdvertiserID < j->AdvertiserID);
    else if (i->KeywordID != j->KeywordID)
        return (i->KeywordID < j->KeywordID);
    else if (i->TitleID != j->TitleID)
        return (i->TitleID < j->TitleID);
    else if (i->DescriptionID != j->DescriptionID)
        return (i->DescriptionID < j->DescriptionID);
    else
        return false;
}

bool CompareByAdID(int const &i, int const &j)
{
    return (i < j);
}

ostream& operator<<(ostream& out, const AdID_QueryID& f) 
{
    out << f.AdID << " " << f.QueryID;
    return out;
}

ostream& operator<<(ostream& out, const RawData& f) 
{
    out << f.Click;
    out << "\t";
    out << f.Impression;
    out << "\t";
    out << f.DisplayURL;
    out << "\t";
    out << f.AdID;
    out << "\t";
    out << f.AdvertiserID;
    out << "\t";
    out << f.Depth;
    out << "\t";
    out << f.Position;
    out << "\t";
    out << f.QueryID;
    out << "\t";
    out << f.KeywordID;
    out << "\t";
    out << f.TitleID;
    out << "\t";
    out << f.DescriptionID;
    return out;
}

istream& operator>>(istream& in, RawData& f) 
{
    in >> f.Click;
    in >> f.Impression;
    in >> f.DisplayURL;
    in >> f.AdID;
    in >> f.AdvertiserID;
    in >> f.Depth;
    in >> f.Position;
    in >> f.QueryID;
    in >> f.KeywordID;
    in >> f.TitleID;
    in >> f.DescriptionID;
    return in;
}

void Profit(vector<ProfitData> *PData)
{
    int AdID;
    double Rate;
    cin >> AdID >> Rate;

    sort(PData[AdID].begin(), PData[AdID].end());

    int TotalClick = PData[AdID].front().Click;
    int TotalImpression = PData[AdID].front().Impression;
    int OldUserID = PData[AdID].front().UserID;

    for (vector<ProfitData>::iterator i = PData[AdID].begin() + 1;
            i != PData[AdID].end();
            ++i)
    {
        if (i->UserID != OldUserID)
        {
            double ans = (TotalImpression > 0)?
                (double)TotalClick / TotalImpression : 0.0;

            if (ans >= (Rate -0.0000001))
            {
                cout << OldUserID << endl;
            }
            TotalClick = 0;
            TotalImpression = 0;
            OldUserID = i->UserID;
        }

        TotalClick += i->Click;
        TotalImpression += i->Impression;

    }

    double ans = (TotalImpression > 0)?
        (double)TotalClick / TotalImpression : 0.0;

    if (ans >= (Rate -0.0000001))
    {
        cout << (PData[AdID].end() - 1)->UserID << endl;
    }

}



void Impressed(vector<RawData*> *Data)
{
    int AUserID, BUserID;
    cin >> AUserID >> BUserID;

    sort(Data[AUserID].begin(), Data[AUserID].end(), CompareByADAKTDI);
    sort(Data[BUserID].begin(), Data[BUserID].end(), CompareByADAKTDI);

    vector<RawData*>::iterator a = Data[AUserID].begin();
    vector<RawData*>::iterator b = Data[BUserID].begin();

    vector<int> AdList;
    while (a != Data[AUserID].end() && b!= Data[BUserID].end())
    {
        if ((*a)->AdID < (*b)->AdID)
            a++;
        else if ((*a)->AdID > (*b)->AdID)
            b++;
        else if ((*a)->AdID == (*b)->AdID)
        {
            if ((*a)->Impression != 0 && (*b)->Impression != 0)
                AdList.push_back((*a)->AdID);
            a++;
            b++;
        }
    }

    sort(AdList.begin(), AdList.end());
    vector<int>::iterator EndOfAdList = unique(AdList.begin(), AdList.end());
    AdList.resize(distance(AdList.begin(), EndOfAdList));

    vector<UAKTD> OutputList;

    a = Data[AUserID].begin();
    while (a != Data[AUserID].end())
    {
        if ((*a)->AdID > AdList.back())
            break;
        
        int Found = 0;
        for (vector<int>::iterator i = AdList.begin();
                i != AdList.end() && !Found;
                ++i)
        {
            if ((*a)->AdID == *i)
                Found = 1;
        }
        if (Found)
        {
            UAKTD u;
            u.AdID = (*a)->AdID;
            u.DisplayURL = (*a)->DisplayURL;
            u.AdvertiserID = (*a)->AdvertiserID;
            u.KeywordID = (*a)->KeywordID;
            u.TitleID = (*a)->TitleID;
            u.DescriptionID = (*a)->DescriptionID;

            OutputList.push_back(u);
        }
        a++;
    }


    b = Data[BUserID].begin();
    while (b != Data[AUserID].end())
    {
        if ((*b)->AdID > AdList.back())
            break;
        
        int Found = 0;
        for (vector<int>::iterator i = AdList.begin();
                i != AdList.end() && !Found;
                ++i)
        {
            if ((*b)->AdID == *i)
                Found = 1;
        }

        if (Found)
        {
            UAKTD u;
            u.AdID = (*b)->AdID;
            u.DisplayURL = (*b)->DisplayURL;
            u.AdvertiserID = (*b)->AdvertiserID;
            u.KeywordID = (*b)->KeywordID;
            u.TitleID = (*b)->TitleID;
            u.DescriptionID = (*b)->DescriptionID;

            OutputList.push_back(u);
        }
        b++;
    }

    sort(OutputList.begin(), OutputList.end(), &CompareByADAKTD);
    vector<UAKTD>::iterator oit = unique(OutputList.begin(), OutputList.end(), &CheckEqByADAKTD);
    OutputList.resize(distance(OutputList.begin(), oit));

    int olda = -1;
    for (vector<UAKTD>::iterator ii = OutputList.begin();
            ii != OutputList.end();
            ++ii)
    {
        if (olda != ii->AdID)
        {
            cout << ii->AdID << endl;
            olda = ii->AdID;
        }
        cout << "\t" << ii->DisplayURL
             << " "  << ii->AdvertiserID
             << " "  << ii->KeywordID
             << " "  << ii->TitleID
             << " "  << ii->DescriptionID << endl;
    }

    return;
}

void Clicked(vector<RawData*> *Data)
{
    int UserID;
    vector<AdID_QueryID> old;
    cin >> UserID;
    for (vector<RawData*>::iterator i = Data[UserID].begin();
            i != Data[UserID].end();
            ++i)
    {
        if ((*i)->Click == 0)
            continue;
        int Found = 0;
        for (vector<AdID_QueryID>::iterator j = old.begin();
                j != old.end() && !Found;
                ++j)
        {
            if (j->AdID == (*i)->AdID && j->QueryID == (*i)->QueryID)
                Found = 1;
        }
        if (!Found)
        {
            AdID_QueryID New;
            New.AdID = (*i)->AdID;
            New.QueryID = (*i)->QueryID;
            old.push_back(New);
        }
    }

    sort(old.begin(), old.end());

    for (vector<AdID_QueryID>::iterator j = old.begin();
            j != old.end();
            ++j)
    {
        cout << *j << endl;
    }

    return;
}

void Get(vector<RawData*> *Data)
{
    int UserID, AdID, QueryID, Position, Depth;
    cin >> UserID 
        >> AdID 
        >> QueryID 
        >> Position 
        >> Depth;
    int TotalClick = 0, TotalImpression = 0;
    for (vector<RawData*>::iterator i = Data[UserID].begin();
            i != Data[UserID].end();
            ++i)
    {
        if (AdID != (*i)->AdID || QueryID != (*i)->QueryID ||
                Position != (*i)->Position || Depth != (*i)->Depth)
            continue;
        TotalClick += (*i)->Click;
        TotalImpression += (*i)->Impression;
    }
    cout << TotalClick << " " << TotalImpression << endl;
    return;
}

int GetCommand(char *InputCommand)
{
    static char const *Command[] = {"get", "clicked", "impressed", "profit", "quit"};

    for (int i = 0; i < 5; i++)
    {
        if (strcmp(InputCommand, Command[i]) == 0)
            return i;
    }
    exit(-1);
}

int main(int argc, char* argv[])
{
    ifstream fin;
    fin.open(argv[1]);

    RawData *Raw = new RawData[MAXLINE];

    vector<RawData*> *Data = new vector<RawData*>[MAXUSER];
    vector<ProfitData> *PData = new vector<ProfitData>[MAXADID];

    ProfitData PBuffer;
    int UserID;
    int LineCount = 0;
    while (fin >> Raw[LineCount])
    {
        fin >> UserID;

        PBuffer.Click = Raw[LineCount].Click;
        PBuffer.Impression = Raw[LineCount].Impression;
        PBuffer.UserID = UserID;

        Data[UserID].push_back(Raw + LineCount);
        PData[Raw[LineCount].AdID].push_back(PBuffer);
        LineCount++;
    }

    fin.close();

    char InputCommand[10];
    enum COMMAND {_GET, _CLICKED, _IMPRESSED, _PROFIT, _QUIT};

    int command;
    cin >> InputCommand;
    while ((command = GetCommand(InputCommand)) != _QUIT)
    {
        cout << "********************" << endl;
        switch(command)
        {
            case _GET:
            {
                Get(Data);
            } break;

            case _CLICKED:
            {
                Clicked(Data);
            } break;

            case _IMPRESSED:
            {
                Impressed(Data);
            } break;

            case _PROFIT:
            {
                Profit(PData);
            } break;
        }

        cout << "********************" << endl;
        cin >> InputCommand;
    }

    delete [] Data;
    delete [] PData;
    delete [] Raw;
}
