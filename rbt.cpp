#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <stdlib.h>

#pragma warning(disable:4996)
using namespace std;

typedef struct Node {
	int key = -1;
	char color = 'B';
	Node* LC = NULL;
	Node* RC = NULL;
	Node* parent = NULL;
}Node;

Node* root, * E_NULL;

Node* makeNode(int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = data;
	node->parent = NULL;
	node->LC = node->RC = NULL;
	return node;
}

Node* Search(Node* node, int data) {//����带 ã��
	if (node == NULL)return NULL;
	if (node->key > data) return Search(node->LC, data);
	else if (node->key < data) return Search(node->RC, data);
	return node;
	/*while (node != NULL || node != E_NULL) {
		if (node->key > data)node = node->LC;
		else if (node->key < data)node = node->RC;
	}
	return node;*/
};

Node* find_Min(Node* node) {//������� ������ ����Ʈ������ ���� ������ ����
	if (node == NULL)return NULL;
	if (node == E_NULL)return E_NULL;
	if (node->LC == E_NULL)return node;
	return find_Min(node->LC);
}

//(Node*)& node >> root�� node��� �̸��� ���ο� �̸��� �߰��ؼ� �״�� Ÿ�� �������� ��
void Insert(Node*& node, Node* newNode) {//�⺻���� ���� 
	if (node == NULL)node = newNode;
	if (node->key < newNode->key) {
		if (node->RC == E_NULL) {
			node->RC = newNode;
			newNode->parent = node;
		}
		else {
			Insert(node->RC, newNode);
		}
	}
	else if (node->key > newNode->key) {
		if (node->LC == E_NULL) {
			node->LC = newNode;
			newNode->parent = node;
		}
		else {
			Insert(node->LC, newNode);
		}
	}
}

void RightLotate(Node*& root, Node* node) {
	Node* LeftCh = node->LC;
	node->LC = LeftCh->RC;
	if (LeftCh->RC != E_NULL) {
		LeftCh->RC->parent = node;
	}
	LeftCh->parent = node->parent;
	if (node->parent == NULL) {
		root = LeftCh;
	}
	else {
		if (node == node->parent->LC) {
			node->parent->LC = LeftCh;
		}
		else {
			node->parent->RC = LeftCh;
		}
	}
	LeftCh->RC = node;
	node->parent = LeftCh;
}

void LeftLotate(Node*& root, Node* node) {
	Node* RightCh = node->RC;
	node->RC = RightCh->LC;
	if (RightCh->LC != E_NULL) {
		RightCh->LC->parent = node;
	}
	RightCh->parent = node->parent;
	if (node->parent == NULL) {
		root = RightCh;
	}
	else {
		if (node == node->parent->LC) {
			node->parent->LC = RightCh;
		}
		else {
			node->parent->RC = RightCh;
		}
	}
	RightCh->LC = node;
	node->parent = RightCh;
}

void ReBuild_Insert(Node*& root, Node* node) {//���� �ȸ����� Ʈ�� �籸�� root�� �籸�� �����
	while (node != root && node->parent->color == 'R') {//�θ� red �� ��� ���� �ڽ��� ������ black

		if (node->parent == node->parent->parent->LC) {//�θ� ���θ� ���� ���� �ڽ�
			Node* u = node->parent->parent->RC;//���� ���� ���θ��� ������ �ڽ�
			if (u->color == 'R') {//Case 1 ������ ���� red �϶�
				node->parent->color = 'B';//�θ�� ����
				u->color = 'B';//���̻� ����
				node->parent->parent->color = 'R';//���θ� �� ����
				node = node->parent->parent;//�籸�� ����带 ���θ�� ����
			}
			else { //Case 2,3 �������� �θ� red ������ black �� ���
				if (node == node->parent->RC) {//Case 2 ���Գ�尡 �θ��� ������ �ڽ�
					node = node->parent;
					LeftLotate(root, node);//������� �θ���� ����ȸ��
				}
				//Case 3 ���Գ�尡 �θ��� ���� �ڽ��� ���
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				RightLotate(root, node->parent->parent);//������� ���θ� ���� ������ ȸ��
			}
		}
		else {//�θ� ���θ� ���� ������ �ڽ�
			Node* u = node->parent->parent->LC;//���� ���� ���θ��� ������ �ڽ�
			if (u->color == 'R') {//Case 1 ������ ���� red �϶�
				node->parent->color = 'B';//�θ�� ����
				u->color = 'B';//���̻� ����
				node->parent->parent->color = 'R';//���θ� �� ����
				node = node->parent->parent;//�籸�� ����带 ���θ�� ����
			}
			else { //Case 2,3 �������� �θ� red ������ black �� ���
				if (node == node->parent->LC) {//Case 2 ���Գ�尡 �θ��� ������ �ڽ�
					node = node->parent;
					RightLotate(root, node);//������� �θ���� ����ȸ��
				}
				//Case 3 ���Գ�尡 �θ��� ���� �ڽ��� ���
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				LeftLotate(root, node->parent->parent);//������� ���θ� ���� ������ ȸ��
			}
		}
	}
	root->color = 'B';//root ���� �׻� Black 
}

void Insertion(int data) {
	Node* newNode = makeNode(data);
	newNode->color = 'R';
	newNode->LC = E_NULL;
	newNode->RC = E_NULL;
	Insert(root, newNode);//��� ����
	ReBuild_Insert(root, newNode);//������ �籸��
}

void ReBuild_delete(Node*& root, Node* x) {
	Node* u = NULL;
	while (x->parent != NULL && x->color == 'B') {
		if (x == x->parent->LC) {//�籸�� ����� �θ��� ���� �ڽ�
			u = x->parent->RC;//������ �θ��� ������ �ڽ�
			if (u->color == 'R') {//���̻� Red
				u->color = 'B';
				x->parent->color = 'R';
				LeftLotate(root, x->parent);//x�� �θ���� ����ȸ��
			}
			else {//���̻� Black
				if (u->LC->color == 'B' && u->RC->color == 'B') {//������ �� �ڽĸ�� Black
					u->color = 'R';
					x = x->parent;
				}//������ �ڽ��� �ϳ��� Red
				else {
					if (u->RC->color == 'B') {//������ �������ڽ��� Black
						u->color = 'R';
						u->LC->color = 'B';
						RightLotate(root, u);//���̱��� ������ ȸ��
						u = x->parent->RC;//���ο� ������ �θ��� ������ �ڽ�
					}
					//������ ������ �ڽ��� Red
					u->color = x->parent->color;
					x->parent->color = 'B';
					u->RC->color = 'B';
					LeftLotate(root, x->parent);//�θ���� ����ȸ��
					x = root;
				}
			}
		}
		else {//�籸�� ����� �θ��� ������ �ڽ�
			u = x->parent->LC;
			if (u->color == 'R') {//������ �� Red
				u->color = 'B';
				x->parent->color = 'R';
				RightLotate(root, x->parent);//x�� �θ���� ����ȸ��
			}
			else {//������ �� Black
				if (u->LC->color == 'B' && u->RC->color == 'B') {
					u->color = 'R';
					x = x->parent;
				}
				else {
					if (u->LC->color == 'B') {
						u->color = 'R';
						u->RC->color = 'B';
						LeftLotate(root, u);
						u = x->parent->LC;
					}
					u->color = x->parent->color;
					x->parent->color = 'B';
					u->LC->color = 'B';
					RightLotate(root, x->parent);
					x = root;
				}
			}
		}
	}
	x->color = 'B';
}

void Deletion(int data) {
	Node* y = NULL;//������ �����Ǵ� ���
	Node* x = NULL;//������ �����Ǵ� ����� ������ �ڽ� or �ڽ� ���� 

	Node* z = Search(root, data);
	if (z->LC == E_NULL || z->RC == E_NULL) {//����������� �ڽ� X
		y = z;
	}
	else {
		y = find_Min(z->RC);//������ ����Ʈ������ ���� ���� ���� ������ Successor
		z->key = y->key;//�� ��������� ���� �����
	}
	//�ǻ������(y)�� �ڽ��� �ִ°��
	if (y->LC != E_NULL)x = y->LC;
	else x = y->RC;

	x->parent = y->parent;
	if (y->parent == NULL) {//�� ��������� root �ΰ��
		if (x == E_NULL)root = NULL;
		else root = x;//x�� ���ο� root �� ��
	}
	else {
		if (y == y->parent->LC) {
			y->parent->LC = x;
		}
		else {
			y->parent->RC = x;
		}
	}
	if (y->color == 'B') ReBuild_delete(root, x);
}

void Find_color(Node* tr, int key) {
	Node* temp = tr;
	while (temp != E_NULL) {
		if (temp->key == key) {
			if (temp->color == 'R')cout << "color(" << key << "): RED\n";
			else if (temp->color == 'B')cout << "color(" << key << "): BLACK\n";
			break;
		}
		if (temp->key > key)temp = temp->LC;
		else temp = temp->RC;

	}
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("rbt.inp", "r", stdin);
	freopen("rbt.out", "w", stdout);

	E_NULL = (Node*)malloc(sizeof(Node));
	E_NULL->color = 'B';
	E_NULL->parent = NULL;
	E_NULL->LC = E_NULL->RC = NULL;

	root = NULL;

	char Ty;
	int num;

	while (1) {
		cin >> Ty >> num;
		if (num == -1)break;
		if (Ty == 'i') {
			Insertion(num);
		}
		else if (Ty == 'c') {
			Find_color(root, num);
		}
		else if (Ty == 'd') {
			Deletion(num);
		}

	}
	//root = TREE;
	return 0;
}
