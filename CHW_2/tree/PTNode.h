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

#ifndef CHW_2_PTNODE_H
#define CHW_2_PTNODE_H
#include <string>
using namespace std;

/*
 * PATRICIA trie node
 */
struct PTNode{
    PTNode(string key, PTNode * sister, PTNode * olderChild){
        this->key = key;
        this->sister = sister;
        this->olderChild = olderChild;
    }
    string key;
    PTNode * sister;
    PTNode * olderChild;
};


#endif //CHW_2_PTNODE_H
