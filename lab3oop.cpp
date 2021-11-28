#include <iostream>

using namespace std;

class MyStorage {
private:
	MyStorage* storage;
protected:
	int iter;
	int size;
public:
	void sizeImprove() {
		MyStorage newStorage;								//we made it static so it'll automatically delete
		int newsize = this->size + 1;
		newStorage = new MyStorage[newsize];
		for (int i = 0; i < this->size; i++)
			newStorage.storage[i] = this->storage[i];

		delete[] this->storage;
		this->size = size + 1;
		storage = new MyStorage[size];
		for (int i = 0; i < this->size; i++)
			this->storage[i] = newStorage.storage[i];
		
	}

	void add(One one) {
		this->sizeImprove();
		this->storage[this->size] = one;
	}

	MyStorage() {
		storage = nullptr;
		iter = 0;
		size = 0;
	}
	MyStorage(int iter, int size) {
		this->iter = 0;
		this->size = size;
		storage = new MyStorage[size];
	}
	MyStorage(MyStorage* storage) {
		this->size = storage->size;

		this->storage = new MyStorage[size];

		for (int i = 0; i < storage->size; i++)
			this->storage[i] = storage[i];
	}
	virtual ~MyStorage() {
		delete[]storage;
	}
};

class One :public MyStorage {
private:
	char* str;
	int length;
public:
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

int main()
{
	MyStorage* storage;

	One one("11111");

	storage->add(&one);

	return 0;
}