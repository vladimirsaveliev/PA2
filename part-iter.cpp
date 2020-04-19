/*
 * This is demo for multiset<class T>:
 *   shows how to select elements in range from container
 */

#include <iostream>
#include <set>
#include <string>

using namespace std;

class T {
private:
	string m_Name;
	string m_SurName;
	int m_Id;
public:
	T(const char *name,  const char *surname, int id);
	bool operator < (const T& t2) const;
	bool operator==(const T& t2) const;

	friend ostream & operator << (ostream &os, const T & t);
};

T::T(const char *name,  const char *surname, int id)
 :m_Name(name), m_SurName(surname), m_Id(id)
{
}

/*
 * T::operator < is for multiset<T> to do insert
 */
bool T::operator <(const T& t2) const
{
	if (m_Name < t2.m_Name)
		return true;
	return m_SurName < t2.m_SurName;
}

/*
 * T::operator == is for multiset<T> to do find
 */
bool T::operator==(const T& t2) const
{
	return m_Name == t2.m_Name && m_SurName == t2.m_SurName;
}

ostream & operator << (ostream &os, const T & t)
{
	os << t.m_Name << " " << t.m_SurName << " " << t.m_Id;
	return os;
}

int main()
{
	multiset<T> s;

	s.insert(T("vasya", "ivanov", 1));
	s.insert(T("petya", "petrov", 2));
	s.insert(T("harry", "truman", 1));
	s.insert(T("harry", "truman", 2));
	s.insert(T("harry", "truman", 3));
	s.insert(T("harry", "truman", 4));
	s.insert(T("aaa", "bbbb", 6));
	s.insert(T("zzz", "bbbb", 6));
	
	T from("harry", "truman", 4);
	T to("harry", "truman", 6);

	set<T>::const_iterator it;

	/* this is supposed to output all 4 "harry truman"s */
	it = find(s.begin(), s.end(), T("harry", "truman", 112312));
	while (it != s.end() && !(to < *it)) {
		cout << "found: " << *it << endl;
		it++;
	}

	return 0;
}
