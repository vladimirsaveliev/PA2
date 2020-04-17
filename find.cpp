/*
 * This is demo for vectror<class T>: shows how to find element in
 * vector using std::find. T::operator == is used by std:find.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	string str;
	vector <string> vec;

	vec.push_back("vasya");
	vec.push_back("petya");
	vec.push_back("john");

	vector<string>::const_iterator it;

	it = find(vec.begin(), vec.end(), "john");
	if (it == vec.end())
		cout << "not found" << endl;
	else
		cout << "found: " << *it << endl;

	return 0;
}
