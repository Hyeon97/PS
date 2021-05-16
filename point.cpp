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

int ccw(Point b, Point c) {//점 a 기준 b,c는 비교대상 선분
	return b.x * c.y - b.y * c.x;//기울기 리턴
}

int Isinside(Point q, int n) {//조건확인하고싶은 정점, 다각형 정점 배열, 다각형 정점수
	int cross = 0;
	vector<Point>temp;
	for (int i = 0; i < n; i++) {//해당정점기준으로 다각형 이동, 반직선은 x축
		Point p;
		p.x = Polygon[i].x - q.x;
		p.y = Polygon[i].y - q.y;
		temp.push_back(p);
	}
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		
		if (temp[i].x == Origin.x && temp[i].y == Origin.y) {
			return true;// >> 원점으로 옮겼을떄 해당 정점이 다각형의 정점에 포함되는 경우 >> 더볼거도 없이 무조건 포함
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
	while (n--) {//다각형 좌표 입력받음
		cin >> temp.x >> temp.y;
		Polygon.push_back(temp);
	}
	cin >> k;
	while (k--) {//확인하고 싶은 정점
		cin >> temp.x >> temp.y;
		cout << Isinside(temp, Polygon.size()) << '\n';
	}
	return 0;
}

