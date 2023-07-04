#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>
using namespace std;

class CDate
{
  public:
    //---------------------------------------------------------------------------------------------
                             CDate                         ( int               y,
                                                             int               m,
                                                             int               d )
      : m_Year ( y ),
        m_Month ( m ),
        m_Day ( d )
    {
    }
    //---------------------------------------------------------------------------------------------
    int                      compare                       ( const CDate     & x ) const
    {
      if ( m_Year != x . m_Year )
        return m_Year - x . m_Year;
      if ( m_Month != x . m_Month )
        return m_Month - x . m_Month;
      return m_Day - x . m_Day;
    }
    //---------------------------------------------------------------------------------------------
    int                      year                          ( void ) const 
    {
      return m_Year;
    }
    //---------------------------------------------------------------------------------------------
    int                      month                         ( void ) const 
    {
      return m_Month;
    }
    //---------------------------------------------------------------------------------------------
    int                      day                           ( void ) const 
    {
      return m_Day;
    }
    //---------------------------------------------------------------------------------------------
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CDate     & x )
    {
      char oldFill = os . fill ();
      return os << setfill ( '0' ) << setw ( 4 ) << x . m_Year << "-" 
                                   << setw ( 2 ) << static_cast<int> ( x . m_Month ) << "-" 
                                   << setw ( 2 ) << static_cast<int> ( x . m_Day ) 
                << setfill ( oldFill );
    }
    //---------------------------------------------------------------------------------------------
  private:
    int16_t                  m_Year;
    int8_t                   m_Month;
    int8_t                   m_Day;
};
#endif /* __PROGTEST__ */


string toLower(const string & str){
    string result;
    for(size_t i = 0; i < str.size(); i++){
        result.push_back(tolower(str[i]));
    }
    return result;
}

string removeExtraSpaces(const string& s) {
    string result;
    size_t i = 0;
    for(i = 0; i < s.size(); i++){
        if(!isspace(s[i])){
            break;
        }
    }
    size_t x = s.size() -1;
    for(x = s.size()- 1; x != i; x--){
        if(!isspace(s[x])){
            break;
        }
    }
    bool flag = true;
    for(; i <= x; i++){
        if(flag && isspace(s[i])){
            result += s[i];
            flag = false;
        }
        else if(!isspace(s[i])){
            result += s[i];
            flag = true;
        } 
    }

    return result;
}

int global = 0;

class CInvoice
{
  public:
    CDate                    date                          ( void ) const;
    string                   buyer                         ( void ) const;
    string                   seller                        ( void ) const;
    unsigned int             amount                        ( void ) const;
    double                   vat                           ( void ) const;
    bool operator !=(const CInvoice & x) const;
    bool operator ==(const CInvoice & x) const;
    CInvoice & operator =(const CInvoice & x);
    bool check() const;
    size_t valueOf() const;
    CInvoice( const CDate & date, const string & seller, const string & buyer, unsigned int amount, double vat )
    : m_Date(date), m_Seller(removeExtraSpaces(toLower(seller))), m_Buyer(removeExtraSpaces(toLower(buyer))), m_Amount(amount), m_Vat(vat), idx(global++), m_accepted(false), m_issued(false)
{
}
  public:
    CDate m_Date;
    string m_Seller;
    string m_Buyer;
    unsigned int m_Amount;
    double m_Vat;
    int idx;
    bool m_accepted;
    bool m_issued;
};


CDate                CInvoice::date                          ( void ) const{
    return m_Date;
}

string                   CInvoice::buyer                         ( void ) const{
    return m_Buyer;
}
string                   CInvoice::seller                        ( void ) const{
    return m_Seller;
}
unsigned int             CInvoice::amount                        ( void ) const{
    return m_Amount;
}
double                   CInvoice::vat( void ) const{
    return m_Vat;
}

size_t CInvoice::valueOf() const{
    size_t res = 0;
    res+=(amount() + 90) * 30 + 5;
    res+=m_Date.day() * 23 + m_Date.month() * 22 + 6 + m_Date.year() * 11;
    string seller_x = removeExtraSpaces(toLower(seller()));
    string buyer_x = removeExtraSpaces(toLower(buyer()));
    for(size_t i = 0; i < buyer_x.size(); i++){
        res += (buyer_x[i] + 1131) * 24;
    }
    for(size_t i = 0; i < seller_x.size(); i++){
        res += (seller_x[i]+19931) * 17;
    }
    res += (((int)vat()) + 1000) * 1113;
    return res;
}

bool CInvoice::operator !=(const CInvoice & x) const{
    if(amount() == x.amount() && (buyer() == x.buyer()) && m_Date.compare(x.date()) == 0 && (seller() == x.seller()) && vat() == x.vat()) return false;
    return true;
}

bool CInvoice::operator ==(const CInvoice & x) const{
    if(amount() == x.amount() && (buyer() == x.buyer()) && m_Date.compare(x.date()) == 0 && (seller() == x.seller()) && vat() == x.vat()) return true;
    return false;
}

bool CInvoice::check() const{
    if(m_Buyer.empty() || m_Seller.empty()) return false;
    return true;
}

CInvoice & CInvoice::operator =(const CInvoice & x){
    m_Date = x.date();
    m_Seller = x.seller();
    m_Buyer = x.buyer();
    m_Vat = x.vat();
    m_Amount = x.amount();
    idx = x.idx;
    m_accepted = x.m_accepted;
    m_issued = x.m_issued;
    return *this;
}

struct Invoicehash {
    size_t operator()(const CInvoice& invoice) const {
        return invoice.valueOf();
    }
};

struct StringHash {
    size_t operator()(const std::string& str) const {
        string normal_str = toLower(removeExtraSpaces(str));
        return std::hash<std::string>()(normal_str);
    }
};


int cmpSeller(const CInvoice & x, const CInvoice & y){
    return strcasecmp(x.seller().c_str(), (y.seller().c_str()));
}

int cmpBuyer(const CInvoice & x, const CInvoice & y){
    return strcasecmp((x.buyer().c_str()), (y.buyer().c_str()));
}


int cmpAmount(const CInvoice & x, const CInvoice & y){
    if(x.amount() == y.amount()) return 0;
    else if(x.amount() < y.amount()) return -1;
    else return 1;
}

int cmpVat(const CInvoice & x, const CInvoice & y){
    if(x.vat() == y.vat()) return 0;
    else if(x.vat() < y.vat()) return -1;
    else return 1;
}

int decoding(int key, bool ascending, const CInvoice & x, const CInvoice & y){
    if(key == 0) {
        if(ascending) return x.date().compare(y.date());
        else return (-1)*x.date().compare(y.date());
    }
    else if(key == 2) {
        if(ascending) return cmpSeller(x,y);
        else return (-1)*cmpSeller(x,y);
    }
    else if(key == 3) {
        if(ascending) return cmpAmount(x, y);
        else return (-1)*cmpAmount(x, y);
    } 
    else if(key == 1){
        if(ascending) return cmpBuyer(x, y);
        else return (-1)*cmpBuyer(x, y);
    }
    else{
        if(ascending) return cmpVat(x, y);
        else return (-1)*cmpVat(x, y);
    }
}

class CSortOpt
{
  public:
    static const int         BY_DATE                       = 0;
    static const int         BY_BUYER                      = 1;
    static const int         BY_SELLER                     = 2;
    static const int         BY_AMOUNT                     = 3;
    static const int         BY_VAT                        = 4;
                             CSortOpt                      ( void );
    CSortOpt & addKey ( int key, bool ascending ){
        for(size_t i = 0; i < m_sort.size(); i++){
            if(m_sort[i].first == key) return *this;
        }
        if(key == 0) m_sort.push_back(make_pair(0, ascending));
        else if(key == 2) m_sort.push_back(make_pair(2, ascending));
        else if(key == 3) m_sort.push_back(make_pair(3, ascending)); 
        else if(key == 1) m_sort.push_back(make_pair(1, ascending));
        else if(key == 4) m_sort.push_back(make_pair(4, ascending));
        else return *this;
        return *this;
    }
    static bool cmpALL(const CInvoice& a, const CInvoice& b) ;
  public:
    vector<pair<int, bool>> m_sort;
};

CSortOpt::CSortOpt ( void ){}

bool cmpALL(const CSortOpt & sortby,const CInvoice& a , const CInvoice& b){
    int decode = 0;
    for(auto key : sortby.m_sort){
        decode = decoding(key.first,key.second, a,b);
        if(decode <= -1) return 1;
        else if(decode == 0) continue;
        else return 0;
    }
    if(decode == 0){
        return a.idx < b.idx;
    }
    return 0;
}

class CVATRegister
{
  public:
                            CVATRegister                  ( void );
                            ~CVATRegister                  ( void );
    bool                     registerCompany               ( const string    & name );
    bool                     addIssued                     ( const CInvoice  & x );
    bool addIss(unordered_map<string, unordered_set<CInvoice, Invoicehash>, StringHash>::iterator it, const CInvoice & x);
    bool                     addAccepted                   ( const CInvoice  & x );
    bool addAcc(unordered_map<string, unordered_set<CInvoice, Invoicehash>, StringHash>::iterator it, const CInvoice & x);
    bool delIss(unordered_map<string, unordered_set<CInvoice, Invoicehash>, StringHash>::iterator it, const CInvoice & x);
    bool delAcc(unordered_map<string, unordered_set<CInvoice, Invoicehash>, StringHash>::iterator it, const CInvoice & x);
    bool                     delIssued                     ( const CInvoice  & x );
    bool                     delAccepted                   ( const CInvoice  & x );
    list<CInvoice>           unmatched                     ( const string    & company,
                                                             const CSortOpt  & sortBy ) const;
  public:
    unordered_map<string, string> orig_name;
    unordered_map<string, unordered_set<CInvoice, Invoicehash>> m_Invoices;
};

CVATRegister::CVATRegister ( void ){}

CVATRegister::~CVATRegister                  ( void ){}

bool CVATRegister::registerCompany ( const string    & name ){
    if(name.empty()) return false;
    string str = toLower(removeExtraSpaces(name));
    if(m_Invoices.find(str) != m_Invoices.end()) return false;
    orig_name.insert({str, name});
    unordered_set<CInvoice, Invoicehash> tmp;
    m_Invoices.insert({str, tmp});
    return true;
}

bool CVATRegister::addIss(unordered_map<string, unordered_set<CInvoice, Invoicehash>, StringHash>::iterator it, const CInvoice & x){
    auto it_inv = it->second.find(x);
    if(it_inv != it->second.end()){
        if( it_inv->m_issued == true) return false;
        else {
            CInvoice a = *it_inv;
            a.m_issued = true;
            it->second.erase(it_inv);
            it->second.insert(a);
            return true;
        }
    }
    CInvoice a = x;
    a.m_issued = true;
    it->second.insert(a);
    return true;
}


bool CVATRegister::addIssued ( const CInvoice  & x ){
    if(!x.check()) return false;
    auto it_seller = m_Invoices.find(x.seller());
    auto it_buyer = m_Invoices.find(x.buyer());
    if(it_seller == m_Invoices.end() || it_buyer == m_Invoices.end() || (x.seller() == x.buyer())) return false;
    if(!addIss(it_seller, x)) return false;;
    return addIss(it_buyer, x);
}

bool CVATRegister::addAcc(unordered_map<string, unordered_set<CInvoice, Invoicehash>, StringHash>::iterator it, const CInvoice & x){
    auto it_inv = it->second.find(x);
    if(it_inv != it->second.end()){
        if( it_inv->m_accepted == true) return false;
        else {
            CInvoice a = *it_inv;
            a.m_accepted = true;
            it->second.erase(it_inv);
            it->second.insert(a);
            return true;
        }
    }
    CInvoice a = x;
    a.m_accepted = true;
    it->second.insert(a);
    return true;
}

bool CVATRegister::addAccepted  ( const CInvoice  & x ){
    if(!x.check()) return false;
    auto it_seller = m_Invoices.find(x.seller());
    auto it_buyer = m_Invoices.find(x.buyer());
    if(it_seller == m_Invoices.end() || it_buyer == m_Invoices.end() || (x.seller() == x.buyer())) return false;
    if(!addAcc(it_seller, x)) return false;;
    return addAcc(it_buyer, x);
}

bool CVATRegister::delIss(unordered_map<string, unordered_set<CInvoice, Invoicehash>, StringHash>::iterator it, const CInvoice & x){
    auto it_vec = it->second.find(x);
    if(it_vec != it->second.end()){
        if(it_vec->m_issued == false) return false;
        else {
            CInvoice a = *it_vec;
            it->second.erase(it_vec);
            a.m_issued = false;
            if(!a.m_accepted && !a.m_issued) {
                return true;
            }
            it->second.insert(a);
            return true;
        }
    }
    return false;
}

bool CVATRegister::delIssued ( const CInvoice  & x ){
    if(!x.check()) return false;
    auto it_seller = m_Invoices.find(x.seller());
    auto it_buyer = m_Invoices.find(x.buyer());
    if(it_seller == m_Invoices.end() || it_buyer == m_Invoices.end() || (x.seller() == x.buyer())) return false;
    if(!delIss(it_seller, x)) return false;
    return delIss(it_buyer, x);
}

bool CVATRegister::delAcc(unordered_map<string, unordered_set<CInvoice, Invoicehash>, StringHash>::iterator it, const CInvoice & x){
    auto it_vec = it->second.find(x);
    if(it_vec != it->second.end()){
        if(it_vec->m_accepted == false) return false;
        else {
            CInvoice a = *it_vec;
            it->second.erase(it_vec);
            a.m_accepted = false;
            if(!a.m_accepted && !a.m_issued) {
                return true;
            }
            it->second.insert(a);
            return true;
        }
    }
    return false;
}

bool CVATRegister::delAccepted ( const CInvoice  & x ){
    if(!x.check()) return false;
    auto it_seller = m_Invoices.find(x.seller());
    auto it_buyer = m_Invoices.find(x.buyer());
    if(it_seller == m_Invoices.end() || it_buyer == m_Invoices.end() || (x.seller() == x.buyer())) return false;
    if(!delAcc(it_seller, x)) return false;
    return delAcc(it_buyer, x);
}

list<CInvoice> CVATRegister::unmatched ( const string    & company, const CSortOpt  & sortBy ) const{
    list<CInvoice> res;
    if(company.empty()){
        return res;
    } 
    string normal_company = toLower(removeExtraSpaces(company));
    auto it = m_Invoices.find(normal_company);
    if(it == m_Invoices.end()) {
        return res;
    }
    for(const auto & a : it->second){
        if(!(a.m_accepted && a.m_issued)){
            CInvoice x = a;
            x.m_Seller = orig_name.find(x.seller())->second;
            x.m_Buyer = orig_name.find(x.buyer())->second;
            res.push_back(x);
        }
    }
    // for(const auto & c : res) cout << "Seller: " << c.seller() << "  Buyer: "  << c.buyer() << "  Date: "  << c.date()<< "  Vat: "  << c.vat() << "  Amount: "  <<  c.amount() << "  Idx: " << c.idx << " " << c.m_issued << " "  << c.m_accepted<< endl;
    res.sort([&](const CInvoice& a, const CInvoice& b) {
        return cmpALL(sortBy, a ,b);
    });
    // cout << endl;
    // for(const auto & c : res) cout << "Seller: " << c.seller() << "  Buyer: "  << c.buyer() << "  Date: "  << c.date()<< "  Vat: "  << c.vat() << "  Amount: "  <<  c.amount() << "  Idx: " << c.idx << " " << c.m_issued << " "  << c.m_accepted<< endl;
    // cout << endl;
    return res;
}

#ifndef __PROGTEST__

bool equalLists ( const list<CInvoice> & a, const list<CInvoice> & b )
{
  if(a.size() != b.size()) return false;
  auto ita = a.begin();
  auto itb = b.begin();
  while (ita != a.end())
  {
    if(ita->amount() != itb->amount() || (removeExtraSpaces(toLower(ita->buyer())) != removeExtraSpaces(toLower(itb->buyer()))) || ((ita->m_Date).compare(itb->date()) != 0) || removeExtraSpaces((toLower(ita->seller()))) != removeExtraSpaces(toLower(itb->seller())) || ita->vat() != itb->vat()){
        // cout << (*ita).asmount() << " " << (*ita).buyer() << " " << (*ita).date() << " " << (*ita).seller() << " " << (*ita).vat() << endl;
        // cout << (*itb).amount() << " " << (*itb).buyer() << " " << (*itb).date() << " " << (*itb).seller() << " " << (*itb).vat() << endl;
        return false;
    } 
    ita++;
    itb++;
  }
  return true;
}

int main ( void )
{
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
