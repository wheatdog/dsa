#include <iostream>
#include <vector>
#include "dsf.h"
#include "dsf.cpp"
extern "C" 
{
#include "avl_ntudsa.h"
}

using namespace std;


int NumCanBuy(struct avl_node *root, long long int money)
{
    if (root == NULL)
        return 0;

    if (root->avl_sum[0] > money)
        return  NumCanBuy(root->avl_link[0], money);

    money -= root->avl_sum[0];
    int num = root->avl_cnode[0];

    for (int count = 0; count < root->avl_cnt; count++) {
        if (root->avl_data > money)
            break;
        num++;
        money -= root->avl_data;
    }

    if (root->avl_sum[1] > money)
        return num + NumCanBuy(root->avl_link[1], money);

    money -= root->avl_sum[1];
    num += root->avl_cnode[1];
    return num;
}

int main()
{
    int friendNum, incidentNum;
    cin >> friendNum >> incidentNum;

    vector<int> priceTable;
    priceTable.push_back(0);
    for (int count = 0; count < friendNum; count++) {
        int tmp;
        cin >> tmp;
        priceTable.push_back(tmp);
    }

    DSF games(friendNum, priceTable);

    int type;
    int incidentCount = 0;
    while ((incidentCount < incidentNum) && (cin >> type)) {
        switch(type) {
            case 1:
            {
                int tediousID, interestID;
                cin >> tediousID >> interestID;

                int target = games.Find(interestID);
                int boring = games.Find(tediousID);

                if (target == boring)
                    break;
                games.Union(boring, target);

            } break;

            case 2:
            {
                int gameID;
                long long int money;
                cin >> gameID >> money;

                int ownerTopGameID = games.Find(gameID);
                int targetOwner = games.Owner(games.Find(gameID));
                struct avl_table* tree = games.GetTree(ownerTopGameID);


                int num = NumCanBuy(tree->avl_root, money);
                cout << targetOwner << " " << num << endl;
            } break;
        }
        incidentCount++;
    }

    return 0;
}

