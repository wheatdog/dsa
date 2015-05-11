#define FEATURENUM (1024 + 5)
#define YES (-3)
#define NO (-4)

using namespace std;

struct BranchChoice {

    int BestFeature;
    double BestTotalConfusion;
    double BestThresholdID;
    double BestThreshold;
};

struct DTree {
    BranchChoice Choice;
    DTree *left;  
    DTree *right;
};

struct Label {
    int Y;
    int N;
};

struct RawData {
    int Label;
    vector<double> Feature;
    RawData() : Label(0), Feature(FEATURENUM, 0) {}
    bool operator==(const RawData& rhs){
        for (int i = 0; i < FEATURENUM; i++)
        {
            if (Feature[i] != rhs.Feature[i])
                return 0;
        }
        return 1;}
        
    bool operator!=(const RawData& rhs){return !(*this == rhs);}
    friend void swap(RawData& lhs, RawData& rhs){
        int TmpLabel;

        TmpLabel = lhs.Label;
        lhs.Label = rhs.Label;
        rhs.Label = TmpLabel;

        rhs.Feature.swap(lhs.Feature);
    }
};

struct CompareByFeature {
    int ID;
    bool operator() (RawData& a, RawData& b) { 
        return a.Feature[ID] < b.Feature[ID];
    }
};

void ReadRawData(vector<RawData> &Data, char* FilePath);

double Confusion(int a, int b);
double TotalConfusion(int a, int b, int c, int d);

void FillThreshold(vector<double> &ThresholdSet,
                   vector<RawData>::iterator start,
                   vector<RawData>::iterator end,
                   int ID);
BranchChoice FindBranchChoice(vector<RawData> &Data, Label Total,
                              vector<RawData>::iterator start,
                              vector<RawData>::iterator end);
bool IsSame(vector<RawData> &Data, vector<RawData>::iterator start, 
                                   vector<RawData>::iterator end);
void BuildTree(DTree *Tree, double Epsilon, vector<RawData> &Data,
               vector<RawData>::iterator start, vector<RawData>::iterator end);

void IndentPrint(int IndentNum);
void PrintCode(DTree *Tree, int IndentNum);
void FreeTree(DTree *Tree);
