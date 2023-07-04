#ifndef __PROGTEST__

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <variant>
#include <vector>


using State = unsigned int;
using Symbol = uint8_t;

struct NFA {
    std::set<State> m_States;
    std::set<Symbol> m_Alphabet;
    std::map<std::pair<State, Symbol>, std::set<State>> m_Transitions;
    State m_InitialState;
    std::set<State> m_FinalStates;
};

struct DFA {
    std::set<State> m_States;
    std::set<Symbol> m_Alphabet;
    std::map<std::pair<State, Symbol>, State> m_Transitions;
    State m_InitialState;
    std::set<State> m_FinalStates;
};

#endif

using namespace std;

void aag_Trans(const NFA& a, const NFA& b,std::set<State> start_a, std::set<State> start_b, std::map< std::pair<std::pair<std::set<State>, std::set<State>>, Symbol>, pair<set<State>, set<State>>> *newStates, Symbol letter, vector<pair<set<State>, set<State>>>* checked){
    set<State> next_a;
    set<State> next_b;
    for(auto it = start_a.begin(); it != start_a.end();it++){
        auto itTrans = a.m_Transitions.find(make_pair(*it, letter));
        if(itTrans != a.m_Transitions.end())next_a.insert(itTrans->second.begin(), itTrans->second.end());
    }
    for(auto it = start_b.begin(); it != start_b.end();it++){
        auto itTrans = b.m_Transitions.find(make_pair(*it, letter));
        if(itTrans != b.m_Transitions.end())next_b.insert(itTrans->second.begin(), itTrans->second.end());
    }
    pair<set<State>, set<State>> tmpKey, tmpState;
    if(next_a.empty() || next_b.empty()){
        return;
    }
    tmpKey.first.insert(start_a.begin(), start_a.end());
    tmpKey.second.insert(start_b.begin(), start_b.end());
    tmpState.first.insert(next_a.begin(), next_a.end());
    tmpState.second.insert(next_b.begin(), next_b.end());
    start_a = next_a;
    start_b = next_b;
    (*newStates).insert(make_pair(make_pair(tmpKey, letter), tmpState));
    if(find((*checked).begin(), (*checked).end(), tmpState) == (*checked).end()) (*checked).push_back(tmpState);           
}

set<Symbol> aag_intersectSets(set<Symbol> a_Alphabet, set<Symbol> b_Alphabet, set<Symbol> tmp){
    for(auto it = a_Alphabet.begin(); it != a_Alphabet.end(); it++){
        if(b_Alphabet.find(*it) != b_Alphabet.end()) tmp.insert(*it);
    }
    return tmp;
}

std::map<std::pair<State, Symbol>, State> aag_rename(std::map<std::pair<State, Symbol>, State> bestStates, set<Symbol> alphabet, std::map< std::pair<std::pair<std::set<State>, std::set<State>>, Symbol>, pair<set<State>, set<State>>> newStates, vector<pair<set<State>, set<State>>> checked){
    State i = 0, pos = 0;
    while(i < checked.size()){
        for(auto itLetter = alphabet.begin(); itLetter != alphabet.end();itLetter++){
            auto it = newStates.find(make_pair(checked.at(i), *itLetter));
            if(!(it != newStates.end())) continue;
            for(size_t ii = 0; ii < checked.size(); ii++){
                if(it->second.first == checked.at(ii).first && it->second.second == checked.at(ii).second){
                    pos = ii;
                    break;
                }
            }
            bestStates.insert({make_pair(i, *itLetter), pos});
        }
        i++;
    }
    return bestStates;
}

// std::map<std::pair<State, Symbol>, std::set<State>> aag_renameStaert(std::map<std::pair<State, Symbol>, std::set<State>> m_Transitions)

vector<pair<State, State>> aag_addEnd(State i, vector<pair<State, State>> endStartSt, vector<pair<set<State>, set<State>>> checked, set<State> aFiniteStates, set<State> bFiniteStates){
    if(i >= checked.size()) return endStartSt;
    for(auto ita = aFiniteStates.begin(); ita != aFiniteStates.end(); ita++){
        for(auto itb = bFiniteStates.begin(); itb != bFiniteStates.end(); itb++){
            if(checked.at(i).first.find(*ita) != checked.at(i).first.end() && checked.at(i).second.find(*itb) != checked.at(i).second.end()){
                endStartSt.push_back(make_pair(i, 1));
                return aag_addEnd(++i, endStartSt, checked, aFiniteStates, bFiniteStates);
            }
        }
    }
    endStartSt.push_back(make_pair(i, 0));
    return aag_addEnd(++i, endStartSt, checked, aFiniteStates, bFiniteStates);
}

vector<pair<State, State>> aag_addEnd_unify(State i, vector<pair<State, State>> endStartSt, vector<pair<set<State>, set<State>>> checked, set<State> aFiniteStates, set<State> bFiniteStates){
    if(i >= checked.size()) return endStartSt;
    for(auto ita = aFiniteStates.begin(); ita != aFiniteStates.end(); ita++){
        if(!bFiniteStates.empty()){for(auto itb = bFiniteStates.begin(); itb != bFiniteStates.end(); itb++){
            if(checked.at(i).first.find(*ita) != checked.at(i).first.end() || checked.at(i).second.find(*itb) != checked.at(i).second.end()){
                endStartSt.push_back(make_pair(i, 1));
                i++;
                return aag_addEnd_unify(i, endStartSt, checked, aFiniteStates, bFiniteStates);
            }
        }
        }
        else{
            if(checked.at(i).first.find(*ita) != checked.at(i).first.end()){
                endStartSt.push_back(make_pair(i, 1));
                i++;
                return aag_addEnd_unify(i, endStartSt, checked, aFiniteStates, bFiniteStates);
            }
        }
    }
    if(aFiniteStates.empty()){for(auto itb = bFiniteStates.begin(); itb != bFiniteStates.end(); itb++){
        if(checked.at(i).second.find(*itb) != checked.at(i).second.end()){
            endStartSt.push_back(make_pair(i, 1));
            i++;
            return aag_addEnd_unify(i, endStartSt, checked, aFiniteStates, bFiniteStates);
        }
        }
    }
    endStartSt.push_back(make_pair(i, 0));
    i++;
    return aag_addEnd_unify(i, endStartSt, checked, aFiniteStates, bFiniteStates);
}

set<State> aag_findUseless(std::map<std::pair<State, Symbol>, State> betterStates,  vector<pair<State, State>> endStartSt,set<State> weUsed){
    int changes = 0;
    do{
        changes = 0;
        for(auto it = betterStates.begin(); it != betterStates.end(); it++){
            if(weUsed.find(it->second) != weUsed.end()){
                if(!(weUsed.find(it->first.first) != weUsed.end())){
                    weUsed.insert(it->first.first);
                    changes++;                    
                }
                if(weUsed.size() == endStartSt.size()) return weUsed;
                continue;
            }
        }
    }while(changes != 0);
    return weUsed;
}

std::map<std::pair<State, Symbol>, State> aag_renameSecond(std::map<std::pair<State, Symbol>, State> bestStates,std::map<std::pair<State, Symbol>, State> tmpStates, vector<pair<State, State>> endStartSt, set<Symbol> alphabet){
    int pos;
    size_t i = 0;
    while(i != endStartSt.size()){
        for(auto itLetter = alphabet.begin(); itLetter != alphabet.end(); itLetter++){
            auto it = bestStates.find(make_pair(endStartSt.at(i).first, *itLetter));
            if(it != bestStates.end()){
                for(size_t ii = 0; ii < endStartSt.size(); ii++){
                    if(it->second == endStartSt.at(ii).first){
                        pos = ii;
                        break;
                    }
                }
                tmpStates.insert({make_pair(i,*itLetter), pos});
            }
        }
        i++;
    }
    return tmpStates;
}

std::map<std::pair<State, Symbol>, State> aag_removeUseless(std::map<std::pair<State, Symbol>, State> bestStates, std::map<std::pair<State, Symbol>, State> betterStates, set<State> weUsed){
    for(auto it = betterStates.begin(); it != betterStates.end(); it++){
        if(weUsed.find(it->first.first) != weUsed.end() && weUsed.find(it->second) != weUsed.end()){
            bestStates.insert(*it);
        }
    }
    return bestStates;
}

vector<pair<State, State>> aag_removeUselessVector(set<State> weUsed, vector<pair<State, State>> endStartSt){
    vector<pair<State, State>> newEndStart;
    for(auto it = endStartSt.begin(); it != endStartSt.end(); it++){
        if(weUsed.find(it->first) != weUsed.end()){
            newEndStart.push_back(*it);
        }
    }
    return newEndStart;
}

pair<map<pair<State,vector<State>>, State>, set<State>> aag_minimizator(std::map<std::pair<State, Symbol>, State>bestStates,vector<pair<State, State>> endStartSt, set<Symbol> alphabet, vector<State> resKey, vector<vector<State>> firstValues, set<State> finStates){
    vector<vector<State>> newValues;
    vector<State> group;
    for(size_t i = 0; i < endStartSt.size(); i++){
        vector<State> vecKey;
        for(auto itLetter = alphabet.begin(); itLetter != alphabet.end(); itLetter++){
            auto it = bestStates.find(make_pair(i, *itLetter));
            if(it == bestStates.end()) vecKey.push_back(-1);
            else if(it != bestStates.end()) vecKey.push_back(resKey.at(it->second));
        }
        newValues.push_back(vecKey);
    }
    //States
    State serie = 0;
    map<pair<State,vector<State>>, State> originality;
    for(size_t i = 0; i < newValues.size(); i++){
        auto it = originality.find(make_pair(resKey.at(i), newValues.at(i))); 
        if( it == originality.end()){
            originality.insert({make_pair(resKey.at(i), newValues.at(i)), serie});
            group.push_back(serie++);
        }
        else group.push_back(it->second);
    }
    if(resKey != group) return aag_minimizator(bestStates, endStartSt, alphabet, group, newValues, finStates);
    else{
        for(auto it = originality.begin(); it != originality.end(); it++){
            for(size_t i = 0; i < group.size(); i++){
                // cout << group[i] << endl;
                if(group.at(i) == it->second && endStartSt.at(i).second == 1) {
                    finStates.insert(group.at(i));
                    break;
                }
            }
        }
        pair<map<pair<State,vector<State>>, State>, set<State>> mySave = make_pair(originality, finStates);
        return mySave;
    }
}

pair<std::map<std::pair<State, Symbol>, State>, set<State>> aag_minimize(std::map<std::pair<State, Symbol>, State> bestStates, vector<pair<State, State>> endStartSt, set<Symbol> alphabet, set<State> ends){
    //step1
    vector<vector<State>> firstValues;
    for(size_t i = 0; i < endStartSt.size(); i++){
        vector<State> vecKey;
        for(auto itLetter = alphabet.begin(); itLetter != alphabet.end(); itLetter++){
            auto it = bestStates.find(make_pair(i, *itLetter));
            if(it == bestStates.end()) vecKey.push_back(-1);
            else if(it != bestStates.end()) vecKey.push_back(endStartSt.at(it->second).second);
        }
        firstValues.push_back(vecKey);
    }
    //"step 1" endStartSt.at(i).second =  firstValues;
    // step 2
    State serie = 0;
    vector<State> vecKey;
    map<pair<State, vector<State>>, State> originality;
    for(size_t i = 0; i < firstValues.size(); i++){
        auto it = originality.find(make_pair(endStartSt.at(i).second, firstValues.at(i))); 
        if( it == originality.end()){
            originality.insert({make_pair(endStartSt.at(i).second, firstValues.at(i)), serie});
            vecKey.push_back(serie++);
        }
        else vecKey.push_back(it->second);
    }
    //step 3 - Plan recursion
    //map<pair<State, Symbol>, State>
    pair<map<pair<State,vector<State>>, State>, set<State>> mySaveMax;
    mySaveMax = aag_minimizator(bestStates, endStartSt, alphabet, vecKey, firstValues, ends);
    originality = mySaveMax.first;
    ends = mySaveMax.second;
    std::map<std::pair<State, Symbol>, State> answer;
    for(auto it = originality.begin(); it != originality.end(); it++){
        State i = 0;
        for(auto itLetter = alphabet.begin(); itLetter != alphabet.end(); itLetter++){
            if(it->first.second.at(i) + 1 != 0) answer.insert({make_pair(it->second, *itLetter), it->first.second.at(i)});
            i++;
        }
    }
    pair<std::map<std::pair<State, Symbol>, State>, set<State>> mySave = make_pair(answer, ends);
    return mySave;
    
}

NFA aag_fullState(const NFA& a, NFA newA, set<Symbol> alphabet){
    newA = a;
    set<State> fillHere;
    auto it = newA.m_States.end();
    it--;
    State x = *it + 1;
    fillHere.insert(x);
    for(auto it = newA.m_States.begin(); it != newA.m_States.end(); it++){
        for(auto itLetter = alphabet.begin(); itLetter != alphabet.end(); itLetter++){
            if(newA.m_Transitions.find(make_pair(*it, *itLetter)) == newA.m_Transitions.end()){
                newA.m_Transitions.insert({make_pair(*it, *itLetter), fillHere});
            }
        }
    }
    for(auto itLetter = alphabet.begin(); itLetter != alphabet.end(); itLetter++){
        newA.m_Transitions.insert({make_pair(x, *itLetter), fillHere});
    }
    newA.m_States.insert(x);
    return newA;
}

vector<pair<State, State>> aag_changeVector(vector<pair<State, State>> endStartSt){
    vector<pair<State, State>> newEndStartSt;
    for(size_t i = 0; i < endStartSt.size(); i++){
        newEndStartSt.push_back(make_pair(i,endStartSt[i].second));
    }
    return newEndStartSt;
}

DFA unify(const NFA& a, const NFA& b){
    DFA tmp;                                                                                   
    NFA newA, newB;
    tmp.m_Alphabet.insert(a.m_Alphabet.begin(), a.m_Alphabet.end());
    tmp.m_Alphabet.insert(b.m_Alphabet.begin(), b.m_Alphabet.end());

    newA = aag_fullState(a, newA, tmp.m_Alphabet);
    newB = aag_fullState(b, newB, tmp.m_Alphabet);
    //
    set<State> start_a;
    set<State> start_b;
    start_a.insert(newA.m_InitialState);
    start_b.insert(newB.m_InitialState);
    map<pair<pair<set<State>, set<State>>, Symbol>, pair<set<State>, set<State>>> newStates;
    vector<pair<set<State>, set<State>>> checked;
    pair<set<State>, set<State>> tmpKey;
    tmpKey.first.insert(start_a.begin(), start_a.end());
    tmpKey.second.insert(start_b.begin(), start_b.end());
    checked.push_back(tmpKey);
    // 
    int i = 0, length = 1;
    while(i < length){
        for(auto itLetter = tmp.m_Alphabet.begin(); itLetter != tmp.m_Alphabet.end(); itLetter++){
            aag_Trans(newA,newB, checked.at(i).first, checked.at(i).second, &newStates, *itLetter , &checked);
        }
        length = checked.size();
        i++;
    }    
    
    std::map<std::pair<State, Symbol>, State> betterStates;
    vector<pair<State, State>> endStartSt;
    std::map<std::pair<State, Symbol>, State> bestStates;
    set<State> weUsed;
    endStartSt = aag_addEnd_unify(0, endStartSt, checked, newA.m_FinalStates, newB.m_FinalStates);
    betterStates = aag_rename(betterStates, tmp.m_Alphabet, newStates, checked);
    // removeUSELESS
    for(size_t i = 0; i < endStartSt.size(); i++){
        if(endStartSt.at(i).second ==  1){
            weUsed.insert(endStartSt.at(i).first);
        } 
    }
    weUsed = aag_findUseless(betterStates, endStartSt, weUsed);
    if(!(weUsed.find(0) != weUsed.end())) {
        tmp.m_Alphabet.insert(newA.m_Alphabet.begin(), newA.m_Alphabet.end());
        tmp.m_Alphabet.insert(newB.m_Alphabet.begin(), newB.m_Alphabet.end());
        tmp.m_InitialState = 0;
        tmp.m_States.insert(0);
        if(a.m_FinalStates.find(a.m_InitialState) != a.m_FinalStates.end() || b.m_FinalStates.find(b.m_InitialState) != b.m_FinalStates.end()) tmp.m_FinalStates.insert(0);
        return tmp;
    }
    if(endStartSt.size() != weUsed.size()){
        bestStates = aag_removeUseless(bestStates, betterStates, weUsed);
        endStartSt = aag_removeUselessVector(weUsed, endStartSt);
        std::map<std::pair<State, Symbol>, State> tmpStates;
        tmpStates = aag_renameSecond(bestStates, tmpStates, endStartSt, tmp.m_Alphabet);
        endStartSt = aag_changeVector(endStartSt);
        bestStates = tmpStates;
    }
    else{
        bestStates = betterStates;
    }
    ////
    set<State> ends;
    pair<std::map<std::pair<State, Symbol>, State>, set<State>> mySaveMin;
    mySaveMin = aag_minimize(bestStates, endStartSt, tmp.m_Alphabet, ends);
    bestStates = mySaveMin.first;
    ends = mySaveMin.second;
    tmp.m_Alphabet.insert(newA.m_Alphabet.begin(), newA.m_Alphabet.end());
    tmp.m_Alphabet.insert(newB.m_Alphabet.begin(), newB.m_Alphabet.end());
    tmp.m_Transitions = bestStates;
    tmp.m_InitialState = 0;
    for(auto it = bestStates.begin(); it != bestStates.end(); it++){
        tmp.m_States.insert(it->first.first);
        tmp.m_States.insert(it->second);
    }
    tmp.m_States.insert(ends.begin(), ends.end());
    tmp.m_FinalStates = ends;
    return tmp;
}

DFA intersect(const NFA& a, const NFA& b){
    DFA tmp;
    ///alphabet
    tmp.m_Alphabet = aag_intersectSets(a.m_Alphabet, b.m_Alphabet, tmp.m_Alphabet);
    ///
    set<State> start_a;
    set<State> start_b;
    start_a.insert(a.m_InitialState);
    start_b.insert(b.m_InitialState);
    map<pair<pair<set<State>, set<State>>, Symbol>, pair<set<State>, set<State>>> newStates;
    vector<pair<set<State>, set<State>>> checked;
    pair<set<State>, set<State>> tmpKey;
    tmpKey.first.insert(start_a.begin(), start_a.end());
    tmpKey.second.insert(start_b.begin(), start_b.end());
    checked.push_back(tmpKey);
    int i = 0, length = 1;
    while(i < length){
        for(auto itLetter = tmp.m_Alphabet.begin(); itLetter != tmp.m_Alphabet.end(); itLetter++){
            aag_Trans(a,b, checked.at(i).first, checked.at(i).second, &newStates, *itLetter , &checked);
        }
        length = checked.size();
        i++;
    }
    std::map<std::pair<State, Symbol>, State> betterStates;
    vector<pair<State, State>> endStartSt;
    std::map<std::pair<State, Symbol>, State> bestStates;
    set<State> weUsed;
    endStartSt = aag_addEnd(0, endStartSt, checked, a.m_FinalStates, b.m_FinalStates);
    betterStates = aag_rename(betterStates, tmp.m_Alphabet, newStates, checked);
    //removeUSELESS
    for(size_t i = 0; i < endStartSt.size(); i++){
        if(endStartSt.at(i).second == 1) weUsed.insert(endStartSt.at(i).first);
    }
    weUsed = aag_findUseless(betterStates, endStartSt, weUsed);
    if(weUsed.find(0) == weUsed.end()) {
        tmp.m_Alphabet.insert(a.m_Alphabet.begin(), a.m_Alphabet.end());
        tmp.m_Alphabet.insert(b.m_Alphabet.begin(), b.m_Alphabet.end());
        tmp.m_InitialState = 0;
        tmp.m_States.insert(0);
        if(a.m_FinalStates.find(a.m_InitialState) != a.m_FinalStates.end() && b.m_FinalStates.find(b.m_InitialState) != b.m_FinalStates.end()) tmp.m_FinalStates.insert(0);
        return tmp;
    }
    if(endStartSt.size() != weUsed.size()){
        bestStates = aag_removeUseless(bestStates, betterStates, weUsed);
        endStartSt = aag_removeUselessVector(weUsed, endStartSt);
        std::map<std::pair<State, Symbol>, State> tmpStates;
        tmpStates = aag_renameSecond(bestStates, tmpStates, endStartSt, tmp.m_Alphabet);
        endStartSt = aag_changeVector(endStartSt);
        bestStates = tmpStates;
    }
    else{
        bestStates = betterStates;
    }
    //////
    set<State> ends;
    pair<std::map<std::pair<State, Symbol>, State>, set<State>> mySaveMin;
    mySaveMin = aag_minimize(bestStates, endStartSt, tmp.m_Alphabet, ends);
    bestStates = mySaveMin.first;
    ends = mySaveMin.second;
    tmp.m_Alphabet.insert(a.m_Alphabet.begin(), a.m_Alphabet.end());
    tmp.m_Alphabet.insert(b.m_Alphabet.begin(), b.m_Alphabet.end());
    tmp.m_Transitions = bestStates;
    tmp.m_InitialState = 0;
    for(auto it = bestStates.begin(); it != bestStates.end(); it++){
        tmp.m_States.insert(it->first.first);
        tmp.m_States.insert(it->second);
    }
    tmp.m_States.insert(ends.begin(), ends.end());
    tmp.m_FinalStates = ends;
    return tmp;
}

#ifndef __PROGTEST__


// You may need to update this function or the sample data if your state naming strategy differs.
bool operator==(const DFA& a, const DFA& b)
{
    return std::tie(a.m_States, a.m_Alphabet, a.m_Transitions, a.m_InitialState, a.m_FinalStates) == std::tie(b.m_States, b.m_Alphabet, b.m_Transitions, b.m_InitialState, b.m_FinalStates);
}

int main()
{
    NFA a1{
            {0, 1, 2},
            {'a', 'b'},
            {
                    {{0, 'a'}, {0, 1}},
                    {{0, 'b'}, {0}},
                    {{1, 'a'}, {2}},
            },
            0,
            {2},
    };
    NFA a2{
            {0, 1, 2},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{1, 'a'}, {2}},
                    {{2, 'a'}, {2}},
                    {{2, 'b'}, {2}},
            },
            0,
            {2},
    };
    DFA a{
            {0, 1, 2, 3, 4},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{1, 'a'}, {2}},
                    {{2, 'a'}, {2}},
                    {{2, 'b'}, {3}},
                    {{3, 'a'}, {4}},
                    {{3, 'b'}, {3}},
                    {{4, 'a'}, {2}},
                    {{4, 'b'}, {3}},
            },
            0,
            {2},
    };
    assert(intersect(a1, a2) == a);

    NFA b1{
            {0, 1, 2, 3, 4},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{0, 'b'}, {2}},
                    {{2, 'a'}, {2, 3}},
                    {{2, 'b'}, {2}},
                    {{3, 'a'}, {4}},
            },
            0,
            {1, 4},
    };
    NFA b2{
            {0, 1, 2, 3, 4},
            {'a', 'b'},
            {
                    {{0, 'b'}, {1}},
                    {{1, 'a'}, {2}},
                    {{2, 'b'}, {3}},
                    {{3, 'a'}, {4}},
                    {{4, 'a'}, {4}},
                    {{4, 'b'}, {4}},
            },
            0,
            {4},
    };
    DFA b{
            {0, 1, 2, 3, 4, 5, 6, 7, 8},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{0, 'b'}, {2}},
                    {{2, 'a'}, {3}},
                    {{2, 'b'}, {4}},
                    {{3, 'a'}, {5}},
                    {{3, 'b'}, {6}},
                    {{4, 'a'}, {7}},
                    {{4, 'b'}, {4}},
                    {{5, 'a'}, {5}},
                    {{5, 'b'}, {4}},
                    {{6, 'a'}, {8}},
                    {{6, 'b'}, {4}},
                    {{7, 'a'}, {5}},
                    {{7, 'b'}, {4}},
                    {{8, 'a'}, {8}},
                    {{8, 'b'}, {8}},
            },
            0,
            {1, 5, 8},
    };
    assert(unify(b1, b2) == b);

    NFA c1{
            {0, 1, 2, 3, 4},
            {'a', 'b'},
            {
                    {{0, 'a'}, {1}},
                    {{0, 'b'}, {2}},
                    {{2, 'a'}, {2, 3}},
                    {{2, 'b'}, {2}},
                    {{3, 'a'}, {4}},
            },
            0,
            {1, 4},
    };
    NFA c2{
            {0, 1, 2},
            {'a', 'b'},
            {
                    {{0, 'a'}, {0}},
                    {{0, 'b'}, {0, 1}},
                    {{1, 'b'}, {2}},
            },
            0,
            {2},
    };
    DFA c{
            {0},
            {'a', 'b'},
            {},
            0,
            {},
    };
    assert(intersect(c1, c2) == c);

    NFA d1{
            {0, 1, 2, 3},
            {'i', 'k', 'q'},
            {
                    {{0, 'i'}, {2}},
                    {{0, 'k'}, {1, 2, 3}},
                    {{0, 'q'}, {0, 3}},
                    {{1, 'i'}, {1}},
                    {{1, 'k'}, {0}},
                    {{1, 'q'}, {1, 2, 3}},
                    {{2, 'i'}, {0, 2}},
                    {{3, 'i'}, {3}},
                    {{3, 'k'}, {1, 2}},
            },
            0,
            {2, 3},
    };
    NFA d2{
            {0, 1, 2, 3},
            {'i', 'k'},
            {
                    {{0, 'i'}, {3}},
                    {{0, 'k'}, {1, 2, 3}},
                    {{1, 'k'}, {2}},
                    {{2, 'i'}, {0, 1, 3}},
                    {{2, 'k'}, {0, 1}},
            },
            0,
            {2, 3},
    };
    DFA d{
            {0, 1, 2, 3},
            {'i', 'k', 'q'},
            {
                    {{0, 'i'}, {1}},
                    {{0, 'k'}, {2}},
                    {{2, 'i'}, {3}},
                    {{2, 'k'}, {2}},
                    {{3, 'i'}, {1}},
                    {{3, 'k'}, {2}},
            },
            0,
            {1, 2, 3},
    };
    assert(intersect(d1, d2) == d);
}

#endif
