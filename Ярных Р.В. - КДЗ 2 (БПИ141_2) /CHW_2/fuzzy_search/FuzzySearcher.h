/*
 * Author: Yarnykh Roman (rvyarnykh@edu.hse.ru)
 * Group: SE141
 * Subgroup: 2
 * Project: Final Home Work #2 (Sem 2)
 * Date: 29.05.2016
 * Language: C++ 11
 * Compiler: GCC
 * IDE: CLion
 *
 * Автор: Ярных Роман (rvyarnykh@edu.hse.ru)
 * Группа: БПИ141
 * Подгруппа: 2
 * Проект: КДЗ №2 (2-й семестр)
 * Дата: 29 мая 2016
 * Язык: C++ 11
 * Компилятор: GCC
 * Среда: CLion
 */

#pragma once

#ifndef CHW_2_FUZZYSEARCHER_H
#define CHW_2_FUZZYSEARCHER_H


#include <iostream>
#include <string>
#include <set>

using namespace std;

/*
 * Abstract fuzzy searcher
 */
class FuzzySearcher {
public:
    FuzzySearcher();
    FuzzySearcher(set<string> ws);
    virtual ~FuzzySearcher();
    virtual map<string, set<string>> fuzzySearch() = 0;

protected:
    int _hamming_distance(string a, string b);
    bool _areDifferentByOneSym(string a, string b);
    string _getPrefix(string s);
    string _getSuffix(string s);
    set<string> *dict_;
};

FuzzySearcher::FuzzySearcher() {

}

FuzzySearcher::FuzzySearcher(set<string> ws) {
    dict_ = new set<string>(move(ws));
}

FuzzySearcher::~FuzzySearcher() {
    delete dict_;
}

int FuzzySearcher::_hamming_distance(string a, string b) {
    const char* a_ = a.c_str();
    const char* b_ = b.c_str();
    int d_ = 0;
    for(int i = 0; i < a.length(); i++){
        d_ += ((a_[i] - b_[i]) == 0 ? 0 : 1);
    }
    return d_;
}

bool FuzzySearcher::_areDifferentByOneSym(string a, string b) {
    bool dif_ = false;
    for(int i = 0; i < a.length(); i++){
        if(a[i] != b[i]){
            if(dif_) {
                dif_ = false;
                break;
            }
            else
                dif_ = true;
        }
    }
    return dif_;
}

string FuzzySearcher::_getPrefix(string s) {
    int prefixEnd_ = (int)floor(s.length() / 2);
    return s.substr(0, (unsigned long)prefixEnd_ + 1);
}

string FuzzySearcher::_getSuffix(string s) {
    int prefixEnd_ = (int)floor(s.length() / 2);
    return s.substr((unsigned long)prefixEnd_ + 1, s.length() - prefixEnd_ - 1);
}


#endif //CHW_2_FUZZYSEARCHER_H
