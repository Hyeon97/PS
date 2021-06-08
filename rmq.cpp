//세그먼트 트리 > 90점 시간초과
//인덱스 트리로 변경
#include <iostream>
#include <algorithm>

#define M  1000010

#pragma warning(disable:4996);
typedef long long ll;
using namespace std;

char ty;
int n, a, b;
ll ans;
struct  node
{
	int idx;
	int val;
};

//node seg[4 * M];//idx 저장
int seg[4 * M];
int num[1000011];

//node query(int node_idx, int start, int end, int left, int right) {
//	if (right < start || end < left)return {M,987654321};
//	if (left <= start && end <= right)return seg[node_idx];
//	int mid = (start + end) / 2;
//	node t1 = query(node_idx * 2, start, mid, left, right);
//	node t2 = query(node_idx * 2 + 1, mid + 1, end, left, right);
//	if (t1.val != t2.val) {
//		if (t1.val < t2.val)return t1;
//		else return t2;
//	}
//	return t1;
//}

//int query(int node_idx, int start, int end, int left, int right) {
//	if (right < start || end < left)return M;
//	if (left <= start && end <= right)return seg[node_idx];
//	int mid = (start + end) / 2;
//	int t1 = query(node_idx * 2, start, mid, left, right);
//	int t2 = query(node_idx * 2 + 1, mid + 1, end, left, right);
//	if (num[t1] != num[t2]) {
//		if (num[t1] < num[t2])return t1;
//		else return t2;
//	}
//	return t1;
//}

int query(int st, int ed) {
	ll idx = M;
	while (st <= ed) {
		if (st % 2 == 1) {
			if (num[seg[st]] != num[idx]) {
				num[seg[st]] < num[idx] ? idx = seg[st] : idx;
			}
			else {
				seg[st] < idx ? idx = seg[st] : idx;
			}
		}
		if (ed % 2 == 0) { 
			if (num[seg[ed]] != num[idx]) {
				num[seg[ed]] < num[idx] ? idx = seg[ed] : idx;
			}
			else {
				seg[ed] < idx ? idx = seg[ed] : idx;
			}
		}
		st = (st + 1) / 2;
		ed = (ed - 1) / 2;
	}
	return idx;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("rmq.inp", "r", stdin);
	//9 : 84546 || 10 : 88596
	freopen("rmq.out", "w", stdout);
	cin >> n;
	ll size = 1;
	while (size < n)size *= 2;
	for (int i = 0; i < n; i++) {
		/*cin >> seg[size + i].val;
		seg[size + i].idx = i;*/
		cin >> num[i];  seg[size+i] = i;
	}
	for (int i = n; i < size; i++) {
		/*seg[size + i].idx = M;
		seg[size + i].val = 987654321;*/
		seg[i+size] = M;
	}
	//연산을 했을때 0이채워지는 나머지 범위 밖 부분을 최대 인덱스로 채워줌으로써 트리 생성시 없는부분은 최고 인덱스가 들어가 자동으로 트리 완성
	
	num[M] = 987654321;
	//양쪽의 자식노드중 더 작은 노드의 값을 가진 노드의 인덱스로 업데이트 < 최초 한번만 업데이트 >
	for (int i = size - 1; i > 0; i--) {
		//두개의 값이 다른경우 작은쪽 인덱스를 가져감
		if (num[seg[i * 2]] != num[seg[i * 2 + 1]]) {
			if (num[seg[i * 2]] < num[seg[i * 2 + 1]]) seg[i] = seg[i * 2];
			else seg[i] = seg[i * 2 + 1];
		}
		//두개의 값이 같은경우 인덱스 작은값 가져감
		else seg[i * 2] < seg[i * 2 + 1] ? seg[i] = seg[i * 2] : seg[i] = seg[i * 2 + 1];
	}

	while (1) {
		cin >> ty;
		if (ty == 'q') {//a~b 사이에서 제일 작은값의 인덱스 || 작은값이 동일한 경우 동일한 값들 중 제일 작은 인덱스 리턴
			cin >> a >> b;
			/*node t = query(1, 0, size - 1, a, b);
			ans += t.idx;
			ans %= 100000;*/
			//ans += query(1, 0, size - 1, a, b);
			ans += query(a+size, b+size);
			ans %= 100000;
		}
		else if (ty == 'c') {//배열의 seg[a] = b >> num[a]=b;
			cin >> a >> b;
			num[seg[size + a]] = b;
			//update
			//실제값은 값만 변환하고 위쪽만 바꿔주면되기 때문에 /2연산을 해서 바로 한단계위에서부터 갱신 시작
			for (int idx = (a+size) / 2; idx > 0; idx /= 2) {
				//두개의 값이 같은경우 왼쪽값 가져감
				if (num[seg[idx * 2]] != num[seg[idx * 2 + 1]]) {//두개의 값이 다른경우 작은쪽 인덱스를 가져감
					if (num[seg[idx * 2]] < num[seg[idx * 2 + 1]]) seg[idx] = seg[idx * 2];
					else seg[idx] = seg[idx * 2 + 1];
				}
				//두개의 값이 같은경우 인덱스 작은값 가져감
				else seg[idx * 2] < seg[idx * 2 + 1] ? seg[idx] = seg[idx * 2] : seg[idx] = seg[idx * 2 + 1];
			}
		}
		else//종료 s
			break;
	}
	cout << ans;

	return 0;
}

