#include <iostream>
#include <algorithm>
#include <vector>

#pragma warning(disable:4996);

typedef long long ll;
using namespace std;

typedef struct {
	ll x;
	ll y;
}point;

vector<point>P, Q;
int T;

ll ccw(point a, point b, point c) {//������ a ���� >> ��ȸ�� ��� >> ��ȸ�� 0 >> ��������
	return (a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
}

bool IsinP(point p) {
	ll c1 = ccw(p, P[0], P[1]);
	ll c2 = ccw(p, P[1], P[2]);
	ll c3 = ccw(p, P[2], P[0]);
	//ccw ��� �´� >0 or <0 �ΰ�� �ش����� ���� ���ο� ����
	if (c1 > 0 && c2 > 0 && c3 > 0 || c1 < 0 && c2 < 0 && c3 < 0) return true;
	return false;
}

bool IsinQ(point p) {
	ll c1 = ccw(p, Q[0], Q[1]);
	ll c2 = ccw(p, Q[1], Q[2]);
	ll c3 = ccw(p, Q[2], Q[0]);
	//ccw ��� �´� >0 or <0 �ΰ�� �ش����� ���� ���ο� ����
	if (c1 > 0 && c2 > 0 && c3 > 0 || c1 < 0 && c2 < 0 && c3 < 0) return true;
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("triangle.inp", "r", stdin);
	freopen("triangle.out", "w", stdout);
	cin >> T;
	point p;
	while (T--) {
		P.clear();
		Q.clear();
		//P�ﰢ�� ��ǥ
		for (int i = 0; i < 3; i++) {
			cin >> p.x >> p.y;
			P.push_back(p);
		}
		//Q�ﰢ�� ��ǥ
		for (int i = 0; i < 3; i++) {
			cin >> p.x >> p.y;
			Q.push_back(p);
		}
		//��ø(2) �з�
		ll p1 = 0, p2 = 0, q1 = 0, q2 = 0;
		bool flag = false;
		//P ����3�� Q ����3�� ��9���� ����� �� ��� Ȯ��
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//�� p,q �� (���-����) or (����-���) �� ���;���
				p1 = ccw(Q[j], Q[(j + 1) % 3], P[i]);
				p2 = ccw(Q[j], Q[(j + 1) % 3], P[(i + 1) % 3]);
				q1 = ccw(P[i], P[(i + 1) % 3], Q[j]);
				q2 = ccw(P[i], P[(i + 1) % 3], Q[(j + 1) % 3]);
				//���ǿ� �´°�� 2 ����� ����
				if (((p1 < 0 && p2 > 0) || (p1 > 0 && p2 < 0)) && ((q1 < 0 && q2 > 0) || (q1 > 0 && q2 < 0))) { cout << 2 << '\n'; flag = true; break; }
			}
			if (flag)break;
		}
		if (flag)continue;
		//��ø(2) ���� �ﰢ���� ��� ���ԵǴ°�� 
		for (int i = 0; i < 3; i++) {
			if (IsinQ(P[i])) {
				cout << 2 << '\n';
				flag = true;
				break;
			}
		}
		if (flag)continue;
		for (int i = 0; i < 3; i++) {
			if (IsinP(Q[i])) {
				cout << 2 << '\n';
				flag = true;
				break;
			}
		}
		if (flag)continue;
		//�и�(1) �Ǵ� ����(3)�� ����
		//����(3)�з�
		//P����
		ll temp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//P�� �ϳ��� Q ���� �ϳ��� ccw
				temp = ccw(P[i], Q[j], Q[(j + 1) % 3]);
				//ccw ���� 0�ΰ�� �������� ���� >> ������
				if (temp == 0) {
					if (Q[j].x <= Q[(j + 1) % 3].x) {
						if (Q[j].x <= P[i].x && P[i].x <= Q[(j + 1) % 3].x) {
							//������ �������� �����鼭 P�� ���� Q�� ���� ���̿� �����ϴ°�� >> ����(3)
							cout << 3 << '\n';
							flag = true;
							break;
						}
					}
					else if ((Q[j].x > Q[(j + 1) % 3].x)) {
						if (Q[j].x >= P[i].x && P[i].x >= Q[(j + 1) % 3].x) {
							//������ �������� �����鼭 P�� ���� Q�� ���� ���̿� �����ϴ°�� >> ����(3)
							cout << 3 << '\n';
							flag = true;
							break;
						}
					}
				}
			}
			if (flag)break;
		}
		if (flag)continue;
		//Q����
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//P�� �ϳ��� Q ���� �ϳ��� ccw
				temp = ccw(Q[i], P[j], P[(j + 1) % 3]);
				//ccw ���� 0�ΰ�� �������� ���� >> ������
				if (temp == 0) {
					if (P[j].x <= P[(j + 1) % 3].x) {
						if (P[j].x <= Q[i].x && Q[i].x <= P[(j + 1) % 3].x) {
							//������ �������� �����鼭 Q�� ���� P�� ���� ���̿� �����ϴ°�� >> ����(3)
							cout << 3 << '\n';
							flag = true;
							break;
						}
					}
					else if ((P[j].x > P[(j + 1) % 3].x)) {
						if (P[j].x >= Q[i].x && Q[i].x >= P[(j + 1) % 3].x) {
							//������ �������� �����鼭 Q�� ���� P�� ���� ���̿� �����ϴ°�� >> ����(3)
							cout << 3 << '\n';
							flag = true;
							break;
						}
					}
				}
			}
			if (flag)break;
		}
		if (flag)continue;
		//������ ��� ���̽��� �и�(1)
		cout << 1 << '\n';
	}
	return 0;
}
