#include <iostream>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <array>
#include <map>
#include <iterator>
#include <random>

#define MIN(a,b) ( ((a)<(b))? (a): (b) )
#define MAX(a,b) ( ((a)>(b))? (a): (b) )


typedef std::pair<std::string, std::string> string_pair;
typedef std::pair<string_pair, std::string> string_triple;
typedef std::vector<std::string> string_vector;
typedef std::multimap<string_pair, std::string> db_t;
typedef db_t::iterator db_it_t;
typedef std::pair<db_it_t, db_it_t> db_range_t;

class Markov
{
public:
    bool readfile(std::string filename)
    {
        std::ifstream in_stream(filename);
        if (!in_stream.is_open())
        {
            return false;
        }

        std::istream_iterator<std::string> cin_it(in_stream);
        std::istream_iterator<std::string> eos;

        std::copy(cin_it, eos, std::insert_iterator< std::vector<std::string> >(words, words.begin()));

        return true;
    }

    string_triple getTriple(std::vector<std::string>::iterator it_from)
    {
        for (auto it = it_from; it<it_from + 2; it++)
        {
            if (it == words.end())
            {
                return string_triple();
            }
        }
        //std::cout << *it_from << " " << *(it_from + 1) << " " << *(it_from + 2) << std::endl;
        return string_triple{ {*it_from, *(it_from + 1)}, *(it_from + 2) };
    }

    void makeDb()
    {
        if (words.size() < 2)
        {
            std::cerr << "makeDb: not enough data" << std::endl;
            return;
        }
        for (auto it = words.begin(); it != (words.end() - 2); it++)
        {
            db.insert(getTriple(it));
        }
    }

    size_t randBelow(size_t limit)
    {
        std::uniform_int_distribution<size_t> dist(0, limit - 1);
        return dist(mt);
    }

    string_vector gen(size_t size)
    {
        if (words.size() <= 0)
        {
            std::cerr << "gen: no data loaded" << std::endl;
            return string_vector();
        }
        if (size <= 0)
        {
            return string_vector();
        }

        size_t rand_word_pos = randBelow(words.size() - 2);
        //std::cout << rand_word_pos << std::endl;

        string_pair start_words = {words[rand_word_pos], words[rand_word_pos + 1]};
        //std::cout << words[rand_word_pos] << " " << words[rand_word_pos + 1] << std::endl;

        string_vector res = {start_words.first};

        if (size > 1)
        {
            res.push_back(start_words.second);
        }

        for (size_t i = 0; i < size - 2; i++)
        {
            std::string new_word = getNextWord(start_words);
            res.push_back( new_word );
            start_words.first = start_words.second;
            start_words.second = new_word;
        }

        return res;
    }

    std::string getNextWord(string_pair words)
    {
        db_range_t range = db.equal_range(words);

        //std::cout << "words for: " << words.first << " " << words.second << std::endl;

        //std::cout << range.first->second << std::endl;
        //std::cout << range.second->second << std::endl;

        size_t count = 0;
        for (auto it = range.first; it != range.second; ++it)
        {
            ++count;
            //std::cout << it->second << ", ";
        }
        //std::cout << count << std::endl;
        //std::cout << std::endl;

        size_t pos = randBelow(count);
        auto res_it = range.first;
        for (size_t i = 0; i < pos; i++)
        {
            res_it++;
        }

        return res_it->second;
    }


public:
    string_vector words;
    db_t db;
    std::mt19937 mt;

public:
    Markov(std::string filename)
    {
        std::random_device rd;
        mt = std::mt19937(rd());
        std::cout << "readfile" << std::endl;
        readfile(filename);
        std::cout << "words: " << words.size() << std::endl;
        std::cout << "make db" << std::endl;
        makeDb();
        std::cout << "db size: " << db.size() << std::endl;
    }
};

int main()
{
    std::cout << "Markov" << std::endl;

    Markov markov("data.txt");
    auto res = markov.gen(100);
    for (auto el: res)
    {
        std::cout << el << " ";
    }

    return 0;
}















