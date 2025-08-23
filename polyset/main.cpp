#include "SearchableBag.hpp"
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "Set.hpp"


#include <iostream>

int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;
	SearchableBag *t = new SearchableTreeBag;
	SearchableBag *a = new SearchableArrayBag;

	for (int i = 1; i < argc; i++) {
		t->insert(atoi(argv[i]));
		a->insert(atoi(argv[i]));
	}
	t->print();
	a->print();

	for (int i = 1; i < argc; i++)
	{
		std::cout << t->has(atoi(argv[i])) << std::endl;
		std::cout << a->has(atoi(argv[i])) << std::endl;
		std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
		std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
	}

	t->clear();
	a->clear();

	const SearchableArrayBag tmp(static_cast<SearchableArrayBag &>(*a));
	tmp.print();
	tmp.has(1);

	Set sa(*a);
	Set st(*t);
    int arr[] = {1, 2, 3, 4};
	for (int i = 1; i < argc; i++)
	{
		st.insert(atoi(argv[i]));
		sa.insert(atoi(argv[i]));

		sa.has(atoi(argv[i]));
		sa.print();
		sa.get_bag().print();
		st.print();
		sa.clear();
		sa.insert(arr, 4);
		std::cout << std::endl;
	}

	return (0);
}
