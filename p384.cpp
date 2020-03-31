#include <iostream>
#include <fstream>
using namespace std;
ifstream fin;
ofstream fout;

int t, c_cnt;
char* key, str[66];

bool Slump() {
   if (*key != 'D' && *key != 'E') return 0;
   key++;
   if (*key != 'F') return 0;
   while (*key == 'F') ++key;
   if (*key == 'G') {
      key++; return 1;
   }
   return Slump();
}

bool Slimp() {
   if (*key != 'A') return 0;
   key++;
   if (*key == 'H') {
      key++; return 1;
   }
   if (*key == 'B') {
      key++;
      bool flag = Slimp() && *key == 'C';
      key++;
      return flag;
   }
   bool flag = Slump() && *key == 'C';
   key++;
   return flag;
}

int main() {
   fin.open("p384.inp");
   fout.open("p384.out");
   ios_base::sync_with_stdio(0);
   fin.tie(0); fout.tie(0);

   fin >> t;
   fout << "SLURPYS OUTPUT\n";
   while (t--) {
      fin >> str;
      key = str;
      Slimp() && Slump() && *key == '\0' ? fout << "YES\n" : fout << "NO\n";
   }
   fout << "END OF OUTPUT\n";

   return 0;
}