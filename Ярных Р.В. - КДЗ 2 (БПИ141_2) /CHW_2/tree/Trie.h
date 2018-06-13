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

#ifndef CHW_2_TRIE_H
#define CHW_2_TRIE_H
#define ALPH_N 26

#include <set>
#include "ITree.h"

/*
 * Prefix tree (trie)
 */
class Trie : public ITree<string> {
private:
    struct Node{
        char key;
        Node* children[ALPH_N];
    };
    Node *head_;

public:
    void add(string key);
    bool contains(string key);
    Trie();
    virtual ~Trie();

private:
    string _constructWord(Node* node, set<string> &sset);
    void _clear(Node* node);
};

/*
 * Construct an instance of trie
 */
Trie::Trie() {
    head_ = new Node;
}

/*
 * Add key into tree
 */
void Trie::add(string key) {
    Node* temp_ = head_;
    for(string::iterator it = key.begin(); it != key.end(); it++){
        Node* child_ = temp_->children[*it - 'a'];
        if(!child_){
            child_ = new Node;
            child_->key = *it;
            temp_->children[*it - 'a'] = child_;
        }
        temp_ = child_;
    }
}

/*
 * Check if key exists in tree
 */
bool Trie::contains(string key) {
    bool inc_ = true;
    Node *temp_ = head_;
    for(string::iterator it = key.begin(); it != key.end(); it++){
        if(!temp_->children[*it - 'a']){
            inc_ = false;
            break;
        }
        else{
            temp_ = temp_->children[*it - 'a'];
        }
    }
    return inc_;
}

/*
 * Clear tree
 */
void Trie::_clear(Node* node){
    if(!node)
        return;
    for(int i = 0; i < ALPH_N; i++){
        if(!node->children[i]) {
            _clear(node->children[i]);
            delete node->children[i];
        }
    }
}

string Trie::_constructWord(Trie::Node *node, set<string> &sset) {
    return "";
}

/*
 * Delete instance
 */
Trie::~Trie() {
    Node* temp_ = head_;
    _clear(temp_);
}

#endif //CHW_2_TRIE_H
