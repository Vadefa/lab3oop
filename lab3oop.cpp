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
	}
	~One() {
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
	void names() {
		cout << "\nWe have those objects in the storage" << endl;
		int tempiter = iter;
		for (iter = 0; iter < size; iter = iter + 1)
			if (storage[iter] != nullptr)
				storage[iter]->name();
			else
				cout << "null" << endl;
		iter = tempiter;
	}
	int getIter() {
		return iter;
	}

	Obj* withdraw() {
		Obj* object = storage[iter];
		storage[iter] = nullptr;
		return object;
	}

	void shift() {
		Obj** tempStorage = new Obj * [size - iter + 1];		// we putting an element after the storage[iter] element
		for (int i = iter + 1; i < size; i++)
			tempStorage[i - iter - 1] = storage[i];
			
		sizeImprove();
		storage[iter + 1] = nullptr;							// later we'll put a new element here

		for (int i = iter + 2; i < size; i++)
			storage[i] = tempStorage[i - iter - 2];

		delete[] tempStorage;
	}

	void sizeImprove() {
		Obj** tempStorage = new Obj*[size];
		for (int i = 0; i < size; i++)
			tempStorage[i] = storage[i];

		size = size + 1;
		delete[] storage;

		storage = new Obj * [size];
		for (int i = 0; i < size - 1; i++)
			storage[i] = tempStorage[i];
		storage[size - 1] = nullptr;

		delete[] tempStorage;
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
		if (iter < size) {
			if (storage[iter] == nullptr) {
				storage[iter] = object;
				iter = iter + 1;
			}
			else {
				shift();
				iter = iter + 1;
				storage[iter] = object;
			}
		}
		else if (iter == size){
			sizeImprove();
			storage[iter] = object;
			iter = iter + 1;
		}
		count = count + 1;
	}
	void remove() {
		if ((count > 0) && (storage[iter] != nullptr) && (iter < size)) {
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
		if (iter < size)
			iter = iter + 1;
	}
	void back() {
		if (iter > 0)
			iter = iter - 1;
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

void proceed(MyStorage& storage) {
	cout << "You are now at the " << storage.getIter() << " element. Type, where should we proceed to" << endl
		<< "(-2 - go to the 2nd element upstairs, +2 - go to the 2nd elements downstairs, 0 - current element) -> "; int a;
	cin >> a;
	if (a > 0)
		for (int i = a; i > 0; i = i - 1)
			storage.next();
	else
		for (int i = a; i < 0; i = i + 1)
			storage.back();
	cout << "Now you are at the " << storage.getIter() << " element." << endl;
}
bool ask() {

	return true;
}

void subMenu(MyStorage& storage)
{
	storage.names();

	cout << "\nWhat do you want to do? \n1 - add objects\n2 - remove objects\n3 - call a method of an object\n4 - withdraw an object\n ==> ";
	short a;
	cin >> a;

	proceed(storage);						// asking, to what element should we proceed

	switch (a) {
	case 1: {
		cout << "How much objects shoud we add?" << endl;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			storage.add();
		storage.names();
		break;
	}
	case 2: {
		cout << "How much objects shoud we delete?" << endl;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			storage.remove();
			storage.next();
		}
		storage.names();
		break;
	}
	case 3: {
		if (storage.getObject() != nullptr)
			storage.getObject()->someMethod();
		else
			cout << "This element of the storage is empty" << endl;
		break;
	}
	case 4: {
		Obj* object = storage.withdraw();
		cout << "We withdrawed this object and gave it to pointer variable. This object has name ";
		object->name();
		delete object;
		break;
	}
	default:
		cout << "You should have typed a number 1, 2 or 3" << endl;
		subMenu(storage);
		return;
	}

	cout << "Do you want to do something else with the current storage?(1 - yes, 0 - no) -> ";
	cin >> a;
	if (a == 1)
		subMenu(storage);
	else
		return;
	
	return;
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

	cout << "Do you want to work with the current storage? (1 - yes, 0 - no) -> ";
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