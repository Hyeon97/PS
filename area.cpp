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
vector< pair <double, double >>XY2;//확인용
double weight;


double ccw(pair <double, double > a, pair <double, double > b, pair <double, double > c) {//기준점 a 음수 >> 우회전 양수 >> 좌회전 0 >> 일직선상
	return (a.first * b.second + b.first * c.second + c.first * a.second) - (a.second * b.first + b.second * c.first + c.second * a.first);
}

double Dist(pair<double, double> p, Circle t) {
	double D = sqrt((t.x - p.first) * (t.x - p.first) + (t.y - p.second) * (t.y - p.second));
	//해당 점과 비교대상의 원의 중점사이의 거리 리턴
	return D;
}

void Find_point(Circle a, Circle b, Circle c) {
	double X, Y, A1, A2, B1, B2, C, X1, X2, Y1, Y2, D1, D2;
	//두개식 연립해서 간단한 일차식으로 만듬
	// y = C1/2B1 - A1/B1 * x 형태
	X = b.x - a.x;
	Y = b.y - a.y;
	//두개의 이차식 중 아무거나 하나랑 연립해서 연립식 구함
	if (X == 0) {//x 값이 같은경우 >> y 값으로
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
	else if (X != 0) {//y 값이 같은경우
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

	//구해진 두 좌표중 다른 원과 거리가 가까운 좌표를 넣어줌
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
		//각 원의 정보 입력
		Circle temp;
		C.clear();
		XY.clear();
		weight = 0;
		for (int i = 0; i < 3; i++) {
			cin >> temp.x >> temp.y >> temp.r;
			C.push_back(temp);
		}
		//원을 2개씩 비교해서 교점 2개 찾은후 다른원과 비교해서 해당원 안에 있는점만 살림
		//A-B
		Find_point(C[0], C[1], C[2]);
		//B-C
		Find_point(C[1], C[2], C[0]);
		//A-C
		Find_point(C[2], C[0], C[1]);


		for (int i = 1; i < XY.size() - 1; ++i) weight += ccw(XY[0], XY[i], XY[i + 1]);
		cout.precision(2);//cout 출력시 소숫점 1자리 고정해주는거
		cout << fixed << fabs(weight / 2) << '\n';
	}

	return 0;
}

