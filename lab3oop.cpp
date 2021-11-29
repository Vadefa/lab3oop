//// создаем хранилище
//MyStorage storage();
//// добавляем в него объекты
//for (int i = 0; i < 10; i++)
//	storage.add(new SomeObject());
//// обращаемся поочередно ко всем
//for (storage.first(); !storage.eol(); storage.next())
//storage.getObject().someMethod();


#include <iostream>

using namespace std;

class Obj{									//The Abstract class
public:
	virtual void add(One& one) {

	}

	Obj() {
	}
	~Obj() {
	}
};


class One: public Obj{
private:
	char* str;
	int length;
public:
	void add() {
		printf("one->add");
	}

	One() {
		str = nullptr;
		length = 0;
	}
	One(const char* one) {
		this->length = strlen(one);

		this->str = new char[length + 1];

		for (int i = 0; i < length; i++)
			this->str[i] = one[i];

		this->str[length] = '\0';
	}
	~One() {
		delete[]str;
	}
};

class MyStorage {
private:
	Obj** storage;
public:
	int iter;
	int size;

	MyStorage() {
		int iter = 0;
		int size = 10;
		storage = new Obj * [size];
	}
	~MyStorage() {
		for (int i = 0; i < size; i++)
			delete storage[i];
		delete[] storage;
	}
};



int main()
{



	return 0;
}