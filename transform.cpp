//±¸Çö
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#pragma warning(disable:4996);
using namespace std;

int Test,n,k,idx;
int arr[1000];

void DFS(int st, int ed) {
	if (st == ed)return;

	for (int i = st; i < ed; i++) {
		if (arr[i] == idx) {
			idx++;
			cout << '(';
			DFS(st, i);
			cout << ')';
			DFS(i + 1, ed);
			break;
		}
	}
	
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("transform.inp", "r", stdin);
	freopen("transform.out", "w", stdout);
	cin >> Test;
	string s;
	while (Test--) {
		cin >> n >> k;
		cout << n << ' ';
		if (k == 0) {//¼ýÀÚ -> °ýÈ£
			for (int i = 0; i < n; i++)cin >> arr[i];
			idx = 1;
			DFS(0, n);
		}
		else {//°ýÈ£ -> ¼ýÀÚ
			cin >> s;
			int cnt = 1;
			vector<int>v;
			for (int i = 0; i < s.length(); i++) {
				if (s[i] == '(') {
					v.push_back(cnt++);
				}
				else if (s[i] == ')') {
					cout << v.back() << ' ';
					v.pop_back();
				}
			}
		}
		cout << '\n';
	}

	return 0;
}

