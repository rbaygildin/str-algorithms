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

#ifndef CHW_2_SPELLCHECKER_H
#define CHW_2_SPELLCHECKER_H
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef unordered_map<string, unordered_set<string>> PREFIX_MAP;
typedef unordered_map<string, unordered_set<string>> SUFFIX_MAP;
typedef unsigned long ULONG;
typedef unordered_set<string> STRING_SET;
typedef unordered_set<string>::iterator SSET_ITERATOR;

/**
 * Implementation of spell checking
 * with search options for replace wrong words by right ones
 */
class SpellChecker {
public:
    SpellChecker();
    virtual ~SpellChecker();
    void loadDictionary(istream& input);
    set<string> options_T(string s);
    set<string> options_D(string s);
    set<string> options_I(string s);
    bool spellCheck(string s);
private:
    set<string> *dict_;
    unordered_map<ULONG, unordered_map<string, unordered_set<string>>> ltg_;
    unordered_map<ULONG, pair<PREFIX_MAP, SUFFIX_MAP>> lpg_;
    void _initLTG();
    void _initLPSG();
    string _getPrefix(string s);
    string _getSuffix(string s);
};

/*
 * Construct an instance of dictionary
 */
SpellChecker::SpellChecker(){
    dict_ = new set<string>();
}

/*
 * Delete instance
 */
SpellChecker::~SpellChecker() {
    delete dict_;
}

/*
 * Load dictionary from input stream (file)
 */
void SpellChecker::loadDictionary(istream &input) {
    string temp_;
    while(getline(input, temp_)){
        dict_->insert(temp_);
    }
    _initLTG();
    _initLPSG();
}

/*
 * Check if word is wrong
 */
bool SpellChecker::spellCheck(string s) {
    return dict_->find(s) != dict_->end();
}

/*
 * Find all options for replace wrong word by right ones
 * which can be transformed into verifiable word through transposition
 * neighborhood in source word
 */
set<string> SpellChecker::options_T(string s) {
    sort(s.begin(), s.end());
    return set<string>(ltg_[s.length()][s].begin(), ltg_[s.length()][s].end());
}

/*
 * Find all options for replace wrong word by right ones
 * which can be transformed into verifiable word through deletion one symbol
 * from source word
 */
set<string> SpellChecker::options_D(string s) {
    set<string> cw_;
    string prefix_ = _getPrefix(s);
    string suffix_ = _getSuffix(s);
    PREFIX_MAP prefix_map = lpg_[s.length() + 1].first;
    SUFFIX_MAP suffix_map = lpg_[s.length() + 1].second;
    STRING_SET suffixes_ = prefix_map[prefix_];
    STRING_SET prefixes_ = suffix_map[suffix_];
    for(auto s_ = suffixes_.begin(); s_ != suffixes_.end(); s_++){
        cw_.insert(prefix_ + *s_);
    }
    for(auto p_ = prefixes_.begin(); p_ != prefixes_.end(); p_++){
        cw_.insert(*p_ + suffix_);
    }
    return cw_;
}

/*
 * Find all options for replace wrong word by right ones
 * which can be transformed into verifiable word through insertion one symbol
 * into source word
 */
set<string> SpellChecker::options_I(string s) {
    set<string> cw_;
    string prefix_ = _getPrefix(s);
    string suffix_ = _getSuffix(s);
    PREFIX_MAP prefix_map = lpg_[s.length() - 1].first;
    SUFFIX_MAP suffix_map = lpg_[s.length() - 1].second;
    STRING_SET suffixes_ = prefix_map[prefix_];
    STRING_SET prefixes_ = suffix_map[suffix_];
    for(auto s_ = suffixes_.begin(); s_ != suffixes_.end(); s_++){
        cw_.insert(prefix_ + *s_);
    }
    for(auto p_ = prefixes_.begin(); p_ != prefixes_.end(); p_++){
        cw_.insert(*p_ + suffix_);
    }
    return cw_;
}


void SpellChecker::_initLTG(){
    for(auto w_ = dict_->begin(); w_ != dict_->end(); w_++){
        if(ltg_.find(w_->length()) == ltg_.end()){
            ltg_[w_->length()] = unordered_map<string, unordered_set<string>>();
        }
        string temp_(*w_);
        sort(temp_.begin(), temp_.end());
        if(ltg_[w_->length()].find(temp_) == ltg_[w_->length()].end()){
            ltg_[w_->length()][temp_] = unordered_set<string>();
        }
        ltg_[w_->length()][temp_].insert(*w_);
    }
}

void SpellChecker::_initLPSG() {
    for(auto w_ = dict_->begin(); w_ != dict_->end(); w_++){
        if(lpg_.find(w_->length()) == lpg_.end()){
            lpg_[w_->length()] = pair<PREFIX_MAP, SUFFIX_MAP>();
        }
        string prefix_ = _getPrefix(*w_);
        string suffix_ = _getSuffix(*w_);
        if(w_->length() % 2){
            if(lpg_[w_->length()].first.find(prefix_) == lpg_[w_->length()].first.end())
                lpg_[w_->length()].first[prefix_] = unordered_set<string>();
            if(lpg_[w_->length()].second.find(suffix_) == lpg_[w_->length()].second.end())
                lpg_[w_->length()].second[suffix_] = unordered_set<string>();
            lpg_[w_->length()].first[prefix_].insert(suffix_);
            lpg_[w_->length()].second[suffix_].insert(prefix_);
        }
        else{
            ULONG plen_ = (ULONG)floor(w_->length() / 2);
            string pkey_ = prefix_;
            if(w_->length() != 1)
                prefix_ += w_->operator[](plen_ + 1);
            if(lpg_[w_->length()].first.find(pkey_) == lpg_[w_->length()].first.end())
                lpg_[w_->length()].first[pkey_] = unordered_set<string>();
            if(lpg_[w_->length()].second.find(suffix_) == lpg_[w_->length()].second.end())
                lpg_[w_->length()].second[suffix_] = unordered_set<string>();
            lpg_[w_->length()].first[pkey_].insert(suffix_);
            lpg_[w_->length()].second[suffix_].insert(prefix_);
        }
    }
}

string SpellChecker::_getPrefix(string s) {
    if(s.length() < 2)
        return s;
    ULONG plen_ = (ULONG)floor(s.length() / 2);
    return s.substr(0, plen_);
}

string SpellChecker::_getSuffix(string s) {
    if(s.length() < 2)
        return s;
    ULONG plen_ = (ULONG)floor(s.length() / 2);
    if(s.length() % 2)
        return s.substr(plen_, s.length() - plen_);
    return s.substr(plen_ + 1, s.length() - plen_ - 1);
}

#endif //CHW_2_SPELLCHECKER_H
