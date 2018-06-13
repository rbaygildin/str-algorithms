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

#ifndef CHW_2_SETDICTIONARY_H
#define CHW_2_SETDICTIONARY_H

#include <set>
#include "IDictionary.h"

/*
 * Dictionary based on red-n-black trees
 */
class SetDictionary : public IDictionary {

public:

    virtual void addWord(string word);

    virtual bool isIncluded(string word);

    virtual set<string> getWords();

    SetDictionary();

    virtual ~SetDictionary();

private:

    set<string> *dict_;
};

/*
 * Add word to dictionary
 */
void SetDictionary::addWord(string word) {
    dict_->insert(word);
}

/*
 * Check if word exists in dictionary
 */
bool SetDictionary::isIncluded(string word) {
    return dict_->find(word) != dict_->end();
}

/*
 * Retrieve all words from dictionary
 */
set<string> SetDictionary::getWords() {
    return set<string>(*dict_);
}

/*
 * Construct an instance of dictionary
 */
SetDictionary::SetDictionary() {
    dict_ = new set<string>;
}

/*
 * Delete instance of dictionary
 */
SetDictionary::~SetDictionary() {
    delete dict_;
}

#endif //CHW_2_SETDICTIONARY_H
