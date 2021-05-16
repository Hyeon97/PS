#include <iostream>
#include <algorithm>
#include <vector>

#define INF 987654321

#pragma warning(disable:4996);
typedef long long ll;
using namespace std;

struct list {
	ll x1;
	ll h;
	ll x2;
	ll h2;
	ll val;
};

list arr[1 << 22];
ll cnt[1 << 22], seg[1 << 22];
vector<list>L;

bool cmp(list a, list b) {
	return a.x1 < b.x1;
}

void update(int node_idx, int start, int end, int left, int right, ll val) {
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
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("contour.inp", "r", stdin);
	freopen("contour.out", "w", stdout);
	ll x1, h, x2;//���ϴ�, ����, ���ϴ�
	int T = 1;
	int sz = 0;
	while (cin >> x1 >> h >> x2) {
		if (x1 == 0 && h == 0 && x2 == 0) {
			sz = L.size();
			for (int i = 0; i < sz; i++) {
				arr[i] = { L[i].x1, h, 0, L[i].h2 - 1, 1 };
				arr[i + sz] = { L[i].x2,h,0,L[i].h2 - 1,-1 };
			}
			//ll size = pow(2, (int)log2(sz*2) + 1);
			ll ans = 0;
			ll lastx = 0;//����x��ǥ
			sort(arr, arr + sz * 2, cmp);
			cout << "Test Case #" << T++ << " :";
			for (int i = 0; i < sz * 2; i++) {
				if (i) {
					ll temp = arr[i].x1 - lastx; //x ����
					ans += (temp * seg[1]);//������ ��Ʈ �����ֱ�
				}
				update(1, 0, 1000001, 0, arr[i].h2, arr[i].val);//�Ϲ������� 1~size������ ��ǥ������ ��ĭ�� ��ܼ� 0~size-1��
				lastx = arr[i].x1;
				if (!seg[1]) {
					cout << ' ' << ans;
					ans = 0;
				}
			}
			L.clear();
			cout << '\n';
		}
		else {
			//cin >> x1 >> h >> x2;
			L.push_back({ x1,0,x2,h });
		}
	}
	//sort(arr, arr + n * 2, cmp);//x�� �������� ����
	//�������� ������ N���϶� N���� ū ���� ���� ����� N�� �������� ���ѵ�
	//�װ��� 2����� �̸� �迭�� ũ�⸦ ����� ���ƾ� �� >> �����ϰ� �����ϸ� 4*N�� ũ��


	return 0;
}

