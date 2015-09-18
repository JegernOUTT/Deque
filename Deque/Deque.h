#ifndef _DEQUE
#define _DEQUE

#define _CRT_SECURE_NO_WARNINGS
#define POP_ERROR 0xD5555555

typedef enum { false_t = 0, true_t = 1} bool_t;  

template <class T1>
class Deque
{
private:
	long	maxElementCount;
	T1 **	memAlloc;
	T1 **	head;
	T1 **	back;
	long	elementCount;

public:
	Deque						(long);
	Deque						(const Deque<T1> &);
	~Deque						(void);

public: 
	Deque<T1> & operator=		(const Deque<T1> &);
	T1 &	operator[]			(const int);
	bool_t	isEmpty				();

	int		push_back			(T1 * const);
	int		push_front			(T1 * const);
	T1 &	pop_back			();
	T1 &	pop_front			();

	int		stabilize			();
	long	getElementCount		();
	long	getMaxElementCount	();
	int		clearDeque_unsafe	();
};

template <class T1>
Deque<T1>::Deque(long elCnt)
{
	maxElementCount = elCnt;
	memAlloc = new T1 * [maxElementCount * 2]();
	head = memAlloc;
	head += maxElementCount;
	back = head;
	elementCount = 0;
}

template <class T1>
Deque<T1>::~Deque(void)
{
	delete memAlloc;
}

template <class T1>
Deque<T1>::Deque(const Deque<T1> & deque)
{
	this->~Deque();
	this = new Deque(deque.getMaxElementCount());

	for (int i = 0; i < elementCount / 2; ++i)
	{
		this->push_back(deque[i]);
	}

	for (int i = elementCount / 2; i < elementCount; ++i)
	{
		this->push_front(deque[i]);
	}

	return 0;
}

template <class T1>
Deque<T1> & Deque<T1>::operator=(const Deque<T1> & deque)
{
	this = deque;

	return *this;
}

template <class T1>
T1 & Deque<T1>::operator[](const int num)
{
	if (num < elementCount)
		return **(back + num);
	else 
	{
		new T1(-1);
	}
}

template <class T1>
bool_t Deque<T1>::isEmpty()
{
	if (head == back && elementCount == 0)
		return true_t;
	else
		return false_t;
}

template <class T1>
int Deque<T1>::push_back(T1 * const element)  
{
	if ((back - 1) >= memAlloc)
	{
		back -= 1;
		*back = element;
		++elementCount;
		return 0;
	}
	else
	{
		return -1;
	}
}

template <class T1>
int Deque<T1>::push_front(T1 * const element)  
{
	T1 ** addr = memAlloc;
	addr += maxElementCount * 2;
	
	if ((head + 1) <= addr)
	{
		*head = element;
		head += 1;
		++elementCount;
		return 0;
	}
	else
	{
		return -1;
	}
}

template <class T1>
T1 & Deque<T1>::pop_back()
{
	if (!isEmpty())
	{
		if (back != head)
			back += 1;
		--elementCount;
		return **(back - 1);
	}
	else 
	{
		stabilize();
		return * (new T1(POP_ERROR));
	}
}

template <class T1>
T1 & Deque<T1>::pop_front()
{
	if (!isEmpty())
	{
		head -= 1;
		--elementCount;
		return **head;
	}
	else 
	{
		stabilize();
		return * (new T1(POP_ERROR));
	}
}

template <class T1>
int Deque<T1>::stabilize()
{
	head = memAlloc;
	head += maxElementCount;
	back = head;
	/*
	!	Make an recounting and moving the array to center of allocated memory
	*/
	return 0;
}

template <class T1>
long Deque<T1>::getElementCount()
{
	return elementCount;
}

template <class T1>
long Deque<T1>::getMaxElementCount()
{
	return maxElementCount;
}

template <class T1>
int Deque<T1>::clearDeque_unsafe()
{
	for (int i = 0; i < elementCount * 2; ++i)
	{
		delete *(memAlloc + i);
	}
	
	elementCount = 0;

	head = memAlloc;
	head += maxElementCount;
	back = head;

	return 0;
}


#endif //_DEQUE