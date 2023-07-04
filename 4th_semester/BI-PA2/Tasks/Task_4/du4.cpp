#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

class MyString{
	public:
    /**
     default constructor for a string
    */
		MyString();

    /**
     destructor to clean memory
    */
		~MyString();

    /**
     * operator ==(x).
     * @param[in] x other string.
     * @returns true if text of the string is equal to string of the object that called operator, false otherwise
    */
		bool operator ==  ( const char * x ) const;

    /**
     * operator ==(x).
     * @param[in] x other array of chars.
     * @returns true if text of the string is equal to string of the object that called operator, false otherwise
    */
		bool operator ==  ( const MyString & x ) const;

    /**
     * operator =(x).
     * @param[in] src other string.
     * @returns an object that called operator, but with the content of x
    */
		MyString & operator = ( const char * src );

    /**
     * operator =(x).
     * @param[in] src other array of chars.
     * @returns string that called operator, but with the content of x
    */
		MyString & operator = ( const MyString & src );
	public:

  /** @var word that contains my string */
		char * m_word;

  /** @var the size of the word */
		size_t m_size;
};

MyString::MyString(){
	m_word = nullptr;
	m_size = 0;
}

MyString::~MyString(){
	if(m_word && m_size){
		delete[] m_word;
		m_word = nullptr;
	}
	m_size = 0;
}

MyString & MyString::operator = ( const char * src ){
  	if(!src) return *this;
	if(m_word)delete[] m_word;
	m_size = strlen(src);
	m_word = new char[m_size+1];
	strncpy(m_word, src, m_size);
	m_word[m_size] = '\0';
	return *this;
}

MyString & MyString::operator=(const MyString & src) {
  if (this == &src) { 
    return *this;
  }
  if (!src.m_word) {
    delete[] m_word;
    m_word = nullptr;
    m_size = 0;
    return *this;
  }
  if (m_word) {
    delete[] m_word;
  }
  m_size = src.m_size;
  m_word = new char[m_size + 1];
  strncpy(m_word, src.m_word, m_size);
  m_word[m_size] = '\0';
  return *this;
}

bool MyString::operator ==  ( const char * x ) const{
	if(!x) return false;
	if(m_size != strlen(x)) return false;
	for(size_t i = 0; i < m_size; i++){
		if(m_word[i] != x[i]) return false;
	}
	return true;
}

bool MyString::operator ==  ( const MyString & x ) const{
	if(m_size != x.m_size) return false;
	for(size_t i = 0; i < m_size; i++){
		if(m_word[i] != x.m_word[i]) return false;
	}
	return true;
}

class CMail
{
  public:
  /**
   default constructor for a mail
  */
  CMail();

  /**
   constructor for an object
   * @param[in] from the addres of a sender.
   * @param[in] to the addres of a reciever.
   * @param[in] body the text of a message.
  */
                             CMail                         ( const char      * from,
                                                             const char      * to,
                                                             const char      * body );

    /**
     * operator ==(x).
     * @param[in] x other mail.
     * @returns true if text of the string is equal to string of the object that called operator, false otherwise
    */
    bool                     operator ==                   ( const CMail     & x ) const;

    /**
     * operator <<(os, m).
     * @param[in] os output ostream.
     * @param[in] m mail to print.
     * @returns output ostream with added information of a mail
    */
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CMail     & m );

    /**
     * operator =(x).
     * @param[in] src other mail.
     * @returns mail that called operator, but with the content of x
    */
    CMail & operator = ( const CMail & src );
  public:

  /** @var the addres of a sender */
    MyString m_sender;

  /** @var the addres of a reciver */
    MyString m_reciever;

  /** @var the text of a message */
    MyString m_body;
};


CMail::CMail(){}

CMail::CMail(const char      * from, const char      * to, const char      * body){
	m_sender = from;
	m_reciever = to;
	m_body = body;
}

bool CMail::operator == (const CMail & x) const{
    if(m_sender == x.m_sender && m_reciever == x.m_reciever && m_body == x.m_body) return true;
    return false;
}

CMail & CMail::operator = ( const CMail & src ){
    m_sender = src.m_sender;
    m_reciever = src.m_reciever;
    m_body = src.m_body;
    return *this;
}

ostream & operator <<( ostream         & os, const CMail     & m ){
    os << "From: " << m.m_sender.m_word << ", To: " << m.m_reciever.m_word << ", Body: " << m.m_body.m_word;
    return os;
}


class CMailIterator 
{
  public:
  /**
   default constructor for a iterator
  */
  CMailIterator();

  /**
   * method operator bool().
   * @return true if iterator is pointed to a mail, false otherwise
  */
    explicit operator bool  ( void ) const{
		return this->i != -1;
	}

  /**
   * method operator !().
   * @return true if iterator is not pointed to a mail, false otherwise
  */
    bool                     operator !                    ( void ) const;

  /**
   * method operator *().
   * @return the mail
  */
    const CMail            & operator *                    ( void ) const;
  /**
   * method operator ++().
   * @return the addres of the next mail with definite name of sender/reciever, if it doesn't exist returns "empty" iterator
  */
    CMailIterator          & operator ++                   ( void );
  public:

  /** @var location in database */
    int i;

  /** @var the size of a database */
    int size;
  
  /** @var defines what mode of iterator is(n - undefined, o - reciver, i - sender ) */
    char mode;

  /** @var the mail */
    CMail * element;
};

bool CMailIterator::operator ! ( void ) const{
	return this->i == -1;
}

const CMail & CMailIterator::operator * ( void ) const{
	return *(this->element);
}

CMailIterator & CMailIterator::operator ++ ( void ){
    if (mode == 'n' || i == -1) return *this;

    char * find;
    if(mode == 'i') find = element->m_reciever.m_word;
    else if(mode == 'o') find = element->m_sender.m_word;
    for(int k = 1 ; k < (size - i); k++ ){
        if(mode == 'i' && (element+k)->m_reciever == find){
            element = element+k;
            i+=k;
            return *this;
        }
        else if(mode == 'o' && (element+k)->m_sender == find){
            element = element+k;
            i+=k;
            return *this;
        }
    }
    i = -1;
    element = NULL;
    return *this;
}

CMailIterator::CMailIterator(){
  i = -1;
  element = NULL;
  mode = 'n';
}

class CMailServer 
{
  public:
  /**
   default constructor for an database of mails
  */
                             CMailServer                   ( void );

    /**
     constructor for an object
    * @param[in] src the database of mails.
    */
                             CMailServer                   ( const CMailServer & src );

    /**
     * operator =(src).
     * @param[in] src other tha database of mails.
     * @returns an object that called operator, but with the content of src
    */
    CMailServer            & operator =                    ( const CMailServer & src );

    /**
     destructor to clean memory of database
    */
                             ~CMailServer                  ( void );

    /**
     * method sendMail(m).
     * @param[in] m other mail.
     * adds mail to database
    */
    void                     sendMail                      ( const CMail     & m );

    /**
     * method outbox(email).
     * @param[in] email the addres of sender.
     * @returns an iterator to first mail of this sender in database
    */
    CMailIterator            outbox                        ( const char      * email ) const;

    /**
     * method inbox(email).
     * @param[in] email the addres of reciever.
     * @returns an iterator to first mail of this reciever in database
    */
    CMailIterator            inbox                         ( const char      * email ) const;
  
  public:

  /** @var array of mails */
    CMail * m_Data;
  
  /** @var the size of database */
    int m_Size;

  /** @var the number of entries in database */
    int m_Capacity;
};

CMailServer:: CMailServer(){
    m_Data = nullptr;
    m_Size = 0;
    m_Capacity = 0;
}

CMailServer::CMailServer ( const CMailServer & src ){
	m_Size = src.m_Size;
	m_Capacity = src.m_Capacity;
	if(m_Capacity>0 && m_Size > 0){
		m_Data = new CMail[m_Capacity];
		for(int i = 0; i < m_Size; i++) m_Data[i] = src.m_Data[i];
	}
	else m_Data = nullptr;
}

CMailServer::~CMailServer (){
  if(m_Data && m_Size > 0){
		  delete [] m_Data;
   		m_Data = nullptr;
	}
	m_Size = 0;
	m_Capacity = 0;
}

void CMailServer::sendMail(const CMail & m){
    if(m_Size == m_Capacity){
        m_Capacity = m_Capacity * 10 + 2;
        CMail* tmp = new CMail[m_Capacity];
        for(int i = 0; i < m_Size; i++) tmp[i] = m_Data[i];
        if(m_Data && m_Size)delete [] m_Data;
        m_Data = tmp;
    }
    m_Data[m_Size++] = m;
}

CMailServer & CMailServer::operator = ( const CMailServer & src ){
    if(m_Data && m_Size)delete [] m_Data;
    m_Size = src.m_Size;
    m_Capacity = src.m_Capacity;
    if(m_Capacity>0 && m_Size > 0)m_Data = new CMail[m_Capacity];
    for(int i = 0; i < m_Size; i++) m_Data[i] = src.m_Data[i];
    return *this;
}

CMailIterator CMailServer::inbox ( const char      * email ) const{
  CMailIterator it;
  for(int i = 0; i < m_Size; i++){
    if(m_Data[i].m_reciever == email) {
		it.i = i;
		it.element = m_Data + i;
		it.mode = 'i';
		it.size = m_Size;
		break;
    }
  }
  return it;
}

CMailIterator CMailServer::outbox ( const char      * email ) const{
  CMailIterator it;
  for(int i = 0; i < m_Size; i++){
    if(m_Data[i].m_sender == email) {
		it.i = i;
		it.element = m_Data + i;
		it.mode = 'o';
		it.size = m_Size;
		break;
    }
  }
  return it;
}


#ifndef __PROGTEST__
bool                         matchOutput                   ( const CMail     & m,
                                                             const char      * str )
{
  ostringstream oss;
  oss << m;
  return oss . str () == str;
}

int main ( void )
{
	// char from[100], to[100], body[1024];

  // assert ( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "peter", "progtest deadline" ) );
  // assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "progtest deadline", "peter" ) ) );
  // assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "john", "progtest deadline" ) ) );
  // assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "progtest deadline", "john" ) ) );
  // assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "john", "peter" ) ) );
  // assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "peter", "john" ) ) );
  // CMailServer s0;
  // s0 . sendMail ( CMail ( "john", "peter", "some important mail" ) );
  // strncpy ( from, "john", sizeof ( from ) );
  // strncpy ( to, "thomas", sizeof ( to ) );
  // strncpy ( body, "another important mail", sizeof ( body ) );
  // s0 . sendMail ( CMail ( from, to, body ) );
  // strncpy ( from, "john", sizeof ( from ) );
  // strncpy ( to, "alice", sizeof ( to ) );
  // strncpy ( body, "deadline notice", sizeof ( body ) );
  // s0 . sendMail ( CMail ( from, to, body ) );
  // s0 . sendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
  // s0 . sendMail ( CMail ( "peter", "alice", "PR bullshit" ) );
  // CMailIterator i0 = s0 . inbox ( "alice" );
  // assert ( i0 && *i0 == CMail ( "john", "alice", "deadline notice" ) );
  // assert ( matchOutput ( *i0,  "From: john, To: alice, Body: deadline notice" ) );
  // assert ( ++i0 && *i0 == CMail ( "peter", "alice", "PR bullshit" ) );
  // assert ( matchOutput ( *i0,  "From: peter, To: alice, Body: PR bullshit" ) );
  // assert ( ! ++i0 );

  // CMailIterator i1 = s0 . inbox ( "john" );
  // assert ( i1 && *i1 == CMail ( "alice", "john", "deadline confirmation" ) );
  // assert ( matchOutput ( *i1,  "From: alice, To: john, Body: deadline confirmation" ) );
  // assert ( ! ++i1 );

  // CMailIterator i2 = s0 . outbox ( "john" );
  // assert ( i2 && *i2 == CMail ( "john", "peter", "some important mail" ) );
  // assert ( matchOutput ( *i2,  "From: john, To: peter, Body: some important mail" ) );
  // assert ( ++i2 && *i2 == CMail ( "john", "thomas", "another important mail" ) );
  // assert ( matchOutput ( *i2,  "From: john, To: thomas, Body: another important mail" ) );
  // assert ( ++i2 && *i2 == CMail ( "john", "alice", "deadline notice" ) );
  // assert ( matchOutput ( *i2,  "From: john, To: alice, Body: deadline notice" ) );
  // assert ( ! ++i2 );

  // CMailIterator i3 = s0 . outbox ( "thomas" );
  // assert ( ! i3 );

  // CMailIterator i4 = s0 . outbox ( "steve" );
  // assert ( ! i4 );

  // CMailIterator i5 = s0 . outbox ( "thomas" );
  // s0 . sendMail ( CMail ( "thomas", "boss", "daily report" ) );
  // assert ( ! i5 );

  // CMailIterator i6 = s0 . outbox ( "thomas" );
  // assert ( i6 && *i6 == CMail ( "thomas", "boss", "daily report" ) );
  // assert ( matchOutput ( *i6,  "From: thomas, To: boss, Body: daily report" ) );
  // assert ( ! ++i6 );

  // CMailIterator i7 = s0 . inbox ( "alice" );
  // s0 . sendMail ( CMail ( "thomas", "alice", "meeting details" ) );
  // assert ( i7 && *i7 == CMail ( "john", "alice", "deadline notice" ) );
  // assert ( matchOutput ( *i7,  "From: john, To: alice, Body: deadline notice" ) );
  // assert ( ++i7 && *i7 == CMail ( "peter", "alice", "PR bullshit" ) );
  // assert ( matchOutput ( *i7,  "From: peter, To: alice, Body: PR bullshit" ) );
  // assert ( ! ++i7 );

  // CMailIterator i8 = s0 . inbox ( "alice" );
  // assert ( i8 && *i8 == CMail ( "john", "alice", "deadline notice" ) );
  // assert ( matchOutput ( *i8,  "From: john, To: alice, Body: deadline notice" ) );
  // assert ( ++i8 && *i8 == CMail ( "peter", "alice", "PR bullshit" ) );
  // assert ( matchOutput ( *i8,  "From: peter, To: alice, Body: PR bullshit" ) );
  // assert ( ++i8 && *i8 == CMail ( "thomas", "alice", "meeting details" ) );
  // assert ( matchOutput ( *i8,  "From: thomas, To: alice, Body: meeting details" ) );
  // assert ( ! ++i8 );

  // CMailServer s1 ( s0 );
  // s0 . sendMail ( CMail ( "joe", "alice", "delivery details" ) );
  // s1 . sendMail ( CMail ( "sam", "alice", "order confirmation" ) );
  // CMailIterator i9 = s0 . inbox ( "alice" );
  // assert ( i9 && *i9 == CMail ( "john", "alice", "deadline notice" ) );
  // assert ( matchOutput ( *i9,  "From: john, To: alice, Body: deadline notice" ) );
  // assert ( ++i9 && *i9 == CMail ( "peter", "alice", "PR bullshit" ) );
  // assert ( matchOutput ( *i9,  "From: peter, To: alice, Body: PR bullshit" ) );
  // assert ( ++i9 && *i9 == CMail ( "thomas", "alice", "meeting details" ) );
  // assert ( matchOutput ( *i9,  "From: thomas, To: alice, Body: meeting details" ) );
  // assert ( ++i9 && *i9 == CMail ( "joe", "alice", "delivery details" ) );
  // assert ( matchOutput ( *i9,  "From: joe, To: alice, Body: delivery details" ) );
  // assert ( ! ++i9 );

  // CMailIterator i10 = s1 . inbox ( "alice" );
  // assert ( i10 && *i10 == CMail ( "john", "alice", "deadline notice" ) );
  // assert ( matchOutput ( *i10,  "From: john, To: alice, Body: deadline notice" ) );
  // assert ( ++i10 && *i10 == CMail ( "peter", "alice", "PR bullshit" ) );
  // assert ( matchOutput ( *i10,  "From: peter, To: alice, Body: PR bullshit" ) );
  // assert ( ++i10 && *i10 == CMail ( "thomas", "alice", "meeting details" ) );
  // assert ( matchOutput ( *i10,  "From: thomas, To: alice, Body: meeting details" ) );
  // assert ( ++i10 && *i10 == CMail ( "sam", "alice", "order confirmation" ) );
  // assert ( matchOutput ( *i10,  "From: sam, To: alice, Body: order confirmation" ) );
  // assert ( ! ++i10 );

  // CMailServer s2;
  // s2 . sendMail ( CMail ( "alice", "alice", "mailbox test" ) );
  // CMailIterator i11 = s2 . inbox ( "alice" );
  // assert ( i11 && *i11 == CMail ( "alice", "alice", "mailbox test" ) );
  // assert ( matchOutput ( *i11,  "From: alice, To: alice, Body: mailbox test" ) );
  // assert ( ! ++i11 );

  // s2 = s0;
  // s0 . sendMail ( CMail ( "steve", "alice", "newsletter" ) );
  // s2 . sendMail ( CMail ( "paul", "alice", "invalid invoice" ) );
  // CMailIterator i12 = s0 . inbox ( "alice" );
  // assert ( i12 && *i12 == CMail ( "john", "alice", "deadline notice" ) );
  // assert ( matchOutput ( *i12,  "From: john, To: alice, Body: deadline notice" ) );
  // assert ( ++i12 && *i12 == CMail ( "peter", "alice", "PR bullshit" ) );
  // assert ( matchOutput ( *i12,  "From: peter, To: alice, Body: PR bullshit" ) );
  // assert ( ++i12 && *i12 == CMail ( "thomas", "alice", "meeting details" ) );
  // assert ( matchOutput ( *i12,  "From: thomas, To: alice, Body: meeting details" ) );
  // assert ( ++i12 && *i12 == CMail ( "joe", "alice", "delivery details" ) );
  // assert ( matchOutput ( *i12,  "From: joe, To: alice, Body: delivery details" ) );
  // assert ( ++i12 && *i12 == CMail ( "steve", "alice", "newsletter" ) );
  // assert ( matchOutput ( *i12,  "From: steve, To: alice, Body: newsletter" ) );
  // assert ( ! ++i12 );

  // CMailIterator i13 = s2 . inbox ( "alice" );
  // assert ( i13 && *i13 == CMail ( "john", "alice", "deadline notice" ) );
  // assert ( matchOutput ( *i13,  "From: john, To: alice, Body: deadline notice" ) );
  // assert ( ++i13 && *i13 == CMail ( "peter", "alice", "PR bullshit" ) );
  // assert ( matchOutput ( *i13,  "From: peter, To: alice, Body: PR bullshit" ) );
  // assert ( ++i13 && *i13 == CMail ( "thomas", "alice", "meeting details" ) );
  // assert ( matchOutput ( *i13,  "From: thomas, To: alice, Body: meeting details" ) );
  // assert ( ++i13 && *i13 == CMail ( "joe", "alice", "delivery details" ) );
  // assert ( matchOutput ( *i13,  "From: joe, To: alice, Body: delivery details" ) );
  // assert ( ++i13 && *i13 == CMail ( "paul", "alice", "invalid invoice" ) );
  // assert ( matchOutput ( *i13,  "From: paul, To: alice, Body: invalid invoice" ) );
  // assert ( ! ++i13 );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
