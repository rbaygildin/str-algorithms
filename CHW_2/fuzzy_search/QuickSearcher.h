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

#ifndef CHW_2_QUICKSEARCHER_H
#define CHW_2_QUICKSEARCHER_H

#include "FuzzySearcher.h"
#include <map>
#include <unordered_set>
#include <unordered_map>

/*
 * Advanced quick fuzzy searching
 */
class QuickSearcher : public FuzzySearcher{

public:
    QuickSearcher(set<string> s) : FuzzySearcher(s) {}
    virtual map<string, set<string>> fuzzySearch();
};

/*
 * Find all words are different by one character
 */
map<string, set<string>> QuickSearcher::fuzzySearch() {
    map<string, set<string>> fsmw_;
    unordered_map<unsigned long, unordered_set<string>> lg_;
    for(auto it = dict_->begin(); it != dict_->end(); it++){
        if(lg_.find(it->length()) != lg_.end()){
            lg_[it->length()].insert(*it);
        }
        else{
            unordered_set<string> clws_;
            clws_.insert(*it);
            lg_.insert(pair<unsigned long, unordered_set<string>>(it->length(), clws_));
        }
    }
    for(auto lg_it = lg_.begin(); lg_it != lg_.end(); lg_it++){
        unordered_map<string, unordered_set<string>> prefixMap_;
        unordered_map<string, unordered_set<string>> suffixMap_;
        for(auto word_ = lg_it->second.begin(); word_ != lg_it->second.end(); word_++){
            string prefix_ = _getPrefix(*word_);
            string suffix_ = _getSuffix(*word_);
            if(prefixMap_.find(prefix_) != prefixMap_.end()){
                prefixMap_[prefix_].insert(suffix_);
            }
            else{
                prefixMap_[prefix_] = unordered_set<string>();
            }

            if(suffixMap_.find(suffix_) != suffixMap_.end()){
                suffixMap_[suffix_].insert(prefix_);
            }
            else{
                suffixMap_[suffix_] = unordered_set<string>();
            }
        }
        for(auto word_ = lg_it->second.begin(); word_ != lg_it->second.end(); word_++){
            set<string> mw_;
            string ownPrefix_ = _getPrefix(*word_);
            string ownSuffix_ = _getSuffix(*word_);
            unordered_set<string> sufs_ = prefixMap_[ownPrefix_];
            unordered_set<string> prefs_ = suffixMap_[ownSuffix_];
            for(auto suf_ = sufs_.begin(); suf_ != sufs_.end(); suf_++){
                if(_areDifferentByOneSym(ownSuffix_, *suf_))
                    mw_.insert(ownPrefix_ + (*suf_));
            }
            for(auto pref_ = prefs_.begin(); pref_ != prefs_.end(); pref_++){
                if(_areDifferentByOneSym(ownPrefix_, *pref_))
                    mw_.insert((*pref_) + ownSuffix_);
            }
            fsmw_.insert(pair<string, set<string>>(*word_, mw_));
        }
    }
    return fsmw_;
}

#endif //CHW_2_QUICKSEARCHER_H
