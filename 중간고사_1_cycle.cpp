#include <iostream>
#include <algorithm>
#include <vector>
#include<stdio.h>

#pragma warning(disable:4996);
typedef long long ll;
using namespace std;

int T;

int Next[51];
int V[51];
int cnt = 0;

void DFS(int now) {
	V[now] = true;
	if (!V[Next[now]])DFS(Next[now]);
	else return;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("cycle.inp", "r", stdin);
	freopen("cycle.out", "w", stdout);

	cin >> T;
	char s;
	scanf("%c", &s);//ó�������� '\n' ����
	while (T--) {
		//�Է�
		int L = 1;
		int temp = 0;
		int cnt = 0;
		//�ʱ�ȭ
		for (int i = 1; i <= 50; i++) {
			V[i] = false;
			Next[i] = i;
		}
		while (scanf("%c", &s) != EOF) {
			if (s == '\n') {
				/*if (temp != 0) {
					Next[L] = temp;
					L++;
				}*/
				break;
			}
			else if (s == ' ') {
				Next[L] = temp;
				temp = 0;
				L++;
			}
			else {//��¥�� �ִ� 2�ڸ���
				temp *= 10;
				temp += (s - '0');
			}
		}
		if (temp != 0) {
			Next[L] = temp;
			L++;
		}
		//����
		for (int i = 1; i < L; i++) {
			if (!V[i]) {
				DFS(i);
				cnt++;
			}
		}

		cout << cnt << '\n';
	}
	return 0;
}

