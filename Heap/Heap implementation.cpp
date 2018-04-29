#include <cassert>
#include <vector>


namespace binary_heap
{


template <class ValueType>
class Heap
{
public:
	
	Heap() {};

	Heap(const ValueType &inValue)
	{
		m_data.push_back(inValue);
	}

	void insert(const ValueType &inValue)
	{
	    m_data.push_back(inValue);
	    if (m_data.size() > 0)
			siftUp(m_data.size() - 1);
	}

	inline ValueType peek() const
	{
		if (m_data.size() > 0)
			return m_data[0];
		else
			throw std::runtime_error("Can't peek in empty heap!");
	}

	inline bool isEmpty() const
	{
		return m_data.size() == 0;
	}

	void pop()
	{
		if (m_data.size() == 0)
			throw std::runtime_error("Can't pop from empty heap!");
	    m_data[0] = m_data[m_data.size() - 1];
		m_data.erase(m_data.begin() + m_data.size() - 1);
		if (m_data.size() > 0)
			siftDown(0);
	}

private:

	void siftUp(long long i)
	{
		long long parent = (i - 1) / 2;
		while (parent >= 0)
		{
			if (m_data[parent] > m_data[i])
			{
				std::swap(m_data[i], m_data[parent]);
				i = parent;
				parent = (i - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void siftDown(long long i)
	{
		long long leftChild = 2 * i + 1, rightChild = 2 * i + 2, minChild;
    
		while (leftChild < m_data.size())
		{
			if (rightChild < m_data.size())
			{
				if (m_data[leftChild] > m_data[rightChild])
					minChild = rightChild;
				else
					minChild = leftChild;

				if (m_data[minChild] < m_data[i])
				{
					std::swap(m_data[minChild], m_data[i]);
					i = minChild;
					leftChild = 2 * i + 1;
					rightChild = 2 * i + 2;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (m_data[leftChild] < m_data[i])
				{
					std::swap(m_data[leftChild], m_data[i]);
					i = leftChild;
					leftChild = 2 * i + 1;
					rightChild = 2 * i + 2;
				}
				else
				{
					break;
				}
			}
		}
	}

private:

	std::vector <ValueType> m_data;
};

}

using namespace binary_heap;

int main()
{
	{
		Heap<int> h;
		assert(h.isEmpty());
		h.insert(5);
		assert(!h.isEmpty());
		h.insert(2);
		assert(h.peek() == 2);
		h.insert(6);
		assert(h.peek() == 2);
		h.insert(5);
		assert(h.peek() == 2);
		h.insert(-1);
		assert(h.peek() == -1);
		h.insert(4);
		assert(h.peek() == -1);
		h.insert(2);
		assert(h.peek() == -1);
		h.pop();
		assert(h.peek() == 2);
		h.pop();
		assert(h.peek() == 2);
		h.pop();
		assert(h.peek() == 4);
		h.pop();
		assert(h.peek() == 5);
		h.pop();
		assert(h.peek() == 5);
		h.pop();
		assert(h.peek() == 6);
		assert(!h.isEmpty());
		h.pop();
		assert(h.isEmpty());

		h.insert(5);
		assert(!h.isEmpty());
		assert(h.peek() == 5);
	}
	
	Heap<int> h(5);
	assert(!h.isEmpty());
	assert(h.peek() == 5);
	h.pop();
	assert(h.isEmpty());

	try 
	{
		h.peek();
	}
	catch (const std::exception &e)
	{		
		assert(strcmp(e.what(), "Can't peek in empty heap!") == 0);
	}

	try
	{
		h.pop();
	}
	catch (const std::exception &e)
	{
		assert(strcmp(e.what(), "Can't pop from empty heap!") == 0);
	}


	return 0;
}
