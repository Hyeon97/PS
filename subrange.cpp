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

//seg 트리 업데이트
void update(int node_idx, int start, int end, int left, int right, ll val) {
	if (end<left || start>right)return;
	if (left <= start && end <= right)seg[node_idx] += val;//해당좌표가 범위 안에 있는경우
	else {
		int mid = (start + end) / 2;
		update(node_idx * 2, start, mid, left, right, val);//왼쪽으로
		update(node_idx * 2 + 1, mid + 1, end, left, right, val);//오른쪽으로
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
	//트리에 저장되어있는 값 갱신
	val += seg[idx];
	if (start == end) {//원하는 위치까지 도달한 경우
		UP(start, val);
		return;
	}
	// 값이 존재안하면 자식노드로 이동
	int mid = (start + end) / 2;
	sum(idx * 2, start, mid, val); //왼쪽 자식
	sum(idx * 2 + 1, mid + 1, end, val); // 오른쪽 자식
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

