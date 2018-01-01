#include <iostream>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <array>

template<typename T, uint32_t N>
class Multi
{
private:
    int8_t cmp(const Multi& rhs, uint32_t from=0)
    {
        if (from >= N)
        {
            return 0;
        }

        if (data[from] > rhs[from])
        {
            return 1;
        }
        else if (data[from] < rhs[from])
        {
            return -1;
        }
        else
        {
            return cmp(rhs, from + 1);
        }
    }

public:
    Multi(std::initializer_list<T> init)
    {

    }

    T data[N];
    bool operator< (const Multi& rhs)
    {
        cmp(rhs) > 0;
    }
};

class Markov
{
public:
    std::vector<std::string> words;

public:
    Markov(std::string filename)
    {
        std::ifstream in_stream(filename);
        if (in_stream.is_open())
        {
            while (in_stream)
            {
                std::string word;
                in_stream >> word;
                //std::cout << word;
                words.push_back(word);
            }
            std::cout << words.size() << std::endl;
        }

    }
};

int main()
{
    std::cout << "Hello World!" << std::endl;

    Markov markov("data.txt");


    //for (int i=0; i< 100; i++)
    //    std::cout << markov.words[i] << " ";

    return 0;
}















