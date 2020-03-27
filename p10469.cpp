#include <iostream>
#include <fstream>
using namespace std;
typedef long long int llt;

ifstream fin;
ofstream fout;

llt op1, op2;

int main() {
	ios_base::sync_with_stdio(0);
	fin.open("p10469.inp");
	fout.open("p10469.out");
	fin.tie(0); fout.tie(0);

	while (fin >> op1 >> op2) {
		llt tmp = op1;
		op1 = (~op1) & op2;
		op2 = tmp & (~op2);
		fout << (op1 | op2) << '\n';
	}
	
	return 0;
}