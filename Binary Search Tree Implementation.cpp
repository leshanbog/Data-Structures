#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


namespace binary_search_tree
{

template <class ValueType> struct Node
{
	ValueType value;
	Node* left;
	Node* right;

	Node(const ValueType &inValue)
	{
		value = inValue;
		left = nullptr;
		right = nullptr;
	}
};


template <class ValueType> class BST
{
public:
	BST()
	{
		m_root = nullptr;
		m_size = 0;
	}

	Node<ValueType>* insert(const ValueType &inValue);

	Node<ValueType>* find(const ValueType &inValue);

	inline void remove(const ValueType &inValue) 
	{
		removeNode(m_root, inValue);
	}

	std::vector <ValueType> getPreOrder();
	std::vector <ValueType> getInOrder();
	std::vector <ValueType> getPostOrder();

	inline bool isBST()
	{
		return isThisBST(m_root);
	}

	inline ValueType getMin()
	{
		return findMin(m_root)->value;
	}

	inline ValueType getMax() 
	{
		return findMax(m_root)->value;
	}

	inline void clear()
	{
		if (m_root)
			destroy(m_root);
	}

	inline size_t getSize()
	{
		return m_size;
	}

	inline bool empty()
	{
		return m_size == 0;
	}

	inline size_t getHeight()
	{
		return getHeightHelper(m_root);
	}

	~BST()
	{
		if (m_root)
			destroy(m_root);
	}
private:
	Node<ValueType>* m_root;
	size_t m_size;

	void destroy(Node<ValueType>* p);
	size_t getHeightHelper(Node<ValueType>* p);
	Node<ValueType>* removeNode(Node<ValueType>* p, const ValueType& inValue);
	Node<ValueType>* findMin(Node<ValueType>* p);
	Node<ValueType>* findMax(Node<ValueType>* p);
	bool isThisBST(Node<ValueType>* p)
};


template<class ValueType> Node<ValueType>* BST<ValueType>::insert(const ValueType& inValue)
{
	++m_size;

	if (!m_root)
	{
		m_root = new Node<ValueType>(inValue);
		return m_root;
	}

	Node<ValueType>* cur = m_root;

	while (cur)
	{
		if (inValue >= cur->value)
		{
			if (!cur->right)
			{
				cur->right = new Node<ValueType>(inValue);
				return cur->right;
			}
			cur = cur->right;
		}
		else
		{
			if (!cur->left)
			{
				cur->left = new Node<ValueType>(inValue);
				return cur->left;
			}
			cur = cur->left;
		}
	}
}

template<class ValueType> Node<ValueType>* BST<ValueType>::find(const ValueType& inValue)
{
	Node<ValueType>* cur = m_root;
	while (cur)
	{
		if (inValue > cur->value)
			cur = cur->right;
		else if (inValue < cur->value)
			cur = cur->left;
		else
			return cur;
	}
	return nullptr;
}

template<class ValueType> std::vector<ValueType> BST<ValueType>::getPreOrder()
{
	std::stack< Node<ValueType>* > s;
	Node<ValueType>* cur = m_root;
	std::vector<ValueType> outVector(m_size);
	size_t i = 0;

	if (cur)
		s.push(cur);

	while (!s.empty())
	{
		cur = s.top();
		outVector[i] = cur->value;
		++i;
		s.pop();
		

		if (cur->right)
			s.push(cur->right);
		if (cur->left)
			s.push(cur->left);
	}

	return outVector;
}

template<class ValueType> std::vector<ValueType> BST<ValueType>::getInOrder()
{
	std::stack< Node<ValueType>* > s;
	Node<ValueType>* cur = m_root;
	std::vector<ValueType> outVector(m_size);
	size_t i = 0;

	while (i < m_size)
	{
		if (cur)
		{
			s.push(cur);
			cur = cur->left;
		}
		else
		{
			cur = s.top();
			outVector[i] = cur->value;
			++i;
			s.pop();
			cur = cur->right;
		}

	}

	return outVector;
}

template<class ValueType> std::vector<ValueType> BST<ValueType>::getPostOrder()
{
	std::stack< Node<ValueType>* > s1, s2;
	Node<ValueType>* cur = m_root;
	if (cur)
		s1.push(cur);

	while (!s1.empty())
	{
		cur = s1.top();
		s2.push(cur);
		s1.pop();

		if (cur->left)
			s1.push(cur->left);
		if (cur->right)
			s1.push(cur->right);
	}
		
	std::vector<ValueType> outVector(s2.size());
	for (int i = 0; i < outVector.size(); ++i)
	{
		outVector[i] = s2.top()->value;
		s2.pop();
	}

	return outVector;
}

template<class ValueType> void BST<ValueType>::destroy(Node<ValueType>* p)
{
	if (p->left)
		destroy(p->left);
	if (p->right)
		destroy(p->right);
	delete p;
}

template<class ValueType> size_t BST<ValueType>::getHeightHelper(Node<ValueType>* p)
{
	if (!p)
		return 0;
	return 1 + std::max(getHeightHelper(p->right), getHeightHelper(p->left));
}

template<class ValueType> Node<ValueType>* BST<ValueType>::removeNode(Node<ValueType>* p, const ValueType& inValue)
{
	if (!p)
		return nullptr;
	else if (p->value < inValue)
		p->right = removeNode(p->right, inValue);
	else if (p->value > inValue)
		p->left = remove(p->left, inValue);
	else
	{
		--m_size;

		if (!p->left)
		{
			Node<ValueType>* temp = p->right;
			delete p;
			return temp;
		}
		if (!p->right)
		{
			Node<ValueType>* temp = p->left;
			delete p;
			return temp;
		}

		Node<ValueType>* temp = getMin(p->right);
		p->value = temp->value;
		p->right = removeNode(p->right, p->value);
	}
	return p;
}

template<class ValueType> Node<ValueType>* BST<ValueType>::findMin(Node<ValueType>*)
{
	if (!p)
		throw std::runtime_error("Trying to get min of empty BST");
	Node<ValueType>* cur = p;
	while (cur->left)
		cur = cur->left;
	return cur;
}

template<class ValueType> Node<ValueType>* BST<ValueType>::findMax(Node<ValueType>* p)
{
	if (!p)
		throw std::runtime_error("Trying to get max of empty BST");
	Node<ValueType>* cur = p;
	while (cur->right)
		cur = cur->right;
	return cur;
}

template<class ValueType> bool BST<ValueType>::isThisBST(Node<ValueType>* p)
{
	if (!p)
		return true;
	if (p->left && p->left->value >= p->value)
		return false;
	if (p->right && p->right->value < p->value)
		return false;
	if (!isThisBST(p->left) || !isThisBST(p->right))
		return false;
	
	return true;
}

}
