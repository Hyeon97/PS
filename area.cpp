#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <utility>

#pragma warning(disable:4996)
using namespace std;

typedef struct Circle
{
	double x;
	double y;
	double r;

}Circle;

int T;
vector<Circle>C;
vector< pair <double, double >>XY;
vector< pair <double, double >>XY2;//Ȯ�ο�
double weight;


double ccw(pair <double, double > a, pair <double, double > b, pair <double, double > c) {//������ a ���� >> ��ȸ�� ��� >> ��ȸ�� 0 >> ��������
	return (a.first * b.second + b.first * c.second + c.first * a.second) - (a.second * b.first + b.second * c.first + c.second * a.first);
}

double Dist(pair<double, double> p, Circle t) {
	double D = sqrt((t.x - p.first) * (t.x - p.first) + (t.y - p.second) * (t.y - p.second));
	//�ش� ���� �񱳴���� ���� ���������� �Ÿ� ����
	return D;
}

void Find_point(Circle a, Circle b, Circle c) {
	double X, Y, A1, A2, B1, B2, C, X1, X2, Y1, Y2, D1, D2;
	//�ΰ��� �����ؼ� ������ ���������� ����
	// y = C1/2B1 - A1/B1 * x ����
	X = b.x - a.x;
	Y = b.y - a.y;
	//�ΰ��� ������ �� �ƹ��ų� �ϳ��� �����ؼ� ������ ����
	if (X == 0) {//x ���� ������� >> y ������
		A1 = (a.r * a.r - b.r * b.r - a.x * a.x - a.y * a.y + b.x * b.x + b.y * b.y) / (2 * (b.y - a.y));
		B1 = (b.x - a.x) / (b.y - a.y);

		A2 = 1 + (B1 * B1);
		B2 = (2 * a.y * B1) - (2 * A1 * B1) - (2 * a.x);
		C = (a.x * a.x) + (A1 * A1) - (2 * a.y * A1) + (a.y * a.y) - (a.r * a.r);
		X1 = ( (-B2 + sqrt(B2 * B2 - 4 * A2 * C)) / (2 * A2));
		X2 = ( (-B2 - sqrt(B2 * B2 - 4 * A2 * C)) / (2 * A2));
		Y1 = A1 - B1 * X1;
		Y2 = A1 - B1 * X2;
		
	}
	else if (X != 0) {//y ���� �������
		A1 = (a.r * a.r - b.r * b.r - a.x * a.x - a.y * a.y + b.x * b.x + b.y * b.y) / (2 * (b.x - a.x));
		B1 = (b.y - a.y) / (b.x - a.x);

		A2 = 1 + (B1 * B1);
		B2 = (2 * a.x * B1) - (2 * A1 * B1) - (2 * a.y);
		C = (a.x * a.x) + (A1 * A1) - (2 * a.x * A1) + (a.y * a.y) - (a.r * a.r);
		Y1 = ((-B2 + sqrt(B2 * B2 - 4 * A2 * C)) / (2 * A2));
		Y2 = ((-B2 - sqrt(B2 * B2 - 4 * A2 * C)) / (2 * A2));
		X1 = A1 - B1 * Y1;
		X2 = A1 - B1 * Y2;
	}

	//������ �� ��ǥ�� �ٸ� ���� �Ÿ��� ����� ��ǥ�� �־���
	D1 = fabs(Dist({ X1,Y1 }, c));
	D2 = fabs(Dist({ X2,Y2 }, c));
	/*XY2.push_back({ X1,Y1 });
	XY2.push_back({ X2,Y2 });*/
	if (D1 > D2)XY.push_back({ X2,Y2 });
	else XY.push_back({ X1,Y1 });
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("area.inp", "r", stdin);
	freopen("area.out", "w", stdout);

	cin >> T;
	while (T--) {
		//�� ���� ���� �Է�
		Circle temp;
		C.clear();
		XY.clear();
		weight = 0;
		for (int i = 0; i < 3; i++) {
			cin >> temp.x >> temp.y >> temp.r;
			C.push_back(temp);
		}
		//���� 2���� ���ؼ� ���� 2�� ã���� �ٸ����� ���ؼ� �ش�� �ȿ� �ִ����� �츲
		//A-B
		Find_point(C[0], C[1], C[2]);
		//B-C
		Find_point(C[1], C[2], C[0]);
		//A-C
		Find_point(C[2], C[0], C[1]);


		for (int i = 1; i < XY.size() - 1; ++i) weight += ccw(XY[0], XY[i], XY[i + 1]);
		cout.precision(2);//cout ��½� �Ҽ��� 1�ڸ� �������ִ°�
		cout << fixed << fabs(weight / 2) << '\n';
	}

	return 0;
}

