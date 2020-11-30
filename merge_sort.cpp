#include <iostream>
using namespace std;

int N, arr[10001];
int* arr2;

// 오름차순
void merge(int left, int right) {
	int mid = (left + right) / 2;
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) arr2[k++] = arr[i++];
		else arr2[k++] = arr[j++];
	}
	int tmp = i > mid ? j : i;
	while (k <= right) arr2[k++] = arr[tmp++];
	for (int i = left;i <= right;++i) arr[i] = arr2[i];
}

void partition(int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		partition(left, mid);
		partition(mid + 1, right);
		merge(left, right);
	}
}

int main() {
	cin >> N;
	arr2 = new int[N];
	for (int i = 0;i < N;++i) cin >> arr[i];
	partition(0, N - 1);
	
	return 0;
}