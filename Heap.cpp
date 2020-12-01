#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#define HEAP_SIZE 256
#define ARRAY_SIZE 10
using namespace std;

void swap(int& a, int& b) { int tmp = a; a = b; b = tmp; }

// Max Heap
class Heap {
private:
	int heap[HEAP_SIZE];
	int heap_size;
public:
	Heap() {		
		fill(heap, heap + HEAP_SIZE, 0);
		heap_size = 0;
	}
	int size() {
		return heap_size;
	}
	void push(int v) {
		// 힙의 가장 끝에 데이터 추가
		heap[++heap_size] = v;
		// child를 parent와 비교하면서 알맞은 위치로 하나씩 올림
		int child = heap_size;
		int parent = child / 2;
		while (child > 1 && heap[parent] < heap[child]) {
			swap(heap[parent], heap[child]);
			child = parent;
			parent = child / 2;
		}
	}
	int top() {
		return heap[1];
	}
	void pop() {
		// 첫번째 원소를 힙의 가장 끝에 원소와 바꿈
		swap(heap[1], heap[heap_size]);
		// 가장 끝은 이제 쓰지 않으므로 --
		heap_size--;

		// child를 parent와 비교하면서 알맞은 위치로 하나씩 내림
		int parent = 1;
		int child = parent * 2;
		if (child + 1 <= heap_size) {
			child = (heap[child] > heap[child + 1]) ? child : child + 1;
		}
		while (child <= heap_size && heap[parent] < heap[child]) {
			swap(heap[parent], heap[child]);
			parent = child;
			child *= 2;
			if (child + 1 <= heap_size) {
				child = (heap[child] > heap[child + 1]) ? child : child + 1;
			}
		}
	}
};

int main() {
	int arr[ARRAY_SIZE];

	// 랜덤함수를 위한 srand와 seed
	srand(time(NULL));

	Heap pq;
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