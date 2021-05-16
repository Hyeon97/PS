#include <iostream>
#include <vector>

#pragma warning(disable:4996)
using namespace std;

long long int a, b;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p10469.inp", "r", stdin);
	freopen("p10469.out", "w", stdout);

	while (cin >> a && cin >> b) {
		long long int ans = a ^ b;
		cout << ans << '\n';
	}
	return 0;
}

