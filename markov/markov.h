#ifndef MARKOV_H
#define MARKOV_H

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
    string_vector words;
    db_t db;
    std::mt19937 mt;

public:
    Markov(std::string filename);

    bool readfile(std::string filename);
    string_triple getTriple(std::vector<std::string>::iterator it_from);
    void makeDb();
    size_t randBelow(size_t liit);
    string_vector gen(size_t size);
    std::string getNextWord(string_pair words);

};

#endif // MARKOV_H
