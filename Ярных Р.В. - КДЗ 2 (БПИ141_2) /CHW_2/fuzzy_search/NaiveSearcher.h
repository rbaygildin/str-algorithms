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

#ifndef CHW_2_NAIVYSEARCHER_H
#define CHW_2_NAIVYSEARCHER_H

#include "FuzzySearcher.h"
#include <map>

/*
 * Naive fuzzy searching
 */
class NaiveSearcher : public FuzzySearcher{

public:
    NaiveSearcher(set<string> s) : FuzzySearcher(s){}
    virtual map<string, set<string>> fuzzySearch();
};

/*
 * Find all words which are different by one character
 */
map<string, set<string>> NaiveSearcher::fuzzySearch() {
    map<string, set<string>> fsmw_;
    for(auto it = dict_->begin(); it != dict_->end(); it++){
        set<string> mw_;
        string current_ = *it;
        for(auto it1 = dict_->begin(); it1 != dict_->end(); it1++){
            string other_ = *it1;
            if(other_.length() != current_.length())
                continue;
            if(_areDifferentByOneSym(current_, other_))
                mw_.insert(other_);
        }
        fsmw_.insert(pair<string, set<string>>(current_, mw_));
    }
    return fsmw_;
}

#endif //CHW_2_NAIVYSEARCHER_H
