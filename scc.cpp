#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <stack>
#include <vector>

#pragma warning(disable:4996)
using namespace std;

stack<int>S;

vector<int>g[100001], gr[100001];//순차 그래프 역차 그래프
bool v[100001];
int n, m;

vector<vector<int>>OUT;
vector<int>Temp;

int count;

void DFS(int num) {
	//해당 정점 방문체크
	v[num] = true;
	//방문 안한 정점으로 순방향 그래프를 타고 탐색
	for (int i = 0; i < g[num].size(); i++) {
		if (!v[g[num][i]])DFS(g[num][i]);
	}
	//더이상 못가는 경우 해당 정점 스택에 푸쉬
	S.push(num);
}
void RDFS(int num) {
	//해당정점을 넣어줌
	Temp.push_back(num);
	//해당 정점 방문체크
	v[num] = true;
	//방문안한 정점으로 역방향 그래프를 타고 탐색
	for (int i = 0; i < gr[num].size(); i++) {
		if (!v[gr[num][i]])RDFS(gr[num][i]);
	}
}
int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	freopen("scc.inp", "r", stdin);
	freopen("scc.out", "w", stdout);
	cin >> m >> n;
	for (int i = 1; i <= n; i++) {
		int a, b;
		cin >> a >> b;
		//순방향 그래프와 역방향 그래프를 만들어줌
		g[a].push_back(b);
		gr[b].push_back(a);
	}
	for (int i = 0; i < m; i++)if (!v[i])DFS(i);//정점들 방문(순회)
	for (int i = 0; i < m; i++)v[i] = false;//방문배열 초기화

	while (!S.empty()) {
		int temp = S.top();
		S.pop();
		if (!v[temp])RDFS(temp);
		//sort(Temp.begin(), Temp.end());
		//Temp배열에 값이 있는경우 == 사이클(그룹)이 하나 만들어짐
		if (Temp.size() != 0) {
			OUT.push_back(Temp);
			::count++;//그룹수++
			Temp.clear();
		}
	}
	cout << ::count << "\n";
	return 0;
}
