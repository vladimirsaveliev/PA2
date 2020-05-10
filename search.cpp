/*
 * Demm for search
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string where;
	string  what;

	cout << "Enter string to look in: ";
	cin >> where;
	cout << "Enter string to look for: ";
	cin >> what;

	if (search(where.begin(), where.end(), what.begin(), what.end()) != where.end())
		cout << "\"" << what << "\" is found in \"" << where << "\"" << endl;
	else
		cout << "\"" << what << "\" is not found in \"" << where << "\"" << endl;
	return 0;
}
