#ifndef _DEQUETESTS
#define _DEQUETESTS

#include "Deque.h"
#include <list>
#include <iostream>

#define ELEMENTS_COUNT 100000

class TestClass
{
public:
	int value;
	static std::list<std::string> state;
	TestClass(int a)						{state.push_back("Constructor")	; value = a;}
	~TestClass()							{state.push_back("Destructor")		;}
	TestClass(TestClass &)					{state.push_back("Copy constructor");}
	TestClass & operator=(TestClass &)		{state.push_back("Operator =")		;	return * this;}
};
std::list<std::string> TestClass::state;

template <class T1>
class TestDeque
{
private:
	Deque<T1> deque;

private:
	bool popBackTest();
	bool popFrontTest();
	bool popBackFrontTest();

	bool pushBackTest();
	bool pushFrontTest();
	bool pushBackFrontTest();

	bool pushBackOverflow();
	bool pushFrontOverflow();

	bool popBackOverflow();
	bool popFrontOverflow();

	bool pushBackFrontPopBackFrontManyTimes();

	bool getElementsViaOperator();
	bool isEmptyCheck();
	bool elementCountCheck();
	bool clearDequeCheck_unsafe();

public:
	TestDeque();
	~TestDeque();
};

template<class T1>
TestDeque<T1>::TestDeque() : 
	deque(ELEMENTS_COUNT)
{
	std::cout << "1: test passed. 0: test not passed" << endl << endl;

	std::cout << "pushBackTest:\t\t"					<< pushBackTest()							<< std::endl;
	std::cout << "popBackTest:\t\t"						<< popBackTest()							<< std::endl << std::endl;

	std::cout << "pushFrontTest:\t\t"					<< pushFrontTest()							<< std::endl;
	std::cout << "popFrontTest:\t\t"					<< popFrontTest()							<< std::endl << std::endl;

	std::cout << "pushBackFrontTest:\t"					<< pushBackFrontTest()						<< std::endl;
	std::cout << "popBackFrontTest:\t"					<< popBackFrontTest()						<< std::endl << std::endl;

	std::cout << "pushBackOverflow:\t"					<< pushBackOverflow()						<< std::endl;
	std::cout << "pushFrontOverflow:\t"					<< pushFrontOverflow()						<< std::endl << std::endl;

	std::cout << "popBackOverflow:\t"					<< popBackOverflow()						<< std::endl;
	std::cout << "popFrontOverflow:\t"					<< popFrontOverflow()						<< std::endl;
	std::cout << "pushBackFrontPopBackFrontManyTimes: "	<< pushBackFrontPopBackFrontManyTimes()		<< std::endl << std::endl;

	std::cout << "getElementsViaOperator:\t"			<< getElementsViaOperator()					<< std::endl;
	std::cout << "isEmptyCheck:\t\t"					<< isEmptyCheck()							<< std::endl;
	std::cout << "elementCountCheck:\t"					<< elementCountCheck()						<< std::endl;
	std::cout << "clearDequeCheck_unsafe:\t"			<< clearDequeCheck_unsafe()					<< std::endl << std::endl;
}

template<class T1>
TestDeque<T1>::~TestDeque(void)
{

};

template<class T1>
bool TestDeque<T1>::popBackTest()
{
	T1 * popBackValue = NULL;
	try
	{
		for (int i = 1; i <= ELEMENTS_COUNT; ++i)
		{
			popBackValue	= & (deque.pop_back());

			if (popBackValue != NULL)
			{
				TestClass * popBackTestClass =	reinterpret_cast<TestClass *>(popBackValue);
				if (popBackTestClass->value != i)
				{
					throw bad_exception("Invalid value from pop_back");
				}
			}
			else
			{
				throw exception("NULL value from pop_back");
			}

			delete popBackValue;
		}

		if (!deque.isEmpty())
		{
			throw exception("After pop_back deque is not empty");
		}
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}
template<class T1>
bool TestDeque<T1>::popFrontTest()
{
	T1 * popFrontValue = NULL;
	try
	{
		for (int i = 1; i <= ELEMENTS_COUNT; ++i)
		{
			popFrontValue = & (deque.pop_front());

			if (popFrontValue != NULL)
			{
				TestClass * popFrontTestClass = reinterpret_cast<TestClass *>(popFrontValue);
				if (popFrontTestClass->value != (ELEMENTS_COUNT - i))
				{
					throw exception("Invalid value from pop_front");
				}
			}
			else
			{
				throw exception("NULL value from pop_front");
			}

			delete popFrontValue;
		}

		if (!deque.isEmpty())
		{
			throw exception("After pop_front deque is not empty");
		}
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}
template<class T1>
bool TestDeque<T1>::popBackFrontTest()
{
	T1 * popBackValue = NULL, * popFrontValue = NULL;
	try
	{
		for (int i = 1; i <= ELEMENTS_COUNT; ++i)
		{
			popBackValue =	& (deque.pop_back());
			popFrontValue = & (deque.pop_front());

			if (popBackValue != NULL && popFrontValue != NULL)
			{
				TestClass * popFrontTestClass = reinterpret_cast<TestClass *>(popFrontValue);
				TestClass * popBackTestClass =	reinterpret_cast<TestClass *>(popBackValue);
				if ((popFrontTestClass->value != (ELEMENTS_COUNT - i)) && (popBackTestClass->value != i))
				{
					throw exception("Invalid value from pop_back or pop_front");
				}
			}
			else
			{
				throw exception("NULL value from pop_back or pop_front");
			}
			
			delete popBackValue;
			delete popFrontValue;
		}

		if (!deque.isEmpty())
		{
			throw exception("After pop_front and pop_back deque is not empty");
		}
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;

}

template<class T1>
bool TestDeque<T1>::pushBackTest()
{
	int err = 0;

	try
	{
		for (int i = 0; i < ELEMENTS_COUNT; ++i)
		{
			err = deque.push_back(new TestClass(ELEMENTS_COUNT - i));
			if (err)
				throw exception("Cannot push front");
		}
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}
template<class T1>
bool TestDeque<T1>::pushFrontTest()
{
	int err = 0;

	try
	{
		for (int i = 0; i < ELEMENTS_COUNT; ++i)
		{
			err = deque.push_front(new TestClass(i));
			if (err)
				throw exception("Cannot push front");
		}
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}
template<class T1>
bool TestDeque<T1>::pushBackFrontTest()
{
	int err = 0;

	try
	{
		for (int i = 0; i < ELEMENTS_COUNT; ++i)
		{
			err = deque.push_front(new TestClass(i));
			if (err)
				throw exception("Cannot push front");
			err = deque.push_back(new TestClass(ELEMENTS_COUNT - i));
			if (err)
				throw exception("Cannot push front");
		}
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}

template<class T1>
bool TestDeque<T1>::pushBackOverflow()
{
	int err = 0;

	try
	{
		for (int i = 0; i < ELEMENTS_COUNT; ++i)
		{
			err = deque.push_back(new TestClass(ELEMENTS_COUNT - i));
			if (err)
				throw exception("Cannot push front");
		}

		err = deque.push_back(new TestClass(0));
		if (err != -1)
			throw exception("Push Back Overflow. Heap corrupted");
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}
template<class T1>
bool TestDeque<T1>::pushFrontOverflow()
{
	int err = 0;

	try
	{
		for (int i = 0; i < ELEMENTS_COUNT; ++i)
		{
			err = deque.push_front(new TestClass(i));
			if (err)
				throw exception("Cannot push front");
		}

		err = deque.push_front(new TestClass(ELEMENTS_COUNT));
		if (err != -1)
			throw exception("Push Back Overflow. Heap corrupted");
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}

template<class T1>
bool TestDeque<T1>::popBackOverflow()
{
	T1 * popBackValue = NULL;
	try
	{
		for (int i = 0; i < ELEMENTS_COUNT * 2; ++i)
		{
			delete & (deque.pop_back());
		}

		if (!deque.isEmpty())
		{
			throw exception("After pop_back deque is not empty");
		}

		popBackValue	= & (deque.pop_back());
		TestClass * popBackTestClass = reinterpret_cast<TestClass *>(popBackValue);

		if (popBackTestClass->value != POP_ERROR)
			throw exception("Pop Back Overflow. Get non-allocated memory");
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}
template<class T1>
bool TestDeque<T1>::popFrontOverflow()
{
	pushBackFrontTest();

	T1 * popFrontValue = NULL;
	try
	{
		for (int i = 0; i < ELEMENTS_COUNT * 2; ++i)
		{
			delete & (deque.pop_back());
		}

		if (!deque.isEmpty())
		{
			throw exception("After pop_back deque is not empty");
		}

		popFrontValue	= & (deque.pop_front());
		TestClass * popFrontTestClass = reinterpret_cast<TestClass *>(popFrontValue);

		if (popFrontTestClass->value != POP_ERROR)
			throw exception("Pop Back Overflow. Get non-allocated memory");
	}
	catch (exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
	return true;
}
template<class T1>
bool TestDeque<T1>::pushBackFrontPopBackFrontManyTimes()
{
	for (int i = 0; i < 100; ++i)
	{
		pushBackFrontTest();

		popBackOverflow();
		popFrontOverflow();
	}
	return true;
}

template<class T1>
bool TestDeque<T1>::getElementsViaOperator()
{
	return true;
}
template<class T1>
bool TestDeque<T1>::isEmptyCheck()
{
	return true;
}
template<class T1>
bool TestDeque<T1>::elementCountCheck()
{
	return true;
}
template<class T1>
bool TestDeque<T1>::clearDequeCheck_unsafe()
{
	return true;
}


#endif //_DEQUETESTS