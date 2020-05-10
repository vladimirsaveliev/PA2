/*
 * This is demo for vectror of strings:
 *   read words from cin into vector
 *   find the longest string in vector
 * To compile:
 *   g++ -Wall max.cpp -o max
 * To run:
 *   ./max <<< "12 23 333"
 * Result:
 *   longest string length: 3
 */

#include <iostream>
#include <vector>

using namespace std;

/* this is used by std::max_element to find max element */
bool compare_strings_by_length(const string& a, const string& b)
{
	return a.length() < b.length();
}

int main()
{
	string str;
	vector <string> vec;

	while (cin >> str) {
		vec.push_back(str);
	}

	cout << "longest string length: " <<
		max_element(vec.begin(), vec.end(), compare_strings_by_length)->size() << endl;

	return 0;
}
