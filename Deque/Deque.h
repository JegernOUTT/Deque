#ifndef _DEQUE
#define _DEQUE

typedef enum { false_t = 0, true_t = 1} bool_t;  

template <class T1>
class Deque
{
private:
	long	elementCount;
	void *	memAlloc;
	T1 *	head;
	T1 *	back;

public:
	Deque					(long);
	~Deque					(void);

public: 
	bool_t	isEmpty			();
	int		push_back		();
	int		push_front		();
	T1		pop_back		();
	T1		pop_front		();
};

template <class T1>
Deque<T1>::Deque(long elCnt)
{
	elementCount = elCnt;
	memAlloc = new T1[elementCount * 2];
	memset(memAlloc, 0, sizeof(T1) * elementCount * 2);
	head = (T1 *)memAlloc;
	head += elementCount;
	back = head;

	cout << memAlloc << "  " << head << "  " << back << endl; 
}

template <class T1>
Deque<T1>::~Deque(void)
{
	delete memAlloc;
}

template <class T1>
bool_t Deque<T1>::isEmpty()
{
	if (head == back)
		return true_t;
	else
		return false_t;
}

#endif //_DEQUE