#include <iostream>
#include <vector>

#pragma warning(disable:4996)
using namespace std;

int TC, M, N, K, L;
char MAP[51][51];
string S;
//���� : �� ���� �� ���� �� �»� �� ���
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
int dy[8] = { 1,1,0,-1,-1,-1,0,1 };
bool E = false;
int X, Y;


void Find(int x, int y, int idx, int Ty) {//8���� Ž���� ������� >> ���� ���ڱ��� 1~8 1:�� ~~ 8: ���
	if (idx == L) {//���� ���ڿ� idx�� ���ڿ� ���̶� �Ȱ������ >> �ش繮�ڸ� ã�Ƴ�
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
		if (Ty == 1) {//��
			if (y + 1 < N && MAP[x][y + 1] == S[idx]) {
				Find(x, y + 1, idx + 1, 1);
			}
		}
		else if (Ty == 2) {//����
			if (x + 1 < M && y + 1 < N && MAP[x + 1][y + 1] == S[idx]) {
				Find(x + 1, y + 1, idx + 1, 2);
			}
		}
		else if (Ty == 3) {//��
			if (x + 1 < M && MAP[x + 1][y] == S[idx]) {
				Find(x + 1, y, idx + 1, 3);
			}
		}
		else if (Ty == 4) {//����
			if (0 <= y - 1 && x + 1 < M && MAP[x + 1][y - 1] == S[idx]) {
				Find(x + 1, y - 1, idx + 1, 4);
			}
		}
		else if (Ty == 5) {//��
			if (0 <= y - 1 && MAP[x][y - 1] == S[idx]) {
				Find(x, y - 1, idx + 1, 5);
			}
		}
		else if (Ty == 6) {//�»�
			if (0 <= x - 1 && 0 <= y - 1 && MAP[x - 1][y - 1] == S[idx]) {
				Find(x - 1, y - 1, idx + 1, 6);
			}
		}
		else if (Ty == 7) {//��
			if (0 <= x - 1 && MAP[x - 1][y] == S[idx]) {
				Find(x - 1, y, idx + 1, 7);
			}
		}
		else if (Ty == 8) {//���
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
		//���ڿ� �� �Է¹���
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> MAP[i][j];
				//��ҹ��� ���о��ϴϱ� �׳� �빮�ڷ� ����
				if (MAP[i][j] >= 'a') {
					MAP[i][j] -= 32;
				}
			}
		}
		//ã�ƾ��ϴ� �����Է¹ް� �ٷ� Ž�� ����
		cin >> K;
		for (int k = 0; k < K; k++) {
			cin >> S;
			L = S.length();
			for (int i = 0; i < L; i++) {
				if (S[i] >= 'a')S[i] -= 32;
			}
			//Ž�� ����
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

