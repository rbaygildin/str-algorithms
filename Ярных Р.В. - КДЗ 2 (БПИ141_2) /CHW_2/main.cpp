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
#include <fstream>
#include "dict/HashDictionary.h"
#include "fuzzy_search/FuzzySearcher.h"
#include "fuzzy_search/QuickSearcher.h"
#include "spell_checkers/SpellChecker.h"
#include "dict/PTrieDictionary.h"
#include "dict/TrieDictionary.h"
#include "dict/SetDictionary.h"

#define TASK_3
#define T_A
#define TEST_LOG_TO_CONSOLE


void testTask_1(string, string);
void testTask_2(string);
void testTask_3(string, string);

/*
 * Test all implemented tasks
 * Hint: To test specific task it's necessary to define macro
 * that tells a compiler which pieces of code should be built
 * for further testing
 * Tutorial:
 * 1. For testing task with specific number, please, define
 * macro 'TASK_N' where N is number of task (eg: TASK_1 for testing task 1)
 * 2. For testing specific part of task, please, define
 * additional macro 'P' or 'TASK_N_P' where N is number of task and
 * P is part of task (eg: TASK_1_A for testing part a of task 1)
 * PS: There are options for logging tests into standard output (console)
 * and file. To select logging into console you need define macro 'TEST_LOG_TO_CONSOLE'.
 * To select logging into file you need define macro 'TEST_LOG_TO_FILE'
 */
int main(int argc, const char** argv)
{

#ifdef TASK_1
    testTask_1(argv[1], argv[2]);
#endif

#ifdef TASK_2
    testTask_2(argv[1]);
#endif

#ifdef TASK_3
    testTask_3(argv[1], argv[2]);
#endif
    return 0;
}

void testTask_1(string dict_path, string text_path){
    IDictionary *dict_;

#if defined(T_A) || defined(TASK1_A)
    dict_ = new HashDictionary();
#endif

#if defined(T_B) || defined(TASK1_B)
    dict_ = new SetDictionary();
#endif

#if defined(T_C) || defined(TASK1_C)
    dict_ = new TrieDictionary();
#endif

#if defined(T_D) || defined(TASK1_D)
    dict_ = new PTrieDictionary();
#endif

    ifstream input;
    ifstream wd;
    wd.open(dict_path);
    input.open(text_path);
    dict_->loadDictFromFile(wd);
    pair<vector<string>, vector<string>> ws_ = dict_->findOccurrences(input);

#if defined(TEST_LOG_TO_CONSOLE)
    cout << "Occurrences: " << endl;
    for_each(ws_.first.begin(), ws_.first.end(), [](string x){
        cout << x << endl;
    });
    cout << "Not included: " << endl;
    for_each(ws_.second.begin(), ws_.second.end(), [](string x){
        cout << x << endl;
    });
    cout << "================================\n" << endl;
#endif
    wd.close();
    input.close();
    delete dict_;
}


void testTask_2(string dict_path){
    IDictionary *dict_;

#if defined(T_A) || defined(TASK2_A)
    dict_ = new HashDictionary();
#endif

#if defined(T_B) || defined(TASK2_B)
    dict_ = new SetDictionary();
#endif

#if defined(T_C) || defined(TASK2_C)
    dict_ = new TrieDictionary();
#endif

#if defined(T_D) || defined(TASK2_D)
    dict_ = new PTrieDictionary();
#endif

    ifstream wd;
    wd.open(dict_path);
    dict_->loadDictFromFile(wd);
    FuzzySearcher *fs = new QuickSearcher(dict_->getWords());
    map<string, set<string>> mw_ = fs->fuzzySearch();

#if defined(TEST_LOG_TO_CONSOLE)
    for(map<string, set<string>>::iterator it = mw_.begin(); it != mw_.end(); it++){
        cout << it->first << ":" << endl;
        for(set<string>::iterator sit = it->second.begin(); sit != it->second.end(); sit++){
            cout << "\t" << (*sit) << endl;
        }
    }
    cout << "================================\n" << endl;
#endif
    delete fs;
    wd.close();
    delete dict_;
}

void testTask_3(string bdict_path, string sdict_path){
    ifstream bd_;
    ifstream sd_;
    bd_.open(bdict_path);
    sd_.open(sdict_path);
    SpellChecker spellChecker;
    spellChecker.loadDictionary(bd_);
    bd_.close();

#if defined(TEST_LOG_TO_CONSOLE)
    string s_;
    int i = 0;
    int mis_count = 0;
    while(getline(sd_, s_)){
        i++;
        if(spellChecker.spellCheck(s_))
            continue;
        mis_count++;
        cout << s_ << " (at " << i << " line):" << endl;
        set<string> opt_ = spellChecker.options_T(s_);
        for(set<string>::iterator it = opt_.begin(); it != opt_.end(); it++){
            cout << "\t" << *it << endl;
        }
    }
    cout << "Wrong words count: " << mis_count << endl;
#endif
    sd_.close();
}