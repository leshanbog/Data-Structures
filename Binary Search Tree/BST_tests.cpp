#include "Binary Search Tree Implementation.h"
#include <cassert>

using namespace binary_search_tree;


int main()
{
	
		BST<int> t;
		t.insert(5);
		t.insert(10);
		t.insert(15);
		t.insert(13);
		t.insert(-20);
		t.insert(-2);

		assert(t.find(5));
		assert(t.find(-20));
		assert(t.find(-2));
		assert(t.find(15));
		assert(!t.find(12));

		assert(t.isBST());

		assert(t.getHeight() == 4);

		assert(!t.empty());

		assert(t.getMax() == 15);
		assert(t.getMin() == -20);

		assert(t.getSize() == 6);

		std::vector<int> actual = t.getPreOrder(); 
		std::vector<int> expected = { 5, -20, -2, 10, 15, 13 };
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		actual = t.getInOrder();
		expected = { -20, -2, 5, 10, 13, 15 };
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		actual = t.getPostOrder();
		expected = { -2, -20, 13, 15, 10, 5 };
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		t.remove(-20);
		assert(!t.find(-20));
		assert(t.isBST());

		actual = t.getPreOrder(); 
		expected = { 5, -2, 10, 15, 13  };
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		actual = t.getInOrder();
		expected = { -2, 5, 10, 13, 15 };
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		actual = t.getPostOrder();
		expected = { -2, 13, 15, 10, 5 };
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		assert(t.getSize() == 5);
		t.insert(6);
		assert(t.getSize() == 6);
		assert(t.isBST());
		t.remove(13);
		assert(t.getSize() == 5);
		assert(t.isBST());
		t.remove(10);
		assert(t.getSize() == 4);
		assert(t.isBST());
		

	
		assert(t.getHeight() == 3);


		actual = t.getPreOrder();
		expected = { 5, -2 , 15, 6 };
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		actual = t.getInOrder();
		expected = { -2, 5 , 6, 15 };
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		actual = t.getPostOrder();
		expected = { -2, 6, 15, 5};
		assert(expected.size() == actual.size());
		for (int i = 0; i < expected.size(); ++i)
			assert(expected[i] == actual[i]);

		t.clear();
		assert(t.isBST());
		assert(t.getSize() == 0);
		assert(t.getHeight() == 0);
		assert(t.empty());

	std::cout << "seems good";
	return 0;
}
