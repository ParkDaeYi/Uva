#include <iostream>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

int n, num[15], shape[4];
char input[2];
vector<int> card[4];

void CardValue(char* input) {
	int v = 0, s = 0;
	switch (input[1]) {
	case 'T': v = 10; break;
	case 'J': v = 11; break;
	case 'Q': v = 12; break;
	case 'K': v = 13; break;
	case 'A': v = 1; break;
	default: v = input[1] - '0';
	}

	switch (input[0]) {
	case 'S': s = 0; break;
	case 'D': s = 1; break;
	case 'H': s = 2; break;
	case 'C': s = 3; break;
	}
	if (v == 1) num[14]++, card[s].push_back(14);
	shape[s]++;
	num[v]++;
	card[s].push_back(v);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("poker.inp", "r", stdin);
	freopen("poker.out", "w", stdout);

	cin >> n;
	while (n--) {
		fill(num, num + 15, 0);
		fill(shape, shape + 4, 0);
		for (int i = 0;i < 4;++i) card[i].clear();
		for (int i = 0;i < 7;++i) {
			cin >> input;
			CardValue(input);
		}

		int two = 0, three = 0, four = 0, flush = 0, straight = 0, sf = 0;
		for (int i = 1;i < 14;++i) {
			if (!num[i]) continue;
			if (num[i] == 2) two++;
			else if (num[i] == 3) three++;
			else if (num[i] == 4) four++;
		}
		for (int i = 0;i < 4;++i)
			if (shape[i] >= 5) flush++;

		for (int i = 1;i < 11;++i) {
			if (!num[i]) continue;
			int sum = 0;
			for (int j = i;j < i + 5;++j) {
				if (!num[j]) break;
				sum++;
			}
			if (sum == 5) {
				straight++;
				break;
			}
		}

		if (straight && flush) {
			for (int i = 0;i < 4;++i) {
				if (card[i].size() < 5) continue;
				int cnum[15] = { 0, };
				for (int j = 0;j < card[i].size();++j) cnum[card[i][j]]++;
				for (int j = 1;j < 11;++j) {
					if (!cnum[j]) continue;
					int sum = 0;
					for (int k = j;k < j + 5;++k) {
						if (!cnum[k]) break;
						sum++;
					}
					if (sum == 5) {
						sf++;
						break;
					}
				}
			}
		}

		if (sf) cout << "Straight Flush\n";
		else if (four) cout << "Four Card\n";
		else if ((three && two) || (three == 2)) cout << "Full House\n";
		else if (flush) cout << "Flush\n";
		else if (straight) cout << "Straight\n";
		else if (three) cout << "Triple\n";
		else if (two >= 2) cout << "Two Pair\n";
		else if (two) cout << "One Pair\n";
		else cout << "Top\n";
	}

	return 0;
}