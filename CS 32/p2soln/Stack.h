#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <cstdlib>

template <typename T>
struct StackNode
{
	T data;
	StackNode<T> * next;
};

template <typename T>
class Stack
{
public:
	Stack( );
	void push(T x);
	void pop();
	T top() const;
	bool empty() const;

private:
	StackNode<T> * m_top;
};


template <typename T>
Stack<T>::Stack()
: m_top(NULL) // or nullptr
{}

template <typename T>
void Stack<T>::push(T x)
{
	StackNode<T> * nextTop = new StackNode<T>;
	nextTop->data = x;
	nextTop->next = m_top;
	m_top = nextTop;
}

template <typename T>
void Stack<T>::pop()
{
	StackNode<T> * oldTop = m_top;
	if ( m_top != NULL ) // or nullptr
	{
		m_top = m_top->next;
		delete oldTop;		
	}
}

template <typename T>
T Stack<T>::top() const
{	// allows an error if stack empty.
	return m_top->data;	
}

template <typename T>
bool Stack<T>::empty() const
{
	return m_top == NULL; // or nullptr
}


#endif

