#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);
class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	int get_integer()const { return integer; }
	int get_numerator() const { return numerator; }
	int get_denominator() const { return denominator; }

	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0) { denominator = 1; }
		this->denominator = denominator;
	}
	// Constructors;
	Fraction()
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		cout << "1ArgConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		numerator = 0;
		denominator = 1;
		cout << "1ArgConstructor:\t" << this << endl;
	}
	Fraction(double decimal)
	{
		decimal += 1e-10;
		integer = decimal;
		denominator = 1e+9;
		decimal -= integer;
		numerator = decimal * denominator;
		reduce();
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		set_numerator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(int integer , int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}

	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}
	//		Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	/*Fraction operator+(const Fraction& other)
	{
		Fraction result;
		int i,num,dnum;
		num = this->numerator + other.numerator;
		dnum = this->denominator * other.denominator;
		i = dnum / num;
		result.set_integer(this->integer+other.integer+i);
		result.set_numerator(dnum % num);
		result.set_denominator(dnum);
		return result;
	}*/
	//		Incremento/Decremento
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction& operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction& operator--()
	{
		integer--;
		return *this;
	}
	Fraction& operator--(int)
	{
		Fraction old = *this;
		integer--;
		return old;
	}

	//		Type-cast operators:
	explicit operator int()
	{
		return integer;
	}
	explicit operator double()
	{
		return integer + (double)numerator/denominator;
	}

	//		Methods:
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	Fraction& reduce()
	{
		int more, less, rest;
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		}while(rest);
		int GCD = more;
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	std::ostream& print(std::ostream& os ) const
	{
		if (integer) os << integer;
		if (numerator)
		{
			if (integer)os << "(";
			os << numerator << "/" << denominator;
			if (integer)os << ")";
		}
		else if (integer == 0)os << 0;
		//os << endl;
		return os;
	}
	
};

Fraction operator*( Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	/*Fraction product;
	product.set_numerator(left.get_numerator() * right.get_numerator());
	product.set_denominator(left.get_denominator() * right.get_denominator());
	return product;*/

	return Fraction 
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
	//Создается временый безымянный объект, исразу же возвращается на место вызова функции.
	//Временые безымянные объекты существуют лишь в пределах одного выражения.
}
Fraction operator/(const Fraction& left,const Fraction& right)
{
	return left * right.inverted();
}
Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator()*right.get_denominator()
	).to_proper().reduce();
}
Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator() - right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
////////////////////////////////////////////////////////
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return 
		left.get_numerator() * right.get_denominator() == 
		right.get_numerator() * left.get_denominator();
}
bool operator!= (const Fraction & left, const Fraction & right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}
bool operator >=(const Fraction& left, const Fraction& right)
{
	//return left > right || left == right;
	return !(left < right);
}
bool operator <=(const Fraction& left, const Fraction& right)
{
	//return left < right || left == right;
	return !(left > right);
}
std::istream& operator>> (std::istream& is, Fraction& obj)
{
	const int SIZE = 256;
	char buffer[SIZE];
	cin >> buffer;
	int n = 0;
	int numbers[3];
	char delimeters[] = "(/ )";
	for (char* pch = strtok(buffer, delimeters); pch; pch = strtok(NULL, delimeters))
		numbers[n++] = std::atoi(pch);
	//for (int i = 0; i < n; i++)cout << numbers[i] << "\t"; cout << endl;
	obj = Fraction();
	switch (n)
	{
	case 1:obj.set_integer(numbers[0]); break;
	case 2:
		obj.set_numerator(numbers[0]);
		obj.set_denominator(numbers[1]);
		break;
	case 3:
		obj.set_integer(numbers[0]);
		obj.set_numerator(numbers[1]);
		obj.set_denominator(numbers[2]);
	}
	return is;
}
//////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	return obj.print(os);
}
//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATOR_CHECK
//#define COMPARISON_OPERATORS_CHECK
// #define 
//#define TYPE_CONVERSIONS_1
//#define TYPE_CONVERSIONS_2
#define HOME_WORK
void main()
{
	setlocale(LC_ALL, "");
	
#ifdef CONSTRUCTORS_CHECK

 // CONSTRUCTORS_CHECK

	Fraction A;
	A.print();

	Fraction B = 5;
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;
	E.print();

	Fraction F;
	F = E;
	F.print();

	Fraction G = A + B;
	G.print(); 
#endif
#ifdef ARITHMETICAL_OPERATOR_CHECK
	Fraction A(1, 2, 3);
	Fraction B(2, 3, 4);
	A.print();
	B.print();

	Fraction C = B + A;
	C.print();
	C--;
	C.print();

	A += B;
	A.print();
	B.print();
#endif
#ifdef COMPARISON_OPERATORS_CHECK
	cout << (Fraction(1, 2) > Fraction(5, 11)) << endl; 
#endif
#ifdef STREAMS_CHECK
	Fraction A(2, 3, 4);
	cout << A << endl;
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl; 
#endif // STREAMS_CHECK
#ifdef TYPE_CONVERSIONS_1
	//(type)value;	//C-like notation (C-подобная форма записи)
//type(value);	//Functional notation (Функциональная форма записи)

	int a = 2;		//No conversions
	double b = 3;	//Conversion from less to more
	int c = b;		//Conversion from more to less without data loss
	int d = 5.5;	//Conversion from more to less with data loss  
#endif // TYPE_CONVERSIONS_1
#ifdef TYPE_CONVERSIONS_2
	//1) From other to class
//2) From class to other

/*
1) From other to class
	Single-Argument constructor
	Copy assignment
*/

	Fraction A = (Fraction)5;		//Conversion from 'int' to 'Fraction'
	cout << A << endl;


	Fraction B;
	B = Fraction(8, 11);
	cout << B << endl;

	/*
	2) From class to other

	type-cast operators

	operator type()
	{
		.......;
		conversion-code;
		.......;
		return value;
	}
	*/

	int a = (int)A;
	cout << a << endl;
#endif // TYPE_CONVERSIONS_2

#ifdef HOME_WORK
	//Fraction A(2, 3, 4);
	//double a = A;
	//cout << A << " = " << a << endl;

	Fraction B = 2.75;
	cout << B << endl;
#endif // HOME_WORK

}