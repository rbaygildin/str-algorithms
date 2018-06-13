cmake_minimum_required(VERSION 3.3)
project(CHW_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(CHW_2 ${SOURCE_FILES} dict/IDictionary.h dict/HashDictionary.h tree/ITree.h tree/Trie.h tree/PTrie.h dict/TrieDictionary.h dict/SetDictionary.h dict/PTrieDictionary.h fuzzy_search/FuzzySearcher.h fuzzy_search/NaiveSearcher.h fuzzy_search/OptNaiveSearcher.h fuzzy_search/QuickSearcher.h spell_checkers/SpellChecker.h tree/PTNode.h)