#include <iostream>
#include <algorithm>
#include <vector>


#pragma warning(disable:4996);
typedef long long ll;
using namespace std;

int N,a,b,k;
int arr[100001];
int Max = 0,ans;
int main()
{
	ios_base::sync_with_stdio(false); //cin.tie(0); cout.tie(0);
	freopen("subrange.inp", "r", stdin);
	freopen("subrange.out", "w", stdout);
	
	cin >> N;
	while (1) {
		cin >> a >> b >> k;
		if (a == -1 && b == -1 && k == -1) {
			break;
		}
		for (int i = a; i <= b; i++) {
			arr[i] += k;
		}
	}
	for (int i = 0; i <= 100000; i++) {
		if (arr[i] > Max) {
			Max = arr[i];
			ans = i;
		}
	}
	cout << ans;

	return 0;
}

