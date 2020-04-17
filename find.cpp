/*
 * This is demo for vectror<class T>: shows how to find element in
 * vector using std::find. T::operator == is used by std:find.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class T {
private:
	string m_Name;
	string m_SurName;
public:
	T(const char *name,  const char *surname) :m_Name(name), m_SurName(surname) {}
	bool operator ==(const T& t2);
	friend ostream & operator << (ostream &os, const T & t);
};

bool T::operator ==(const T& t2)
{
	return m_Name == t2.m_Name && m_SurName == t2.m_SurName;
}

ostream & operator << (ostream &os, const T & t)
{
	os << t.m_Name << " " << t.m_SurName;
	return os;
}

int main()
{
	vector <T> vec;

	vec.push_back(T("vasya", "ivanov"));
	vec.push_back(T("petya", "petrov"));
	vec.push_back(T("harry", "truman"));

	vector<T>::const_iterator it;

	it = find(vec.begin(), vec.end(), T("harry", "truman"));
	if (it == vec.end())
		cout << "not found" << endl;
	else
		cout << "found: " << *it << endl;

	return 0;
}
