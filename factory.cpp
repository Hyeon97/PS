//2-AST
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <math.h>


#pragma warning(disable:4996);
using namespace std;

struct II {
	int st;
	int idx;
};

int TestCase, N, D;
int cnt, sn_cnt, ch;
int scc[10002];
bool v[10002];
vector< vector<int> >g;//���� ���� 1~5000(B) || 5001~10000(R) 
vector< vector<int> >gr;//���� ���� 1~5000(B) || 5001~10000(R) 
stack<int>node;
II list[2001];

bool cmp(II a, II b) {
	return a.st < b.st;
}

void DFS(int num) {
	//�ش� ���� �湮üũ
	v[num] = true;
	//�湮 ���� �������� ������ �׷����� Ÿ�� Ž��
	for (int i = 0; i < g[num].size(); i++) {
		if (!v[g[num][i]])DFS(g[num][i]);
	}
	//���̻� ������ ��� �ش� ���� ���ÿ� Ǫ��
	node.push(num);
}

void RDFS(int num) {
	//�ش������� �־���
	scc[num] = ch;
	//�ش� ���� �湮üũ
	v[num] = true;
	//�湮���� �������� ������ �׷����� Ÿ�� Ž��
	for (int i = 0; i < gr[num].size(); i++) {
		if (!v[gr[num][i]])RDFS(gr[num][i]);
	}
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("factory.inp", "r", stdin);
	freopen("factory.out", "w", stdout);
	cin >> TestCase;
	for (int i = 1; i <= TestCase; i++) {
		cout << "Test Case #" << i << ": ";
		cin >> N >> D;
		//�ʱ�ȭ
		for (int i = 0; i < N * 2; i++)v[i] = false;//�湮�迭 �ʱ�ȭ
		cnt = sn_cnt = 0;
		g.clear();
		gr.clear();
		g.resize(2 * N);
		gr.resize(2 * N);
		//�׷��� ����
		for (int i = 0, a, b; i < N; i++) {
			cin >> a >> b;
			if (a > b) {
				int temp = a;
				a = b;
				b = temp;
			}
			list[i] = { a,i };
			list[i + N] = { b,i + N };
		}
		sort(list, list + 2 * N, cmp);
		for (int i = 0; i < N * 2; i++) {
			for (int j = i + 1, to, from; j < N * 2; j++) {
				if (list[j].st - list[i].st >= D) break;

				from = list[i].idx < N ? list[i].idx + N : list[i].idx - N;
				to = list[j].idx;

				g[from].push_back(to);
				gr[to].push_back(from);

				from = list[i].idx;
				to = list[j].idx < N ? list[j].idx + N : list[j].idx - N;

				g[to].push_back(from);
				gr[from].push_back(to);
			}
		}

		//SCC
		for (int i = 0; i < N * 2; i++)if (!v[i])DFS(i);//������ �湮(��ȸ)
		for (int i = 0; i < N * 2; i++)v[i] = false;//�湮�迭 �ʱ�ȭ

		ch = 0;
		while (!node.empty()) {
			int temp = node.top();
			node.pop();
			if (!v[temp])RDFS(temp), ch++;
		}
		bool NO = false;
		for (int i = 0; i < N; i++) {
			if (scc[i] == scc[i + N]) {
				NO = true;
				break;
			}
		}
		NO ? cout << "Impossible\n" : cout << "Possible\n";
	}

	return 0;
}

