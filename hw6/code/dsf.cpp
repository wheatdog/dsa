#include <vector>
#include "dsf.h"
extern "C" 
{
#include "avl_ntudsa.h"
}

int Compare_by_int(const void *pa, const void *pb, void *param)
{
    int a = *(const int *)pa;
    int b = *(const int *)pb;

    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

DSF::DSF(int num, std::vector<int> priceTable)
{
    for (int count = 0; count <= num; count++) {
        elements.push_back(count);
        ownerTable.push_back(count);
        depthTable.push_back(1);

        struct avl_table *tmp;
        tmp = avl_create(Compare_by_int, NULL, NULL);
        avl_probe(tmp, priceTable[count]);

        price_tree_table.push_back(tmp);
    }
}

int DSF::Find(int n)
{
    while (elements[n] != n)
        n = elements[n];
    return n;
}

void insert(struct avl_table *target, struct avl_node *node)
{
    if (node == NULL)
        return;

    for (int count = 0; count < node->avl_cnt; count++) {
        avl_probe(target, node->avl_data);
    }


    for (int branch = 0; branch < 2; branch++)
        insert(target, node->avl_link[branch]);
}

void DSF::Union(int first, int second)
{
    ownerTable[second] = Owner(first);
    ownerTable[first] = Owner(first);

    if (depthTable[second] < depthTable[first]) {
        elements[second] = first;

        struct avl_table *tmp =  price_tree_table[second];
        struct avl_table *target =  price_tree_table[first];
        insert(target, tmp->avl_root);
    }
    else if (depthTable[second] > depthTable[first]) {
        elements[first] = second;

        struct avl_table *tmp =  price_tree_table[first];
        struct avl_table *target =  price_tree_table[second];
        insert(target, tmp->avl_root);
    }
    else {
        elements[second] = first;
        depthTable[first]++;

        struct avl_table *tmp =  price_tree_table[second];
        struct avl_table *target =  price_tree_table[first];
        insert(target, tmp->avl_root);
    }

}

int DSF::Owner(int n)
{
    return ownerTable[n];
}

struct avl_table* DSF::GetTree(int n)
{
    return price_tree_table[n];
}
