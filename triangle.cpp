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

ll ccw(point a, point b, point c) {//기준점 a 음수 >> 우회전 양수 >> 좌회전 0 >> 일직선상
	return (a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
}

bool IsinP(point p) {
	ll c1 = ccw(p, P[0], P[1]);
	ll c2 = ccw(p, P[1], P[2]);
	ll c3 = ccw(p, P[2], P[0]);
	//ccw 결과 셋다 >0 or <0 인경우 해당점은 도형 내부에 존재
	if (c1 > 0 && c2 > 0 && c3 > 0 || c1 < 0 && c2 < 0 && c3 < 0) return true;
	return false;
}

bool IsinQ(point p) {
	ll c1 = ccw(p, Q[0], Q[1]);
	ll c2 = ccw(p, Q[1], Q[2]);
	ll c3 = ccw(p, Q[2], Q[0]);
	//ccw 결과 셋다 >0 or <0 인경우 해당점은 도형 내부에 존재
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
		//P삼각형 좌표
		for (int i = 0; i < 3; i++) {
			cin >> p.x >> p.y;
			P.push_back(p);
		}
		//Q삼각형 좌표
		for (int i = 0; i < 3; i++) {
			cin >> p.x >> p.y;
			Q.push_back(p);
		}
		//중첩(2) 분류
		ll p1 = 0, p2 = 0, q1 = 0, q2 = 0;
		bool flag = false;
		//P 선분3개 Q 선분3개 총9가지 경우의 수 모두 확인
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//각 p,q 는 (양수-음수) or (음수-양수) 로 나와야함
				p1 = ccw(Q[j], Q[(j + 1) % 3], P[i]);
				p2 = ccw(Q[j], Q[(j + 1) % 3], P[(i + 1) % 3]);
				q1 = ccw(P[i], P[(i + 1) % 3], Q[j]);
				q2 = ccw(P[i], P[(i + 1) % 3], Q[(j + 1) % 3]);
				//조건에 맞는경우 2 출력후 종료
				if (((p1 < 0 && p2 > 0) || (p1 > 0 && p2 < 0)) && ((q1 < 0 && q2 > 0) || (q1 > 0 && q2 < 0))) { cout << 2 << '\n'; flag = true; break; }
			}
			if (flag)break;
		}
		if (flag)continue;
		//중첩(2) 예외 삼각형이 모두 포함되는경우 
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
		//분리(1) 또는 접함(3)만 남음
		//접함(3)분류
		//P기준
		ll temp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//P점 하나와 Q 선분 하나를 ccw
				temp = ccw(P[i], Q[j], Q[(j + 1) % 3]);
				//ccw 값이 0인경우 일직선상에 있음 >> 고려대상
				if (temp == 0) {
					if (Q[j].x <= Q[(j + 1) % 3].x) {
						if (Q[j].x <= P[i].x && P[i].x <= Q[(j + 1) % 3].x) {
							//세점이 일직선상에 있으면서 P의 점이 Q의 선분 사이에 존재하는경우 >> 접함(3)
							cout << 3 << '\n';
							flag = true;
							break;
						}
					}
					else if ((Q[j].x > Q[(j + 1) % 3].x)) {
						if (Q[j].x >= P[i].x && P[i].x >= Q[(j + 1) % 3].x) {
							//세점이 일직선상에 있으면서 P의 점이 Q의 선분 사이에 존재하는경우 >> 접함(3)
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
		//Q기준
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//P점 하나와 Q 선분 하나를 ccw
				temp = ccw(Q[i], P[j], P[(j + 1) % 3]);
				//ccw 값이 0인경우 일직선상에 있음 >> 고려대상
				if (temp == 0) {
					if (P[j].x <= P[(j + 1) % 3].x) {
						if (P[j].x <= Q[i].x && Q[i].x <= P[(j + 1) % 3].x) {
							//세점이 일직선상에 있으면서 Q의 점이 P의 선분 사이에 존재하는경우 >> 접함(3)
							cout << 3 << '\n';
							flag = true;
							break;
						}
					}
					else if ((P[j].x > P[(j + 1) % 3].x)) {
						if (P[j].x >= Q[i].x && Q[i].x >= P[(j + 1) % 3].x) {
							//세점이 일직선상에 있으면서 Q의 점이 P의 선분 사이에 존재하는경우 >> 접함(3)
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
		//나머지 모든 케이스는 분리(1)
		cout << 1 << '\n';
	}
	return 0;
}
