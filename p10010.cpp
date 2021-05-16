#include <iostream>
#include <vector>

#pragma warning(disable:4996)
using namespace std;

int TC, M, N, K, L;
char MAP[51][51];
string S;
//방향 : 우 우하 하 좌하 좌 좌상 상 우상
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
int dy[8] = { 1,1,0,-1,-1,-1,0,1 };
bool E = false;
int X, Y;


void Find(int x, int y, int idx, int Ty) {//8방향 탐색을 해줘야함 >> 현재 문자기준 1~8 1:우 ~~ 8: 우상
	if (idx == L) {//현재 문자열 idx가 문자열 길이랑 똑같은경우 >> 해당문자를 찾아냄
		cout << X+1 << ' ' << Y+1 << '\n';
		E = true;
		return;
	}
	if (Ty == 0) {
		for (int i = 0; i < 8; i++) {
			if (0 <= x + dx[i] && x + dx[i] < M && 0 <= y + dy[i] && y + dy[i] < N && MAP[x + dx[i]][y + dy[i]] == S[idx]) {
				Find(x + dx[i], y + dy[i], idx + 1, i + 1);
			}
		}
	}
	else {
		if (Ty == 1) {//우
			if (y + 1 < N && MAP[x][y + 1] == S[idx]) {
				Find(x, y + 1, idx + 1, 1);
			}
		}
		else if (Ty == 2) {//우하
			if (x + 1 < M && y + 1 < N && MAP[x + 1][y + 1] == S[idx]) {
				Find(x + 1, y + 1, idx + 1, 2);
			}
		}
		else if (Ty == 3) {//하
			if (x + 1 < M && MAP[x + 1][y] == S[idx]) {
				Find(x + 1, y, idx + 1, 3);
			}
		}
		else if (Ty == 4) {//좌하
			if (0 <= y - 1 && x + 1 < M && MAP[x + 1][y - 1] == S[idx]) {
				Find(x + 1, y - 1, idx + 1, 4);
			}
		}
		else if (Ty == 5) {//좌
			if (0 <= y - 1 && MAP[x][y - 1] == S[idx]) {
				Find(x, y - 1, idx + 1, 5);
			}
		}
		else if (Ty == 6) {//좌상
			if (0 <= x - 1 && 0 <= y - 1 && MAP[x - 1][y - 1] == S[idx]) {
				Find(x - 1, y - 1, idx + 1, 6);
			}
		}
		else if (Ty == 7) {//상
			if (0 <= x - 1 && MAP[x - 1][y] == S[idx]) {
				Find(x - 1, y, idx + 1, 7);
			}
		}
		else if (Ty == 8) {//우상
			if (y + 1 < N && 0 <= x - 1 && MAP[x - 1][y + 1] == S[idx]) {
				Find(x - 1, y + 1, idx + 1, 8);
			}
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p10010.inp", "r", stdin);
	freopen("p10010.out", "w", stdout);
	cin >> TC;
	while (TC--) {
		cin >> M >> N;
		//문자열 판 입력받음
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
				//대소문자 구분안하니까 그냥 대문자로 통일
				if (MAP[i][j] >= 'a') {
					MAP[i][j] -= 32;
				}
			}
		}
		//찾아야하는 문자입력받고 바로 탐색 시작
		cin >> K;
		for (int k = 0; k < K; k++) {
			cin >> S;
			L = S.length();
			for (int i = 0; i < L; i++) {
				if (S[i] >= 'a')S[i] -= 32;
			}
			//탐색 시작
			E = false;
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					if (MAP[i][j] == S[0]) {
						X = i;
						Y = j;
						Find(i, j, 1, 0);
					}
					if (E)break;
				}
				if (E)break;
			}
		}
		cout << '\n';
	}



	return 0;
}

