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

#define WINDOW_SIZE 3

typedef std::pair       <std::string, std::string>      string_pair;
typedef std::vector     <std::string>                   string_vector;
typedef string_vector   window_el;


typedef std::pair       <window_el, std::string>        dict_el;
typedef std::multimap   <window_el, std::string>        db_t;

typedef db_t::iterator                                  db_it_t;
typedef std::pair       <db_it_t, db_it_t>              db_range_t;

class Markov
{
public:
    string_vector words;
    db_t db;
    std::mt19937 mt;

public:
    Markov(std::string filename);

    bool readfile(std::string filename);
    dict_el getDictEl(std::vector<std::string>::iterator it_from);
    void makeDb();
    size_t randBelow(size_t liit);
    window_el gen(size_t size);
    std::string getNextWord(window_el words);

};

#endif // MARKOV_H
