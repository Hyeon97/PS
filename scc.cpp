#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <stack>
#include <vector>

#pragma warning(disable:4996)
using namespace std;

stack<int>S;

vector<int>g[100001], gr[100001];//���� �׷��� ���� �׷���
bool v[100001];
int n, m;

vector<vector<int>>OUT;
vector<int>Temp;

int count;

void DFS(int num) {
	//�ش� ���� �湮üũ
	v[num] = true;
	//�湮 ���� �������� ������ �׷����� Ÿ�� Ž��
	for (int i = 0; i < g[num].size(); i++) {
		if (!v[g[num][i]])DFS(g[num][i]);
	}
	//���̻� ������ ��� �ش� ���� ���ÿ� Ǫ��
	S.push(num);
}
void RDFS(int num) {
	//�ش������� �־���
	Temp.push_back(num);
	//�ش� ���� �湮üũ
	v[num] = true;
	//�湮���� �������� ������ �׷����� Ÿ�� Ž��
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
		//������ �׷����� ������ �׷����� �������
		g[a].push_back(b);
		gr[b].push_back(a);
	}
	for (int i = 0; i < m; i++)if (!v[i])DFS(i);//������ �湮(��ȸ)
	for (int i = 0; i < m; i++)v[i] = false;//�湮�迭 �ʱ�ȭ

	while (!S.empty()) {
		int temp = S.top();
		S.pop();
		if (!v[temp])RDFS(temp);
		//sort(Temp.begin(), Temp.end());
		//Temp�迭�� ���� �ִ°�� == ����Ŭ(�׷�)�� �ϳ� �������
		if (Temp.size() != 0) {
			OUT.push_back(Temp);
			::count++;//�׷��++
			Temp.clear();
		}
	}
	cout << ::count << "\n";
	return 0;
}
