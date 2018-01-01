#include <iostream>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <array>

#define MIN(a,b) ( ((a)<(b))? (a): (b) )
#define MAX(a,b) ( ((a)>(b))? (a): (b) )

template<typename T, size_t N>
class Multi
{
private:
    int8_t cmp(const Multi& rhs, size_t from=0)
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
        std::copy(init.begin(), init.begin()+MIN(N, init.size()), data.begin());
    }

    std::array<T, N> data;
    bool operator< (const Multi& rhs)
    {
        cmp(rhs) > 0;
    }
};


typedef std::pair<std::string, std::string> string_pair;
typedef std::pair<string_pair, std::string> string_triple;

class Markov
{
private:
    bool readfile(std::string filename)
    {
        std::ifstream in_stream(filename);
        if (!in_stream.is_open())
        {
            return false;
        }

        while (in_stream)
        {
            std::string word;
            in_stream >> word;
            //std::cout << word;
            words.push_back(word);
        }
        std::cout << words.size() << std::endl;

        return true;
    }
    string_triple get_triple(size_t pos)
    {
        if (pos + 2 >= words.size())
        {
            std::cerr << "get_triple: incorrect position parameter";
            return string_triple();
        }
        return string_triple{ {words[pos], words[pos + 1]}, words[pos+2] };
    }

public:
    std::vector<std::string> words;

public:
    Markov(std::string filename)
    {
        readfile(filename);
    }
};

int main()
{
    std::cout << "Markov" << std::endl;

    Markov markov("data.txt");
    std::pair<std::string, std::string> pair = {"a", "b"};


    return 0;
}















