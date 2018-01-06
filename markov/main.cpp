#include <iostream>
#include "markov.h"

int main()
{
    std::cout << "Markov" << std::endl;

    Markov markov("coma.txt");
    auto res = markov.gen(10000);
    for (auto el: res)
    {
        std::cout << el << " ";
    }

    return 0;
}















