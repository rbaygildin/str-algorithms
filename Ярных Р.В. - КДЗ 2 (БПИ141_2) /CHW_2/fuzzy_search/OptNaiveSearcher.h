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

#ifndef CHW_2_OPTNAIVESEARCHER_H
#define CHW_2_OPTNAIVESEARCHER_H

#include "FuzzySearcher.h"
#include <map>

/*
 * Optimized naive searching
 */
class OptNaiveSearcher : public FuzzySearcher{

public:
    OptNaiveSearcher(set<string> s) : FuzzySearcher(s){}
    virtual map<string, set<string>> fuzzySearch();
};

/*
 * Find all words which are different by one character
 */
map<string, set<string>> OptNaiveSearcher::fuzzySearch() {
    map<string, set<string>> fsmw_;
    map<unsigned long, set<string>> lg_;
    for(auto it = dict_->begin(); it != dict_->end(); it++){
        if(lg_.find(it->length()) != lg_.end()){
            lg_[it->length()].insert(*it);
        }
        else{
            set<string> clws_;
            clws_.insert(*it);
            lg_.insert(pair<unsigned long, set<string>>(it->length(), clws_));
        }
    }
    for(auto lg_it = lg_.begin(); lg_it != lg_.end(); lg_it++){
        for(set<string>::iterator word_ = lg_it->second.begin(); word_ != lg_it->second.end(); word_++){
            set<string> mw_;
            for(set<string>::iterator oword_ = lg_it->second.begin(); oword_ != lg_it->second.end(); oword_++){
                if(_areDifferentByOneSym(*word_, *oword_))
                    mw_.insert(*oword_);
            }
            fsmw_.insert(pair<string, set<string>>(*word_, mw_));
        }
    }
    return fsmw_;
}

#endif //CHW_2_OPTNAIVESEARCHER_H