#pragma once
#include <iostream>
template <class T>

struct Node
{
	T data;
	Node <T> *next;

	Node(const Node <T> &other)
	{
		next = other.next ? new Node(*other.next) : NULL;
		data = other.data;
	}
	
	Node(const T &data)
	{
		this->next = NULL;
		this->data = data;
	}
	Node(const T &data, Node <T> *next)
	{
		this->next = next;
		this->data = data;
	}

	~Node()
	{
		if (next)
		{
			delete next;
		}
	}
};

template <class T>

class List
{
protected:
	Node <T> *last, *first;
	size_t size;

	void clear()
	{
		delete first;
		first = last = NULL;
	}
	Node <T>* getAt(size_t index)
	{
		Node <T> *node = first;
		if (index >= size)
		{
			return NULL;
		}
		while (index > 0)
		{
			index--;
			node = node->next;
		}
		return node;
	}

public:
	bool isEmpty() const
	{
		return size == 0;
	}

	size_t getSize() const
	{
		return size;
	}

	List()
	{
		first = last = NULL;
		size = 0;
	}

	List(const T &node)
	{
		first = last = new Node <T> (node);
		size = 1;
	}

	List(const List <T> &other)
	{
		if (other.isEmpty())
		{
			first = last = NULL;
			size = 0;
		}
		else
		{
			first = new Node <T> (*other.first);
			size = list.size;
			last = first;
			while (last->next)
			{
				last = last->next;
			}
		}
	}

	~List()
	{
		delete first;
	}
	List <T> &operator=(const List <T> &other)
	{
		if (this != &other)
		{
			clear();
			if (!isEmpty())
			{
				first = new Node <T> (*other.first);
				size = other.size;
				for (last = first; last->next; last = last->next) {}
			}
		}

		return *this;
	}
	void  addFront(const T &elem)
	{
		first = new Node <T> (elem,first);
		if (!size)
		{
			last = first;
		}
		size++;
	}
	void addLast(const T &elem)
	{
		if (isEmpty())
		{
			first = last = new Node <T> (elem);
		}
		else 
		{
			last  = last->next = new Node <T> (elem);
		}
		size++;
	}
	T removeFirst()
	{
		if (isEmpty())
		{
			throw "Error, List is empty!";
		}
		T data = first->data;
		Node <T> *oldNode = first;
		first = first->next;
		size--;
		oldNode->next = NULL;
		delete oldNode;
		if (!size)
		{
			last = NULL;
		}
		return data;
	}
	T removeLast()
	{
		if (isEmpty())
		{
			throw "Error, List is empty!";
		}
		if (size == 1)
		{
			return removeFirst();
		}

		Node <T> *beforeLast = getAt(size-2);
		T data = beforeLast->next->data;
		size--;
		last = beforeLast;
		delete beforeLast->next;
		beforeLast->next = NULL;
		return data;
	}
	const T& operator[](size_t pos) const
	{
		if (pos >= size)
		{
			throw "invalid index!";
		}
		return (const_cast <List <T>*>(this)->getAt(pos))->data;
	}
	T removeAt(size_t pos)
	{
		if (pos >= size)
		{
			throw "Invalid index!";
		}

		if (pos == 0)
		{
			return removeFirst();
		}
		if (pos == size-1)
		{
			return removeLast();
		}
		Node <T> *PreviousNode = getAt(pos-1);
		T data = PreviousNode->next->data;
		Node <T> *toRemove = PreviousNode->next;
		PreviousNode->next = toRemove->next;
		toRemove->next = NULL;
		delete toRemove;
		toRemove = NULL;
		size--;
		return data;
	}
	void insertAt(size_t pos, const T& elem)
	{
		if (pos >= size)
		{
			throw "invalid index!";
		}
		else if (pos == 0)
		{
			addFront(elem);	
		}
		else if (pos == size)
		{
			addLast(elem);
		}
		else 
		{
			Node <T> *previousNode = getAt(pos-1);
			Node <T> *toAdd = new Node <T> (elem);
			toAdd->next = previousNode->next;
			previousNode->next = toAdd;
			size++;
		}
	}
};