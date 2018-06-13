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

#ifndef CHW_2_ABSTRACTDICTIONARY_H
#define CHW_2_ABSTRACTDICTIONARY_H

#include <iostream>
#include <vector>

using namespace std;

/*
 * Abstract dictionary
 */
class IDictionary {
public:
    virtual void loadDictFromFile(istream& input);
    virtual void addWord(string word) = 0;
    virtual pair<vector<string>, vector<string>> findOccurrences(istream& input);
    virtual bool isIncluded(string word) = 0;
    virtual set<string> getWords() = 0;
    virtual ~IDictionary() = 0;
};

/*
 * Load dictionary from input stream (file)
 */
void IDictionary::loadDictFromFile(istream &input) {
    string temp_;
    while(getline(input, temp_)){
        addWord(temp_);
    }
}

/*
 * Find occurrences of words from dictionary in a text
 */
pair<vector<string>, vector<string>> IDictionary::findOccurrences(istream &input) {
    string temp_;
    vector<string> occurrences_;
    vector<string> notIncluded_;
    while(input >> temp_){
        stringstream ss;
        bool lastNonAlpha = false;
        for(string::iterator it = temp_.begin(); it != temp_.end(); it++){
            if((*it < 'a' || *it > 'z') && !lastNonAlpha) {
                string word_ = ss.str();
                if (isIncluded(word_)) {
                    occurrences_.push_back(word_);
                }
                else{
                    notIncluded_.push_back(word_);
                }
                ss.str("");
                lastNonAlpha = true;
            }
            else if(isalpha(*it)){
                lastNonAlpha = false;
                ss << (*it);
            }
        }
        if(ss.str().size() > 0){
            string word_ = ss.str();
            if (isIncluded(word_)) {
                occurrences_.push_back(word_);
            }
            else{
                notIncluded_.push_back(word_);
            }
        }
    }
    return pair<vector<string>, vector<string>>(occurrences_, notIncluded_);
}

/*
 * Delete instance
 */
IDictionary::~IDictionary(){

}

#endif //CHW_2_ABSTRACTDICTIONARY_H
