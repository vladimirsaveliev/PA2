/*
 * This is demo for vectror of strings: read from cin, sort, output
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip> /* for setw() */

using namespace std;

int main()
{
	string str;
	vector <string> vec;

	while (cin >> str) {
		vec.push_back(str);
	}

	vector<string>::const_iterator it;
	for (it = vec.begin(); it != vec.end(); it++)
		cout << setw(10) << *it;
	cout << endl;

	sort(vec.begin(), vec.end());

	for (it = vec.begin(); it != vec.end(); it++)
		cout << setw(10) << *it;
	cout << endl;

	return 0;
}
