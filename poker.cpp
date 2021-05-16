#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#pragma warning(disable:4996)
using namespace std;

int T, P, N;
string s;
vector<pair<int, int>>Card;//문양, 숫자

int pattern[4];//Clover, Dia, Heart, Spade 순
int num[15];//1~14까지만 확인 1 or 14 ==A 10==T 11==J 12==Q 13==K

int Pair() {
	int cnt = 0;//cnt가 0이면 Top 1개면 One_Pair 2개면 Two_Pair
	for (int i = 1; i <= 13; i++) {
		if (num[i] >= 2)cnt++;
	}
	return cnt;
}

bool Triple() {//같은숫자 3개존재
	for (int i = 1; i <= 13; i++) {
		if (num[i] == 3)return true;
	}
	return false;
}
bool Four() {//같은숫자 4개
	for (int i = 1; i <= 13; i++) {
		//같은숫자 4개이상 존재하는경우 더이상 볼필요 없음
		if (num[i] >= 4)return true;
	}
	return false;
}
bool Flush() {//같은문양5개 이상
	for (int i = 0; i < 4; i++) {
		if (pattern[i] >= 5)return true;
	}
	return false;
}
bool Straight() {//연속된숫자 5개이상
	int cnt = 0;
	for (int i = 1; i <= 14; i++) {
		if (num[i])cnt++;
		else cnt = 0;
		if (cnt >= 5)return true;
	}
	return false;
}
bool Full_House() {//Tripe + One_pair
	//Tripe 먼저 찾고 그다음 One pair 찾기
	int Tripe = 0;
	for (int i = 1; i <= 13; i++) {
		if (num[i] >= 3) {
			Tripe = i; break;
		}
	}
	if (Tripe==0)return false;//Triple이 없는경우 풀하우스 성립 X
	for (int i = 1; i <= 13; i++) {
		//트리플 숫자외에 다른 숫자에서 페어가 존재하는경우 >> 풀하우스
		if (i != Tripe && num[i] >= 2)return true;
	}
	return false;
}
bool Straight_Flush() {//5개의 카드가 같은문양이면서 연속된 숫자
	//먼저 플러쉬가 존재하는지 확인
	if (!Flush())return false;//Flush가 없으면 확인할 필요 없음
	int cnt = 0;
	for (int i = 1; i < Card.size(); i++) {
		//바로 앞의 카드와 문양이 같으며 직전카드보다 숫자가 +1 높으면 cnt++
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
		//초기화
		for (int i = 0; i < 4; i++)pattern[i] = 0;
		for (int i = 0; i < 15; i++)num[i] = 0;
		Card.clear();

		for (int i = 0; i < 7; i++) {
			cin >> s;
			//카드 문양 처리
			if (s[0] == 'C')P = 0;
			else if (s[0] == 'D')P = 1;
			else if (s[0] == 'H') P = 2;
			else P = 3;
			//카드 숫자 처리
			//숫자가 1인경우 14도 함께 넣어줄것
			if ('1' <= s[1] && s[1] <= '9')N = s[1] - '0';
			else if (s[1] == 'T')N = 10;
			else if (s[1] == 'J')N = 11;
			else if (s[1] == 'Q')N = 12;
			else if (s[1] == 'K')N = 13;
			else if(s[1]=='A') N = 14; 

			pattern[P]++; num[N]++;
			Card.push_back({ P,N });

			if (N == 14) {//A는 1 또는 14로 취급 그래서 1도 하나 더 추가해줌
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
		sort(Card.begin(), Card.end());//문자 , 숫자 순으로 정렬

		//족보확인
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

