#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Polynom
{
	vector<double> coefs;

public:
	Polynom()
	{	
	}
	Polynom(const vector<double>& initCoefs)
	{
		coefs = initCoefs;
	}
	Polynom(const Polynom& polynom)
	{
		*this = polynom;
	}
	~Polynom()
	{
		coefs.clear();
	}

	double getCoef(size_t rank)
	{
		if (rank < coefs.size()) return coefs[rank];
		else return 0;
	}

	Polynom& operator= (const Polynom& polynom)
	{
		coefs = polynom.coefs;
		return *this;
	}

	bool operator== (const Polynom& polynom)
	{
		if (coefs.size() < polynom.coefs.size())
		{
			for (size_t i = 0; i < coefs.size(); i++){
				if (coefs[i] != polynom.coefs[i]) return false;
			}
			for (size_t i = coefs.size(); i < polynom.coefs.size(); i++){
				if (polynom.coefs[i] != 0) return false;
			}
		}
		else
		{
			for (size_t i = 0; i < polynom.coefs.size(); i++){
				if (coefs[i] != polynom.coefs[i]) return false;
			}
			for (size_t i = polynom.coefs.size(); i < coefs.size(); i++){
				if (polynom.coefs[i] != 0) return false;
			}
		}
		return true;
	}
	bool operator!= (const Polynom& polynom)
	{
		return !(*this == polynom);
	}

	Polynom& operator+ (Polynom& polynom) 
	{
		Polynom* result = new Polynom();
		
		size_t length = coefs.size() > polynom.coefs.size() ? coefs.size() : polynom.coefs.size();
		for (size_t i = 0; i < length; i++)
		{
			result->coefs.push_back(getCoef(i) + polynom.getCoef(i));
		}
		return *result;
	}
	Polynom& operator- () 
	{
		Polynom* result = new Polynom();
		for (double coef : coefs)
		{
			result->coefs.push_back(-coef);
		}
		return *result;
	}
	Polynom& operator- (Polynom& polynom) {
		return *(new Polynom(-polynom + *this));
	}
	
	Polynom& operator+= (Polynom& polynom) {
		*this = *this + polynom;
		return *this;
	}
	Polynom& operator-= (Polynom& polynom) {
		*this = *this - polynom;
		return *this;
	}

	Polynom& operator* (const double& value) {
		Polynom* result = new Polynom();
		for (double coef : coefs)
		{
			result->coefs.push_back(coef * value);
		}
		return *result;
	}
	Polynom& operator/ (const double& value) {
		Polynom* result = new Polynom();
		for (double coef : coefs)
		{
			result->coefs.push_back(coef / value);
		}
		return *result;
	}
	Polynom& operator*= (const double& value) {
		*this = *this * value;
		return *this;
	}
	Polynom& operator/= (const double& value) {
		*this = *this / value;
		return *this;
	}

	friend ostream& operator<< (ostream& os,Polynom& p);
	friend istream& operator>> (istream& os, Polynom& p);
};

ostream& operator<< (ostream& stream, Polynom& polynom) 
{
	for (int i = polynom.coefs.size() - 1; i >= 0 ; i--)
	{
		if (polynom.coefs[i] != 0)
		{
			if( i == 0 || polynom.coefs[i] != 1) cout << polynom.coefs[i];
			if (i > 1) cout << "x^" << i;
			else if (i == 1) cout << "x";
			cout << " ";
		}
	}
	return stream;
}
istream& operator>> (istream& stream, Polynom& polynom)
{
	polynom.coefs.clear();
	double value;
	int coefNumber;
	cout << "Enter the number of coefficients: ";
	cin >> coefNumber;
	cout << "Enter polynom starting from the lowest coefficient: ";
	for (int i = 0; i < coefNumber; i++)
	{
		cin >> value;
		polynom.coefs.push_back(value);
	}
	return stream;
}

int main()
{
	Polynom a(vector<double>({ 3, 4, 5 }));
	cout << a << endl;
	Polynom b = a;
	cin >> a;
	cout << endl << b - a;

}