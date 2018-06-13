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

#ifndef CHW_2_TRIEDICTIONARY_H
#define CHW_2_TRIEDICTIONARY_H

#include "IDictionary.h"
#include "../tree/Trie.h"

/*
 * Dictionary based on prefix trees
 */
class TrieDictionary : public IDictionary {

public:
    virtual set<string> getWords();

    void addWord(string word);

    bool isIncluded(string word);

    TrieDictionary();

    virtual ~TrieDictionary();

private:
    Trie *trie_;
};

/*
 * Add word to dictionary
 */
void TrieDictionary::addWord(string word) {
    trie_->add(word);
}

/*
 * Check if word exists in dictionary
 */
bool TrieDictionary::isIncluded(string word) {
    return trie_->contains(word);
}

/*
 * Construct an instance of dictionary
 */
TrieDictionary::TrieDictionary() {
    trie_ = new Trie;
}
TrieDictionary::~TrieDictionary() {
    delete trie_;
}

#endif //CHW_2_TRIEDICTIONARY_H

set<string> TrieDictionary::getWords() {
    return set<string>();
}
