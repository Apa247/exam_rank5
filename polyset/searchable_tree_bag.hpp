#pragma once
#include <iostream>
#include "TreeBag.hpp"
#include "SearchableBag.hpp"

class SearchableTreeBag :  public TreeBag, public SearchableBag {
	public:
	SearchableTreeBag() : TreeBag() {}
	SearchableTreeBag(const SearchableTreeBag& other) : TreeBag(other) {}
	~SearchableTreeBag() {}
	SearchableTreeBag& operator=(const SearchableTreeBag& other) {
		if (this != &other)
			TreeBag::operator=(other);
		return *this;
	}
	virtual bool has(int value) const{
		Node *current = root;
		while (current) {
			if (current->value == value)
				return true;
			else if (value < current->value)
				current = current->left;
			else
				current = current->right;
		}
		return false;
	}
};