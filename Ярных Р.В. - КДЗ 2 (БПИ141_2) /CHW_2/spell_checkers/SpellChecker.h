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
    unordered_map<unsigned long, unordered_map<string, unordered_set<string>>> ltg_;
    void _initLTG();
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
    unordered_map<unsigned long, unordered_set<string>> lg_;
    for(auto w_ = dict_->begin(); w_ != dict_->end(); w_++){
        if(lg_.find(w_->length()) == lg_.end())
            lg_[w_->length()] = unordered_set<string>();
        lg_[w_->length()].insert(*w_);
    }
    return cw_;
}

/*
 * Find all options for replace wrong word by right ones
 * which can be transformed into verifiable word through insertion one symbol
 * into source word
 */
set<string> SpellChecker::options_I(string s) {
    return set<string>();
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

#endif //CHW_2_SPELLCHECKER_H
