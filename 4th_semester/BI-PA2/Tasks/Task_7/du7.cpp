#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include <iterator>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */


struct HashOfPair {
    size_t operator()(const std::pair<std::string, std::string>& x) const {
        // Combine the hash values of the two strings
        size_t h1 = std::hash<std::string>{}(x.first);
        size_t h2 = std::hash<std::string>{}(x.second);
        return h1 ^ (h2 << 1);
    }
};

class Graph{
public:
    unordered_map<string, vector<string> > m_losers;
    unordered_map<string, unordered_set<string> > m_winners;
    unordered_set<string> m_names;
};

string differ(const unordered_set<string> & x, const unordered_map<string, vector<string> > & y){
    for(const auto & it : x){
        if(y.find(it) == y.end()) return it;
    }
    return "Kek";
}

std::list<string> findSolution(const Graph & m_graph, std::list<string> result, string winner , size_t step){
    if(step > 5) return result;
    if(m_graph.m_winners.find(winner) == m_graph.m_winners.end() && (step + 1) != m_graph.m_names.size()) return result;
    result.push_back(winner);
    if(m_graph.m_winners.find(winner) == m_graph.m_winners.end() && (step + 1) == m_graph.m_names.size()) return result;
    if((step + 1) == m_graph.m_names.size()){
        result.pop_back();
        return result;
    }
    for(const auto & it : m_graph.m_winners.find(result.back())->second){
        result = findSolution(m_graph, result, it, step+1);
        if(result.size() == m_graph.m_names.size()) return result;
    }
    result.pop_back();
    return result;
}

template <typename M_>
class CContest
{
public:
    // default constructor
    CContest(){}
    // destructor
    ~CContest(){}
    // addMatch ( contestant1, contestant2, result )
    CContest & addMatch ( const string & contestant1, const string & contestant2, const M_ & result){
        if(m_data.find(make_pair(contestant2,contestant1)) != m_data.end() || m_data.find(make_pair(contestant1,contestant2)) != m_data.end()) throw std::logic_error("Same match was already added");
        m_data.insert({make_pair(contestant1, contestant2), result});
        return (*this);
    }
    // // isOrdered ( comparator )
    bool isOrdered(std::function<int(const M_&)> compare) const {
        Graph m_graph;
		if(m_data.empty()) return false;
        for( const auto & match : m_data ){
            if(m_graph.m_names.find(match.first.first) == m_graph.m_names.end()) m_graph.m_names.insert(match.first.first);
            if(m_graph.m_names.find(match.first.second) == m_graph.m_names.end()) m_graph.m_names.insert(match.first.second);

            if(compare(match.second) == 0) return false;
            else if(compare(match.second) < 0) {
                auto find = m_graph.m_losers.find(match.first.first);
                if(find == m_graph.m_losers.end()) {
                    vector<string> tmp;
                    tmp.push_back(match.first.second);
                    m_graph.m_losers.insert({match.first.first, tmp});
                }
                else{
                    find->second.push_back(match.first.second);
                }
                auto findw = m_graph.m_winners.find(match.first.second);
                if(findw == m_graph.m_winners.end()) {
                    unordered_set<string> tmp;
                    tmp.insert(match.first.first);
                    m_graph.m_winners.insert({match.first.second, tmp});
                }
                else{
                    findw->second.insert(match.first.first);
                }
            }
            else {
                auto find = m_graph.m_losers.find(match.first.second);
                if(find == m_graph.m_losers.end()) {
                    vector<string> tmp;
                    tmp.push_back(match.first.first);
                    m_graph.m_losers.insert({match.first.second, tmp});
                }
                else{
                    find->second.push_back(match.first.first);
                }
                auto findw = m_graph.m_winners.find(match.first.first);
                if(findw == m_graph.m_winners.end()) {
                    unordered_set<string> tmp;
                    tmp.insert(match.first.second);
                    m_graph.m_winners.insert({match.first.first, tmp});
                }
                else{
                    findw->second.insert(match.first.second);
                }
            }
        }

        if(m_graph.m_names.size() - m_graph.m_losers.size() != 1) return false;
        std::list<string> result;
        result.push_back(differ(m_graph.m_names, m_graph.m_losers));
        for(const auto & it : m_graph.m_winners.find(result.back())->second){
            result = findSolution(m_graph, result, it, 1);
            if(result.size() == m_graph.m_names.size()) break;
        }
        if(result.size() != m_graph.m_names.size()) return false;
		for(const auto& winner : result){
			for (const auto& it : result) {
				if(it == winner) break;
				auto it_f = m_graph.m_winners.find(winner);
				if(it_f == m_graph.m_winners.end()) break;
				if (it_f->second.find(it) != it_f->second.end()) {
					return false;
				}
			}
		}
        return true;
    }


    // // results ( comparator )
    std::list<string> results (std::function<int(const M_&)> compare) const{
        Graph m_graph;
		if(m_data.empty()) throw std::logic_error("The list cant be created");
        for( const auto & match : m_data ){
            if(m_graph.m_names.find(match.first.first) == m_graph.m_names.end()) m_graph.m_names.insert(match.first.first);
            if(m_graph.m_names.find(match.first.second) == m_graph.m_names.end()) m_graph.m_names.insert(match.first.second);

            if(compare(match.second) == 0) throw std::logic_error("The list cant be created");
            else if(compare(match.second) < 0) {
                auto find = m_graph.m_losers.find(match.first.first);
                if(find == m_graph.m_losers.end()) {
                    vector<string> tmp;
                    tmp.push_back(match.first.second);
                    m_graph.m_losers.insert({match.first.first, tmp});
                }
                else{
                    find->second.push_back(match.first.second);
                }
                auto findw = m_graph.m_winners.find(match.first.second);
                if(findw == m_graph.m_winners.end()) {
                    unordered_set<string> tmp;
                    tmp.insert(match.first.first);
                    m_graph.m_winners.insert({match.first.second, tmp});
                }
                else{
                    findw->second.insert(match.first.first);
                }
            }
            else {
                auto find = m_graph.m_losers.find(match.first.second);
                if(find == m_graph.m_losers.end()) {
                    vector<string> tmp;
                    tmp.push_back(match.first.first);
                    m_graph.m_losers.insert({match.first.second, tmp});
                }
                else{
                    find->second.push_back(match.first.first);
                }
                auto findw = m_graph.m_winners.find(match.first.first);
                if(findw == m_graph.m_winners.end()) {
                    unordered_set<string> tmp;
                    tmp.insert(match.first.second);
                    m_graph.m_winners.insert({match.first.first, tmp});
                }
                else{
                    findw->second.insert(match.first.second);
                }
            }
        }

        if(m_graph.m_names.size() - m_graph.m_losers.size() != 1) throw std::logic_error("The list cant be created");
        std::list<string> result;
        result.push_back(differ(m_graph.m_names, m_graph.m_losers));
        for(const auto & it : m_graph.m_winners.find(result.back())->second){
            result = findSolution(m_graph, result, it, 1);
            if(result.size() == m_graph.m_names.size()) break;
        }
        if(result.size() != m_graph.m_names.size()) throw std::logic_error("The list cant be created");
		for(const auto& winner : result){
			for (const auto& it : result) {
				if(it == winner) break;
				auto it_f = m_graph.m_winners.find(winner);
				if(it_f == m_graph.m_winners.end()) break;
				if (it_f->second.find(it) != it_f->second.end()) {
					throw std::logic_error("The list cant be created");
				}
			}
		}
        return result;
    }

private:
    unordered_map<std::pair<string, string>, M_, HashOfPair> m_data;
};

#ifndef __PROGTEST__
struct CMatch
{
public:
    CMatch                        ( int               a,
                                    int               b )
            : m_A ( a ),
              m_B ( b )
    {
    }

    int                      m_A;
    int                      m_B;
};

class HigherScoreThreshold
{
public:
    HigherScoreThreshold          ( int diffAtLeast )
            : m_DiffAtLeast ( diffAtLeast )
    {
    }
    int                      operator ()                   ( const CMatch & x ) const
    {
        return ( x . m_A > x . m_B + m_DiffAtLeast ) - ( x . m_B > x . m_A + m_DiffAtLeast );
    }
private:
    int            m_DiffAtLeast;
};

int                HigherScore                             ( const CMatch    & x )
{
    return ( x . m_A > x . m_B ) - ( x . m_B > x . m_A );
}

int                main                                    ( void )
{
    // CContest<CMatch>  x;

    // x . addMatch ( "C++", "Pascal", CMatch ( 10, 3 ) )
    //         . addMatch ( "C++", "Java", CMatch ( 8, 1 ) )
    //         . addMatch ( "Pascal", "Basic", CMatch ( 40, 0 ) )
    //         . addMatch ( "Java", "PHP", CMatch ( 6, 2 ) )
    //         . addMatch ( "Java", "Pascal", CMatch ( 7, 3 ) )
    //         . addMatch ( "PHP", "Basic", CMatch ( 10, 0 ) );


    // assert ( ! x . isOrdered ( HigherScore ) );
    // try
    // {
    //     list<string> res = x . results ( HigherScore );
    //     assert ( "Exception missing!" == nullptr );
    // }
    // catch ( const logic_error & e )
    // {
    // }
    // catch ( ... )
    // {
    //     assert ( "Invalid exception thrown!" == nullptr );
    // }

    // x . addMatch ( "PHP", "Pascal", CMatch ( 3, 6 ) );

    // assert ( x . isOrdered ( HigherScore ) );
    // try
    // {
    //     list<string> res = x . results ( HigherScore );
    //     assert ( ( res == list<string>{ "C++", "Java", "Pascal", "PHP", "Basic" } ) );
    // }
    // catch ( ... )
    // {
    //     assert ( "Unexpected exception!" == nullptr );
    // }


    // assert ( ! x . isOrdered ( HigherScoreThreshold ( 3 ) ) );
    // try
    // {
    //     list<string> res = x . results ( HigherScoreThreshold ( 3 ) );
    //     assert ( "Exception missing!" == nullptr );
    // }
    // catch ( const logic_error & e )
    // {
    // }
    // catch ( ... )
    // {
    //     assert ( "Invalid exception thrown!" == nullptr );
    // }

    // assert ( x . isOrdered ( [] ( const CMatch & x )
    //                          {
    //                              return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A );
    //                          } ) );
    // try
    // {
    //     list<string> res = x . results ( [] ( const CMatch & x )
    //                                      {
    //                                          return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A );
    //                                      } );
    //     assert ( ( res == list<string>{ "Basic", "PHP", "Pascal", "Java", "C++" } ) );
    // }
    // catch ( ... )
    // {
    //     assert ( "Unexpected exception!" == nullptr );
    // }

    // CContest<bool>  y;

    // y . addMatch ( "Python", "PHP", true )
    //         . addMatch ( "PHP", "Perl", true )
    //         . addMatch ( "Perl", "Bash", true )
    //         . addMatch ( "Bash", "JavaScript", true )
    //         . addMatch ( "JavaScript", "VBScript", true );

    // assert ( y . isOrdered ( [] ( bool v )
    //                          {
    //                              return v ? 10 : - 10;
    //                          } ) );
    // try
    // {
    //     list<string> res = y . results ( [] ( bool v )
    //                                      {
    //                                          return v ? 10 : - 10;
    //                                      });
    //     assert ( ( res == list<string>{ "Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript" } ) );
    // }
    // catch ( ... )
    // {
    //     assert ( "Unexpected exception!" == nullptr );
    // }

    // y . addMatch ( "PHP", "JavaScript", false );
    // assert ( !y . isOrdered ( [] ( bool v )
    //                           {
    //                               return v ? 10 : - 10;
    //                           } ) );
    // try
    // {
    //     list<string> res = y . results ( [] ( bool v )
    //                                      {
    //                                          return v ? 10 : - 10;
    //                                      } );
    //     assert ( "Exception missing!" == nullptr );
    // }
    // catch ( const logic_error & e )
    // {
    // }
    // catch ( ... )
    // {
    //     assert ( "Invalid exception thrown!" == nullptr );
    // }

    // try
    // {
    //     y . addMatch ( "PHP", "JavaScript", false );
    //     assert ( "Exception missing!" == nullptr );
    // }
    // catch ( const logic_error & e )
    // {
    // }
    // catch ( ... )
    // {
    //     assert ( "Invalid exception thrown!" == nullptr );
    // }

    // try
    // {
    //     y . addMatch ( "JavaScript", "PHP", true );
    //     assert ( "Exception missing!" == nullptr );
    // }
    // catch ( const logic_error & e )
    // {
    // }
    // catch ( ... )
    // {
    //     assert ( "Invalid exception thrown!" == nullptr );
    // }
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
