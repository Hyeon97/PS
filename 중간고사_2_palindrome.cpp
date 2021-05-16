#include <iostream>
#include <algorithm>
#include <vector>


#pragma warning(disable:4996);
typedef long long ll;
using namespace std;

string s;
int T;
int ans = 0;
bool nc = false;

bool ch(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != s[s.length() - 1 - i]) {
			return true;
		}
	}
	return false;
}

int NUM2(string s) {//역수
	int n = 0;
	int t = 1;
	for (int i =0; i< s.length(); i++) {
		n += ((s[i]-'0') * t);
		t *= 10;
	}
	return n;
}

int NUM1(string s) {//정방향
	int n = 0;
	int t = 1;
	for (int i = s.length() - 1; i >= 0; i--) {
		n += ((s[i]-'0')*t);
		t *= 10;
	}
	return n;
}

string ST(int num) {
	string temp,temp2;
	while (num) {
		temp += (num % 10+'0');
		num /= 10;
	}
	for (int i = temp.length() - 1; i >= 0; i--) {
		temp2 += temp[i];
	}
	return temp2;
}

int main()
{
	ios_base::sync_with_stdio(false); //cin.tie(0); cout.tie(0);
	freopen("palindrome.inp", "r", stdin);
	freopen("palindrome.out", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> s;
		nc = false;
		ans = 0;	
		while (1) {
			if (ans >= 1000) {
				cout << -1 << '\n';
				break;
			}
			if (!ch(s)) {
				cout << ans << '\n';
				break;
			}
			else {
				int t1 = NUM1(s);
				int t2 = NUM2(s);
				int C = abs(t1 - t2);
				s = ST(C);
				ans++;
			}
		}
	}

	return 0;
}

