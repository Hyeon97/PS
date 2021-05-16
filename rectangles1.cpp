//세그먼트 트리, 라인스위핑
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
	if (left <= start && end <= right)cnt[node_idx] += val;//해당좌표가 범위 안에 있는경우
	else {
		int mid = (start + end) / 2;
		update(node_idx * 2, start, mid, left, right, val);//왼쪽으로
		update(node_idx * 2 + 1, mid + 1, end, left, right, val);//오른쪽으로
	}
	if (cnt[node_idx])seg[node_idx] = (end - start) + 1;//x축 길이를 구해줌
	else seg[node_idx] = start == end ? 0 : seg[node_idx * 2] + seg[node_idx * 2 + 1];
}

int main() {
	freopen("rectangles.inp", "r", stdin);
	freopen("rectangles.out", "w", stdout);
	cin >> n;
	int a, b, c, d;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c >> d;//a:x시작좌표 b:y시작좌표 c:x끝좌표 d:y끝좌표
		a += 10000;
		b += 10000;
		c += 10000;
		d += 10000;
		arr[i] = { a,b,d - 1,1 };//0부터 한다고 했을때 좌표계 기준 -1 해줘야 정확한 넓이 >> 그냥 넣으면 크키가 좀더 크게나옴 || 맨뒤 1은 시작 -1은 끝좌표 의미
		arr[i + n] = { c,b,d - 1,-1 };
	}
	sort(arr, arr + n * 2, cmp);//x축 기준으로 정렬
	//데이터의 개수가 N개일때 N보다 큰 수중 가장 가까운 N의 제곱수를 구한뒤
	//그것의 2배까지 미리 배열의 크기를 만들어 놓아야 함 >> 간단하게 생각하면 4*N의 크기
	ll size = pow(2, (int)log2(30000 - 1) + 1);
	ll out = 0;//전체넖이
	int lastx = 0;//직전x좌표
	for (int i = 0; i < n * 2; i++) {
		if (i) {
			int temp = arr[i].x - lastx;//x 길이
			out += temp * seg[1];//무조건 루트 곱해주기
		}
		update(1, 0, size - 1, arr[i].y, arr[i].y2, arr[i].val);//일반적으론 1~size이지만 좌표임으로 한칸식 당겨서 0~size-1로
		lastx = arr[i].x;
	}
	cout << out;
	return 0;
}