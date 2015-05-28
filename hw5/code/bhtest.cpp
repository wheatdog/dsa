#include <iostream>
#include "binomial_heap.h"

#define ArraySize(A) (sizeof((A)) / sizeof(*(A)))

int main()
{
    BinomialHeap<int> bh, bh2;

    int input[] = {1, 29, 33, 234, 234, 92, 11};
    int input2[] = {2, 30, 31, 34, 92, 0, 111};

    std::cout << "****************" << std::endl;
    for (unsigned int i = 0; i < ArraySize(input); i++)
    {
        bh.insert(input[i]);
        std::cout << "insert [" << input[i] << "] to bh,\t" 
                  << "bh.size = " << bh.size << std::endl;
    }
    std::cout << "****************" << std::endl;

    std::cout << "****************" << std::endl;
    for (unsigned int i = 0; i < ArraySize(input2); i++)
    {
        bh2.insert(input2[i]);
        std::cout << "insert [" << input[i] << "] to bh2,\t" 
                  << "bh2.size = " << bh2.size << std::endl;
    }
    
    std::cout << "****************" << std::endl;

    std::cout << "****************" << std::endl;
    std::cout << "bh.size = " << bh.size << std::endl;
    std::cout << "bh2.size = " << bh2.size << std::endl;
    bh.merge(bh2);
    std::cout << "Merge bh2 to bh" << std::endl;
    std::cout << "bh.size = " << bh.size << std::endl;
    std::cout << "bh2.size = " << bh2.size << std::endl;
    std::cout << "****************" << std::endl;

    std::cout << "****************" << std::endl;
    while (bh.size)
    {
        std::cout << "bh.top() is " << bh.top() << " and do bh.pop()" << std::endl;
        bh.pop();
    }
    std::cout << "bh.size = " << bh.size << std::endl;
    std::cout << "****************" << std::endl;

    return 0;
}
