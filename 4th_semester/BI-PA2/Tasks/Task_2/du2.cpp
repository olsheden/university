#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

struct Email;

struct Salary;

struct Person{
  string name;
  string surname;
  Email* email;
  Salary* salary;

  Person(){
  }

  Person(string name, string surname, Email* email = nullptr, Salary* salary = nullptr){
	this->name = name;
	this->surname = surname;
	this->salary = salary;
	this->email = email;
  }
};

struct Email{
  string email;
  Person* person;
  Salary* salary;

  Email(){
  }

  Email(string email, Person* person = nullptr, Salary* salary = nullptr){
	this->email = email;
	this->person = person;
	this->salary = salary;
  }
};

struct Salary{
	unsigned int salary;
	Person* person;
	Email* email;

	Salary(){

	}

	Salary(unsigned int salary, Person* person = nullptr, Email* email = nullptr){
	this->salary = salary;
	this->person = person;
	this->email = email;
  }
};

class CPersonalAgenda
{
public:
	CPersonalAgenda  ( void );
	~CPersonalAgenda ( void );
	bool          add              ( const string    & name,
							const string    & surname,
							const string    & email,
							unsigned int      salary );
	bool          del              ( const string    & name,
							const string    & surname );
	bool          del              ( const string    & email );
	bool          changeName       ( const string    & email,
							const string    & newName,
							const string    & newSurname );
	bool          changeEmail      ( const string    & name,
							const string    & surname,
							const string    & newEmail );
	bool          setSalary        ( const string    & name,
							const string    & surname,
							unsigned int      salary );
	bool          setSalary        ( const string    & email,
							unsigned int      salary );
	unsigned int  getSalary        ( const string    & name,
							const string    & surname ) const;
	unsigned int  getSalary        ( const string    & email ) const;
	bool          getRank          ( const string    & name,
							const string    & surname,
							int             & rankMin,
							int             & rankMax ) const;
	bool          getRank          ( const string    & email,
							int             & rankMin,
							int             & rankMax ) const;
	bool          getFirst         ( string          & outName,
							string          & outSurname ) const;
	bool          getNext          ( const string    & name,
							const string    & surname,
							string          & outName,
							string          & outSurname ) const;
private:
	vector<Person*> m_persons;
	vector<Email> m_emails;
	vector<Salary> m_salaries;
};

bool cmpName(const Person * x, const Person * y){
	return x->surname < y->surname || (x->surname == y->surname && x->name < y->name);
}

bool cmpEmail(const Email & x, const Email & y){
	return x.email < y.email;
}

bool cmpSalary(const Salary & x, const Salary & y){
	return x.salary < y.salary;
}

CPersonalAgenda::~CPersonalAgenda() {
	// for(auto& email : this->m_emails) delete email.person;
	for(auto& person : this->m_persons){
		delete person->email;
		delete person->salary;
		delete person;
	}
	// for(int i = m_persons.size()-1; i >= 0; i++){
	// 	delete m_persons[i]->email;
	// 	delete m_persons[i]->salary;
	// 	delete m_persons[i];
	// }
}

CPersonalAgenda::CPersonalAgenda() {
}

bool CPersonalAgenda::add( const string    & name, const string    & surname, const string    & email, unsigned int      salary ){
	Person* newPerson = new Person(name,surname);
	Email* newEmail = new Email(email, newPerson);
	Salary* newSalary = new Salary(salary, newPerson, newEmail);
	newPerson->email = newEmail;
	newPerson->salary = newSalary;
	newEmail->salary = newSalary;

	if(m_persons.empty()) {
		m_persons.push_back(newPerson);
		m_emails.push_back(*newEmail);
		m_salaries.push_back(*newSalary);
		return true;
	}
	auto it_person = lower_bound(m_persons.begin(), m_persons.end(), newPerson, cmpName);
	if(it_person != m_persons.end() && (*it_person)->name == name && (*it_person)->surname == surname){
		delete newEmail;
		delete newPerson;
		delete newSalary;
		return false;
	}
	auto it_email = lower_bound(m_emails.begin(), m_emails.end(), *newEmail, cmpEmail);
	if(it_email != m_emails.end() &&  it_email->email == email){
		delete newEmail;
		delete newPerson;
		delete newSalary;
		return false;
	}
	m_persons.insert(it_person, newPerson);
	m_emails.insert(it_email, *newEmail);	
	auto it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *newSalary, cmpSalary);
	m_salaries.insert(it_salary, *newSalary);
	return true;
}

bool CPersonalAgenda::getFirst( string & outName, string& outSurname ) const{
	if(m_persons.empty()) return false;
	outName = m_persons[0]->name;
	outSurname = m_persons[0]->surname;
	return true;
}

bool CPersonalAgenda::getNext( const string    & name,const string    & surname, string          & outName, string          & outSurname ) const{
	if(m_persons.empty()) return false;
	Person *find = new Person(name, surname);
	auto it = lower_bound(m_persons.begin(), m_persons.end(), find, cmpName);
	delete find;
	if(it == m_persons.end() || ((*it)->name != name && (*it)->surname != surname)) return false;
	auto next = upper_bound(m_persons.begin(), m_persons.end(), *it, cmpName);
	if(next == m_persons.end()) return false;
	outName = (*next)->name;
	outSurname = (*next)->surname;
	return true;
}

bool CPersonalAgenda::setSalary ( const string    & name, const string    & surname, unsigned int      salary ){
	if(m_persons.empty()) return false;
	Person* find = new Person(name, surname);
	auto it = lower_bound(m_persons.begin(), m_persons.end(), find, cmpName);
	delete find;
	if(it == m_persons.end() || (*it)->name != name || (*it)->surname != surname) return false;
	if((*it)->salary->salary == salary) return false;
	auto it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *((*it)->salary), cmpSalary);
	(*it)->salary->salary = salary;
	*it_salary = *((*it)->salary);
	Salary* change = (*it)->salary;
	m_salaries.erase(it_salary);
	it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *change, cmpSalary);
	m_salaries.insert(it_salary, *change);
	return true;
}

bool CPersonalAgenda::setSalary ( const string    & email, unsigned int      salary ){
	if(m_persons.empty()) return false;
	Email find(email, nullptr, nullptr);
	auto it = lower_bound(m_emails.begin(), m_emails.end(), find, cmpEmail);
	if(it == m_emails.end() || it->email != email) return false;
	auto it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *(it->salary), cmpSalary);
	it->salary->salary = salary;
	*it_salary = *(it->salary);
	Salary* change = it->salary;
	m_salaries.erase(it_salary);
	it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *change, cmpSalary);
	m_salaries.insert(it_salary, *change);
	return true;
}

unsigned int  CPersonalAgenda::getSalary( const string    & name, const string    & surname ) const{
	if(m_persons.empty()) return false;
	Person* find = new Person(name, surname);
	auto it = lower_bound(m_persons.begin(), m_persons.end(), find, cmpName);
	delete find;
	if(it == m_persons.end() || (*it)->name != name || (*it)->surname != surname) return 0;
	return (*it)->salary->salary;
}

unsigned int  CPersonalAgenda::getSalary( const string    & email ) const{
	if(m_persons.empty()) return false;
	Email find;
	find.email = email;
	auto it = lower_bound(m_emails.begin(), m_emails.end(), find, cmpEmail);
	if(it == m_emails.end() || it->email != email) return 0;
	return it->salary->salary;
}

bool CPersonalAgenda::getRank ( const string    & name, const string & surname, int & rankMin, int & rankMax ) const{
	if(m_persons.empty()) return false;
	Person *find = new Person(name, surname);
	auto it = lower_bound(m_persons.begin(), m_persons.end(), find, cmpName);
	delete find;
	if(it == m_persons.end() || (*it)->name != name || (*it)->surname != surname) return false;
	auto it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *((*it)->salary), cmpSalary);
	auto ita = upper_bound(m_salaries.begin(), m_salaries.end(), *((*it)->salary), cmpSalary);
	rankMin = it_salary - m_salaries.begin();
	rankMax = ita - m_salaries.begin() - 1;
	return true;
}

bool CPersonalAgenda::getRank ( const string    & email, int & rankMin, int & rankMax ) const{
	if(m_persons.empty()) return false;
	Email find(email);
	auto it = lower_bound(m_emails.begin(), m_emails.end(), find, cmpEmail);
	if(it == m_emails.end() || it->email != email) return false;
	auto it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *(it->salary), cmpSalary);
	auto ita = upper_bound(m_salaries.begin(), m_salaries.end(), *(it->salary), cmpSalary);
	rankMin = it_salary - m_salaries.begin();
	rankMax = ita - m_salaries.begin() - 1;
	return true;
}

bool CPersonalAgenda::changeName ( const string    & email, const string    & newName, const string    & newSurname ){
	if(m_persons.empty()) return false;
	Email find(email);
	auto it_email = lower_bound(m_emails.begin(), m_emails.end(), find, cmpEmail);
	if(it_email == m_emails.end() || it_email->email != email) return false;
	auto it = lower_bound(m_persons.begin(), m_persons.end(), it_email->person, cmpName);
	if((*it)->name == newName && (*it)->surname == newSurname) return false;
	Person* newPerson = new Person(newName, newSurname, (*it)->email, (*it)->salary);
	auto it_check = lower_bound(m_persons.begin(), m_persons.end(), newPerson, cmpName);
	if((*it_check)->name == newName && (*it_check)->surname == newSurname) {
		delete newPerson;
		return false;
	}
	m_persons.erase(it);
	it = lower_bound(m_persons.begin(), m_persons.end(), newPerson, cmpName);
	m_persons.insert(it, newPerson);
	delete it_email->person;
	it_email->person = newPerson;
	return true;
}

bool CPersonalAgenda::changeEmail ( const string    & name, const string & surname, const string    & newEmail ){
	if(m_persons.empty()) return false;
	Person* find = new Person(name, surname);
	auto it = lower_bound(m_persons.begin(), m_persons.end(), find, cmpName);
	delete find;
	if(it == m_persons.end() || (*it)->name != name || (*it)->surname != surname) return false;
	auto it_email = lower_bound(m_emails.begin(), m_emails.end(), *((*it)->email), cmpEmail);
	if(it_email->email == newEmail) return false;
	Email* email = new Email(newEmail, it_email->person, it_email->salary);
	auto it_check = lower_bound(m_emails.begin(), m_emails.end(), *email, cmpEmail);
	if(it_check->email == newEmail) {
		delete email;
		return false;
	}
	m_emails.erase(it_email);
	it_email = lower_bound(m_emails.begin(), m_emails.end(), *email, cmpEmail);
	m_emails.insert(it_email, *email);
	delete (*it)->email ;
	(*it)->email = email;
	return true;
}

bool CPersonalAgenda::del(const string &name, const string &surname) {
  if (m_persons.empty()) return false;
  Person* find = new Person(name, surname);
  auto it_person = lower_bound(m_persons.begin(), m_persons.end(), find, cmpName);
  delete find;
  if (it_person == m_persons.end() || (*it_person)->surname != surname) return false;
  
  auto it_email = lower_bound(m_emails.begin(), m_emails.end(), *((*it_person)->email), cmpEmail);
  auto it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *((*it_person)->salary), cmpSalary);
  
  Email* email_ptr = (*it_person)->email;
  Salary* salary_ptr = (*it_person)->salary;
  Person* person_ptr = it_email->person;
  
  m_emails.erase(it_email);
  m_persons.erase(it_person);
  m_salaries.erase(it_salary);
  
  delete email_ptr;
  delete salary_ptr;
  delete person_ptr;
  
  return true;
}

bool CPersonalAgenda::del(const string &email) {
  if (m_persons.empty()) return false;
  Email find(email);
  auto it_email = lower_bound(m_emails.begin(), m_emails.end(), find, cmpEmail);
  if (it_email == m_emails.end() || it_email->email != email) return false;
  
  auto it_person = lower_bound(m_persons.begin(), m_persons.end(), it_email->person, cmpName);
  auto it_salary = lower_bound(m_salaries.begin(), m_salaries.end(), *(it_email->salary), cmpSalary);
  
  Email* email_ptr = (*it_person)->email;
  Salary* salary_ptr = (*it_person)->salary;
  Person* person_ptr = it_email->person;
  
  m_emails.erase(it_email);
  m_persons.erase(it_person);
  m_salaries.erase(it_salary);
  
  delete email_ptr;
  delete salary_ptr;
  delete person_ptr;
  
  return true;
}


#ifndef __PROGTEST__
int main ( void )
{
  
}
#endif /* __PROGTEST__ */
