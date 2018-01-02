#include <iostream>
#include "markov.h"

int main()
{
    std::cout << "Markov" << std::endl;

    Markov markov("pantadeusz.txt");
    auto res = markov.gen(1000);
    for (auto el: res)
    {
        std::cout << el << " ";
    }

    return 0;
}















