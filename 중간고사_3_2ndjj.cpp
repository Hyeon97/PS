#include <iostream>
#include <algorithm>
#include <vector>


#pragma warning(disable:4996);
typedef long long ll;
using namespace std;

int T;
vector<int>L;
vector<int>jj;
vector<int>sjj;
bool N[1001];

int main()
{
	ios_base::sync_with_stdio(false); //cin.tie(0); cout.tie(0);
	freopen("2ndjj.inp", "r", stdin);
	freopen("2ndjj.out", "w", stdout);
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		//√ ±‚»≠
		L.clear();
		jj.clear();
		sjj.clear();
		for (int i = 0; i <= 1000; i++)N[i] = 0;
		for (int i = 0, temp; i < n; i++) {
			cin >> temp;
			L.push_back(temp);
		}
		for (int i = 0; i < L.size() - 1; i++) {
			jj.push_back(abs(L[i] - L[i + 1]));
			//N[abs(L[i] - L[i + 1])] = true;
		}
		for (int i = 0; i < jj.size() - 1; i++) {
			sjj.push_back(abs(jj[i] - jj[i + 1]));
			N[abs(jj[i] - jj[i + 1])] = true;
		}
		bool ch = false;
		for (int i = 1; i <=sjj.size(); i++) {
			if (!N[i])ch = true;
		}
		if (ch)cout << "No\n";
		else cout << "Yes\n";

	}


	return 0;
}

