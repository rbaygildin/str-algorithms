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

#ifndef CHW_2_PTREEDICTIONARY_H
#define CHW_2_PTREEDICTIONARY_H

#include <set>
#include "IDictionary.h"
#include "../tree/PTrie.h"

/*
 * Compressed radix (prefix) tree
 */
class PTrieDictionary : public IDictionary {

public:

    virtual set<string> getWords();

    PTrieDictionary();
    virtual void addWord(string word);

    virtual bool isIncluded(string word);

    virtual ~PTrieDictionary();

private:
    PTrie *trie_;
};

/*
 * Construct an instance of PATRICIA trie
 */
PTrieDictionary::PTrieDictionary() {
    trie_ = new PTrie;
}

/*
 * Add word to dictionary
 */
void PTrieDictionary::addWord(string word) {
    trie_->add(word);
}

/*
 * Check if word exists in dictionary
 */
bool PTrieDictionary::isIncluded(string word) {
    return trie_->contains(word);
}

/*
 * Retrieve all words from dictionary
 */
set<string> PTrieDictionary::getWords() {
    return set<string>();
}

/*
 * Delete instance
 */
PTrieDictionary::~PTrieDictionary() {
    delete trie_;
}

#endif //CHW_2_PTREEDICTIONARY_H