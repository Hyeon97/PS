#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#pragma warning(disable:4996);

typedef long long ll;
using namespace std;

int seg[1 << 22];
int N, st, ed, val, H;

pair<int, int>Max = { -1,-1 };//idx, val
pair<int, int>Min = { -1,-1 };//idx, val

//seg Ʈ�� ������Ʈ
void update(int node_idx, int start, int end, int left, int right, ll val) {
	if (end<left || start>right)return;
	if (left <= start && end <= right)seg[node_idx] += val;//�ش���ǥ�� ���� �ȿ� �ִ°��
	else {
		int mid = (start + end) / 2;
		update(node_idx * 2, start, mid, left, right, val);//��������
		update(node_idx * 2 + 1, mid + 1, end, left, right, val);//����������
	}
}

void UP(int idx, ll val) {
	if (Max.first == -1 || val > Max.second) {
		Max.first = idx;
		Max.second = val;
	}
	if (Min.first == -1 || val < Min.second) {
		Min.first = idx;
		Min.second = val;
	}
}

void sum(int idx, int start, int end, ll val) {
	//Ʈ���� ����Ǿ��ִ� �� ����
	val += seg[idx];
	if (start == end) {//���ϴ� ��ġ���� ������ ���
		UP(start, val);
		return;
	}
	// ���� ������ϸ� �ڽĳ��� �̵�
	int mid = (start + end) / 2;
	sum(idx * 2, start, mid, val); //���� �ڽ�
	sum(idx * 2 + 1, mid + 1, end, val); // ������ �ڽ�
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("subrange.inp", "r", stdin);
	freopen("subrange.out", "w", stdout);

	cin >> N;
	while (1) {
		cin >> st >> ed >> val;
		if (st == -1)break;
		update(1, 0, N - 1, st, ed, val);
	}
	sum(1, 0, N - 1, 0);
	cout << Min.second << ' ' << Min.first << ' ' << Max.second << ' ' << Max.first<<'\n';
	return 0;
}

