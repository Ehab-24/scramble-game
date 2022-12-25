#pragma once

#include<iostream>
#include<fstream>

template<typename T>
class StretchyArray {

public:

	StretchyArray(int size = 0) : _size(size), capacity(size ? size * 2 : 8) {
		this->Vs = new T[capacity];
	}

	int size() const {
		return this->_size;
	}

	bool isempty()const {

		if (_size == 0)
			return true;
		return false;
	}

	int search(T val)const {

		if (this->isempty())
			return -2;

		for (int i = 0; i < _size; i++)
			if (Vs[i] == val)
				return i;
		return -1;
	}

	void add(T val) {

		if (_size == capacity)
		{
			this->stretch();
		}

		int i = 0;
		while (i < _size && Vs[i] < val)
			++i;

		for (int si = _size; si > i; si--)
			Vs[si] = Vs[si - 1];

		Vs[i] = val;
		++_size;

		return;
	}

	void push_back(T val) {

		if (_size == capacity) {
			this->stretch();
		}

		Vs[_size] = val;
		_size++;
	}

	void erase(T val) {

		if (this->isempty())
		{
			std::cout << "Array is empty.\n";
			return;
		}

		int index = search(val);

		if (index == -1)
		{
			std::cout << "Element not found!";
			return;
		}

		for (int i = index; i + 1 < _size; i++)
			Vs[i] = Vs[i + 1];

		--_size;

		return;
	}

	friend std::ostream& operator<<(std::ostream&, const StretchyArray<T>& arr) {

		if (arr.isempty())
		{
			std::cout << "Array is empty";
			return std::cout;
		}

		for (int i = 0; i < arr.size(); i++)
			std::cout << arr.Vs[i] << " ";
		std::cout << "\n";

		return std::cout;
	}

	T& operator[](int i) {
		return this->Vs[i];
	}
	T operator[](int i) const {
		return this->Vs[i];
	}

private:
	T* Vs{ nullptr };
	int _size{};
	int capacity;

	void stretch() {

		this->capacity *= 2;

		T* temp = this->Vs;

		this->Vs = new T[this->capacity];

		for (int i = 0; i < this->_size; i++) {
			this->Vs[i] = temp[i];
		}

		delete[]temp;
	}
};