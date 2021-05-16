#include <iostream>
#include <algorithm>
#include <vector>


#pragma warning(disable:4996);
typedef long long ll;
using namespace std;

typedef struct point {
	long long x;
	long long y;
}point;

int T;
vector< point >P;
point p, temp1, temp2, Next, Prev;
vector<point>convex;

long long int ccw(point a, point b, point c) {//������ a ���� >> ��ȸ�� ��� >> ��ȸ�� 0 >> ��������
	return (a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
}

bool cmp_x(point a, point b) {//x���� ���� || x�� y�� �ٲٸ� y���� ������ ��
	if (a.x != b.x) return a.x < b.x;
	else return a.y < b.y;
}

bool cmp_c(point a, point b) {//�ݽð���� ����
	long long  angle = ccw(temp1, a, b);
	if (angle != 0)return angle > 0;
	else return (a.x + a.y) < (b.x + b.y);
}


int main()
{
	ios_base::sync_with_stdio(false); //cin.tie(0); cout.tie(0);
	freopen("spiral.inp", "r", stdin);
	//freopen("spiral.out", "w", stdout);
	cin >> T;
	int n;

	while (T--) {
		//���� ��
		cin >> n;
		//�ʱ�ȭ
		temp1.x = 1000000001;
		temp1.y = -1000000001;
		temp2.x = 1000000001;
		temp2.y = 1000000001;
		P.clear();
		for (int i = 0; i < n; i++) {
			cin >> p.x >> p.y;
			if (p.x<temp1.x && p.y>temp1.y) {
				temp1 = p;
			}
			P.push_back(p);
		}
		for (int i = 0; i < n; i++) {
			if (p.x < temp2.x && p.y < temp2.y && p.x != temp1.x && p.y != temp1.y) {
				temp2 = p;
			}
		}
		point tt = P[0];
		P[0] = temp1;
		temp1 = tt;

		point tt2 = P[1];
		P[1] = temp2;
		temp2 = tt2;
		sort(P.begin() + 2, P.end(), cmp_x);//x ������ ����
		sort(P.begin() + 2, P.end(), cmp_c);//������ ���� �ݽð�������� ����
		convex.push_back(P[0]);
		convex.push_back(P[1]);
		for (int i = 1; i < P.size(); i++) {
			while (convex.size() >= 2) {
				Next = convex.back();
				convex.pop_back();
				Prev = convex.back();
				if (ccw(Prev, Next, P[i]) > 0) {
					convex.push_back(Next);
					break;
				}
			}
			convex.push_back(P[i]);
		}
		int S = P.size() - 1;
	}


	return 0;
}

