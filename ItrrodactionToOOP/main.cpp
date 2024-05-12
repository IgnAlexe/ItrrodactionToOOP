#include<iostream>
using namespace std;

class Point
{
	double x;
	double y;
public:
	double get_x() const { return x; }
	double get_y() const { return y; }
	
	void set_x(double x)  { this->x = x;}
	void set_y(double y)  { this->y = y;}
	//   Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "Constructor:\t" << this << endl;
	}*/
	/*Point(double x)
	{
		this->x = x;
		this->y = 0;
		cout << "SingleArgumentConstructor:\t" << this <<  endl;
	}*/
	Point(double x=0, double y=0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyContructor\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//	Operators:
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment" << this << endl;
		return *this;
	}
	Point& operator++() //prefix increment
	{
		x++;
		y++;
		return *this;
	}
	Point operator++(int) //Suffix increment
	{
		Point old = *this;
		x++;
		y++;
		return old;
	}
	
	//   Methods
	double distance(const Point& other) const
	{
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
		return distance;
	}
	void print() const
	{
		cout << "X = " << x << "\tY = " << y << endl;
	}
};

double distance(const Point& A, const Point& B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
	return distance;
}
Point operator+(const Point& left, Point& right)
{
	Point result;
	result.set_x(left.get_x() + right.get_x());
	result.set_y(left.get_y() + right.get_y());
	return result;
}
bool operator==(const Point& left, const Point& right)
{
	//if (left.get_x() == right.get_x() && left.get_y() == right.get_y())
		//return true;
	//else 
		//return false;
	return (left.get_x() == right.get_x() && left.get_y() == right.get_y());
}
std::ostream& operator<<(std::ostream& os, const Point& obj)
{
	return os << "X = " << obj.get_x() << "\tY = " << obj.get_y();
	
}
std::ostream& operator>>(std::ostream& os, const Point& obj)
{

}

//#define STRUCT_POINT
//#define DISTANCE_CHECK
//#define CUNSTRUCTOR_CHECK
//#define ASSIGNMENT_CHECK
//#define OPERATORS_CHECK
void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	Point A;		//Объявление переменной А типа Поинт
					//Создание объекта А структуры Поинт
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;

	Point B;
	B.set_x(7);
	B.set_y(8);
	cout << B.get_x() << "\t" << B.get_y() << endl;

	cout << "Растояние от точки 'A' до точки 'B'=" << A.distance(B) << endl;
	cout << "Растояние от точки 'B' до точки 'A'=" << B.distance(A) << endl;
	cout << "Растояние между точками 'A' и 'B'= " << distance(A, B) << endl;
	cout << "Растояние между точками 'B' и 'A'= " << distance(B, A) << endl;
#endif 

#ifdef CUNSTRUCTOR_CHECK
	Point A;
	A.print();

	Point B = 5;
	B.print();

	Point C(2, 3);
	C.print();

	Point D = C;
	D.print(); 
#endif // CUNSTRUCTOR_CHECK

#ifdef ASSIGNMENT_CHECK
	//Point A(2, 3);
	//Point B;
	//B = A;
	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << "\t" << endl;

	Point A, B, C;
	A = B = C = Point(2, 3);
	A.print();
	B.print();
	C.print();
	/*
	A = B = C = Point(2, 3); Явно вызывается конструктор, и создается временныйй безымянный объект
	*/
#endif

#ifdef OPERATORS_CHECK
	Point A(2, 3);
	Point B(7, 8);
	Point C = A + B;
	A.print();
	B.print();
	C.print();
	Point D=C++;
	C.print();
	D.print();

	cout << (C == D) << endl;
#endif // OPERATORS_CHECK

	Point A(2, 3);
	cout << ""; cin >> A;
	cout << A<< endl;
}
/*
-------------------------------------------------------
.  - оператор прямого доступа, используется для обращения к полям  объекта по имени объекта;
-> - оператор косвенного доступа, используется для обращения к полям объекта по адресу объекта;
-------------------------------------------------------
*/
/*
-------------------------------------------------------
1. Incapsulation - это сокрытие пределенной части класса от внешнего мира;
	private:	закрытые поля, доступны только внутри класса;
	public:		открытые поля, доступнык в любом месте программы;
	protected:	защищенные поля, доступные внутри класса, и его дочерних классов;

	get/set - методы

2. Inheritance;
3. Polymorphism;
-------------------------------------------------------
*/
/*
-------------------------------------------------------
1. Constructor; - Это метот, который создает объект;
	- С параметрами;
	-Без параметров;
	-По умолчанию (Default Constructor) - это конструктор, который может быть вызван без параметров;
	-Конструктор копирования (Deep copy);
	-Конструктор переноса;
2. ~Destructor; - это метод, который уничтожает объект по истечению его времени жизни;
3. Assignment operator (CopyAssignment);
-------------------------------------------------------
*/
/*
-------------------------------------------------------
						OPERATORS OVERLOADING RULES
1.Перегружать можно только существующие операторы.
	'+'- перегружаются
	'++'- перегружается
	'%' - перегружается
	'%%'- Не перегружается
2. Не все существующие операторы можно перегрузить.
	Не перегружаются:
	/: -Conditional Ternary Operator;
	:: -Scope operator (Оператор разрешения видимости)
	. - Point operator (Оператор прямого доступа)
	.* - Pointer to member selection;
	# - Preprocessor convert to string;
	## - Preprocessor concatenate;
3. Пегруженные операторы сохраняют приоретет;
4. Переопределить поведение операторов над встроеными типами данных невозможно;
-------------------------------------------------------
type operator@ (parameters)
{
	......;
	group-of-statements;
	......;
}
-------------------------------------------------------*/