# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
    stack<T> values;
    stack<T> minimums;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	if(values.empty()){
	    return true;
	}
	else{
	    return false;
	}
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    return values.top();
}

template <class T>
void StackExt<T>::pop()
{
    T val = values.top();
    values.pop();
    if (minimums.top() == val) minimums.pop();
}

template <class T>
void StackExt<T>::push(const T & val)
{
    values.push(val);
    if ( ! minimums.empty() ) {
        if ( val <= minimums.top() ) minimums.push(val);
    }
    else minimums.push(val);
}

template <class T>
T& StackExt<T>::findMin()
{
    return minimums.top();

};


