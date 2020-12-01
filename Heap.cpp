#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#define HEAP_SIZE 256
#define ARRAY_SIZE 10
using namespace std;

template<class T> class Heap {
private:
	T* heap;
	int sz;
	void swap(T& a, T& b) { T tmp = a; a = b; b = tmp; }
public:
	Heap() {
		heap = new T[M];
		sz = 0;
	}
	int size() {
		return sz;
	}
	bool empty() {
		return !sz;
	}
	void push(T v) {
		heap[++sz] = v;
		int child = sz;
		int parent = sz / 2;
		while (child > 1 && heap[parent] < heap[child]) {
			swap(heap[parent], heap[child]);
			child = parent;
			parent /= 2;
		}
	}
	T top() {
		return heap[1];
	}
	void pop() {
		swap(heap[1], heap[sz--]);
		int parent = 1;
		int child = parent * 2;
		if (child + 1 <= sz) {
			child = heap[child] > heap[child + 1] ? child : child + 1;
		}
		while (child <= sz && heap[parent] < heap[child]) {
			swap(heap[parent], heap[child]);
			parent = child;
			child *= 2;
			if (child + 1 <= sz) {
				child = heap[child] > heap[child + 1] ? child : child + 1;
			}
		}
	}
};

int main() {
	int arr[ARRAY_SIZE];

	// 랜덤함수를 위한 srand와 seed
	srand(time(NULL));

	Heap<int> pq;
	// 배열 초기화
	for (int i = 0; i < ARRAY_SIZE; i++) {
		// 1 ~ 50까지의 난수 생성
		arr[i] = rand() % 50 + 1;
	}

	// 삽입
	for (int i = 0; i < ARRAY_SIZE; i++) {
		pq.push(arr[i]);
	}

	// pop 하면서 값들 하나씩 확인
	// Max Heap이기 때문에 값들이 내림차순으로 정렬됨 -> Heap Sort
	for (int i = 0; i < ARRAY_SIZE; i++) {
		int t = pq.top(); pq.pop();
		printf("%d ", t);
	}
	printf("\n");

	return 0;
}
