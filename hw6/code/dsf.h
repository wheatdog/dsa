#ifndef DSF_H
#define DSF_H 1

#include <vector>

class DSF {
    private:
        std::vector<int> elements;
        std::vector<int> depthTable;
        std::vector<int> ownerTable;
        std::vector<struct avl_table*> price_tree_table;

    public:
        DSF(int, std::vector<int>);
        int Find(int);
        void Union(int, int);
        int Owner(int);
        struct avl_table* GetTree(int);
};

#endif /* dsf.h */
