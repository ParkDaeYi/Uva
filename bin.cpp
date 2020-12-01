#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ofstream outp("data.bin", ios::out | ios::binary);
	int n1 = 500;
	int n2 = 1000;
	double f = 3.14;
	int arr[5] = { 1, 2, 4, 8, 16 };

	outp.write((char*)&n1, sizeof(int));
	outp.write((char*)arr, sizeof(arr));
	outp.write((char*)&n2, sizeof(int));
	outp.write((char*)&f, sizeof(double));

	outp.close();

	ifstream inp("data.bin", ios::in | ios::binary);
	n1 = n2 = 0;
	f = 0;
	for (int i = 0;i < 5;++i) arr[i] = 0;
	inp.read((char*)&n1, sizeof(int));
	inp.read((char*)arr, sizeof(arr));
	inp.read((char*)&n2, sizeof(int));
	inp.read((char*)&f, sizeof(double));

	cout << "n1: " << n1 << ", n2: " << n2 << ", f: " << f << endl;
	cout << "arr: " << arr[0] << ", " << arr[1] << ", " << arr[2] << ", ";
	cout << arr[3] << ", " << arr[4] << endl;

	inp.close();
	return 0;
}