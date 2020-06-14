#include <iostream>
#include <stack>
#include <vector>
#pragma warning(disable:4996)
using namespace std;

int t, n, k, idx;
char bracket[40001];
int arr[20001];
vector<char> ans;

void inorder(int left,int right) {
   if (left == right) return;

   int i;
   for (i = left; i < right; ++i) {
      if (arr[i] == idx) break;
   }

   idx++;
   ans.push_back('(');
   inorder(left, i);
   ans.push_back(')');
   inorder(i + 1, right);
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
   freopen("transform.inp", "r", stdin);
   freopen("transform.out", "w", stdout);

   cin >> t;
   while (t--) {
      cin >> n >> k;

      cout << n << ' ';
      if (k) {
         cin >> bracket;

         stack<int> ans;
         for (int i = 0, j = 1; i < n + n; ++i) {
            if (bracket[i] == '(') ans.push(j++);
            else if (bracket[i] == ')') {
               cout << ans.top() << ' ';
               ans.pop();
            }
         }   
      }
      else {
         for (int i = 0; i < n; ++i) cin >> arr[i];
         
         idx = 1;
         ans.clear();
         inorder(0, n);

         for (char c : ans) cout << c;      
      }
      cout << '\n';
   }
   return 0;
}