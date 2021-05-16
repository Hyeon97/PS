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
	int idx;//�迭�ε���
	int L_cnt = 0;
	int R_cnt = 0;
	int Rank = 0;//ũ�� ����
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

//(Node*)& node >> root�� node��� �̸��� ���ο� �̸��� �߰��ؼ� �״�� Ÿ�� �������� ��
void Insert(Node*& node, Node* newNode) {//�⺻���� ���� 
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
	//ȸ����� ���ʻ����� ������ �ڽļ�
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
	//�ڽļ� ����
	node->L_cnt = LCH_RCNT;
	LeftCh->R_cnt = node->R_cnt + node->L_cnt + 1;
}

void LeftLotate(Node*& root, Node* node) {
	Node* RightCh = node->R;
	//ȸ����� ������ �ڽ��� ���� �ڽļ� 
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
	//�ڽļ� ����
	node->R_cnt = RCH_LCNT;
	RightCh->L_cnt = node->R_cnt + node->L_cnt + 1;
}

void ReBuild_Insert(Node*& root, Node* node) {//���� �ȸ����� Ʈ�� �籸�� root�� �籸�� �����
	while (node != root && node->P->color == 'R') {//�θ� red �� ��� ���� �ڽ��� ������ black

		if (node->P == node->P->P->L) {//�θ� ���θ� ���� ���� �ڽ�
			Node* u = node->P->P->R;//���� ���� ���θ��� ������ �ڽ�
			if (u->color == 'R') {//Case 1 ������ ���� red �϶�
				node->P->color = 'B';//�θ�� ����
				u->color = 'B';//���̻� ����
				node->P->P->color = 'R';//���θ� �� ����
				node = node->P->P;//�籸�� ����带 ���θ�� ����
			}
			else { //Case 2,3 �������� �θ� red ������ black �� ���
				if (node == node->P->R) {//Case 2 ���Գ�尡 �θ��� ������ �ڽ�
					node = node->P;
					LeftLotate(root, node);//������� �θ���� ����ȸ��
				}
				//Case 3 ���Գ�尡 �θ��� ���� �ڽ��� ���
				node->P->color = 'B';
				node->P->P->color = 'R';
				RightLotate(root, node->P->P);//������� ���θ� ���� ������ ȸ��
			}
		}
		else {//�θ� ���θ� ���� ������ �ڽ�
			Node* u = node->P->P->L;//���� ���� ���θ��� ������ �ڽ�
			if (u->color == 'R') {//Case 1 ������ ���� red �϶�
				node->P->color = 'B';//�θ�� ����
				u->color = 'B';//���̻� ����
				node->P->P->color = 'R';//���θ� �� ����
				node = node->P->P;//�籸�� ����带 ���θ�� ����
			}
			else { //Case 2,3 �������� �θ� red ������ black �� ���
				if (node == node->P->L) {//Case 2 ���Գ�尡 �θ��� ������ �ڽ�
					node = node->P;
					RightLotate(root, node);//������� �θ���� ����ȸ��
				}
				//Case 3 ���Գ�尡 �θ��� ���� �ڽ��� ���
				node->P->color = 'B';
				node->P->P->color = 'R';
				LeftLotate(root, node->P->P);//������� ���θ� ���� ������ ȸ��
			}
		}
	}
	root->color = 'B';//root ���� �׻� Black 
}

void Insertion(int data, int idx) {
	Node* newNode = makeNode(data, idx);
	newNode->color = 'R';
	newNode->L = E_NULL;
	newNode->R = E_NULL;
	Insert(root, newNode);//��� ����
	ReBuild_Insert(root, newNode);//������ �籸��
}

void ReBuild_delete(Node*& root, Node* x) {
	Node* u = NULL;
	while (x->P != NULL && x->color == 'B') {
		if (x == x->P->L) {//�籸�� ����� �θ��� ���� �ڽ�
			u = x->P->R;//������ �θ��� ������ �ڽ�
			if (u->color == 'R') {//���̻� Red
				u->color = 'B';
				x->P->color = 'R';
				LeftLotate(root, x->P);//x�� �θ���� ����ȸ��
			}
			else {//���̻� Black
				if (u->L->color == 'B' && u->R->color == 'B') {//������ �� �ڽĸ�� Black
					u->color = 'R';
					x = x->P;
				}//������ �ڽ��� �ϳ��� Red
				else {
					if (u->R->color == 'B') {//������ �������ڽ��� Black
						u->color = 'R';
						u->L->color = 'B';
						RightLotate(root, u);//���̱��� ������ ȸ��
						u = x->P->R;//���ο� ������ �θ��� ������ �ڽ�
					}
					//������ ������ �ڽ��� Red
					u->color = x->P->color;
					x->P->color = 'B';
					u->R->color = 'B';
					LeftLotate(root, x->P);//�θ���� ����ȸ��
					x = root;
				}
			}
		}
		else {//�籸�� ����� �θ��� ������ �ڽ�
			u = x->P->L;
			if (u->color == 'R') {//������ �� Red
				u->color = 'B';
				x->P->color = 'R';
				RightLotate(root, x->P);//x�� �θ���� ����ȸ��
			}
			else {//������ �� Black
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

Node* Search(Node* node, int val) {//����带 ã��
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

Node* find_Min(Node* node) {//������� ������ ����Ʈ������ ���� ������ ����
	if (node == NULL)return NULL;
	if (node == E_NULL)return E_NULL;
	if (node->L == E_NULL)return node;
	return find_Min(node->L);
}


void Deletion(int idx) {//������ �ε���
	Node* y = NULL;//������ �����Ǵ� ���
	Node* x = NULL;//������ �����Ǵ� ����� ������ �ڽ� or �ڽ� ���� 

	Node* z = Search(root, arr[idx]);
	if (z->L == E_NULL || z->R == E_NULL) {//����������� �ڽ� X
		y = z;
	}
	else {
		y = find_Min(z->R);//������ ����Ʈ������ ���� ���� ���� ������ Successor
		z->val = y->val;//�� ��������� ���� �����
		z->idx = y->idx;//�� ��������� idx�� �����
	}
	//�ǻ������(y)�� �ڽ��� �ִ°��
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
	if (y->P == NULL) {//�� ��������� root �ΰ��
		if (x == E_NULL)root = NULL;
		else root = x;//x�� ���ο� root �� ��
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
	//Ž���ϸ鼭 ��ŷ ����
	if (node->P == NULL) {//�θ� X
		//�θ� ������ ������ ��Ʈ
		//��Ʈ�� ������ �ڱ⺸�� ���� ���̵鸸 ����������
		//���� �ڽļ� + 1(�ڱ��ڽ�) ���ָ� �ڽ��� ������ ������
		node->Rank = node->L_cnt + 1;
	}
	else {
		if (node->P->L == node) {//���� �ڽ�
			//�θ��� ��� == �θ𺸴� ���� ������ +1
			//����� == �θ��� ��� - ���� ������ �ڽļ� + 1(�ڱ��ڽ�)
			//���� ������ �ڽ� == ���� �θ������ ���ڵ�( ������ ũ�� �θ𺸴� ���� )
			node->Rank = node->P->Rank - (node->R_cnt + 1);
		}
		else if (node->P->R == node) {//������ �ڽ�
			//����� == �θ��� ��� + ���� ���� �ڽļ� + 1(�ڱ��ڽ�)
			//���� ���� �ڽ� == ���� �θ������ ���ڵ�( �θ𺸴� ũ�� ������ ���� )
			node->Rank = node->P->Rank + (node->L_cnt + 1);
		}
	}
	//��� Ž��
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

int A(Node* node, int v) {//�⺻���� ������ W�� ����
	if (node->P == NULL) {//�θ� X
		node->Rank = node->L_cnt + 1;
	}
	else {
		if (node->P->L == node) {//���� �ڽ�
			node->Rank = node->P->Rank - (node->R_cnt + 1);
		}
		else if (node->P->R == node) {//������ �ڽ�
			node->Rank = node->P->Rank + (node->L_cnt + 1);
		}
	}


	if (node->val > v) {//v���� �� ������� >> ���� Ž��
		if (node->L == E_NULL || node->L == NULL) {//���� �ڽ� ����
			return node->Rank - 1;//�ڱ��ڽŵ� v���� ũ�� ������ �ڱ� �ڽ� ������ ��ũ ����
		}
		else {
			A(node->L, v);
		}
	}
	else if (node->val < v) {//v���� �� ū��� >> ������ Ž��
		if (node->R == E_NULL || node->R == NULL) {//������ �ڽ� ����
			return node->Rank;//�ڱ��ڽŵ� v���� �۱� ������ �ڱ� �ڽ� ������ ��ũ ����
		}
		else {
			A(node->R, v);
		}
	}
	else {//v�� ���� ������� >> �ڱ��ڽ� ���� ��ũ ����
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
		else if (ty == 'f') {//�Ϸ�
			cin >> v;
			ans += F(root, v);
			ans %= DIV;
		}
	}
	cout << ans;
	return 0;
}
//����Ʈ������ - ���¿�
//<c k v> :  ��, �迭�� Ư�� ��ġ�� ���� ������ ������ �ٲ۴�.�� ���� �Ŀ��� �迭 �� ����� ���� ���� �ٸ��ٴ� ���� ����ȴ�.
//<w k> : �迭 a�� ����� �� �߿��� k >=1��° ���� ���� ����� ���� ��ġ�� ã�� �� �ε����� ����Ѵ�.
//<a v> : �迭 a�� ����� �� �߿���  v���� ���� ���� �� ������ ã��, �� ������ ����Ѵ�.
//<f v> : �� v�� ����� ���� ��ġ�� ã�� �� �ε����� ����Ѵ�.�� ��, �� �迭�� �ݵ�� �ִ� ������ ����ȴ�.
//�迭ũ�� 10~10��, ����Ƚ�� 10~50�� �� ũ�� -10 9�� +10 �� 9�� -1��~1��

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAX 1000000007
using namespace std;

ifstream in("array.inp");
ofstream out("array.out");

typedef struct node {
	int idx; // �迭�ε���
	int val; // ��
	int LCN; // �����ڽ� ����
	int RCN; // �������ڽ� ����
	int rank; // ��ŷ 
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
	if (root->val > tree[idx].val) { //����
		root->LCN++;
		if (root->LC == NULL) { //�������
			root->LC = &tree[idx];
			tree[idx].P = root;
		}
		else { //�ڽ�����
			tree_connect(root->LC, idx);
		}
	}
	else if (root->val < tree[idx].val) { //����
		root->RCN++;
		if (root->RC == NULL) { //�������
			root->RC = &tree[idx];
			tree[idx].P = root;
		}
		else { //�ڽ�����
			tree_connect(root->RC, idx);
		}
	}
}

node* find_posi(node* root) {//�������ֿ���
	if (root->LC == NULL)
		return root;
	else
		root->LCN--;
	find_posi(root->LC);
}

void del(node* root, int idx, int val) {  // �����ֿ���
	node* a = root;

	if (root->RC != NULL) { //����o
		if (root->RC->LC != NULL) { //����o ����o
			root->RCN--;
			a = find_posi(root->RC); //����-�ֿ���
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

			if (temp.RC != NULL) { //a �ܸ�x
				temp.P->LC = temp.RC;
				temp.RC->P = temp.P;
			}
			else {
				temp.P->LC = NULL;
			}
		}
		else { //����o ����x
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
			//if (temp.RC != NULL) { //a �ܸ�x
			//	temp.P->RC = temp.RC;
			//	temp.RC->P = temp.P;
			//}
		}
		if (root->P != NULL) {//�θ�o
			if (root->P->LC == root)
				root->P->LC = a;
			else if (root->P->RC == root)
				root->P->RC = a;
		}
	}
	else { //����x �������ڽ��� ���»��¿��� �����ڽ��� �ְ����� �ܸ����ox��
		if (root->LC != NULL) { //����x ����o
			root->LCN--;
			a = root->LC;
			root->LC->P = root->P;
			if (root->P != NULL) {//�θ�o
				if (root->P->LC == root)
					root->P->LC = root->LC;
				else if (root->P->RC == root)
					root->P->RC = root->LC;
			}
		}
		else {//����x ����x
			//��� �� ���� ������ �θ��ִ�
			if (root->P != NULL) {//�θ�o
				if (root->P->LC == root)
					root->P->LC = root->LC;
				else if (root->P->RC == root)
					root->P->RC = root->LC;
			}
		}
	}
	if (root->idx == root_idx)
		root_idx = a->idx;
	tree[idx] = make_node(val, idx); //��� ����� ���ο�val������
	tree_connect(&tree[root_idx], idx); //��� �翬��
}

void op_c(node* root, int idx, int val) { // tree[idx] = val; //idx ���� -> idx val ���� -> idx ����

	if (root->val > tree[idx].val) { //���� Ž��
		root->LCN--; // ���ʿ� �ִ� �ڽ��� �������� ����ϱ⶧���� �ڱ��ڽ��� �ڽİ������� ������
		op_c(root->LC, idx, val);
	}
	else if (root->val < tree[idx].val) { //���� Ž��
		root->RCN--;// �����ʿ� �ִ� �ڽ��� �������� ����ϱ⶧���� �ڱ��ڽ��� �ڽİ������� ������
		op_c(root->RC, idx, val);
	}
	else { //ã�� -> �������� 

		del(root, idx, val);
		return;
	}

}

int op_w(node* root, int rank) { //rank��° �������� idx���
	if (root->P == NULL) { //�θ� ����
		root->rank = root->LCN + 1;
	}
	else {//�θ� �ִٸ� ���� ���� �����ڽ�or�������ڽĿ� ���� �ٸ�
		if (root->P->LC == root) { //���� �ڽ��̴�.
			root->rank = root->P->rank - (root->RCN + 1);
		}
		else if (root->P->RC == root) { //������ �ڽ��̴�.
			root->rank = root->P->rank + root->LCN + 1;
		}
	}

	if (root->rank > rank) { // ��Ʈ���� �� ���� ����
		op_w(root->LC, rank);
	}
	else if (root->rank < rank) { // ��Ʈ���� ū ����
		op_w(root->RC, rank);
	}
	else { // ã��
		return root->idx;
	}
}

int op_a(node* root, int val) { // val���� �������� ���� �ڽ��� ���±������� ã�Ƴ���������

	if (root->P == NULL) { //�θ� ����
		root->rank = root->LCN + 1;
	}
	else {//�θ� �ִٸ� ���� ���� �����ڽ�or�������ڽĿ� ���� �ٸ�
		if (root->P->LC == root) { //���� �ڽ��̴�.
			root->rank = root->P->rank - (root->RCN + 1);
		}
		else if (root->P->RC == root) { //������ �ڽ��̴�.
			root->rank = root->P->rank + root->LCN + 1;
		}
	}

	if (root->val > val) { //���� Ž��
		if (root->LC == NULL) { //�����ڽ��� ����
			return root->rank - 1;
		}
		else {
			op_a(root->LC, val);
		}
	}
	else if (root->val < val) { //������ Ž��
		if (root->RC == NULL) { //������ �ڽ��� ����.
			return root->rank;
		}
		else {
			op_a(root->RC, val);
		}
	}
	else { //�������
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
	for (int i = 0; i < n; i++) { // �迭����
		int val; in >> val;
		v.push_back(val);
		tree[i] = make_node(val, i);
	}

	for (int i = 1; i < n; i++) { // Ʈ������ (tree[0]�� ��Ʈ���)
		tree_connect(&tree[root_idx], i);
	}

	for (int i = 0; i < m; i++) { // ��ɽ���
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