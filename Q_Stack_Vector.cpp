#include <iostream>
#define N 101
using namespace std;

template<class T> class Queue {
private:
	int f;
	int r;
	int size;
	T* values;
public:
	Queue() {
		size = N;
		values = new T[size];
		f = 0;
		r = 0;
	};
	~Queue() {
		delete[] values;
	}
	void push(T v) {
		if (!isFull()) {
			values[r] = v;
			r = (r + 1) % size;
		}
		else cout << "Queue is Full\n";
	}
	void pop() {
		if (!empty()) f = (f + 1) % size;
		else cout << "Queue is Empty\n";
	}
	T front() {
		if (!empty()) return values[f];
		else return NULL;
	}
	bool empty() {
		if (r == f) return 1;
		else return 0;
	}
	bool isFull() {
		if ((r + 1) % size == f) return 1;
		else return 0;
	}
};


template<class T> class Stack {
private:
	int top;
	int size;
	T *values;
public:
	Stack() {
		size = N;
		values = new T[size];
		top = -1;
	}
	~Stack() {
		delete[] values;
	}
	void push(T v) {
		if (!isFull()) values[++top] = v;
		else cout << "Stack is FUll\n";
	}
	void pop() {
		if (!empty()) --top;
		else cout << "Stack is Empty\n";
	}
	T Top() {
		if (!empty()) return values[top];
		else return NULL;
	}
	bool empty() {
		if (top < 0) return 1;
		else return 0;
	}
	bool isFull() {
		if (top + 1 == size) return 1;
		else return 0;
	}
};

template<class T>class vector {
private:
    int cap, sz;
    T* vc;
public:
    vector() {
        cap = 1, sz = 0;
        vc = new T[cap];
    }
    ~vector() {
        delete[] vc;
    }
    void push_back(T val) {
        if (cap == sz) {
            cap *= 2;
            T* tmp = new T[cap];
            for (int i = 0; i < sz; i++) {
                tmp[i] = vc[i];
            }
            delete[] vc;
            
            vc = tmp;
        }
        vc[sz++] = val;
    }
    void pop_back() {
        if (!sz) return;
        vc[--sz] = NULL;
    }
    T back() {
        return vc[sz - 1];
    }
    int size() {
        return sz;
    }
    bool empty() {
        return !sz;
    }
    void clear() {
        cap = 1;
        sz = 0;
        delete[] vc;
        vc = new T[cap];
    }
    T& operator [](T i) {
        return vc[i];
    }
};
