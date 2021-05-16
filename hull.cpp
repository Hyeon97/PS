#include <iostream>
#include <algorithm>
#include <vector>


#pragma warning(disable:4996)
using namespace std;

int N;
typedef struct point {
	int x;
	int y;
}point;

vector<point>convex;
vector<point>Inp;

int ccw(point a, point b, point c) {//������ a ���� >> ��ȸ�� ��� >> ��ȸ�� 0 >> ��������
	return (a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
}

bool cmp_x(point a, point b) {//x���� ���� || x�� y�� �ٲٸ� y���� ������ ��
	if (a.x != b.x) return a.x < b.x;
	else return a.y < b.y;
}

bool cmp_c(point a, point b) {//�ݽð���� ����
	int angle = ccw(Inp[0], a, b);
	if (angle != 0)return angle > 0;
	else return (a.x + a.y) < (b.x + b.y);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("hull.inp", "r", stdin);
	freopen("hull.out", "w", stdout);
	cin >> N;
	point temp,Next, Prev;
	for (int i = 0; i < N; i++) {
		cin >> temp.x >> temp.y;
		Inp.push_back(temp);
	}
	sort(Inp.begin() , Inp.end(), cmp_x);//x ������ ���� //x�� �����Ҳ��� xy�ݴ��
	sort(Inp.begin() + 1, Inp.end(), cmp_c);//������ ���� �ݽð�������� ����
	convex.push_back(Inp[0]);
	convex.push_back(Inp[1]);
	for (int i = 1; i < Inp.size(); i++) {
		while (convex.size() >= 2) {
			Next = convex.back();
			convex.pop_back();
			Prev = convex.back();
			if (ccw(Prev, Next, Inp[i]) > 0) {
				convex.push_back(Next);
				break;
			}
		}
		convex.push_back(Inp[i]);
	}
	cout << convex.size()<<'\n';
	for (int i = 0; i < convex.size(); i++) {
		cout << convex[i].x << ' ' << convex[i].y << '\n';
	}

	convex.clear();
	return 0;
}

