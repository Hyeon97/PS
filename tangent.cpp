#include <iostream>
#include <vector>
#include <algorithm>

#pragma warning(disable:4996)
using namespace std;

int T, P, Q;
typedef struct point {
	long long x;
	long long y;
	char where;//�ش� ��ǥ�� ��������� �����ִ°� Ȯ��
	int original_idx;//��ó�� �� ��ǥ�� ���� ���� ����
}point;

point p[10001];//�ٰ��� p�� ��� ������ �Է¹���
point q[10001];//�ٰ��� q�� ��� ������ �Է¹���
point All[20001];//�ٰ��� p,q�� ��� ������ �Է¹���
vector<point>convex;//�ٰ��� p,q �ش��� �� �ΰ��� ��ģ ���ϲ����� �ش����� ��
vector<point>PQ;


long long int ccw(point a, point b, point c) {//������ a ���� >> ��ȸ�� ��� >> ��ȸ�� 0 >> ��������
	return (a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
}

bool cmp_x(point a, point b) {//x���� ���� || x�� y�� �ٲٸ� y���� ������ ��
	if (a.x != b.x) return a.x < b.x;
	else return a.y < b.y;
}

bool cmp_c(point a, point b) {//�ݽð���� ����
	long long  angle = ccw(All[0], a, b);
	if (angle != 0)return angle > 0;
	else return (a.x + a.y) < (b.x + b.y);
}

//ppt�� �ִ°� �״�� ���ٹ���
bool between(point a, point b, point c) {
	int temp = ccw(a, b, c);//ccw�� Ȯ�ο�
	if (ccw(a, b, c))return false;//ccw�� 0�̳��;� �������� ��ġ���� �ǹ� || 0 �̿��� ���� ���°�� �������� ���� �������� ������ �ƴ�
	//�������� ��ġ�ϴ� ���
	if (a.x != b.x) {//x���� �ٸ��� x�� ����
		return a.x <= c.x && c.x <= b.x || b.x <= c.x && c.x <= a.x;
	}
	else {//x���� ������ y�� ����
		return a.y <= c.y && c.y <= b.y || b.y <= c.y && c.y <= a.y;
	}
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("tangent.inp", "r", stdin);
	freopen("tangent.out", "w", stdout);
	cin >> T;
	while (T--) {
		cin >> P;
		//�� �ٰ��� ��ǥ�� ���ö� �ݽð�������� ���ĵǾ ����
		//p
		for (int i = 0; i < P; i++) {
			cin >> p[i].x >> p[i].y;
			p[i].where = All[i].where = 'p';
			All[i].original_idx = p[i].original_idx = i;
			All[i].x = p[i].x; All[i].y = p[i].y;
		}
		//q
		cin >> Q;
		for (int i = 0; i < Q; i++) {
			cin >> q[i].x >> q[i].y;
			q[i].where = All[i + P].where = 'q';
			q[i].original_idx = i;
			All[i + P].x = q[i].x; All[i + P].y = q[i].y;
			//All[i + P].original_idx = i + P;
			All[i + P].original_idx = i;
		}

		//���ϲ��� ���� ����
		point Prev, Next;
		sort(All, All + P + Q, cmp_x);//x ������ ���� //x�� �����Ҳ��� xy�ݴ��
		sort(All + 1, All + P + Q, cmp_c);//������ ���� �ݽð�������� ����
		convex.push_back(All[0]);
		convex.push_back(All[1]);
		for (int i = 1; i < P + Q; i++) {
			while (convex.size() >= 2) {
				Next = convex.back();
				convex.pop_back();
				Prev = convex.back();
				if (ccw(Prev, Next, All[i]) > 0) {
					convex.push_back(Next);
					break;
				}
			}
			convex.push_back(All[i]);
		}
		//��ü �ش������� ����� p ����� q �ٰ����� �����ִ��� ���� 
		int Size = convex.size();
		for (int i = 0; i < Size; i++) {
			int j = (i + 1) % Size;
			if (convex[i].where != convex[j].where) {
				PQ.push_back(convex[i]);
				PQ.push_back(convex[j]);
			}
		}
		convex.clear();
		//���ܴ� �� 2����
		//1�� ���� �� �ش��� ���̿� �ٸ����� ���ִ� ���
		//�� ���� ���̿� �ٸ����� ���ִ°��(��������) >> �ش������� ���� || �ִ��� ���� ª���ŷ�
		bool temp;
		if (PQ[1].where == 'q' && PQ[2].where == 'q') {
			for (int j = 0; j < P + Q; j++) {
				//�ش����� ���� ���� �������� ��ġ�ϴ��� Ȯ��
				if (All[j].where == 'p') {//�������� ��ġ�ϴ°�� convex_p[i]�� ���� ������ ������ �ٲ���
					temp = between(PQ[0], PQ[1], All[j]);//between �� Ȯ�ο�
					if (temp) {
						PQ[0] = All[j];
					}
				}
				else {
					temp = between(PQ[0], PQ[1], All[j]);
					if (temp) {
						PQ[1] = All[j];
					}
				}
			}
			for (int j = 0; j < P + Q; j++) {
				//�ش����� ���� ���� �������� ��ġ�ϴ��� Ȯ��
				if (All[j].where == 'p') {//�������� ��ġ�ϴ°�� convex_p[i]�� ���� ������ ������ �ٲ���
					temp = between(PQ[3], PQ[2], All[j]);//between �� Ȯ�ο�
					if (temp) {
						PQ[3] = All[j];
					}
				}
				else {
					temp = between(PQ[3], PQ[2], All[j]);
					if (temp) {
						PQ[2] = All[j];
					}
				}
			}
			// p q q p
			//�ٰ��� P,Q���� �������� ������ ���������� ��� ã�Ƴ�����
			//p
			for (int i = PQ[0].original_idx;; i = (i + 1) % P) {
				convex.push_back(p[i]);
				if (i == PQ[3].original_idx)break;
			}
			//q
			for (int i = PQ[2].original_idx;; i = (i + 1) % Q) {
				convex.push_back(q[i]);
				if (i == PQ[1].original_idx)break;
			}
		}
		else if (PQ[1].where == 'p' && PQ[2].where == 'p') {
			for (int j = 0; j < P + Q; j++) {
				//�ش����� ���� ���� �������� ��ġ�ϴ��� Ȯ��
				if (All[j].where == 'p') {//�������� ��ġ�ϴ°�� convex_p[i]�� ���� ������ ������ �ٲ���
					temp = between(PQ[1], PQ[0], All[j]);//between �� Ȯ�ο�
					if (temp) {
						PQ[1] = All[j];
					}
				}
				else {
					temp = between(PQ[1], PQ[0], All[j]);
					if (temp) {
						PQ[0] = All[j];
					}
				}
			}
			for (int j = 0; j < P + Q; j++) {
				//�ش����� ���� ���� �������� ��ġ�ϴ��� Ȯ��
				if (All[j].where == 'p') {//�������� ��ġ�ϴ°�� convex_p[i]�� ���� ������ ������ �ٲ���
					temp = between(PQ[2], PQ[3], All[j]);//between �� Ȯ�ο�
					if (temp) {
						PQ[2] = All[j];
					}
				}
				else {
					temp = between(PQ[2], PQ[3], All[j]);
					if (temp) {
						PQ[3] = All[j];
					}
				}
			}
			// q p p q
			//�ٰ��� P,Q���� �������� ������ ���������� ��� ã�Ƴ�����
			//p
			for (int i = PQ[2].original_idx;; i = (i + 1) % P) {
				convex.push_back(p[i]);
				if (i == PQ[1].original_idx)break;
			}
			//q
			for (int i = PQ[0].original_idx;; i = (i + 1) % Q) {
				convex.push_back(q[i]);
				if (i == PQ[3].original_idx)break;
			}
		}

		double area = 0;
		//������ ���� �������� �̿� ������ ���� ����
		//ù��° ������ �������� �����ؼ� ���� ������
		for (int i = 1; i < convex.size() - 1; ++i) area += ccw(convex[0], convex[i], convex[i + 1]);
		//2������ ��� >> �ѵ����� �ش��� 2���� �������(�ش����� �����ϰ� ������ ��������� �� �ٰ������� ���̸� ���ؾ� �ϴ� �κп� �� ������ �ǹ�) >> ������� ���̸�ŭ ����
		if (PQ[1].where == 'q' && PQ[2].where == 'q') {
			if (PQ[1].x == PQ[2].x && PQ[1].y == PQ[2].y) {//q
				for (int i = 1; i < Q - 1; i++) area += ccw(q[0], q[i], q[i + 1]);
			}
			if (PQ[0].x == PQ[3].x && PQ[0].y == PQ[3].y) {//p
				for (int i = 1; i < P - 1; i++) area += ccw(p[0], p[i], p[i + 1]);
			}
		}
		else if (PQ[1].where == 'p' && PQ[2].where == 'p') {
			if (PQ[1].x == PQ[2].x && PQ[1].y == PQ[2].y) {//p
				for (int i = 1; i < P - 1; i++) area += ccw(p[0], p[i], p[i + 1]);
			}
			if (PQ[0].x == PQ[3].x && PQ[0].y == PQ[3].y) {//q
				for (int i = 1; i < Q - 1; i++) area += ccw(q[0], q[i], q[i + 1]);
			}
		}

		if (area < 0)area *= -1;
		//if (temp_area < 0)temp_area *= -1;
		//if (temp_area)area -= temp_area / 2;
		cout.precision(1);//cout ��½� �Ҽ��� 1�ڸ� �������ִ°�
		cout << fixed << area / 2 << '\n';

		//�ʱ�ȭ
		convex.clear();
		PQ.clear();
	}

	return 0;
}

