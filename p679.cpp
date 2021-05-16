#include <iostream>
#include <algorithm>

#pragma warning(disable:4996)
using namespace std;

int TestCase;
int D, B;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p679.inp", "r", stdin);
	freopen("p679.out", "w", stdout);

	cin >> TestCase;
	while (TestCase--) {
		cin >> D;//현재트리 깊이
		cin >> B;//출발하는 공의 순서
		int N = 1;
		for (int i = 0; i < D - 1; i++) {
			if (B % 2) {
				B /= 2;
				B += 1;
				N *= 2;
			}
			else {
				B /= 2;
				N *= 2;
				N += 1;	
			}
		}
		cout << N << '\n';
	}
	cin >> TestCase;
	return 0;
}

