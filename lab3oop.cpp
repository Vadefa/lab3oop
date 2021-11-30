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
	}
	virtual void name() {
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

	void name() {
		cout << "One" << endl;
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

class Boom : public Obj {
public:
	void someMethod() {
		int a = rand() % 3;
		if (a == 1)
			this->boom();
		else
			this->caboom();
	}
	void boom() {
		cout << "BOOM" << endl;
	}
	void caboom() {
		cout << "CABOOM" << endl;
	}

	void name() {
		cout << "Boom" << endl;
	}

	Boom() {
	}
	~Boom() {
	}
};

class Earth : public Obj {
public:
	void someMethod() {
		this->rotation();
	}
	void rotation() {
		cout << "Earth turned" << endl;
	}
	
	void name() {
		cout << "Earth" << endl;
	}

	Earth() {
	}
	~Earth(){
	}
};
class Continent : public Earth {
public:
	void someMethod() {
		this->print();
	}
	void print() {
		cout << "This is a continent" << endl;
	}

	void name() {
		cout << "Continent" << endl;
	}

	Continent() {
	}
	~Continent() {
	}
};

class MyStorage {
private:
	Obj** storage;
protected:
	int iter;
	int size;
	int count;
	int classes = 4;							//amount of different classes, whose objects we can fit there
public:
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

	void add() {
		Obj* object = nullptr;
		int a = rand() % classes + 1;
		switch (a) {
		case 1: {
			object = new One;
			break;
		}
		case 2: {
			object = new Boom;
			break;
		}
		case 3: {
			object = new Earth;
			break;
		}
		case 4: {
			object = new Continent;
			break;
		}
		}
		if (count < size)
			storage[iter] = object;
		else {
			sizeImprove();
			storage[size - 1] = object;
		}
		iter = iter + 1;
		count = count + 1;
	}
	void remove() {
		if ((count > 0) && (storage[iter] != nullptr)) {
			delete storage[iter];
			storage[iter] = nullptr;
			count = count - 1;
		}
	}
	bool eol() {
		if (iter == size) {
			iter = iter - 1;					// if we call storage[iter] now, then we'll go out of the storage limits
			return true;
		}
		else
			return false;
	}
	void first() {
		iter = 0;
	}
	void next() {
		iter = iter + 1;
	}
	void back() {
		if (iter > 0)
			iter = iter - 1;
		else
			cout << "It is the first object in the storage" << endl;
	}
	Obj* getObject() {
		return storage[iter];
	}

	MyStorage() {
		iter = 0;
		count = 0;
		size = 1;
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

void subMenu(MyStorage& storage)
{
	cout << "What do you want to do? (1 - add an object, 0 - remove an object) -> ";
	bool a;
	cin >> a;

	cout << "How much?" << endl;
	int n;
	cin >> n;

	if (a == true)
		for (int i = 0; i < n; i++)
			storage.add();
	else
		for (int i = 0; i < n; i++)
			storage.remove();

	cout << "Now we have those objects here:" << endl;
	for (storage.first(); !storage.eol(); storage.next())
		storage.getObject()->name();
}

void menu()
{
	MyStorage storage;

	cout << "How many objects do you want to add? -> ";
	int n = 0;
	cin >> n;

	if (n <= 0) {
		cout << "n should be a natural number." << endl;
		menu();
		return;
	}

	cout << "Starting work" << endl;
	double start = clock();										//clock() - uses <ctime> and returns time in milliseconds



	for (int i = 0; i < n; i++)
		storage.add();

	for (storage.first(); !storage.eol(); storage.next())
		storage.getObject()->someMethod();						//virtual methods work only with references



	double end = clock();
	cout << "Program working time equals " << (end - start)/1000 << " seconds" << endl;

	cout << "Do you want to add/remove some object? (1 - yes, 0 - no) -> ";
	bool a;
	cin >> a;
	if (a == true)
		subMenu(storage);
	else
		return;

}

int main()
{
	menu();

	cout << "Do you want to restart? (1 - yes, 0 - no) -> ";
	bool a;
	cin >> a;
	if (a == true)
		main();
	else
		return 0;

	return 0;
}