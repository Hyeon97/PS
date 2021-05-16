#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#pragma warning(disable:4996)
using namespace std;

int path[10001];
vector<int>adj[10001];//모든 간선
int F[10001][10001];//현재 유량
int C[10001][10001];//전체 유량
int N, st, ed, val;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("flow.inp", "r", stdin);
	freopen("flow.out", "w", stdout);

	cin >> N;
	while (1) {
		cin >> st >> ed >> val;
		if (st == -1)break;
		adj[st].push_back(ed);
		adj[ed].push_back(st);

		C[st][ed] += val;
		C[ed][st] += val;

	}
	int Total_Flow = 0, S = 0, E = N - 1;

	while (1) {
		queue<int>q;
		q.push(S);
		for (int i = 0; i < 10001; i++)path[i] = -1;
		while (!q.empty()) {
			int now = q.front();
			q.pop();

			for (int i = 0; i < adj[now].size(); i++) {
				int next = adj[now][i];

				if (path[next] != -1)continue;

				if (C[now][next] - F[now][next] > 0) {
					q.push(next);
					path[next] = now;
					if (next == E)break;
				}
			}
		}
		if (path[E] == -1)break;
		int flow = 987654321;
		for (int i = E; i != S; i = path[i]) {
			flow = min(flow, C[path[i]][i] - F[path[i]][i]);
		}
		for (int i = E; i != S; i = path[i]) {
			F[path[i]][i] += flow;//순방향으론 최소 유량만큼 +
			F[i][path[i]] -= flow;//역방향으로 총 흐를수 있는 유량 - 현재 흐르는 유량
		}
		Total_Flow += flow;

	}
	cout << Total_Flow << '\n';

	return 0;
}

