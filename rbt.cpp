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

Node* Search(Node* node, int data) {//대상노드를 찾음
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

Node* find_Min(Node* node) {//대상노드의 오른쪽 서브트리에서 제일 작은값 리턴
	if (node == NULL)return NULL;
	if (node == E_NULL)return E_NULL;
	if (node->LC == E_NULL)return node;
	return find_Min(node->LC);
}

//(Node*)& node >> root에 node라는 이름의 새로운 이름을 추가해서 그대로 타고 내려가게 함
void Insert(Node*& node, Node* newNode) {//기본적인 삽입 
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

void ReBuild_Insert(Node*& root, Node* node) {//조건 안맞을시 트리 재구축 root와 재구축 대상노드
	while (node != root && node->parent->color == 'R') {//부모가 red 인 경우 양쪽 자식은 무조건 black

		if (node->parent == node->parent->parent->LC) {//부모가 조부모 기준 왼쪽 자식
			Node* u = node->parent->parent->RC;//삼촌 노드는 조부모의 오른쪽 자식
			if (u->color == 'R') {//Case 1 삼촌의 색이 red 일때
				node->parent->color = 'B';//부모색 변경
				u->color = 'B';//삼촌색 변경
				node->parent->parent->color = 'R';//조부모 색 변경
				node = node->parent->parent;//재구축 대상노드를 조부모로 변경
			}
			else { //Case 2,3 공통조건 부모가 red 삼촌이 black 인 경우
				if (node == node->parent->RC) {//Case 2 삽입노드가 부모의 오른쪽 자식
					node = node->parent;
					LeftLotate(root, node);//대상노드의 부모기준 왼쪽회전
				}
				//Case 3 삽입노드가 부모의 왼쪽 자식인 경우
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				RightLotate(root, node->parent->parent);//대상노드의 조부모 기준 오른쪽 회전
			}
		}
		else {//부모가 조부모 기준 오른쪽 자식
			Node* u = node->parent->parent->LC;//삼촌 노드는 조부모의 오른쪽 자식
			if (u->color == 'R') {//Case 1 삼촌의 색이 red 일때
				node->parent->color = 'B';//부모색 변경
				u->color = 'B';//삼촌색 변경
				node->parent->parent->color = 'R';//조부모 색 변경
				node = node->parent->parent;//재구축 대상노드를 조부모로 변경
			}
			else { //Case 2,3 공통조건 부모가 red 삼촌이 black 인 경우
				if (node == node->parent->LC) {//Case 2 삽입노드가 부모의 오른쪽 자식
					node = node->parent;
					RightLotate(root, node);//대상노드의 부모기준 왼쪽회전
				}
				//Case 3 삽입노드가 부모의 왼쪽 자식인 경우
				node->parent->color = 'B';
				node->parent->parent->color = 'R';
				LeftLotate(root, node->parent->parent);//대상노드의 조부모 기준 오른쪽 회전
			}
		}
	}
	root->color = 'B';//root 노드는 항상 Black 
}

void Insertion(int data) {
	Node* newNode = makeNode(data);
	newNode->color = 'R';
	newNode->LC = E_NULL;
	newNode->RC = E_NULL;
	Insert(root, newNode);//노드 삽입
	ReBuild_Insert(root, newNode);//삽입후 재구축
}

void ReBuild_delete(Node*& root, Node* x) {
	Node* u = NULL;
	while (x->parent != NULL && x->color == 'B') {
		if (x == x->parent->LC) {//재구축 대상이 부모의 왼쪽 자식
			u = x->parent->RC;//삼촌은 부모의 오른쪽 자식
			if (u->color == 'R') {//삼촌색 Red
				u->color = 'B';
				x->parent->color = 'R';
				LeftLotate(root, x->parent);//x의 부모기준 왼쪽회전
			}
			else {//삼촌색 Black
				if (u->LC->color == 'B' && u->RC->color == 'B') {//삼촌의 두 자식모두 Black
					u->color = 'R';
					x = x->parent;
				}//삼촌의 자식중 하나라도 Red
				else {
					if (u->RC->color == 'B') {//삼촌의 오른쪽자식이 Black
						u->color = 'R';
						u->LC->color = 'B';
						RightLotate(root, u);//삼촌기준 오른족 회전
						u = x->parent->RC;//새로운 삼촌은 부모의 오른쪽 자식
					}
					//삼촌의 오른쪽 자식이 Red
					u->color = x->parent->color;
					x->parent->color = 'B';
					u->RC->color = 'B';
					LeftLotate(root, x->parent);//부모기준 왼쪽회전
					x = root;
				}
			}
		}
		else {//재구축 대상이 부모의 오른쪽 자식
			u = x->parent->LC;
			if (u->color == 'R') {//삼촌의 색 Red
				u->color = 'B';
				x->parent->color = 'R';
				RightLotate(root, x->parent);//x의 부모기준 우측회전
			}
			else {//삼촌의 색 Black
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
	Node* y = NULL;//실제로 삭제되는 노드
	Node* x = NULL;//실제로 삭제되는 노드의 유일한 자식 or 자식 없음 

	Node* z = Search(root, data);
	if (z->LC == E_NULL || z->RC == E_NULL) {//삭제대상노드의 자식 X
		y = z;
	}
	else {
		y = find_Min(z->RC);//오른쪽 서브트리에서 제일 작은 값을 가져옴 Successor
		z->key = y->key;//실 삭제노드의 값을 덮어씌움
	}
	//실삭제대상(y)의 자식이 있는경우
	if (y->LC != E_NULL)x = y->LC;
	else x = y->RC;

	x->parent = y->parent;
	if (y->parent == NULL) {//실 삭제대상이 root 인경우
		if (x == E_NULL)root = NULL;
		else root = x;//x가 새로운 root 가 됨
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
