#include <iostream>
#include "binomial_heap.h"

#define ArraySize(A) (sizeof((A)) / sizeof(*(A)))

int main()
{
    BinomialHeap<int> BH, BH2;

    int input[] = {1, 29, 33, 234, 234, 92, 11};
    int input2[] = {2, 30, 31, 34, 92, 0, 111};

    std::cout << ArraySize(input) << std::endl;
    for (unsigned int i = 0; i < ArraySize(input); i++)
    {
        std::cout << "[" << input[i] << "]" << std::endl;
        std::cout << "[" << input2[i] << "]" << std::endl;
        BH.insert(input[i]);
        BH2.insert(input2[i]);
    }

    std::cout << "*" << BH.size << std::endl;
    BH.merge(BH2);
    std::cout << "*" << BH.size << std::endl;

    for (unsigned int i = 0; i < 2*ArraySize(input); i++)
    {
        std::cout << BH.top() << std::endl;
        BH.pop();
        std::cout << "*" << BH.size << std::endl;
    }

    BH.merge(BH2);

    return 0;
}
