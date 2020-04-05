#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

class CBigInt
{
  public:
    	// default constructor
	CBigInt();
        // int constructor
	CBigInt(int arg);
   	// string constructor, throw exceptio if s is not decimal number
	CBigInt (const string &s);

	// copying/assignment/destruction
	~CBigInt() { }

	CBigInt & operator = (const string & str);

	// operator +, any combination {CBigInt/int/string} + {CBigInt/int/string}
	CBigInt operator + (const CBigInt &addendum2) const;
	CBigInt operator + (int addendum2) const;
	CBigInt operator + (const string & addendum2) const;
	friend CBigInt operator + (int addendum1, CBigInt addendum2);
	friend CBigInt operator + (string addendum1, CBigInt addendum2);

	// For substraction
	CBigInt operator - (const CBigInt &sub) const;

	// operator *, any combination {CBigInt/int/string} * {CBigInt/int/string}
	CBigInt operator * (const CBigInt & factor2) const;
	CBigInt operator * (int factor2) const;
	CBigInt operator * (const string & factor2) const;
	friend CBigInt operator * (int factor1, CBigInt factor2);
	friend CBigInt operator * (string factor1, CBigInt factor2);
	// operator +=, any of {CBigInt/int/string}
	CBigInt & operator +=(int rhoperand);
	CBigInt & operator +=(const CBigInt & rhoperand);
	CBigInt & operator +=(const string & rhoperand);
	// operator *=, any of {CBigInt/int/string}
	CBigInt & operator *=(int rhoperand);
	CBigInt & operator *=(const CBigInt & rhoperand);
	CBigInt & operator *=(const string & rhoperand);
	
	// comparison operators, any combination {CBigInt/int/string} {<,<=,>,>=,==,!=} {CBigInt/int/string}
	bool operator < (const CBigInt & rhoperand) const;
	bool operator < (int rhoperand) const;
	bool operator < (const string & rhoperand) const;
	friend bool operator < (int lhoperand, CBigInt rhoperand);
	friend bool operator < (string lhoperand, CBigInt rhoperand);

	//  Less or equal 
	bool operator <= (const CBigInt & rhoperand) const;
	bool operator <= (int rhoperand) const;
	bool operator <= (const string & rhoperand) const;
	friend bool operator <= (int lhoperand, CBigInt rhoperand);
	friend bool operator <= (string lhoperand, CBigInt rhoperand);

	// >
	bool operator > (const CBigInt & rhoperand) const;
	bool operator > (int rhoperand) const;
	bool operator > (const string & rhoperand) const;
	friend bool operator > (int lhoperand, CBigInt rhoperand);
	friend bool operator > (string lhoperand, CBigInt rhoperand);

	// >=
	bool operator >= (const CBigInt & rhoperand) const;
	bool operator >= (int rhoperand) const;
	bool operator >= (const string & rhoperand) const;
	friend bool operator >= (int lhoperand, CBigInt rhoperand);
	friend bool operator >= (string lhoperand, CBigInt rhoperand);

	// ==
	bool operator == (const CBigInt & rhoperand) const;
	bool operator == (int rhoperand) const;
	bool operator == (const string & rhoperand) const;
	friend bool operator == (int lhoperand, CBigInt rhoperand);
	friend bool operator == (string lhoperand, CBigInt rhoperand);

	// !=
	bool operator != (const CBigInt & rhoperand) const;
	bool operator != (int rhoperand) const;
	bool operator != (const string & rhoperand) const;
	friend bool operator != (int lhoperand, CBigInt rhoperand);
	friend bool operator != (string lhoperand, CBigInt rhoperand);

       	// output operator <<
	friend ostream & operator << (ostream & os, const CBigInt &x);
	
	// input operator >>
  	friend istream & operator >> (istream & is, CBigInt &x);
private:
	// todo
	string m_Number;
	bool m_Positive; // true if positive and false if negative

	CBigInt add(const CBigInt &addendum2) const;
	bool cmpabsless(const CBigInt &rhoperand) const;
	CBigInt multbydigit(int mult) const;
};

// Default constructor
CBigInt::CBigInt()
{
	this->m_Number = "0";
	this->m_Positive = true;
}

CBigInt::CBigInt(int arg)
{
	if (arg > 0) {
		this->m_Positive = true;
		this->m_Number = to_string(arg);
	} else {
		this->m_Positive = false;
		this->m_Number = to_string(-arg);
	}
}

// Examples of valid s:
//    "123"
//    "0010"
//    "-500"
//    "-0012"
//    "+123"
//    "+00123"
CBigInt::CBigInt(const string &s)
{
	string::const_iterator it;
	int lead0num = 0;

	// Check first symbol
	it = s.begin();
	if (it == s.end()) {
		throw invalid_argument("Empty string");
	}
	if (!isdigit(*it) && *it != '+' && *it != '-') {
		throw invalid_argument("First symbol is invalid");
	}
	if (*it == '-') {
		this->m_Positive = false;
	} else {
		this->m_Positive = true;
		if (*it != '+' && *it != '0') {
			this->m_Number.push_back(*it);
		}
		if (*it == '0') {
			lead0num++;
		}
	}
	
	// Check all symbols but first one
	for (it = s.begin() + 1; it != s.end(); it ++) {
		if (!isdigit(*it)) {
			throw invalid_argument("Not a digit");
		}
		// Append symbol to m_Number
		if (this->m_Number.size() == 0 && *it == '0') {
			lead0num++;
			continue;
		}
		this->m_Number.push_back(*it);
	}
	if (this->m_Number.size() == 0) {
		if (lead0num > 0) {
			this->m_Positive = true;
			this->m_Number.push_back('0');
		} else {
			throw invalid_argument("Sign only string");
		}
	}
}

// CBitInt = (string)
CBigInt & CBigInt::operator = (const string & str)
{
	*this = CBigInt(str);
	return *this;
}

// operator +.
// Cases: *this and addendum2 > 0
//        *this and addendum2 < 0
//        *this < 0 addendum2 > 0
//        *this > 0 addendum2 < 0
CBigInt CBigInt::operator + (const CBigInt &addendum2) const
{
	CBigInt res;

	if ( (this->m_Positive == true && addendum2.m_Positive == true) ||
	     (this->m_Positive == false && addendum2.m_Positive == false) ) {
		return this->add(addendum2);
	} else {
		if (this->cmpabsless(addendum2)) {
			return addendum2 - *this;
		} else {
			return *this - addendum2;
		}
	}
}



// Adding two positives
CBigInt CBigInt::add(const CBigInt &addendum2) const
{
	const string &a1 = this->m_Number;
	const string &a2 = addendum2.m_Number;
	string::const_reverse_iterator it1;
	string::const_reverse_iterator it2;
	CBigInt res; // We have m_Number is "0"
	int carry = 0;

	res.m_Number.erase(res.m_Number.begin()); // Erase "0" which came from default constructor

	for (it1 = a1.rbegin(), it2 = a2.rbegin(); it1 != a1.rend() || it2 != a2.rend();) {
		// Adding by
		int d1;
		int d2;
		if (it1 == a1.rend()) {
		        d1 = 0;
		} else {
		        d1 = *it1 - '0';
			it1++;
		}
		if (it2 == a2.rend()) {
			d2 = 0;
		} else {
			d2 = *it2 - '0';
			it2++;
		}
		int sum = d1 + d2 + carry;
		char c = (sum % 10) + '0';
		carry = sum / 10;
		res.m_Number.insert(res.m_Number.begin(), c);
	}
	if (carry == 1) {
		res.m_Number.insert(res.m_Number.begin(), '1');
	}

	res.m_Positive = this->m_Positive;
	cout << *this << " + " << addendum2 << " = "  << res << endl;
	return res;
}


// *this - sub
// if this >= sub
CBigInt CBigInt::operator - (const CBigInt &sub) const
{
	const string &a1 = this->m_Number;
	const string &a2 = sub.m_Number;
	string::const_reverse_iterator it1;
	string::const_reverse_iterator it2;
	CBigInt res; // We have m_Number is "0"
	int carry = 0;

	res.m_Number.erase(res.m_Number.begin()); // Erase "0" which came from default constructor

	for (it1 = a1.rbegin(), it2 = a2.rbegin(); it1 != a1.rend() || it2 != a2.rend();) {
		// Adding by
		int d1;
		int d2;
		if (it1 == a1.rend()) {
		        d1 = 0;
		} else {
		        d1 = *it1 - '0';
			it1++;
		}
		if (it2 == a2.rend()) {
			d2 = 0;
		} else {
			d2 = *it2 - '0';
			it2++;
		}
		d1 -= carry;
		if (d1 < d2) {
			d1 += 10;
			carry = 1;
		} else {
			carry = 0;
		}
		
		int diff = d1 - d2;
		char c = diff + '0';
		res.m_Number.insert(res.m_Number.begin(), c);
	}
       
	// Erase leading zeroes
	string::iterator it3;
	
	while(1) {
		it3 = res.m_Number.begin();
		if (*it3 != '0' || res.m_Number.size() == 1) {
			break;
		}
	       	res.m_Number.erase(it3);
	}

	// Determine sign of result
	res.m_Positive = this->m_Positive;

	cout << *this << " - " << sub << " = "  << res << endl;
       	return res;
}

// CBigInt + int
CBigInt CBigInt::operator + (int addendum2) const
{
	CBigInt b(addendum2);
	
	return *this + b;
}

// CBigInt + string
CBigInt CBigInt::operator + (const string & addendum2) const
{
	CBigInt b(addendum2);
	
	return *this + b;
}

CBigInt operator + (int addendum1, CBigInt addendum2)
{
	return 0;
}

CBigInt operator + (string addendum1, CBigInt addendum2)
{
	cout << "I can do string + CBigInt" << endl;
	return 0;
}

// Helper for multiplier by one digit
CBigInt CBigInt::multbydigit(int mult) const
{
	string::const_reverse_iterator it;
	const string &a = this->m_Number;
	CBigInt res;
	int carry = 0;

	res.m_Number.erase(res.m_Number.begin());

	for (it = a.rbegin(); it != a.rend(); it++) {
		int f1 = *it - '0';
		int prod = f1 * mult + carry;
		char c = (prod % 10) + '0';
		carry = prod / 10; 
		res.m_Number.insert(res.m_Number.begin(), c);
	}
	if (carry > 0) {
		res.m_Number.insert(res.m_Number.begin(), carry + '0');
	}
	return res;
}

// returns CBigInt
CBigInt CBigInt::operator *(const CBigInt & factor2) const
{
	string::const_reverse_iterator it;
	const string &a = factor2.m_Number;
	CBigInt res;
	int pad0num = 0;

	for (it = a.rbegin(); it != a.rend(); it++, pad0num++) {
		int mult = *it - '0';
		CBigInt r1 = this->multbydigit(mult);
		// append zeros
		for(int i = 0; i < pad0num; i++) {
			r1.m_Number.push_back('0');
		}
		res = res + r1;
	}

	// Erase leading zeroes
	string::iterator it3;
	
	while(1) {
		it3 = res.m_Number.begin();
		if (*it3 != '0' || res.m_Number.size() == 1) {
			break;
		}
	       	res.m_Number.erase(it3);
	}

	// Sort out sign of result
	res.m_Positive = this->m_Positive == factor2.m_Positive;
	cout << *this << " * " << factor2  << " = " << res << endl;
	return res;
}

CBigInt CBigInt::operator *(int factor2) const
{
	CBigInt b(factor2); 
	return *this * b;
}

CBigInt CBigInt::operator * (const string & factor2) const
{
	CBigInt b(factor2);
	return *this * b;
}

CBigInt operator * (int factor1, CBigInt factor2)
{
	cout << "I can do int * CBigInt" << endl;
	return 0;
}

CBigInt operator * (string factor1, CBigInt factor2)
{
	cout << "I can do string * CBigInt" << endl;
	return 0;
}

// CBigInt += int
CBigInt & CBigInt::operator += (int rhoperand)
{
	CBigInt b(rhoperand);
	*this = *this + b;
	return *this;
}

// CBigInt += CBigInt
CBigInt & CBigInt::operator +=(const CBigInt &rhoperand)
{
	*this = *this + rhoperand;
	return *this;
}

// CBigInt += string
CBigInt & CBigInt::operator +=(const string &rhoperand)
{
	CBigInt b(rhoperand);
	*this = *this + b;
	return *this;
}

// CBigInt *= int
CBigInt & CBigInt::operator *=(int rhoperand)
{
	CBigInt b(rhoperand);
	*this = *this * b;
	return *this;
}

// CBigInt *= CBigInt
CBigInt & CBigInt::operator *=(const CBigInt & rhoperand)
{
	*this = *this * rhoperand;
	return *this;
}

// CBigInt *= string
CBigInt & CBigInt::operator *=(const string & rhoperand)
{
	CBigInt b(rhoperand);
	*this = *this * b;
	return *this;
}

// Compare absolute values of CBigInts
// Return true if *this < rhoperand
// false if otherwise
bool CBigInt::cmpabsless(const CBigInt &rhoperand) const
{
	if (this->m_Number.size() == rhoperand.m_Number.size()) {
		return this->m_Number < rhoperand.m_Number;
	}
	return this->m_Number.size() < rhoperand.m_Number.size();
}

bool CBigInt::operator < (const CBigInt & rhoperand) const
{
	if (this->m_Positive == true && rhoperand.m_Positive == false) {
		// + and -
		return false;
	}
	if (this->m_Positive == false && rhoperand.m_Positive == true) {
		// - and +
		return true;
	}
	if (this->m_Positive == false && rhoperand.m_Positive == false) {
		// - and -
		return !(this->cmpabsless(rhoperand));
	}
	// + and +
	return this->cmpabsless(rhoperand);
}

bool CBigInt::operator < (int rhoperand) const
{
	CBigInt b(rhoperand);
	return *this < b;
}

bool CBigInt::operator < (const string & rhoperand) const
{
	CBigInt b(rhoperand);
	return *this < b;
}

bool operator < (int lhoperand, CBigInt rhoperand)
{
	cout << "I can do int < CBigInt" << endl;
	return 0;
}

bool operator < (string lhoperand, CBigInt rhoperand)
{
	cout << "I can do string < CBigInt" << endl;
	return 0;
}

bool CBigInt::operator <= (const CBigInt & rhoperand) const
{
	if (*this < rhoperand) {
		return true;
	}
	
	return !(rhoperand < *this);
}

bool CBigInt::operator <= (int rhoperand) const
{
	CBigInt b(rhoperand);
	return *this <= b;
}

bool CBigInt::operator <= (const string & rhoperand) const
{
	CBigInt b(rhoperand);
	return *this <= b;;
}

bool operator <= (int lhoperand, CBigInt rhoperand)
{
	cout << "I can do int < CBigInt" << endl;
	return 0;
}

bool CBigInt::operator > (const CBigInt & rhoperand) const
{
	return rhoperand < *this;
}

bool CBigInt::operator > (int rhoperand) const
{
	CBigInt b(rhoperand); 
	return rhoperand < *this;
}

bool CBigInt::operator > (const string & rhoperand) const
{
	CBigInt b(rhoperand); 
	return rhoperand < *this;
}

bool operator > (int lhoperand, CBigInt rhoperand)
{
	cout << "I can do int < CBigInt" << endl;
	return 0;
}

bool CBigInt::operator >= (const CBigInt & rhoperand) const
{
	return rhoperand <= *this;
}

bool CBigInt::operator >= (int rhoperand) const
{
	CBigInt b(rhoperand);
	return *this >= b;
}

bool CBigInt::operator >= (const string & rhoperand) const
{
	CBigInt b(rhoperand);
	return *this >= b;
}

bool operator >= (int lhoperand, CBigInt rhoperand)
{
	cout << "I can do int >= CBigInt" << endl;
	return 0;
}

bool CBigInt::operator == (const CBigInt & rhoperand) const
{
	return !(*this < rhoperand) && !(*this > rhoperand);
}

bool CBigInt::operator == (int rhoperand) const
{
	CBigInt b(rhoperand);
	return *this == b;
}

bool CBigInt::operator == (const string & rhoperand) const
{
	CBigInt b(rhoperand);
	return *this == b;
}

bool operator == (int lhoperand, CBigInt rhoperand)
{
	cout << "I can do int == CBigInt" << endl;
	return 0;
}

bool operator == (string lhoperand, CBigInt rhoperand)
{
	cout << "I can do string == CBigInt" << endl;
	return 0;
}

bool CBigInt::operator != (const CBigInt & rhoperand) const
{
	return !(*this == rhoperand);
}

bool CBigInt::operator != (int rhoperand) const
{
	CBigInt b(rhoperand);
	return *this != b;
}

bool CBigInt::operator != (const string & rhoperand) const
{
	CBigInt b(rhoperand);
	return *this != b;
}

bool operator != (int lhoperand, CBigInt rhoperand)
{
	cout << "I can do int != CBigInt" << endl;
	return 0;
}

bool operator != (string lhoperand, CBigInt rhoperand)
{
	cout << "I can do string != CBigInt" << endl;
	return 0;
}

ostream & operator << (ostream & os, const CBigInt &x)
{
	if (x.m_Positive == false) {
		os << "-" << x.m_Number;
	} else {
		os << x.m_Number;
	}

	return os;
}

//
// valid input:
//  "   1234" -> 1234
//  "+0001" -> 1
//  "-0111" -> -111
//  "0000" -> 0
//  is no decimal digits - failbit is set on is
istream & operator >> (istream  & is, CBigInt &x)
{
	char c;
	bool whitespaceok = true;
	bool signok = true;
	int lead0num = 0;

	x.m_Number = "";

	while ((c = is.peek()) != EOF) {
		c = is.get();
		if (whitespaceok) {
			if (isspace(c)) {
				continue;
			}
			/* no space anymore */
			whitespaceok = false;
		}
		
		if (signok) {
			if (c == '-' || c == '+') {
				x.m_Positive = (c == '+');
				signok = false;
				continue;
			}
		}

		/* only digits */
		if (!isdigit(c)) {
			break;
		}
		whitespaceok = false;
		signok = false;

		/* skip leading '0' */
		if (x.m_Number.size() == 0 &&  c == '0') {
			lead0num++;
			continue;
		}

		x.m_Number.push_back(c);
	}

	if (x.m_Number.size() == 0) {
		if (lead0num)
			x.m_Number.push_back('0');
		else
			is.setstate(ios::failbit);
	}

	return is;
}


#ifndef __PROGTEST__
static bool equal ( const CBigInt & x, const char * val )
{
  ostringstream oss;
  oss << x;
  return oss . str () == val;
}
int main ( void )
{
  CBigInt a, b;
  istringstream is;
  a = 10;
  a += 20;
  assert ( equal ( a, "30" ) );
  a *= 5;
  assert ( equal ( a, "150" ) );
  b = a + 3;
  assert ( equal ( b, "153" ) );
  b = a * 7;
  assert ( equal ( b, "1050" ) );
  assert ( equal ( a, "150" ) );

  a = 10;
  a += -20;
  assert ( equal ( a, "-10" ) );
  a *= 5;
  assert ( equal ( a, "-50" ) );
  b = a + 73;
  assert ( equal ( b, "23" ) );
  b = a * -7;
  assert ( equal ( b, "350" ) );
  assert ( equal ( a, "-50" ) );
#if 1
  a = "12345678901234567890";
  a += "-99999999999999999999";
  assert ( equal ( a, "-87654321098765432109" ) );
  a *= "54321987654321987654";
  assert ( equal ( a, "-4761556948575111126880627366067073182286" ) );
  a *= 0;
  assert ( equal ( a, "0" ) );
  a = 10;
  b = a + "400";
  assert ( equal ( b, "410" ) );
  b = a * "15";
  assert ( equal ( b, "150" ) );
  assert ( equal ( a, "10" ) );

  is . clear ();
  is . str ( " 1234" );
  assert ( is >> b );
  assert ( equal ( b, "1234" ) );
  is . clear ();
  is . str ( " 12 34" );
  assert ( is >> b );
  assert ( equal ( b, "12" ) );
  is . clear ();
  is . str ( "999z" );
  assert ( is >> b );
  assert ( equal ( b, "999" ) );
  is . clear ();
  is . str ( "abcd" );
  assert ( ! ( is >> b ) );
  is . clear ();
  is . str ( "- 758" );
  assert ( ! ( is >> b ) );
  a = 42;
  try
  {
    a = "-xyz";
    assert ( "missing an exception" == NULL );
  }
  catch ( const invalid_argument & e )
  {
    assert ( equal ( a, "42" ) );
  }

  a = "73786976294838206464";
  assert ( a < "1361129467683753853853498429727072845824" );
  assert ( a <= "1361129467683753853853498429727072845824" );
  assert ( ! ( a > "1361129467683753853853498429727072845824" ) );
  assert ( ! ( a >= "1361129467683753853853498429727072845824" ) );
  assert ( ! ( a == "1361129467683753853853498429727072845824" ) );
  assert ( a != "1361129467683753853853498429727072845824" );
  assert ( ! ( a < "73786976294838206464" ) );
  assert ( a <= "73786976294838206464" );
  assert ( ! ( a > "73786976294838206464" ) );
  assert ( a >= "73786976294838206464" );
  assert ( a == "73786976294838206464" );
  assert ( ! ( a != "73786976294838206464" ) );
  assert ( a < "73786976294838206465" );
  assert ( a <= "73786976294838206465" );
  assert ( ! ( a > "73786976294838206465" ) );
  assert ( ! ( a >= "73786976294838206465" ) );
  assert ( ! ( a == "73786976294838206465" ) );
  assert ( a != "73786976294838206465" );
  a = "2147483648";
  assert ( ! ( a < -2147483648 ) );
  assert ( ! ( a <= -2147483648 ) );
  assert ( a > -2147483648 );
  assert ( a >= -2147483648 );
  assert ( ! ( a == -2147483648 ) );
  assert ( a != -2147483648 );
#endif
  return 0;
}
#endif /* __PROGTEST__ */
