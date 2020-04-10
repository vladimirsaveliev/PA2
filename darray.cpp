#include <iostream>
#include <iomanip> /* for setw() */

using namespace std;

/*
 * dynamic array of integers
 */
class CDarray {
private:
	int m_max_size;
	int m_cur_size;
	int *m_data;
public:
	/* default constructor */
	CDarray();
	~CDarray();
	void append(int n);
	int operator [](int idx) const;
  	int & operator [](int idx);

	friend ostream & operator <<(ostream &os, const CDarray &arr);
};

/*
 * output (<<) operator friend for CDarray
 */
ostream & operator <<(ostream &os, const CDarray &arr)
{
	for (int i = 0; i < arr.m_cur_size; i++)
		os << setw(5) << arr.m_data[i];
	return os;
}

/*
 * Default constructor
 *   this make empty array of initial max size
 */
CDarray::CDarray()
{
	m_max_size = 1;
	m_cur_size = 0;
	m_data = new int[m_max_size];
}

/*
 * Destructor
 */
CDarray::~CDarray()
{
	delete [] m_data;
}

/*
 * CDarray::append
 *   add one element to end of array
 *   allocate more memory if needed
 */
void CDarray::append(int n)
{
	if (m_max_size == m_cur_size) {
		/* allocate more space */
		int *new_data = new int[m_max_size * 2];
		/* copy ole data to new space */
		for (int i = 0; i < m_cur_size; i++)
			new_data[i] = m_data[i];
		/* free old space, set data pointer to new space */
		delete [] m_data;
		m_data = new_data;
		m_max_size *= 2;
	}
	m_data[m_cur_size] = n;
	m_cur_size++;
}

int CDarray::operator[](int idx) const
{
	if (idx >= m_cur_size)
		throw invalid_argument("too big index");
	return 0;
}

int & CDarray::operator [](int idx)
{
	if (idx >= m_cur_size)
		throw invalid_argument("too big index 2");
	return m_data[idx];
}


int main(void)
{
	int n;
	CDarray arr;

	cout << "dynamic array demo" << endl;

	while (cin >> n)
		arr.append(n);

	cout << arr << endl;
	arr[0] = 25;
	cout << "[0] has to be 25: " << arr << endl;
	cout << arr[100] << endl;
	return 0;
}
