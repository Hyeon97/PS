#include <iostream>
#include <vector>

#pragma warning(disable:4996)
using namespace std;

int n, k, x, y;
typedef struct Point {
	int x = 0;
	int y = 0;
}Point;

Point Origin;

vector<Point>Polygon;

int ccw(Point b, Point c) {//�� a ���� b,c�� �񱳴�� ����
	return b.x * c.y - b.y * c.x;//���� ����
}

int Isinside(Point q, int n) {//����Ȯ���ϰ���� ����, �ٰ��� ���� �迭, �ٰ��� ������
	int cross = 0;
	vector<Point>temp;
	for (int i = 0; i < n; i++) {//�ش������������� �ٰ��� �̵�, �������� x��
		Point p;
		p.x = Polygon[i].x - q.x;
		p.y = Polygon[i].y - q.y;
		temp.push_back(p);
	}
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		
		if (temp[i].x == Origin.x && temp[i].y == Origin.y) {
			return true;// >> �������� �Ű����� �ش� ������ �ٰ����� ������ ���ԵǴ� ��� >> �����ŵ� ���� ������ ����
		}
		if ((temp[i].y < 0 && temp[j].y >= 0 && ccw(temp[i], temp[j]) > 0)) {
			cross++;
		}
		else if ((temp[i].y >= 0 && temp[j].y < 0 && ccw(temp[j], temp[i]) > 0)) {
			cross++;
		}
	}
	return cross % 2;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("point.inp", "r", stdin);
	freopen("point.out", "w", stdout);

	cin >> n;
	Point temp;
	while (n--) {//�ٰ��� ��ǥ �Է¹���
		cin >> temp.x >> temp.y;
		Polygon.push_back(temp);
	}
	cin >> k;
	while (k--) {//Ȯ���ϰ� ���� ����
		cin >> temp.x >> temp.y;
		cout << Isinside(temp, Polygon.size()) << '\n';
	}
	return 0;
}

