#include <iostream>
using namespace std;

class String
{
	int size;
	char* str;
public:
	int get_size() const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}
	//		Constructors
	explicit String(int size = 80) :size(size), str(new char[size] {})
	{
		//this->size = size;
		//this->str = new char[size] {};
		cout << "DefaultConstrructor:\t" << this << endl;
	}
	String(const char* str) :String(strlen(str)+1)
	{
		//this->size = strlen(str)+1;
		//this->str = new char[size] {};
		for (int i = 0; str[i]; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other):String(other.str)
	{
		//this->size = other.size;
		//this->str = new char[size] {};
		//for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConsructor:\t" << this << endl;
	}
	String(String&& other):size(other.size),str(other.str)
	{
		//Shallow copy
		//this->size = other.size;
		//this->str = other.str;
		other.str = nullptr;
		other.size = 0;
		cout << "MoveConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[]str;
		cout << "Destructor:\t\t" << this << endl;
	}
	//		Operators
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	String& operator=(String&& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	char operator[](int i) const
	{
		return str[i];
	}
	char& operator[](int i) 
	{
		return str[i];
	}

	//		Methods:
	void print() const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
String operator+(const String& left, const String& right)
{
	String cat (left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		cat[i] = left[i];
	//cat.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		cat[i + left.get_size()-1] = right[i];
	//cat.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return cat;
}
//#define CONSTRUCTOR_CHECK
#define OPERATOR_PLUS_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTOR_CHECK
	String str;				//Default constructor
	str.print();

	String str1 = "Hello";	//Single-argument constructor
	//str1.print();
	cout << str1 << endl;

	String str2 = str1;		//Copy constructor
	cout << str2 << endl;

	String str3 ;
	str3 = str2;			//Copy assignment
	cout << str3 << endl; 
#endif // CONSTRUCTOR_CHECK
#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "Wold";
	str1 = str1;
	cout << str1 << endl;
	cout << str2 << endl;

	String str3;
	str3 = str1 + str2;
	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK
	String str1 = "Deligation";
	cout << "\n---------------\n";
	String str2 = str1;
	cout << "\n---------------\n";
	cout << str2 << endl;

}