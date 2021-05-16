#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#pragma warning(disable:4996)
using namespace std;

int T, P, N;
string s;
vector<pair<int, int>>Card;//����, ����

int pattern[4];//Clover, Dia, Heart, Spade ��
int num[15];//1~14������ Ȯ�� 1 or 14 ==A 10==T 11==J 12==Q 13==K

int Pair() {
	int cnt = 0;//cnt�� 0�̸� Top 1���� One_Pair 2���� Two_Pair
	for (int i = 1; i <= 13; i++) {
		if (num[i] >= 2)cnt++;
	}
	return cnt;
}

bool Triple() {//�������� 3������
	for (int i = 1; i <= 13; i++) {
		if (num[i] == 3)return true;
	}
	return false;
}
bool Four() {//�������� 4��
	for (int i = 1; i <= 13; i++) {
		//�������� 4���̻� �����ϴ°�� ���̻� ���ʿ� ����
		if (num[i] >= 4)return true;
	}
	return false;
}
bool Flush() {//��������5�� �̻�
	for (int i = 0; i < 4; i++) {
		if (pattern[i] >= 5)return true;
	}
	return false;
}
bool Straight() {//���ӵȼ��� 5���̻�
	int cnt = 0;
	for (int i = 1; i <= 14; i++) {
		if (num[i])cnt++;
		else cnt = 0;
		if (cnt >= 5)return true;
	}
	return false;
}
bool Full_House() {//Tripe + One_pair
	//Tripe ���� ã�� �״��� One pair ã��
	int Tripe = 0;
	for (int i = 1; i <= 13; i++) {
		if (num[i] >= 3) {
			Tripe = i; break;
		}
	}
	if (Tripe==0)return false;//Triple�� ���°�� Ǯ�Ͽ콺 ���� X
	for (int i = 1; i <= 13; i++) {
		//Ʈ���� ���ڿܿ� �ٸ� ���ڿ��� �� �����ϴ°�� >> Ǯ�Ͽ콺
		if (i != Tripe && num[i] >= 2)return true;
	}
	return false;
}
bool Straight_Flush() {//5���� ī�尡 ���������̸鼭 ���ӵ� ����
	//���� �÷����� �����ϴ��� Ȯ��
	if (!Flush())return false;//Flush�� ������ Ȯ���� �ʿ� ����
	int cnt = 0;
	for (int i = 1; i < Card.size(); i++) {
		//�ٷ� ���� ī��� ������ ������ ����ī�庸�� ���ڰ� +1 ������ cnt++
		if (Card[i-1].first == Card[i].first && Card[i-1].second+1 == Card[i].second)cnt++;
		else cnt = 0;

		if (cnt == 4)return true;
	}
	return false;
}



int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	//freopen("poker.inp", "r", stdin);
	//freopen("poker.out", "w", stdout);
	cin >> T;
	while (T--) {
		//�ʱ�ȭ
		for (int i = 0; i < 4; i++)pattern[i] = 0;
		for (int i = 0; i < 15; i++)num[i] = 0;
		Card.clear();

		for (int i = 0; i < 7; i++) {
			cin >> s;
			//ī�� ���� ó��
			if (s[0] == 'C')P = 0;
			else if (s[0] == 'D')P = 1;
			else if (s[0] == 'H') P = 2;
			else P = 3;
			//ī�� ���� ó��
			//���ڰ� 1�ΰ�� 14�� �Բ� �־��ٰ�
			if ('1' <= s[1] && s[1] <= '9')N = s[1] - '0';
			else if (s[1] == 'T')N = 10;
			else if (s[1] == 'J')N = 11;
			else if (s[1] == 'Q')N = 12;
			else if (s[1] == 'K')N = 13;
			else if(s[1]=='A') N = 14; 

			pattern[P]++; num[N]++;
			Card.push_back({ P,N });

			if (N == 14) {//A�� 1 �Ǵ� 14�� ��� �׷��� 1�� �ϳ� �� �߰�����
				N = 1;
				num[N]++;
				Card.push_back({ P,N });
			}
			if (N == 1) {
				N = 14;
				num[N]++;
				Card.push_back({P,N});
			}
			
		}
		sort(Card.begin(), Card.end());//���� , ���� ������ ����

		//����Ȯ��
		if (Straight_Flush())cout << "Straight Flush\n";
		else if (Four()) cout << "Four Card\n";
		else if (Full_House())  cout << "Full House\n";
		else if (Flush())  cout << "Flush\n";
		else if (Straight())  cout << "Straight\n";
		else if (Triple())  cout << "Triple\n";
		else if (Pair()>=2) cout << "Two Pair\n";
		else if (Pair()==1) cout << "One Pair\n";
		else cout << "Top\n";
	}
	return 0;
}

