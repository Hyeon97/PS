//���׸�Ʈ Ʈ��, ���ν�����
#include <iostream>
#include <algorithm>
#include <cstring> //memset
#include <cmath>
#include <string>
#include <queue>

#define INF 987654321

#pragma warning(disable:4996);
typedef long long ll;
using namespace std;

struct list {
	int x;
	int y;
	int y2;
	int val;
};

list arr[120001];
int cnt[120001], seg[120001];
int n;

bool cmp(list a, list b) {
	return a.x < b.x;
}

void update(int node_idx, int start, int end, int left, int right, int val) {
	if (end<left || start>right)return;
	if (left <= start && end <= right)cnt[node_idx] += val;//�ش���ǥ�� ���� �ȿ� �ִ°��
	else {
		int mid = (start + end) / 2;
		update(node_idx * 2, start, mid, left, right, val);//��������
		update(node_idx * 2 + 1, mid + 1, end, left, right, val);//����������
	}
	if (cnt[node_idx])seg[node_idx] = (end - start) + 1;//x�� ���̸� ������
	else seg[node_idx] = start == end ? 0 : seg[node_idx * 2] + seg[node_idx * 2 + 1];
}

int main() {
	freopen("rectangles.inp", "r", stdin);
	freopen("rectangles.out", "w", stdout);
	cin >> n;
	int a, b, c, d;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c >> d;//a:x������ǥ b:y������ǥ c:x����ǥ d:y����ǥ
		a += 10000;
		b += 10000;
		c += 10000;
		d += 10000;
		arr[i] = { a,b,d - 1,1 };//0���� �Ѵٰ� ������ ��ǥ�� ���� -1 ����� ��Ȯ�� ���� >> �׳� ������ ũŰ�� ���� ũ�Գ��� || �ǵ� 1�� ���� -1�� ����ǥ �ǹ�
		arr[i + n] = { c,b,d - 1,-1 };
	}
	sort(arr, arr + n * 2, cmp);//x�� �������� ����
	//�������� ������ N���϶� N���� ū ���� ���� ����� N�� �������� ���ѵ�
	//�װ��� 2����� �̸� �迭�� ũ�⸦ ����� ���ƾ� �� >> �����ϰ� �����ϸ� 4*N�� ũ��
	ll size = pow(2, (int)log2(30000 - 1) + 1);
	ll out = 0;//��ü����
	int lastx = 0;//����x��ǥ
	for (int i = 0; i < n * 2; i++) {
		if (i) {
			int temp = arr[i].x - lastx;//x ����
			out += temp * seg[1];//������ ��Ʈ �����ֱ�
		}
		update(1, 0, size - 1, arr[i].y, arr[i].y2, arr[i].val);//�Ϲ������� 1~size������ ��ǥ������ ��ĭ�� ��ܼ� 0~size-1��
		lastx = arr[i].x;
	}
	cout << out;
	return 0;
}