using namespace std;

template <class T>

struct elem
{
	T data;
	elem <T> *next;
	elem(const T& data,elem <T> *next = NULL)
	{
		this->data = data;
		this->next = next;
	}
	~elem() // cascade destructor
	{
		if (next)
		{
			delete next;
		}
	}
};

template <class T>

class Stack
{
private:
	elem <T> *tos;

public:
	Stack() : tos(NULL) {}

	~Stack() { delete tos; }

	bool isEmpty() const
	{
		return tos == NULL;
	}

	const T& peek() const
	{
		if (isEmpty())
		{
			throw "The stack is empty..."; // error
		}
		return tos->data;
	}

	void push(const T& el)
	{
		elem <T> *pNewElem = new elem <T> (el);
		pNewElem->data = el;
		pNewElem->next = tos;
		tos = pNewElem;
	}
	T pop()
	{
		if(isEmpty())
		{
			throw "The stack is empty";
		}

		elem <T> *pOldElem = tos;
		tos = tos->next;
		pOldElem->next = NULL;
		T data = pOldElem->data;
		delete pOldElem;
		return data;
	}
};