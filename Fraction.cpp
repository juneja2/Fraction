#include <iostream>
#include <cstdlib>
using namespace std;

class Fraction {
public:
	Fraction(); // These are constructors
	Fraction(int n, int d); // They are overloaded.
	Fraction(int n, int d, int w);
	Fraction(const Fraction & f);
	~Fraction();
	Fraction operator+(const Fraction& f)const;
	bool operator==(const Fraction& f)const;
	bool operator!=(const Fraction &f)const;
	Fraction operator*(const Fraction& f)const;
	const Fraction& operator=(const Fraction& f);
	void operator+=(const Fraction&f);

	friend ostream & operator<<(ostream& out, const Fraction &f);
	friend istream & operator>>(istream& in, Fraction &f);

	void setNumerator(int n); // Mutator functions start here
	void setDenominator(int d);
	void setWhole(int w);// and end here

	int	 getNumerator()const; // Accessor functions start here
	int  getDenominator()const;
	int  getWhole()const;

	void printFraction()const; // and end here
private:
	int numerator;
	int denominator;
	int whole;
};

void settingN_And_D(int &n, int &d); // user defined not a class function

int main() {
	int n, d, choice;
	n = d = choice = 0;
	do {
		cout << "Any negative number will be made positive\n"
			"What constructor you want to call"
			" default, two parameters, three parameters.\n"
			"Enter 1, 2 or 3 for invoking constructors in their respective order or"
			" Enter 4 to terminate the loop\n";
		cin >> choice;
		Fraction *object;
		switch (choice) {
		case 4:
			break;
		case 1:
			object = new(nothrow) Fraction;
			if (object == nullptr) {
				cout << "Wasn't able to allocate memory for the object\n";
				exit(EXIT_FAILURE);
			}
			cout << "For object with default constructor "
				<< " before setting the numerator and denominator they are equal to "
				<< object->getNumerator() << ", " << object->getDenominator() << "\n";
			cout << "Whole was set to " << object->getWhole() << endl;
			object->printFraction();
			delete object;
			break;
		case 2:
			settingN_And_D(n, d);

			object = new(nothrow) Fraction(n, d);
			if (object == nullptr) {
				cout << "Wasn't able to allocate memory for the object\n";
				exit(EXIT_FAILURE);
			}

			cout << "After invoking the 2 parameter constructor of object\n";
			object->printFraction();
			delete object;
			break;
		case 3:
			settingN_And_D(n, d);
			int w;
			cout << "What do you want the whole part to be ";
			cin >> w;

			object = new(nothrow) Fraction(n, d, w);
			if (object == nullptr) {
				cout << "Wasn't able to allocate memory for the object\n";
				exit(EXIT_FAILURE);
			}

			cout << "After invoking the 3 parameter constructor of object\n";
			object->printFraction();
			delete object;
			break;
		default:
			cout << "Invalid Input\n";
		}
	} while (choice != 4);

	cout << "Any negative number will be made positive" << endl;
	settingN_And_D(n, d);
	cout << "What do you want the whole part to be ";
	int w;
	cin >> w;
	Fraction *object = new(nothrow) Fraction(n, d, w);
	if (object == nullptr) {
		cout << "Wasn't able to allocate memory outside do while for object\n";
		exit(EXIT_FAILURE);
	}
	Fraction *object2 = new(nothrow) Fraction;
	
	if (object2 == nullptr) {
		cout << "Wasn't able to allocate memory for the object\n";
		exit(EXIT_FAILURE);
	}
	else cout << "Creating new object" << endl;

	*object2 = *object;
	cout << "After using overloaded assignment(*object2 = *object) operator\nObject2 ";
	object2->printFraction();

	cout << "Object ";
	object->printFraction();

	cout << " After adding two fractions(*object2 + *object) Object0 ";
	Fraction object0 = (*object2 + *object);
	object0.printFraction();

	cout << "After multiplying((*object2)*(*object)) 2 fractions Object0";
	object0 = ((*object2) * (*object));
	object0.printFraction();

	cout << "Using cin and cout to input and print the object0" << endl;
	cin >> object0;
	cout << object0;
	cout << "Using overloaded equality operator == on object0" << endl;
	
	cout << "Object 0 == *object returns " << (object0 == *object) << endl;

	object0 = *object2 = *object;
	cout << "Object0 " << object0 << "*Object2" << *object2;
	cout << "Object 0 != *object2 returns " << (object0 != *object2) << endl;

	object0 += *object2;
	cout << "Object0 " << object0;

	delete object;
	delete object2;
	object = object2 = nullptr;

	return 0;
}
Fraction::Fraction() {
	denominator = 1;
	numerator = whole = 0;
}
Fraction::Fraction(int n, int d) {
	setNumerator(n);
	setDenominator(d);
	whole = 0;
}
Fraction::Fraction(int n, int d, int w) {
	setNumerator(n);
	setDenominator(d);
	setWhole(w);
}
void Fraction::setNumerator(int n) {
	if (n >= 0)numerator = n;
	else {
		numerator = -n;
	}
}
void Fraction::setDenominator(int d) {
	if (d == 0) {
		denominator = 1;
		cout << "Denominator can't be 0. So, it is set to 1\n";
	}
	else if (d < 0) {
		denominator = -d;
	}
	else denominator = d;
}
void Fraction::setWhole(int w) {
	if (w < 0) {
		whole = -w;
	}
	else whole = w;
}
int Fraction::getNumerator()const {
	return numerator;
}
int Fraction::getDenominator()const {
	return denominator;
}
int Fraction::getWhole()const {
	return whole;
}
Fraction::Fraction(const Fraction& f) {
	whole = f.whole;
	denominator = f.denominator;
	numerator = f.numerator;
}
Fraction::~Fraction() {
	whole = numerator = 0;
	denominator = 1;
}
Fraction Fraction::operator+(const Fraction& f) const{
	Fraction temp;
	temp.denominator = denominator * f.denominator;
	temp.numerator = ((whole * denominator) + numerator)* f.denominator + ((f.whole * f.denominator) + f.numerator)*denominator;
	return temp;
}
bool Fraction::operator==(const Fraction& f) const{
	int n, n1;
	n = ((whole * denominator) + numerator)*f.denominator;
	n1 = ((f.whole * f.denominator) + f.numerator)*denominator;
	return n == n1;
}
bool Fraction::operator!=(const Fraction &f)const {
	int n, n1;
	n = ((whole * denominator) + numerator)*f.denominator;
	n1 = ((f.whole * f.denominator) + f.numerator)*denominator;
	return(n != n1);
}
Fraction Fraction::operator*(const Fraction& f)const {
	Fraction temp;
	temp.denominator = denominator * f.denominator;
	temp.numerator = ((whole * denominator) + numerator)*((f.whole * f.denominator) + f.numerator);
	temp.whole = 0;
	return temp;
}
const Fraction& Fraction::operator=(const Fraction& f) {
	if(this != &f){
	whole = f.whole;
	denominator = f.denominator;
	numerator = f.numerator;
	}
	return *this;
}
void Fraction::operator+=(const Fraction&f) {
	numerator = whole * denominator + numerator;
	whole = 0; // denominator will remain the same just changed it into improper Fraction
	int n = f.whole * f.denominator + f.numerator;
	numerator = numerator * f.denominator + n * denominator;
	denominator *= f.denominator;
	//whole was set to zero by the constructor
}
ostream& operator<<(ostream& out, const Fraction &f) {
	if (f.whole == 0)
		out << "Fraction = " << f.numerator << "/" << f.denominator << endl;
	else
		out << "Fraction = " << f.whole << " " << f.numerator << "/" << f.denominator << endl;
	return out;
}
istream& operator>>(istream& in, Fraction &f) {
	cout << "Please enter whole ";
	in >> f.whole;
	if (f.whole < 0)
		f.whole = -f.whole;
	cout << "Please enter numerator ";
	in >> f.numerator;
	if (f.numerator < 0)
		f.numerator = -f.numerator;
	cout << "Please enter denominator ";
	in >> f.denominator;
	if (f.denominator < 0)
		f.denominator = -f.denominator;
	else if (f.denominator == 0) {
		f.denominator = 1;
		cout << "Denominator can't be 0. So it is set to 1\n";
	}
	return in;
}
void Fraction::printFraction()const {
	if (getWhole() == 0)
		cout << "Fraction " << getNumerator() << "/" << getDenominator() << endl << endl;
	else
		cout << "Fraction " << getWhole() << " " << getNumerator() << "/" << getDenominator() << endl << endl;
}
void settingN_And_D(int &n, int &d) {// Not a class function
	cout << "What do you want to set the numerator of object to be ";
	cin >> n;
	cout << "What do you want to set the denominator of object to be ";
	cin >> d;
}