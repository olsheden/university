#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
#define EXTENDED_SYNTAX

class CRangeList;

class CRange
{
public:
    long long m_start;
    long long m_end;
public:
    CRange();
    CRange(long long start, long long end);
    bool isNotCrossed(const CRange & check) const;
    bool isNotCrossedForMin(const CRange & check) const;
    CRange intersect(const CRange & x) const;
    CRange& operator =(const CRange & x);
    CRangeList operator+(const CRange & x) const;
    CRangeList operator-(const CRange & x) const;
};

CRange::CRange(){}

CRange::CRange(long long start, long long end){
    if(start > end) throw logic_error("");
    m_start = start;
    m_end = end;
}    

bool isSameSign(long long x, long long y){
    return ((x >= 0 && y >= 0) || (x <= 0 && y <= 0));
}

bool CRange::isNotCrossed(const CRange & check) const{
    if ( (  (isSameSign(check.m_start,m_end) && abs(check.m_start - m_end) == 1) || (isSameSign(check.m_end, m_start) && abs(check.m_end - m_start) == 1)) || ((check.m_start >= m_start && check.m_start <= m_end) || 
        (check.m_end >= m_start && check.m_end <= m_end) || 
        (check.m_start <= m_start && check.m_end >= m_end))) return false;
    return true;
}

bool CRange::isNotCrossedForMin(const CRange & check) const{
    if (((check.m_start >= m_start && check.m_start <= m_end) || 
        (check.m_end >= m_start && check.m_end <= m_end) || 
        (check.m_start <= m_start && check.m_end >= m_end))) return false;
    return true;
}

CRange CRange::intersect(const CRange & interval) const{
    long long min = m_start, max = m_end;
    if( m_start <= interval.m_start) min = m_start;
    else min = interval.m_start;
    if(m_end >= interval.m_end) max = m_end;
    else max = interval.m_end;
    return CRange(min, max);
}

CRange& CRange::operator =(const CRange & x){
    m_start = x.m_start;
    m_end = x.m_end;
    return *this;
}

class CRangeList
{
  public:
    // constructor
    CRangeList();
    CRangeList(std::initializer_list<CRange> intervals);

    // includes long long / range
    bool includes(const long long & num) const;
    bool includes(const CRange & find) const;
    // += range / range list
    CRangeList operator+(const CRange & second) const;
    CRangeList operator+(const CRangeList & x) const;
    // operator +=
    CRangeList& operator +=( const CRange & interval);
    CRangeList& operator +=( const CRangeList & x_list);
    CRangeList& operator +=( const vector<CRange> & x_list);
    // -= range / range list
    CRangeList& operator -=( const CRange & interval);
    CRangeList& operator -=( const CRangeList & x_list);

    CRangeList operator-(const CRange & second) const;
    CRangeList operator-(const CRangeList & x) const;
    // = range / range list
    CRangeList& operator =(const CRange& interval);
    CRangeList& operator =(const CRangeList& list);
    // operator ==
    friend bool operator ==(const CRange & first,const CRange & second);
    friend bool operator ==(const CRangeList & first,const CRangeList & second);
    // operator !=
    friend bool operator !=(const CRange & first,const CRange & second);
    friend bool operator !=(const CRangeList & first,const CRangeList & second);
    // operator <<
    friend std::ostream & operator << ( std::ostream & os, const CRangeList & a );
    //
    vector<CRange>::iterator begin() { return data.begin(); }
    vector<CRange>::iterator end() { return data.end(); }
  public:
    vector<CRange> data;
};

bool cmpStart(const CRange & a, const CRange & b){
    if(a.m_end < 0 && b.m_start > 0) return true;
    else if(a.m_end > 0 && b.m_start < 0) return false;
    return a.m_end - b.m_start < -1;
}

bool cmpEnd(const CRange & a, const CRange & b){
    return a.m_end < b.m_start;
}

bool cmpSpec(const CRange & a, const long long & num){
    return a.m_end < num;
}

CRangeList::CRangeList(){}


bool CRangeList::includes(const long long & num) const{
    auto it = lower_bound(data.begin(), data.end(), num, cmpSpec);
    if(it!= data.end() && it->m_start <= num) return true;
    return false;
}

bool CRangeList::includes(const CRange& find) const{
    auto it = lower_bound(data.begin(), data.end(), find, cmpEnd);
    while(it != data.end() && !(find.isNotCrossed(*it))){
        if(find.m_start >= (*it).m_start && find.m_end <= (*it).m_end) return true;
        it++;
    }
    return false;
}



CRangeList& CRangeList::operator =(const CRange& interval){
    data.clear();
    data.push_back(interval);
    return *this;
}

CRangeList& CRangeList::operator =(const CRangeList& list){
    data.clear();
    for(auto& x : list.data) data.push_back(x);
    return *this;
}



ostream &operator<<(ostream &os, const CRangeList &a) {
    ios_base::fmtflags flags = os.flags();
    int precision = os.precision();
    int width = os.width();
    os << dec;

    os << '{';
    for (size_t i = 0; i < a.data.size(); ++i) {
        if (a.data[i].m_start == a.data[i].m_end) {
            os << a.data[i].m_start;
        } else {
            os << '<' << a.data[i].m_start << ".." << a.data[i].m_end << '>';
        }
        if (i != a.data.size() - 1) {
            os << ',';
        }
    }
    os << '}';
    os.flags(flags);
    os.precision(precision);
    os.width(width);
    return os;
}

ostream &operator<<(ostream &os, const CRange &a) {
    ios_base::fmtflags flags = os.flags();
    int precision = os.precision();
    int width = os.width();
    os << dec;

    if (a.m_start == a.m_end) {
        os << a.m_start;
    } else {
        os << '<' << a.m_start << ".." << a.m_end << '>';
    }

    os.flags(flags);
    os.precision(precision);
    os.width(width);
    return os;
}


CRangeList& CRangeList::operator+=(const CRange& interval) {
    auto it = lower_bound(data.begin(), data.end(), interval, cmpStart);
    CRange tmp = std::move(interval);
    if (it != data.end()) {
        if (tmp.isNotCrossed((*it))) {
            data.insert(it, std::move(tmp));
            return *this;
        } else {
            while (it != data.end() && !(tmp.isNotCrossed(*it))) {
                if (tmp.isNotCrossed(*it)) {
                    break;
                }
                tmp = tmp.intersect(*it);
                it = data.erase(it);
            }
        }
    }

    while (it != data.end() && tmp.m_end + 1 >= it->m_start) {
        tmp = tmp.intersect(*it);
        it = data.erase(it);
    }

    data.insert(it, move(tmp));
    return *this;
}

CRangeList& CRangeList::operator +=( const CRangeList & x_list){
    for(auto& it_interval : x_list.data){
        *this += it_interval;
    }
    return *this;
}

CRangeList& CRangeList::operator +=( const vector<CRange> & x_list){
    for(auto& it_interval : x_list){
        *this += it_interval;
    }
    return *this;
}


CRangeList::CRangeList(std::initializer_list<CRange> intervals){
    *this += vector<CRange>(intervals);
}


int situation(const CRange & a, const CRange & b){
    if(b.m_start <= a.m_start && b.m_end >= a.m_end) return 0;
    else if((b.m_start >= a.m_start && b.m_start <= a.m_end) && b.m_end >= a.m_end) return 1;
    else if((b.m_end >= a.m_start && b.m_end <= a.m_end) && b.m_start <= a.m_start) return 2; 
    else if(b.m_start >= a.m_start && b.m_end <= a.m_end) return 3;
    else return 4;
}

CRangeList CRange::operator-(const CRange& x) const {
    CRangeList result;

    if (x.m_end < m_start || x.m_start > m_end) {
        result.data.push_back(*this);
    } else {
        if (x.m_start > m_start) {
            result.data.push_back(CRange(m_start, x.m_start - 1));
        }
        if (x.m_end < m_end) {
            result.data.push_back(CRange(x.m_end + 1, m_end));
        }
    }

    return result;
}

CRangeList& CRangeList::operator-=(const CRange& interval) {
    auto it = lower_bound(data.begin(), data.end(), interval, cmpEnd);
    CRangeList tmp;
    int situat;
    if (it != data.end()) {
        while (it != data.end() && !(interval.isNotCrossedForMin(*it))) {
            situat = situation(*it, interval);
            if (situat == 0) {
                data.erase(it);
            } 
            else if (situat == 1) {
                tmp = *it - interval;
                data.erase(it);
                it = data.insert(it, move(tmp.data[0]));
                it++;
            }
            else if (situat == 2) {
                tmp = *it - interval;
                data.erase(it);
                it = data.insert(it, move(tmp.data[0]));
                *this += move(tmp);
                return *this;
            }
            else if (situat == 3) {
                tmp = *it - interval;
                data.erase(it);
                it = data.insert(it, move(tmp.data[0]));
                it++;
                it = data.insert(it, move(tmp.data[1]));
                it++;
            }
            else if (situat == 4) {
                return *this;
            }
        }
        return *this;
    }
    else {
        return *this;
    }
}


CRangeList& CRangeList::operator -=( const CRangeList & x_list){
    for(auto& it_interval : x_list.data){
        *this -= it_interval;
    }
    return *this;
}


CRangeList CRangeList::operator-(const CRange & second) const{
    CRangeList result = *this;
    result -= second;
    return result;
}

CRangeList CRangeList::operator-(const CRangeList & x) const{
    CRangeList result = *this;
    result -= x;
    return result;
}

bool operator ==(const CRange & first,const CRange & second){
    if(first.m_start == second.m_start && second.m_end == first.m_end) return true;
    return false;
}

bool operator !=(const CRange & first,const CRange & second){
    if(first == second) return false;
    return true;
}

bool operator ==(const CRangeList & first,const CRangeList & second){
    if(first.data.size() != second.data.size()) return false;
    for(size_t i = 0; i < first.data.size(); i++){
        if(first.data[i] != second.data[i]) return false;
    }
    return true;
}

bool operator !=(const CRangeList & first,const CRangeList & second){
    if(first == second) return false;
    return true;
}


CRangeList CRange::operator+(const CRange & x) const{
    CRangeList result = CRangeList();
    result += *this;
    result += x;
    return result;
}

CRangeList CRangeList::operator+(const CRange & second) const{
    CRangeList result = *this;
    result += second;
    return result;
}

CRangeList CRangeList::operator+(const CRangeList & x) const{
    CRangeList result = *this;
    result += x;
    return result;
}



#ifndef __PROGTEST__
string             toString                                ( const CRangeList& x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int                main                                    ( void )
{
#ifdef EXTENDED_SYNTAX
#endif /* EXTENDED_SYNTAX */
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
