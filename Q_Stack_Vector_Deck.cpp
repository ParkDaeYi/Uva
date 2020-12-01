#include <iostream>
#define N 101
using namespace std;

template<class T> class Queue {
private:
	int f, r, sz;
	T* q;
public:
	Queue() {
		f = r = sz = 0;
		q = new T[N];
	}
	~Queue() {
		delete[] q;
	}
	int size() {
		return sz;
	}
	bool empty() {
		if (r == f) return 1;
		return 0;
	}
	bool isFull() {
		if ((r + 1) % N == f) return 1;
		return 0;
	}
	void push(T v) {
		if (!isFull()) {
			q[r] = v;
			r = (r + 1) % N;
			++sz;
		}
	}
	void pop() {
		if (!empty()) {
			f = (f + 1) % N;
			--sz;
		}
	}
	T front() {
		return q[f];
	}
};

template<class T> class Deque {
private:
	int f, r, sz;
	T* dq;
public:
	Deque() {
		f = r = sz = 0;
		dq = new T[N];
	}
	~Deque() {
		delete[] dq;
	}
	int size() {
		return sz;
	}
	bool empty() {
		return !sz;
	}
	bool isFull() {
		return sz == N;
	}
	void push_front(T v) {
		if (!isFull()) {
			f = (f - 1 + N) % N;
			dq[f] = v;
			++sz;
		}
	}
	void push_back(T v) {
		if (!isFull()) {
			dq[r] = v;
			r = (r + 1) % N;
			++sz;
		}
	}
	void pop_front() {
		if (!empty()) {
			f = (f + 1) % N;
			--sz;
		}
	}
	void pop_back() {
		if (!empty()) {
			r = (r - 1 + N) % N;
			--sz;
		}
	}
	T front() {
		return dq[f];
	}
	T back() {
		int idx = (r - 1 + N) % N;
		return dq[idx];
	}
};


template<class T> class Stack {
private:
	int sz;
	T* st;
public:
	Stack() {
		sz = -1;
		st = new T[N];
	}
	~Stack() {
		delete[] st;
	}
	int size() {
		return sz + 1;
	}
	bool empty() {
		if (sz < 0) return 1;
		return 0;
	}
	bool isFull() {
		if (sz + 1 == N) return 1;
		return 0;
	}
	void push(T v) {
		if (!isFull()) st[++sz] = v;
	}
	void pop() {
		if (!empty()) --sz;
	}
	T top() {
		return st[sz];
	}
};

template<class T> class vector {
private:
	int cap, sz;
	T* vc;
public:
	vector() {
		cap = 1; sz = 0;
		vc = new T[cap];
	}
	~vector() {
		delete[] vc;
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
	void push_back(T v) {
		if (cap == sz) {
			cap *= 2;
			T* tmp = new T[cap];
			for (int i = 0;i < sz;++i) tmp[i] = vc[i];
			delete[] vc;
			vc = tmp;
		}
		vc[sz++] = v;
	}
	void pop_back() {
		if (empty()) return;
		vc[--sz] = NULL;
	}
	T back() {
		return vc[sz - 1];
	}
	T& operator[] (int i) {
		return vc[i];
	}
};
