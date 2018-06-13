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

#ifndef CHW_2_PTRIE_H
#define CHW_2_PTRIE_H

#include "ITree.h"
#include "PTNode.h"

/*
 * PATRICIA trie
 */
class PTrie : public ITree<string>{
private:
    PTNode *head_;

public:
    virtual void add(string key);
    virtual bool contains(string key);
    virtual ~PTrie();

private:
    void _clear(PTNode * node);
    PTNode * _find(PTNode * node, string str);
    unsigned long _prefixLen(string s1, string s2);
    PTNode * _insert(PTNode * node, string str);
    void _cutNode(PTNode * node, unsigned long index);
};

/*
 * Add key into tree
 */
void PTrie::add(string key) {
    head_ = _insert(head_, key);
}

/*
 * Check if key exists in tree
 */
bool PTrie::contains(string key) {
    return _find(head_, key) != nullptr;
}

/*
 * Clear tree
 */
void PTrie::_clear(PTNode *node) {
    if(!node)
        return;
    PTNode * olderChild = node->olderChild;
    _clear(olderChild);
    PTNode * sister = node->sister;
    delete node;
    _clear(sister);
}

/*
 * Find node with specific key
 */
PTNode * PTrie::_find(PTNode *node, string str){
    if(!node)
        return nullptr;
    unsigned long pfl_ = _prefixLen(str, node->key);
    if(pfl_ == str.length())
        return node;
    else if(!pfl_)
        return _find(node->sister, str);
    else if(pfl_ == node->key.length())
        return _find(node->olderChild, str.substr(pfl_, str.length() - pfl_));
    return nullptr;
}

/*
 * Compute length of largest common prefix
 */
unsigned long PTrie::_prefixLen(string s1, string s2) {
    for(unsigned long k = 0; k < s1.length(); k++)
        if(k == s2.length() || (s1[k] != s2[k]))
            return k;
    return s1.length();
}

/*
 * Insert a node into tree
 */
PTNode * PTrie::_insert(PTNode *node, string str) {
    if(!node)
        return new PTNode(str, nullptr, nullptr);
    unsigned long pfl_ = _prefixLen(str, node->key);
    if(pfl_ == 0)
        node->sister = _insert(node->sister, str);
    else if(pfl_ < str.length()){
        if(pfl_ < node->key.length())
            _cutNode(node, pfl_);
        node->olderChild = _insert(node->olderChild, str.substr(pfl_, str.length() - pfl_));
    }
    return node;
}

/*
 * Split node into two new ones
 */
void PTrie::_cutNode(PTNode *node, unsigned long index) {
    PTNode *newChild_ = new PTNode(node->key.substr(index, node->key.length() - index), nullptr, node->olderChild);
    node->key = node->key.substr(0, index);
    node->olderChild = newChild_;
}

/*
 * Delete instance
 */
PTrie::~PTrie() {
    _clear(head_);
}

#endif //CHW_2_PTRIE_H
