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

#ifndef CHW_2_ITREE_H
#define CHW_2_ITREE_H
#include <string>

using namespace std;

/*
 * Abstract tree
 */
template <class K>
class ITree {
public:
    virtual void add(K key) = 0;
    virtual bool contains(K key) = 0;
    virtual ~ITree(){}
};


#endif //CHW_2_ITREE_H
