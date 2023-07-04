#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>
using namespace std;

class CRect 
{
  public:
                             CRect                         ( double            x,
                                                             double            y,
                                                             double            w,
                                                             double            h )
      : m_X ( x ),
        m_Y ( y ),
        m_W ( w ),
        m_H ( h )
    {
    }
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CRect     & x )
    {
      return os << '(' << x . m_X << ',' << x . m_Y << ',' << x . m_W << ',' << x . m_H << ')';
    }
    double                   m_X;
    double                   m_Y;
    double                   m_W;
    double                   m_H;
};
#endif /* __PROGTEST__ */

enum class TypeOf { BOX, LABEL, WINDOW, INPUT, BUTTON};

class CBase {
public:
    int id() const {
        return m_id;
    }

    CRect pos() const {
        return m_Pos;
    }

    CRect relPos() const {
        return m_RelPos;
    }

    virtual ~CBase() = default;

public:
    int m_id;
    CRect m_Pos;
    CRect m_RelPos;
    TypeOf m_type;
    bool m_last = false;

    CBase(const int & id, const CRect & pos) : m_id(id), m_Pos(pos), m_RelPos(pos){}

    virtual unique_ptr<CBase> clone() const = 0;

    virtual void print(ostream & os, const int & indent) const = 0;

    friend ostream         & operator <<                   ( ostream         & os, const CBase     & x ){
        x.print(os, 0);
        return os;
    }
};

class CBaseName : public CBase {
public:
    string name() const {
        return m_Name;
    }

protected:
    string m_Name;

    CBaseName(const int& id, const CRect& pos, const string& name)
        : CBase(id, pos), m_Name(name) {}


    virtual void print(ostream & os, const int & indent) const override = 0;
};

class CWindow: public CBaseName
{
  public:
CWindow ( int id,const string    & title,const CRect     & absPos
                                                             );
CWindow(const CWindow& x);
    CWindow& add(const CBase & x);
    // search
    CBase* search(const int & x) const;
    // setPosition
    CWindow& setPosition(const CRect & absPos);

    CWindow & operator=(const CWindow & x){
        if(this == &x) return *this;
        

        CWindow cloned(x);
        m_Name = x.name();
        m_id = x.id();
        m_Pos = x.pos();
        m_RelPos = x.m_RelPos;
        std::swap(m_data, cloned.m_data);
        return *this;
    }

    void print(ostream & os, const int & indent) const override{
        if(m_data[m_data.size()-1]->m_type == TypeOf::BOX){
            m_data[m_data.size()-1]->m_last = true;
        }
        if(!indent) os << "[" << id() << "]" << " Window" << " \"" << name() << "\" " << pos() << endl;
        else os << "+- [" << id() << "]" << " Window" << " \"" << name() << "\" " << pos() << endl;
        for(const auto & object : m_data){
            object->print(os, indent+1);
        }
        if(m_data[m_data.size()-1]->m_type == TypeOf::BOX){
            m_data[m_data.size()-1]->m_last = false;
        }
    }

    unique_ptr<CBase> clone() const override{
        unique_ptr<CWindow> tmp =  make_unique<CWindow>(*this);
        tmp->m_type = TypeOf::WINDOW;
        return tmp;
    }

    vector<unique_ptr<CBase>> m_data;
};

CWindow::CWindow( int id,const string & title, const CRect & absPos) : CBaseName(id, absPos, title){}

CWindow::CWindow(const CWindow& x) : CBaseName(x.id(), x.pos(), x.name()){
    for(const auto & object : x.m_data){
        add(*object);
    }
}


CWindow& CWindow::add(const CBase & x){
    unique_ptr<CBase> cloned= x.clone();
    cloned->m_RelPos.m_H = cloned->m_Pos.m_H * m_Pos.m_H ;
    cloned->m_RelPos.m_W = cloned->m_Pos.m_W * m_Pos.m_W ;
    cloned->m_RelPos.m_X = cloned->m_Pos.m_X * m_Pos.m_W + m_Pos.m_X ;
    cloned->m_RelPos.m_Y = cloned->m_Pos.m_Y * m_Pos.m_H + m_Pos.m_Y;
    m_data.emplace_back(move(cloned));
    return *this;
}

CBase* CWindow::search(const int & x) const{
    for(size_t i =0 ; i < m_data.size(); i++){
        if(x == m_data[i]->id()){
            return (m_data.begin()+i)->get();
        }
    }
    return nullptr;
}

CWindow& CWindow::setPosition(const CRect & absPos){
    m_Pos = absPos;
    for(auto & object : m_data){
        object->m_RelPos.m_H = object->m_Pos.m_H * m_Pos.m_H ;
        object->m_RelPos.m_W = object->m_Pos.m_W * m_Pos.m_W ;
        object->m_RelPos.m_X = object->m_Pos.m_X * m_Pos.m_W + m_Pos.m_X ;
        object->m_RelPos.m_Y = object->m_Pos.m_Y * m_Pos.m_H + m_Pos.m_Y;
    }
    return *this;
}

class CButton: public CBaseName
{
  public:
                             CButton                       ( int               id,
                                                             const CRect     & relPos,
                                                             const string    & name );

    void print(ostream & os, const int & indent) const override{
       if(!indent) os << "[" << id() << "]" << " Button" << " \"" << name() << "\" " << relPos() << endl;
       else os << "+- [" << id() << "]" << " Button" << " \"" << name() << "\" " << relPos() << endl;
    }

    unique_ptr<CBase> clone() const override{
        unique_ptr<CButton> tmp =  make_unique<CButton>(*this);
        tmp->m_type = TypeOf::BUTTON;
        return tmp;
    }
};

CButton::CButton(int id, const CRect     & relPos, const string    & name ) : CBaseName(id, relPos, name) {}

class CInput: public CBaseName
{
  public:
                             CInput                        ( int               id,
                                                             const CRect     & relPos,
                                                             const string    & value );
    // setValue
    CInput & setValue( const string & x);
    // getValue 
    string getValue() const;

    void print(ostream & os, const int & indent) const override{
        if(!indent) os << "[" << id() << "]" << " Input" << " \"" << name() << "\" " << relPos() << endl;
        else os << "+- [" << id() << "]" << " Input" << " \"" << name() << "\" " << relPos() << endl;
    }

    unique_ptr<CBase> clone() const override{
        unique_ptr<CInput> tmp =  make_unique<CInput>(*this);
        tmp->m_type = TypeOf::INPUT;
        return tmp;
    }

};

CInput::CInput(int id, const CRect & relPos, const string & value) : CBaseName(id, relPos, value) {}

CInput & CInput::setValue(const string & x){
   m_Name = x;
   return *this;
}

string CInput::getValue() const{
    return m_Name;
}

class CLabel : public CBaseName
{
  public:
                             CLabel                        ( int               id,
                                                             const CRect     & relPos,
                                                             const string    & label );

    void print(ostream & os, const int & indent) const override{
        if(!indent)os << "[" << id() << "]" << " Label" << " \"" << name() << "\" " << relPos() << endl;
        else os << "+- [" << id() << "]" << " Label" << " \"" << name() << "\" " << relPos() << endl;
    }

    unique_ptr<CBase> clone() const override{
        unique_ptr<CLabel> tmp =  make_unique<CLabel>(*this);
        tmp->m_type = TypeOf::LABEL;
        return tmp;
    }
};

CLabel::CLabel(int id, const CRect & relPos, const string & label) : CBaseName(id, relPos, label) {}

class CComboBox: public CBase
{
  public:
                             CComboBox                     ( int               id,
                                                             const CRect     & relPos );
    // add                
    CComboBox& add (const string & x);                                                    
    // setSelected
    bool setSelected(const size_t & x);
    // getSelected
    int getSelected() const;

    CComboBox & operator=(const CComboBox & x){
        CBase::operator=(x);
        m_offers = x.m_offers;
        pointer = x.pointer;
        return *this;
    }

    void print(ostream & os, const int & indent) const override{
        if(!indent)os << "[" << id() << "]" << " ComboBox " << relPos() << endl;
        else os << "+- [" << id() << "]" << " ComboBox " << relPos() << endl;
        if(m_last || !indent){
            for(size_t i =0 ; i < m_offers.size(); i++){
                if(indent) os << "   ";
                if(i == pointer) os << "+->" << m_offers[i] << "<"<< endl;
                else os << "+- " << m_offers[i] << endl;
            }
        }
        else{
            for(size_t i =0 ; i < m_offers.size(); i++){
                if(indent) os << "|  ";
                if(i == pointer) os << "+->" << m_offers[i] << "<"<< endl;
                else os << "+- " << m_offers[i] << endl;
            }
        }
    }

    unique_ptr<CBase> clone() const override{
        unique_ptr<CComboBox> tmp =  make_unique<CComboBox>(*this);
        tmp->m_type = TypeOf::BOX;
        return tmp;
    }

    vector<string> m_offers;
    size_t pointer = 0;
};

CComboBox::CComboBox(int id, const CRect & relPos) : CBase(id, relPos) {}

CComboBox& CComboBox::add (const string & x){
    if(x.empty()) return *this;
    m_offers.emplace_back(x);
    return *this;
}

bool CComboBox::setSelected(const size_t & x){
    if(x >= m_offers.size()) return false;
    pointer = x;
    return true;
}

int CComboBox::getSelected() const{
    return pointer;
}

// output operators

#ifndef __PROGTEST__
template <typename _T>
string toString ( const _T & x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int main ( void )
{
//   assert ( sizeof ( CButton ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
//   assert ( sizeof ( CInput ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
//   assert ( sizeof ( CLabel ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
//   CWindow a ( 0, "Sample window", CRect ( 10, 10, 600, 480 ) );
//   a . add ( CButton ( 1, CRect ( 0.1, 0.8, 0.3, 0.1 ), "Ok" ) ) . add ( CButton ( 2, CRect ( 0.6, 0.8, 0.3, 0.1 ), "Cancel" ) );
//   a . add ( CLabel ( 10, CRect ( 0.1, 0.1, 0.2, 0.1 ), "Username:" ) );
//   a . add ( CInput ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ) );
//   a . add ( CComboBox ( 20, CRect ( 0.1, 0.3, 0.8, 0.1 ) ) . add ( "Karate" ) . add ( "Judo" ) . add ( "Box" ) . add ( "Progtest" ) );
//   assert ( toString ( a ) ==
//     "[0] Window \"Sample window\" (10,10,600,480)\n"
//     "+- [1] Button \"Ok\" (70,394,180,48)\n"
//     "+- [2] Button \"Cancel\" (370,394,180,48)\n"
//     "+- [10] Label \"Username:\" (70,58,120,48)\n"
//     "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
//     "+- [20] ComboBox (70,154,480,48)\n"
//     "   +->Karate<\n"
//     "   +- Judo\n"
//     "   +- Box\n"
//     "   +- Progtest\n" );
//   CWindow b = a;
//   assert ( toString ( *b . search ( 20 ) ) ==
//     "[20] ComboBox (70,154,480,48)\n"
//     "+->Karate<\n"
//     "+- Judo\n"
//     "+- Box\n"
//     "+- Progtest\n" );
//   assert ( dynamic_cast<CComboBox &> ( *b . search ( 20 ) ) . getSelected () == 0 );
//   dynamic_cast<CComboBox &> ( *b . search ( 20 ) ) . setSelected ( 3 );
//   assert ( dynamic_cast<CInput &> ( *b . search ( 11 ) ) . getValue () == "chucknorris" );
//   dynamic_cast<CInput &> ( *b . search ( 11 ) ) . setValue ( "chucknorris@fit.cvut.cz" );
//   b . add ( CComboBox ( 21, CRect ( 0.1, 0.5, 0.8, 0.1 ) ) . add ( "PA2" ) . add ( "OSY" ) . add ( "Both" ) );
//   assert ( toString ( b ) ==
//     "[0] Window \"Sample window\" (10,10,600,480)\n"
//     "+- [1] Button \"Ok\" (70,394,180,48)\n"
//     "+- [2] Button \"Cancel\" (370,394,180,48)\n"
//     "+- [10] Label \"Username:\" (70,58,120,48)\n"
//     "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
//     "+- [20] ComboBox (70,154,480,48)\n"
//     "|  +- Karate\n"
//     "|  +- Judo\n"
//     "|  +- Box\n"
//     "|  +->Progtest<\n"
//     "+- [21] ComboBox (70,250,480,48)\n"
//     "   +->PA2<\n"
//     "   +- OSY\n"
//     "   +- Both\n" );
//   assert ( toString ( a ) ==
//     "[0] Window \"Sample window\" (10,10,600,480)\n"
//     "+- [1] Button \"Ok\" (70,394,180,48)\n"
//     "+- [2] Button \"Cancel\" (370,394,180,48)\n"
//     "+- [10] Label \"Username:\" (70,58,120,48)\n"
//     "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
//     "+- [20] ComboBox (70,154,480,48)\n"
//     "   +->Karate<\n"
//     "   +- Judo\n"
//     "   +- Box\n"
//     "   +- Progtest\n" );
//   b . setPosition ( CRect ( 20, 30, 640, 520 ) );
//   assert ( toString ( b ) ==
//     "[0] Window \"Sample window\" (20,30,640,520)\n"
//     "+- [1] Button \"Ok\" (84,446,192,52)\n"
//     "+- [2] Button \"Cancel\" (404,446,192,52)\n"
//     "+- [10] Label \"Username:\" (84,82,128,52)\n"
//     "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
//     "+- [20] ComboBox (84,186,512,52)\n"
//     "|  +- Karate\n"
//     "|  +- Judo\n"
//     "|  +- Box\n"
//     "|  +->Progtest<\n"
//     "+- [21] ComboBox (84,290,512,52)\n"
//     "   +->PA2<\n"
//     "   +- OSY\n"
//     "   +- Both\n" );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
