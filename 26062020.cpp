#include <iostream>
using namespace std;
template <class T, class U>
class Test
{
	T a;
	U b;
public:
	Test() : a(0), b(0) {} // нструтор без параметрів
	Test(T A, U B) : a(A), b(B) {} // конструктор з параметрами
	//геттери
	T getA()const;
	U getB()const;
	//вивід
	void Print()const; // константні обєкти можуть викликати лише константні методи
	Test <T, U> operator + (const Test <T, U>& ob); // оператор додавання обєкт + обєкт 
	Test <T, U> operator + (int ob); // оператор додавання обєкт + число
	template<class X, class Y>
	friend Test <X, Y> operator + (int n, Test <X, Y>& ob); // оператор додавання число + обєкт
	template<class X, class Y>
	friend ostream& operator << (ostream& os, const Test <X, Y>& Ob); // перегрузка оператора << 
	template<class X, class Y>
	auto operator + (Test <X, Y>& ob);
	template<class X, class Y>
	Test <T, U>  operator = (const Test<X, Y>& ob);
};
template<class T, class U>
T Test<T, U>::getA() const
{
	return a;
}
template<class T, class U>
U Test<T, U>::getB() const
{
	return  b;
}
template<class T, class U>
void Test<T, U>::Print() const
{
	cout << "a = " << a << ", b = " << b << endl;
}
template<class T, class U>
Test<T, U> Test<T, U>::operator+(const Test<T, U>& ob)
{
	return Test<T, U>(a + ob.a, b + ob.b);
}
template<class T, class U>
Test<T, U> Test<T, U>::operator+(int ob)
{
	return Test<T, U>(a + ob, b + ob);
}
template<class X, class Y>
Test <X, Y> operator + (int n, Test <X, Y>& ob) // оператор додавання число + обєкт
{
	return ob + n;
}
template<class X, class Y>
ostream& operator << (ostream& os, const Test <X, Y>& Ob) // оператор додавання число + обєкт
{
	os << Ob.a << "\t" << Ob.b << endl;
	return os;
}
template<class T, class U>
template<class X, class Y>
auto Test <T, U> :: operator + (Test <X, Y>& ob)
{
	auto k = a + ob.getA();
	auto m = b + ob.getB();
	return Test <decltype(k), decltype (m)>(k, m);
}
template<class T, class U>
template<class X, class Y>
Test <T, U> Test<T, U>::operator = (const Test<X, Y>& ob)
{
	if (this != (Test<T, U>*) & ob) {
		a = (T)ob.getA();
		b = (U)ob.getB();
	}
	return *this;
}

int main()
{
	Test <int, int> Ob1(3, 5);
	Ob1.Print();
	Test<int, int> Ob2(4, 5), R;
	cout << "Ob1 + Ob2" << endl;
	R = Ob1 + Ob2;
	R.Print();
	cout << "Ob1 + 10" << endl;
	R = Ob1 + 10;
	R.Print();
	cout << "10 + Ob1" << endl;
	R = 10 + Ob1;
	R.Print();
	cout << R;
	Test<double, double> dO(10.9, 3.9);
	cout << dO << endl;
	cout << Ob1 + dO;
	cout << dO + Ob1;
	R = Ob1 + dO;
	cout << R;
	R = R;
}