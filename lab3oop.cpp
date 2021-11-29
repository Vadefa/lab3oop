//// создаем хранилище
//MyStorage storage();
//// добавляем в него объекты
//for (int i = 0; i < 10; i++)
//	storage.add(new SomeObject());
//// обращаемся поочередно ко всем
//for (storage.first(); !storage.eol(); storage.next())
//storage.getObject().someMethod();


#include <iostream>
#include <ctime>

using namespace std;

//The Abstract class:
class Obj {
public:
	virtual void someMethod() {
		this->someMethod();
	}

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
	void someMethod() {
		int a = rand() % 3;
		if (a == 1)
			this->numbers();
		else
			this->words();
	}
	void numbers() {
		cout << "11111" << endl;
	}
	void words() {
		cout << "one one one" << endl;
	}
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

	Obj getObject(int iter) {
		iter = rand() % count + 1;
		return *storage[iter];
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
	srand(time(NULL));

	MyStorage storage;
	for (int i = 0; i < 5; i++)
		storage.add(new One("11111"));

	for (int i = 0; i < 5; i++)
		storage.getObject(i).someMethod();

	return 0;
}