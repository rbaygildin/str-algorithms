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

#ifndef CHW_2_HASHDICTIONARY_H
#define CHW_2_HASHDICTIONARY_H

#include <unordered_set>
#include <sstream>
#include <set>
#include <map>
#include "IDictionary.h"

/*
 * Dictionary based on hash tables
 */
class HashDictionary : public IDictionary {
public:
    void addWord(string word);
    bool isIncluded(string word);
    set<string> getWords();
    HashDictionary();
    virtual ~HashDictionary();
private:
    unordered_set<string> *dict_;
};

/*
 * Add word to dictionary
 */
void HashDictionary::addWord(string word) {
    dict_->insert(word);
}

/*
 * Check if word exists in dictionary
 */
bool HashDictionary::isIncluded(string word){
    return dict_->find(word) != dict_->end();
}

/*
 * Retrieve all words from dictionary
 */
set<string> HashDictionary::getWords() {
    set<string> words_;
    for(unordered_set<string>::iterator it = dict_->begin(); it != dict_->end(); it++)
        words_.insert(*it);
    return words_;
}

/*
 * Construct an instance of dictionary
 */
HashDictionary::HashDictionary() {
    dict_ = new unordered_set<string>();
}

/*
 * Delete instance of dictionary
 */
HashDictionary::~HashDictionary() {
    delete dict_;
}

#endif //CHW_2_HASHDICTIONARY_H