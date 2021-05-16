#include <iostream>
#include <vector>
#include <algorithm>

#pragma warning(disable:4996)
using namespace std;

int T, P, Q;
typedef struct point {
	long long x;
	long long y;
	char where;//해당 좌표가 어느도형에 속해있는가 확인
	int original_idx;//맨처음 각 좌표가 들어온 순서 저장
}point;

point p[10001];//다각형 p의 모든 정점을 입력받음
point q[10001];//다각형 q의 모든 정점을 입력받음
point All[20001];//다각형 p,q의 모든 정점을 입력받음
vector<point>convex;//다각형 p,q 극단점 중 두개를 합친 볼록껍질의 극단점만 들어감
vector<point>PQ;


long long int ccw(point a, point b, point c) {//기준점 a 음수 >> 우회전 양수 >> 좌회전 0 >> 일직선상
	return (a.x * b.y + b.x * c.y + c.x * a.y) - (a.y * b.x + b.y * c.x + c.y * a.x);
}

bool cmp_x(point a, point b) {//x기준 정렬 || x를 y로 바꾸면 y기준 정렬이 됨
	if (a.x != b.x) return a.x < b.x;
	else return a.y < b.y;
}

bool cmp_c(point a, point b) {//반시계방향 정렬
	long long  angle = ccw(All[0], a, b);
	if (angle != 0)return angle > 0;
	else return (a.x + a.y) < (b.x + b.y);
}

//ppt에 있는거 그대로 갖다박음
bool between(point a, point b, point c) {
	int temp = ccw(a, b, c);//ccw값 확인용
	if (ccw(a, b, c))return false;//ccw가 0이나와야 일직선상에 위치함을 의미 || 0 이외의 값이 나온경우 일직선상에 있지 않음으로 고려대상 아님
	//일직선상에 위치하는 경우
	if (a.x != b.x) {//x값이 다르면 x값 기준
		return a.x <= c.x && c.x <= b.x || b.x <= c.x && c.x <= a.x;
	}
	else {//x값이 같으면 y값 기준
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
		//각 다각형 좌표는 들어올때 반시계방향으로 정렬되어서 들어옴
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

		//볼록껍질 제작 시작
		point Prev, Next;
		sort(All, All + P + Q, cmp_x);//x 작은순 정렬 //x축 정렬할꺼면 xy반대로
		sort(All + 1, All + P + Q, cmp_c);//시작점 제외 반시계방향으로 정렬
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
		//전체 극단점에서 어떤점이 p 어떤점이 q 다각형에 속해있는지 구분 
		int Size = convex.size();
		for (int i = 0; i < Size; i++) {
			int j = (i + 1) % Size;
			if (convex[i].where != convex[j].where) {
				PQ.push_back(convex[i]);
				PQ.push_back(convex[j]);
			}
		}
		convex.clear();
		//예외는 총 2가지
		//1번 예외 두 극단점 사이에 다른점이 껴있는 경우
		//두 접선 사이에 다른점이 껴있는경우(일직선상) >> 해당점으로 갱신 || 최대한 길이 짧은거로
		bool temp;
		if (PQ[1].where == 'q' && PQ[2].where == 'q') {
			for (int j = 0; j < P + Q; j++) {
				//해당점이 접선 사이 일직선상에 위치하는지 확인
				if (All[j].where == 'p') {//일직선상에 위치하는경우 convex_p[i]의 값을 현재의 점으로 바꿔줌
					temp = between(PQ[0], PQ[1], All[j]);//between 값 확인용
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
				//해당점이 접선 사이 일직선상에 위치하는지 확인
				if (All[j].where == 'p') {//일직선상에 위치하는경우 convex_p[i]의 값을 현재의 점으로 바꿔줌
					temp = between(PQ[3], PQ[2], All[j]);//between 값 확인용
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
			//다각형 P,Q에서 접점사이 나머지 내부점들을 모두 찾아내야함
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
				//해당점이 접선 사이 일직선상에 위치하는지 확인
				if (All[j].where == 'p') {//일직선상에 위치하는경우 convex_p[i]의 값을 현재의 점으로 바꿔줌
					temp = between(PQ[1], PQ[0], All[j]);//between 값 확인용
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
				//해당점이 접선 사이 일직선상에 위치하는지 확인
				if (All[j].where == 'p') {//일직선상에 위치하는경우 convex_p[i]의 값을 현재의 점으로 바꿔줌
					temp = between(PQ[2], PQ[3], All[j]);//between 값 확인용
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
			//다각형 P,Q에서 접점사이 나머지 내부점들을 모두 찾아내야함
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
		//구해진 내부 정점들을 이용 내부의 넓이 구함
		//첫번째 정점을 기준으로 외적해서 넓이 구해줌
		for (int i = 1; i < convex.size() - 1; ++i) area += ccw(convex[0], convex[i], convex[i + 1]);
		//2번예외 고려 >> 한도형의 극단점 2개가 같은경우(극단점을 제외하고 나머지 모든점들이 두 다각형사이 넓이를 구해야 하는 부분에 들어가 있음을 의미) >> 대상도형의 넓이만큼 빼줌
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
		cout.precision(1);//cout 출력시 소숫점 1자리 고정해주는거
		cout << fixed << area / 2 << '\n';

		//초기화
		convex.clear();
		PQ.clear();
	}

	return 0;
}

