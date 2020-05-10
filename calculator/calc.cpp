#include <iostream>
#include <vector>

using namespace std;

/*
 * 123
 * -123
 * 123.45
 * 1234E+10
 * 1234.56E+1
 */
class CNumber {
protected:
	bool m_Invalid;
	bool m_positive;
	vector<int> m_IntPart;
	vector<int> m_FractPart;
	bool m_exppositive;
	vector<int> m_Exp;
public:
	CNumber() :m_Invalid(true) {}
	CNumber(int el) :m_Invalid(false) { m_IntPart.push_back(el);}
	bool isinvalid() { return m_Invalid; }
	CNumber operator +(const CNumber &) const { return CNumber(1); }
	CNumber operator -(const CNumber &) const { return CNumber(1); }
	CNumber operator *(const CNumber &) const { return CNumber(1); }
	CNumber operator /(const CNumber &) const { return CNumber(1); }
	CNumber operator %(const CNumber &) const { return CNumber(1); }
	friend ostream& operator <<(ostream& os, const CNumber& num);
};

ostream& operator <<(ostream& os, const CNumber*num)
{
	os << "output for CNumber";
	return os;
}

class CVariable {
public:
	CVariable(const string& name): m_Name(name) {}
private:
	string m_Name;
};


class COperation {
public:
	virtual CNumber op(const CNumber* v1, const CNumber* v2)  const = 0;
};

class CAdd : public COperation {
public:
	CAdd() {}
	virtual CNumber op(const CNumber* v1, const CNumber* v2) const { return *v1 + *v2; }
};

class CSub : public COperation {
public:
	CSub() {}
	virtual CNumber op(const CNumber* v1, const CNumber* v2) const { return *v1 - *v2; }
};

class CMul : public COperation {
public:
	CMul() {}
	virtual CNumber op(const CNumber* v1, const CNumber* v2) const { return *v1 * *v2; }
};

class CDiv : public COperation {
public:
	CDiv() {}
	virtual CNumber op(const CNumber* v1, const CNumber* v2) const { return *v1 / *v2; }
};

class CMod : public COperation {
public:
	CMod() {}
	virtual CNumber op(const CNumber* v1, const CNumber* v2) const { return *v1 % *v2; }
};
class CNone : public COperation {
public:
	CNone() {}
	virtual CNumber op(const CNumber* v1, const CNumber* v2) const { return *v1; }
};


class CLexer {
public:
	bool isparenthesis(char p);
	void putback();
	CNumber number();
	COperation factorop();
	COperation exprop();
private:
	char m_last;
};

bool CLexer::isparenthesis(char p)
{
	m_last = cin.get();
	if (m_last == p)
		return true;
	cin.putback(m_last);
	return false;
}

/*
 */
CNumber CLexer::number()
{
	CNumber res;

	while (1) {
		m_last = cin.get();
		if (isdigit(m_last)) {
			/* expand CNumber */
			;//res = res * 10 + c - '0';
			
		} else  {
			if (res.isinvalid())
				throw "not a number";
			else
				cin.putback(m_last);
			break;
		}
	}

	return res;
}

/*
 * *, / , %
 */
COperation CLexer::factorop()
{
	m_last = cin.get();

	switch (m_last) {
	case '*':
		return CMul();
	case '/':
		return CDiv();
	case '%':
		return CMod();
	default:
		cin.putback(m_last);
	}
	return CNone();
}

/*
 * +, -
 */
COperation CLexer::exprop()
{
	m_last = cin.get();

	switch (m_last) {
	case '+':
		return CAdd();
	case '-':
		return CSub();
	case '\n':
		return CNone();
	default:
		cin.putback(m_last);
		return CNone();
	}
}

CNumber expr(CLexer& lex);

CNumber factor(CLexer& lex)
{
	CNumber x;

	if (lex.isparenthesis('(')) {
		x = expr(lex);
		if (!lex.isparenthesis(')')) {
			throw("missing closing parenthesis");
		}			
	} else {
		//cin.putback(c);
		x = lex.number();
	}

	/* */
	CNumber v2 = factor(lex);
	x = lex.factorop().op(&x, &v2);

#if 0
	c = cin.get();
	switch(c) {
	case '*':
		x *= factor();
		break;
	case '/':
		x /= factor();
		break;
	case '%':
		x %= factor();
		break;
	default:
		cin.putback(c);
		break;
	}
#endif
	return x;
}

CNumber expr(CLexer& lex)
{
	CNumber x = factor(lex);

	CNumber v2 = expr(lex);
	x = lex.exprop().op(&x, &v2);

/*
	char c = cin.get();
	switch(c) {
	case '+':
		x += expr();
		break;
	case '-':
		x -= expr();
		break;
	case '\n':
		break;
	default:
		cin.putback(c);
		break;
	}
*/
	return x;
}


void set_variable()
{
	string str;
	getline(cin, str);
	cout << "set variable: not ready" << endl;
}

void run_command()
{
	string cmd;

	getline(cin, cmd);
	if (cmd == "quit") {
		exit(0);
	} else if (cmd == "help") {
		cout << ":quit to exit" << endl;
	} else if (cmd == "load" || cmd == "load") {
		cout << cmd << endl;
	} else {
		cout << "unknown command" << endl;
	}
}

int main()
{
	CLexer lex;

	while (1) {
		cout << "enter expr: " << endl;
		try {
			char c = cin.get();
			if (c == ':') {
				/* commands
				 * quit
				 * load
				 * save
				 * help
				 */
				run_command();
			} else if (isalpha(c)) {
				/* val=exression */
				cin.putback(c);
				set_variable();
			} else {
				cin.putback(c);
				cout << expr(lex) << endl;
			}
		} catch (const char *str)  {
			cout << str << endl;
		}
	}
	return 0;
}
