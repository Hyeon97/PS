#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <stdlib.h>

#pragma warning(disable:4996)
#define DIV 1000000007
#define E -1000000001 //(-10^9 - 1)

typedef long long ll;
using namespace std;


typedef struct Node {
	ll val;
	int idx;//배열인덱스
	int L_cnt = 0;
	int R_cnt = 0;
	int Rank = 0;//크기 순서
	char color = 'B';
	Node* L = NULL;
	Node* R = NULL;
	Node* P = NULL;
}Node;

Node* root, * E_NULL;
ll arr[100001];

Node* makeNode(int data, int idx) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->Rank = node->L_cnt = node->R_cnt = 0;
	node->val = data;
	node->idx = idx;
	node->L = node->R = E_NULL;
	node->P = NULL;
	return node;
}

//(Node*)& node >> root에 node라는 이름의 새로운 이름을 추가해서 그대로 타고 내려가게 함
void Insert(Node*& node, Node* newNode) {//기본적인 삽입 
	if (node == NULL)node = newNode;
	if (node->val < newNode->val) {
		node->R_cnt++;
		if (node->R == E_NULL) {
			node->R = newNode;
			newNode->P = node;
		}
		else {
			Insert(node->R, newNode);
		}
	}
	else if (node->val > newNode->val) {
		node->L_cnt++;
		if (node->L == E_NULL) {
			node->L = newNode;
			newNode->P = node;
		}
		else {
			Insert(node->L, newNode);
		}
	}
}

void RightLotate(Node*& root, Node* node) {
	Node* LeftCh = node->L;
	//회전대상 왼쪽사직의 오른쪽 자식수
	int LCH_RCNT = LeftCh->R_cnt;
	node->L = LeftCh->R;
	if (LeftCh->R != E_NULL) {
		LeftCh->R->P = node;
	}
	LeftCh->P = node->P;
	if (node->P == NULL) {
		root = LeftCh;
	}
	else {
		if (node == node->P->L) {
			node->P->L = LeftCh;
		}
		else {
			node->P->R = LeftCh;
		}
	}
	LeftCh->R = node;
	node->P = LeftCh;
	//자식수 갱신
	node->L_cnt = LCH_RCNT;
	LeftCh->R_cnt = node->R_cnt + node->L_cnt + 1;
}

void LeftLotate(Node*& root, Node* node) {
	Node* RightCh = node->R;
	//회전대상 오른쪽 자식의 왼쪽 자식수 
	int RCH_LCNT = RightCh->L_cnt;
	node->R = RightCh->L;
	if (RightCh->L != E_NULL) {
		RightCh->L->P = node;
	}
	RightCh->P = node->P;
	if (node->P == NULL) {
		root = RightCh;
	}
	else {
		if (node == node->P->L) {
			node->P->L = RightCh;
		}
		else {
			node->P->R = RightCh;
		}
	}
	RightCh->L = node;
	node->P = RightCh;
	//자식수 갱신
	node->R_cnt = RCH_LCNT;
	RightCh->L_cnt = node->R_cnt + node->L_cnt + 1;
}

void ReBuild_Insert(Node*& root, Node* node) {//조건 안맞을시 트리 재구축 root와 재구축 대상노드
	while (node != root && node->P->color == 'R') {//부모가 red 인 경우 양쪽 자식은 무조건 black

		if (node->P == node->P->P->L) {//부모가 조부모 기준 왼쪽 자식
			Node* u = node->P->P->R;//삼촌 노드는 조부모의 오른쪽 자식
			if (u->color == 'R') {//Case 1 삼촌의 색이 red 일때
				node->P->color = 'B';//부모색 변경
				u->color = 'B';//삼촌색 변경
				node->P->P->color = 'R';//조부모 색 변경
				node = node->P->P;//재구축 대상노드를 조부모로 변경
			}
			else { //Case 2,3 공통조건 부모가 red 삼촌이 black 인 경우
				if (node == node->P->R) {//Case 2 삽입노드가 부모의 오른쪽 자식
					node = node->P;
					LeftLotate(root, node);//대상노드의 부모기준 왼쪽회전
				}
				//Case 3 삽입노드가 부모의 왼쪽 자식인 경우
				node->P->color = 'B';
				node->P->P->color = 'R';
				RightLotate(root, node->P->P);//대상노드의 조부모 기준 오른쪽 회전
			}
		}
		else {//부모가 조부모 기준 오른쪽 자식
			Node* u = node->P->P->L;//삼촌 노드는 조부모의 오른쪽 자식
			if (u->color == 'R') {//Case 1 삼촌의 색이 red 일때
				node->P->color = 'B';//부모색 변경
				u->color = 'B';//삼촌색 변경
				node->P->P->color = 'R';//조부모 색 변경
				node = node->P->P;//재구축 대상노드를 조부모로 변경
			}
			else { //Case 2,3 공통조건 부모가 red 삼촌이 black 인 경우
				if (node == node->P->L) {//Case 2 삽입노드가 부모의 오른쪽 자식
					node = node->P;
					RightLotate(root, node);//대상노드의 부모기준 왼쪽회전
				}
				//Case 3 삽입노드가 부모의 왼쪽 자식인 경우
				node->P->color = 'B';
				node->P->P->color = 'R';
				LeftLotate(root, node->P->P);//대상노드의 조부모 기준 오른쪽 회전
			}
		}
	}
	root->color = 'B';//root 노드는 항상 Black 
}

void Insertion(int data, int idx) {
	Node* newNode = makeNode(data, idx);
	newNode->color = 'R';
	newNode->L = E_NULL;
	newNode->R = E_NULL;
	Insert(root, newNode);//노드 삽입
	ReBuild_Insert(root, newNode);//삽입후 재구축
}

void ReBuild_delete(Node*& root, Node* x) {
	Node* u = NULL;
	while (x->P != NULL && x->color == 'B') {
		if (x == x->P->L) {//재구축 대상이 부모의 왼쪽 자식
			u = x->P->R;//삼촌은 부모의 오른쪽 자식
			if (u->color == 'R') {//삼촌색 Red
				u->color = 'B';
				x->P->color = 'R';
				LeftLotate(root, x->P);//x의 부모기준 왼쪽회전
			}
			else {//삼촌색 Black
				if (u->L->color == 'B' && u->R->color == 'B') {//삼촌의 두 자식모두 Black
					u->color = 'R';
					x = x->P;
				}//삼촌의 자식중 하나라도 Red
				else {
					if (u->R->color == 'B') {//삼촌의 오른쪽자식이 Black
						u->color = 'R';
						u->L->color = 'B';
						RightLotate(root, u);//삼촌기준 오른족 회전
						u = x->P->R;//새로운 삼촌은 부모의 오른쪽 자식
					}
					//삼촌의 오른쪽 자식이 Red
					u->color = x->P->color;
					x->P->color = 'B';
					u->R->color = 'B';
					LeftLotate(root, x->P);//부모기준 왼쪽회전
					x = root;
				}
			}
		}
		else {//재구축 대상이 부모의 오른쪽 자식
			u = x->P->L;
			if (u->color == 'R') {//삼촌의 색 Red
				u->color = 'B';
				x->P->color = 'R';
				RightLotate(root, x->P);//x의 부모기준 우측회전
			}
			else {//삼촌의 색 Black
				if (u->L->color == 'B' && u->R->color == 'B') {
					u->color = 'R';
					x = x->P;
				}
				else {
					if (u->L->color == 'B') {
						u->color = 'R';
						u->R->color = 'B';
						LeftLotate(root, u);
						u = x->P->L;
					}
					u->color = x->P->color;
					x->P->color = 'B';
					u->L->color = 'B';
					RightLotate(root, x->P);
					x = root;
				}
			}
		}
	}
	x->color = 'B';
}

Node* Search(Node* node, int val) {//대상노드를 찾음
	if (node == NULL)return NULL;
	if (node->val > val) {
		//node->L_cnt--;
		return Search(node->L, val);
	}
	else if (node->val < val) {
		//node->R_cnt--;
		return Search(node->R, val);
	}
	return node;
	/*while (node != NULL || node != E_NULL) {
		if (node->val > data)node = node->L;
		else if (node->val < data)node = node->R;
	}
	return node;*/
};

Node* find_Min(Node* node) {//대상노드의 오른쪽 서브트리에서 제일 작은값 리턴
	if (node == NULL)return NULL;
	if (node == E_NULL)return E_NULL;
	if (node->L == E_NULL)return node;
	return find_Min(node->L);
}


void Deletion(int idx) {//삭제할 인덱스
	Node* y = NULL;//실제로 삭제되는 노드
	Node* x = NULL;//실제로 삭제되는 노드의 유일한 자식 or 자식 없음 

	Node* z = Search(root, arr[idx]);
	if (z->L == E_NULL || z->R == E_NULL) {//삭제대상노드의 자식 X
		y = z;
	}
	else {
		y = find_Min(z->R);//오른쪽 서브트리에서 제일 작은 값을 가져옴 Successor
		z->val = y->val;//실 삭제노드의 값을 덮어씌움
		z->idx = y->idx;//실 삭제노드의 idx를 덮어씌움
	}
	//실삭제대상(y)의 자식이 있는경우
	if (y->L != E_NULL)x = y->L;
	else x = y->R;

	Node* up = y;

	while (up->P != NULL) {
		if (up == up->P->L) {
			up->P->L_cnt--;
		}
		else if (up == up->P->R) {
			up->P->R_cnt--;
		}
		up = up->P;
	}

	x->P = y->P;
	if (y->P == NULL) {//실 삭제대상이 root 인경우
		if (x == E_NULL)root = NULL;
		else root = x;//x가 새로운 root 가 됨
	}
	else {
		if (y == y->P->L) {
			y->P->L = x;
		}
		else {
			y->P->R = x;
		}
	}
	/*while (y->P!=NULL) {
		if (y == y->P->L) {
			y->P->L_cnt--;
		}
		else if (y == y->P->R) {
			y->P->R_cnt--;
		}
		y == y->P;
	}*/

	if (y->color == 'B') ReBuild_delete(root, x);
}

void C(Node* node, int idx, int ch_val) {
	Deletion(idx);
	arr[idx] = ch_val;
	Insertion(ch_val, idx);
}

int W(Node* node, int r) {
	//탐색하면서 랭킹 갱신
	if (node->P == NULL) {//부모 X
		//부모가 없으니 대상노드는 루트
		//루트의 왼쪽이 자기보다 작은 아이들만 모여있음으로
		//왼쪽 자식수 + 1(자기자신) 해주면 자신의 순위가 결정됨
		node->Rank = node->L_cnt + 1;
	}
	else {
		if (node->P->L == node) {//왼쪽 자식
			//부모의 등수 == 부모보다 작은 모든숫자 +1
			//내등수 == 부모의 등수 - 나의 오른쪽 자식수 + 1(자기자신)
			//나의 오른쪽 자식 == 나와 부모사이의 숫자들( 나보단 크고 부모보단 작음 )
			node->Rank = node->P->Rank - (node->R_cnt + 1);
		}
		else if (node->P->R == node) {//오른쪽 자식
			//내등수 == 부모의 등수 + 나의 왼쪽 자식수 + 1(자기자신)
			//나의 왼쪽 자식 == 나와 부모사이의 숫자들( 부모보단 크고 나보단 작음 )
			node->Rank = node->P->Rank + (node->L_cnt + 1);
		}
	}
	//등수 탐색
	if (node->Rank == r) {
		return node->idx;
	}
	else if (node->Rank > r) {
		W(node->L, r);
	}
	else if (node->Rank < r) {
		W(node->R, r);
	}
}

int A(Node* node, int v) {//기본적인 동작은 W와 유사
	if (node->P == NULL) {//부모 X
		node->Rank = node->L_cnt + 1;
	}
	else {
		if (node->P->L == node) {//왼쪽 자식
			node->Rank = node->P->Rank - (node->R_cnt + 1);
		}
		else if (node->P->R == node) {//오른쪽 자식
			node->Rank = node->P->Rank + (node->L_cnt + 1);
		}
	}


	if (node->val > v) {//v값이 더 작은경우 >> 왼쪽 탐색
		if (node->L == E_NULL || node->L == NULL) {//왼쪽 자식 없음
			return node->Rank - 1;//자기자신도 v보다 크기 때문에 자기 자신 제외한 랭크 리턴
		}
		else {
			A(node->L, v);
		}
	}
	else if (node->val < v) {//v값이 더 큰경우 >> 오른쪽 탐색
		if (node->R == E_NULL || node->R == NULL) {//오른쪽 자식 없음
			return node->Rank;//자기자신도 v보다 작기 때문에 자기 자신 포함한 랭크 리턴
		}
		else {
			A(node->R, v);
		}
	}
	else {//v와 값이 같은경우 >> 자기자신 빼고 랭크 리턴
		return node->Rank - 1;
	}

}

int F(Node* node, int find) {
	if (node == NULL)return NULL;
	if (node->val > find) return F(node->L, find);
	else if (node->val < find) return F(node->R, find);
	return node->idx;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("array.inp", "r", stdin);
	freopen("array.out", "w", stdout);

	E_NULL = (Node*)malloc(sizeof(Node));
	E_NULL->color = 'B';
	E_NULL->idx = -1;
	E_NULL->P = NULL;
	E_NULL->L = E_NULL->R = NULL;

	root = NULL;

	int n, m, k, v;
	char ty;
	ll ans = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> k;
		arr[i] = k;
		Insertion(k, i);
	}
	for (int i = 0; i < m; i++) {
		cin >> ty;
		if (ty == 'c') {
			cin >> k >> v;
			C(root, k, v);
		}
		else if (ty == 'w') {
			cin >> k;
			ans += W(root, k);
			ans %= DIV;
		}
		else if (ty == 'a') {
			cin >> v;
			ans += A(root, v);
			ans %= DIV;
		}
		else if (ty == 'f') {//완료
			cin >> v;
			ans += F(root, v);
			ans %= DIV;
		}
	}
	cout << ans;
	return 0;
}
//이진트리버전 - 윤태영
//<c k v> :  즉, 배열의 특정 위치의 값을 지정한 것으로 바꾼다.이 연산 후에도 배열 에 저장된 값은 서로 다르다는 것이 보장된다.
//<w k> : 배열 a에 저장된 것 중에서 k >=1번째 작은 값이 저장된 곳의 위치를 찾아 그 인덱스를 출력한다.
//<a v> : 배열 a에 저장된 것 중에서  v보다 작은 값이 몇 개인지 찾아, 그 개수를 출력한다.
//<f v> : 값 v가 저장된 곳의 위치를 찾아 그 인덱스를 출력한다.이 때, 는 배열에 반드시 있는 수임이 보장된다.
//배열크기 10~10만, 연산횟수 10~50만 값 크기 -10 9승 +10 의 9승 -1억~1억

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAX 1000000007
using namespace std;

ifstream in("array.inp");
ofstream out("array.out");

typedef struct node {
	int idx; // 배열인덱스
	int val; // 값
	int LCN; // 왼쪽자식 개수
	int RCN; // 오른쪽자식 개수
	int rank; // 랭킹 
	node* LC, * RC, * P;
}node;
long long ret;
int n, m, root_idx;
vector<node> tree;

node make_node(int val, int idx) { //insert
	node newnode;
	newnode.val = val;
	newnode.idx = idx;
	newnode.LCN = 0;
	newnode.RCN = 0;
	newnode.rank = 0;
	newnode.LC = NULL;
	newnode.RC = NULL;
	newnode.P = NULL;
	return newnode;
}

void tree_connect(node* root, int idx) {
	if (root->val > tree[idx].val) { //왼자
		root->LCN++;
		if (root->LC == NULL) { //비어있음
			root->LC = &tree[idx];
			tree[idx].P = root;
		}
		else { //자식있음
			tree_connect(root->LC, idx);
		}
	}
	else if (root->val < tree[idx].val) { //오자
		root->RCN++;
		if (root->RC == NULL) { //비어있음
			root->RC = &tree[idx];
			tree[idx].P = root;
		}
		else { //자식있음
			tree_connect(root->RC, idx);
		}
	}
}

node* find_posi(node* root) {//오른쪽최왼자
	if (root->LC == NULL)
		return root;
	else
		root->LCN--;
	find_posi(root->LC);
}

void del(node* root, int idx, int val) {  // 오자최왼자
	node* a = root;

	if (root->RC != NULL) { //오자o
		if (root->RC->LC != NULL) { //오자o 왼자o
			root->RCN--;
			a = find_posi(root->RC); //오자-최왼자
			node temp = *a;
			a->LCN = root->LCN;
			a->RCN = root->RCN;
			a->LC = root->LC;
			a->RC = root->RC;
			a->P = root->P;
			if (a->LC != NULL)
				a->LC->P = a;
			if (a->RC != NULL)
				a->RC->P = a;

			if (temp.RC != NULL) { //a 단말x
				temp.P->LC = temp.RC;
				temp.RC->P = temp.P;
			}
			else {
				temp.P->LC = NULL;
			}
		}
		else { //오자o 왼자x
			root->RCN--;
			a = root->RC;
			//node temp = *a;
			a->LCN = root->LCN;
			a->RCN = root->RCN;
			a->LC = root->LC;
			a->P = root->P;
			if (a->LC != NULL)
				a->LC->P = a;
			if (a->RC != NULL)
				a->RC->P = a;
			//a->RC = root;
			//if (temp.RC != NULL) { //a 단말x
			//	temp.P->RC = temp.RC;
			//	temp.RC->P = temp.P;
			//}
		}
		if (root->P != NULL) {//부모o
			if (root->P->LC == root)
				root->P->LC = a;
			else if (root->P->RC == root)
				root->P->RC = a;
		}
	}
	else { //오자x 오른쪽자식이 없는상태에서 왼쪽자식이 있고없고는 단말노드ox임
		if (root->LC != NULL) { //오자x 왼자o
			root->LCN--;
			a = root->LC;
			root->LC->P = root->P;
			if (root->P != NULL) {//부모o
				if (root->P->LC == root)
					root->P->LC = root->LC;
				else if (root->P->RC == root)
					root->P->RC = root->LC;
			}
		}
		else {//오자x 왼자x
			//사실 이 경우는 무조건 부모가있다
			if (root->P != NULL) {//부모o
				if (root->P->LC == root)
					root->P->LC = root->LC;
				else if (root->P->RC == root)
					root->P->RC = root->LC;
			}
		}
	}
	if (root->idx == root_idx)
		root_idx = a->idx;
	tree[idx] = make_node(val, idx); //노드 재생성 새로운val값으로
	tree_connect(&tree[root_idx], idx); //노드 재연결
}

void op_c(node* root, int idx, int val) { // tree[idx] = val; //idx 삭제 -> idx val 변경 -> idx 삽입

	if (root->val > tree[idx].val) { //왼자 탐색
		root->LCN--; // 왼쪽에 있는 자식이 내역할을 대신하기때문에 자기자신은 자식개수에서 빼야함
		op_c(root->LC, idx, val);
	}
	else if (root->val < tree[idx].val) { //오자 탐색
		root->RCN--;// 오른쪽에 있는 자식이 내역할을 대신하기때문에 자기자신은 자식개수에서 빼야함
		op_c(root->RC, idx, val);
	}
	else { //찾음 -> 삭제수행 

		del(root, idx, val);
		return;
	}

}

int op_w(node* root, int rank) { //rank번째 작은값의 idx출력
	if (root->P == NULL) { //부모가 없다
		root->rank = root->LCN + 1;
	}
	else {//부모가 있다면 순위 수정 왼쪽자식or오른쪽자식에 따라 다름
		if (root->P->LC == root) { //왼쪽 자식이다.
			root->rank = root->P->rank - (root->RCN + 1);
		}
		else if (root->P->RC == root) { //오른쪽 자식이다.
			root->rank = root->P->rank + root->LCN + 1;
		}
	}

	if (root->rank > rank) { // 루트보다 더 작은 순위
		op_w(root->LC, rank);
	}
	else if (root->rank < rank) { // 루트보다 큰 순위
		op_w(root->RC, rank);
	}
	else { // 찾음
		return root->idx;
	}
}

int op_a(node* root, int val) { // val보다 작은값의 개수 자식이 없는구간까지 찾아내려가야함

	if (root->P == NULL) { //부모가 없다
		root->rank = root->LCN + 1;
	}
	else {//부모가 있다면 순위 수정 왼쪽자식or오른쪽자식에 따라 다름
		if (root->P->LC == root) { //왼쪽 자식이다.
			root->rank = root->P->rank - (root->RCN + 1);
		}
		else if (root->P->RC == root) { //오른쪽 자식이다.
			root->rank = root->P->rank + root->LCN + 1;
		}
	}

	if (root->val > val) { //왼쪽 탐색
		if (root->LC == NULL) { //왼쪽자식이 없다
			return root->rank - 1;
		}
		else {
			op_a(root->LC, val);
		}
	}
	else if (root->val < val) { //오른쪽 탐색
		if (root->RC == NULL) { //오른쪽 자식이 없다.
			return root->rank;
		}
		else {
			op_a(root->RC, val);
		}
	}
	else { //같은경우
		return root->rank - 1;
	}
}

int op_f(node* root, int val) {
	if (root->val > val) {
		op_f(root->LC, val);
	}
	else if (root->val < val) {
		op_f(root->RC, val);
	}
	else {
		return root->idx;
	}
}

int main() {
	in >> n >> m;
	tree.resize(n);
	vector<int> v;
	for (int i = 0; i < n; i++) { // 배열생성
		int val; in >> val;
		v.push_back(val);
		tree[i] = make_node(val, i);
	}

	for (int i = 1; i < n; i++) { // 트리연결 (tree[0]이 루트노드)
		tree_connect(&tree[root_idx], i);
	}

	for (int i = 0; i < m; i++) { // 명령실행
		char op; in >> op;
		int val;
		switch (op) {
		case 'c':
			int val2;
			in >> val >> val2;
			op_c(&tree[root_idx], val, val2);
			break;
		case 'w':
			in >> val;
			ret += op_w(&tree[root_idx], val);
			break;
		case 'a':
			in >> val;
			ret += op_a(&tree[root_idx], val);
			break;
		case 'f':
			in >> val;
			ret += op_f(&tree[root_idx], val);
			break;
		}
	}

	out << ret % MAX;

	return 0;
}