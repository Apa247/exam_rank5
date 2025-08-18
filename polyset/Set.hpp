#pragma once
#include <iostream>
#include "SearchableBag.hpp"

class Set  {
	private:
		SearchableBag *bag;

	public:
		Set(SearchableBag* b) : bag(b) {}
		Set(const Set& other) : bag(other.bag) {}
		~Set() {}
		Set& operator=(const Set& other) {
			if (this != &other)
				bag = other.bag;
			return *this;
		}
		bool has(int value)const{
			return bag->has(value);
		}
		void insert(int value) {
			if (!bag->has(value))
				bag->insert(value);
		}
		void insert(int *values, int size) {
			for (int i = 0; i < size; i++)
				if (!bag->has(values[i]))
					bag->insert(values[i]);
		}
		void print() {
			bag->print();
		}
		void clear() {
			bag->clear();
		}
};
