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

	Obj() {
	}
	virtual ~Obj() {
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
	int count;

	void sizeImprove() {
		Obj** tempStorage = new Obj*[size];
		for (int i = 0; i < size; i++)
			tempStorage[i] = storage[i];

		size = size + 1;

		storage = new Obj * [size];
		for (int i = 0; i < size - 1; i++)
			storage[i] = tempStorage[i];
		storage[size - 1] = nullptr;
	}

	void add(Obj *object) {
		count = count + 1;
		if (count <= size)
			storage[iter] = object;
		else {
			sizeImprove();
			storage[size - 1] = object;
		}
		iter = iter + 1;
	}

	MyStorage() {
		iter = 0;
		count = 0;
		size = 2;
		storage = new Obj * [size];
		for (int i = 0; i < size; i++)
			storage[i] = nullptr;
	}
	~MyStorage() {
		for (int i = 0; i < size; i++)
			delete storage[i];
		delete[] storage;
	}
};



int main()
{
	MyStorage storage;
	for (int i = 0; i < 5; i++)
		storage.add(new One);

	return 0;
}