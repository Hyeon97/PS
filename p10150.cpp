//set 없는 버전
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <queue>

#pragma warning(disable:4996)
using namespace std;

vector<string>dict;// 사전 입력 단어들
vector<string>ANS;// 결과 출력용
bool visit[25144];// 문자열 방문 체크
int arr[25144];// 탐색순서 저장 배열
int st_idx;

bool CH(string a, string b) {// 현재문자열과 1개의 단어만 차이나는 문자열 판별
	int cnt = 0;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] != b[i])cnt++;// 다른 문자 발견시 cnt++
		if (cnt > 1)return false;// 다른 문자가 2개 이상인경우는 필요한 문자가 아님
	}
	if (cnt == 1) return true;
	return false;
}

void BFS(string st, string ed, int st_idx) {// 시작문자열, 마지막 문자열, 시작문자열 사전내 idx
	queue< pair<string, int > >Q;
	bool OUT = false;
	int ed_idx = 0;

	for (int i = 0; i < dict.size(); i++) {
		arr[i] = -1;
		visit[i] = false;
	}

	Q.push({ st, st_idx });// 시작문자열과 시작문자열의 dict 내 idx를 넣어줌

	// 탐색
	while (!Q.empty()) {
		string now_str = Q.front().first;
		int arr_idx = Q.front().second;
		Q.pop();

		if (now_str.compare(ed) == 0) {// 끝까지 도착
			ANS.push_back(ed);
			ed_idx = arr_idx;
			while (1) {
				
				now_str = dict[arr[ed_idx]];
				ANS.push_back(now_str);
				ed_idx = arr[ed_idx];

				if (arr[ed_idx] == -1)break;
				
			}
			for (int i = ANS.size()-1; i >= 0; i--) {
				cout << ANS[i] << '\n';
			}
			ANS.clear();
			OUT = true;
			break;
		}
		//이미 now_str이 방문된경우 >> 더이상 볼 필요 없음
		if (visit[arr_idx])continue;
		
		visit[arr_idx] = true;

		for (int i = 0; i < dict.size(); i++) {
			if (now_str.length() != dict[i].length())continue;//길이가 다르면 애초에 고려대상이 아님

			if (CH(now_str, dict[i])) {// 길이가 같은경우 내가 원하는 문자열이 맞는지 체크
				//문자의 차이가 1개인 경우
				//해당 문자열을 방문하지 않은경우
				if (!visit[i]) {
					Q.push({ dict[i], i });
					if (arr[i] == -1)arr[i] = arr_idx;
				}

			}
		}
	}
	//탐색이 끝났는데도 경로 출력을 못함
	if(!OUT)cout << "No solution.\n";
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p10150.inp", "r", stdin);
	//freopen("p10150.out", "w", stdout);

	//사전에 들어갈 내용 입력받기
	while (1) {
		string temp;
		getline(cin, temp);
		if (temp == "")break;
		dict.push_back(temp);
	}
	string st, ed;
	int C = 0;
	while (cin >> st >> ed) {
		if (C != 0)cout << '\n';
		C++;
		// 두 문자열의 길이가 다른경우 바로 no solution
		if (st.length() != ed.length()) {
			cout << "No solution.\n";
			continue;
		}
		// 두 문자중 하나라도 사전에 없는경우
		bool ch = false;
		st_idx = 0;
		for (int i = 0; i < dict.size(); i++) {
			if (st.compare(dict[i]) == 0) {
				ch = true;
				st_idx = i;// 시작 문자열 위치(배열내 idx) 저장
			}
		}
		if (!ch)continue;

		ch = false;

		for (int i = 0; i < dict.size(); i++) {
			if (ed.compare(dict[i]) == 0)ch = true;
		}
		if (!ch)continue;

		//시작과 끝 문자열이 같은경우
		if (st.compare(ed) == 0) {
			cout << st << ' ' << ed << '\n';
			continue;
		}

		//모든 조건 통과시 탐색 시작
		BFS(st, ed, st_idx);
	}


	return 0;
}

//set 사용한 버전
//#include <iostream>
//#include <vector>
//#include <utility>
//#include <string>
//#include <queue>
//#include <set>
//
//#pragma warning(disable:4996)
//using namespace std;
//
//vector<string>dict;// 사전 입력 단어들
//vector<string>ANS;// 결과 출력용
//int arr[25144];// 방문+탐색순서 저장 배열
//int st_idx;
//
//bool CH(string a, string b) {// 현재문자열과 1개의 단어만 차이나는 문자열 판별
//	int cnt = 0;
//	for (int i = 0; i < a.length(); i++) {
//		if (a[i] != b[i])cnt++;// 다른 문자 발견시 cnt++
//		if (cnt > 1)return false;// 다른 문자가 2개 이상인경우는 필요한 문자가 아님
//	}
//	if (cnt == 1) return true;
//	return false;
//}
//
//void BFS(string st, string ed, int st_idx) {// 시작문자열, 마지막 문자열, 시작문자열 사전내 idx
//	queue< pair<string, int > >Q;
//	set<string>visit;
//	bool OUT = false;
//	int ed_idx = 0;
//
//	for (int i = 0; i < dict.size(); i++)arr[i] = -1;
//
//	Q.push({ st, st_idx });// 시작문자열과 시작문자열의 dict 내 idx를 넣어줌
//
//	// 탐색
//	while (!Q.empty()) {
//		string now_str = Q.front().first;
//		int arr_idx = Q.front().second;
//		Q.pop();
//
//		if (now_str.compare(ed) == 0) {// 끝까지 도착
//			ANS.push_back(ed);
//			ed_idx = arr_idx;
//			while (1) {
//
//				now_str = dict[arr[ed_idx]];
//				ANS.push_back(now_str);
//				ed_idx = arr[ed_idx];
//
//				if (arr[ed_idx] == -1)break;
//
//			}
//			for (int i = ANS.size() - 1; i >= 0; i--) {
//				cout << ANS[i] << '\n';
//			}
//			ANS.clear();
//			OUT = true;
//			break;
//		}
//		//이미 now_str이 방문된경우 >> 더이상 볼 필요 없음
//		if (visit.find(now_str) != visit.end())continue;
//
//		visit.insert(now_str);
//
//		for (int i = 0; i < dict.size(); i++) {
//			if (now_str.length() != dict[i].length())continue;//길이가 다르면 애초에 고려대상이 아님
//
//			if (CH(now_str, dict[i])) {// 길이가 같은경우 내가 원하는 문자열이 맞는지 체크
//				//문자의 차이가 1개인 경우
//				if (visit.find(dict[i]) == visit.end()) {//해당 문자열을 방문하지 않은경우
//					//visit.insert(dict[i]);// 해당문자열 방문 체크
//					Q.push({ dict[i], i });
//					if (arr[i] == -1)arr[i] = arr_idx;
//				}
//
//			}
//		}
//	}
//	//탐색이 끝났는데도 ANS에 아무것도 없는경우 >> 경로 출력을 못함
//	if (!OUT)cout << "No solution.\n";
//}
//
//int main()
//{
//	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	freopen("p10150.inp", "r", stdin);
//	freopen("p10150.out", "w", stdout);
//
//	//사전에 들어갈 내용 입력받기
//	while (1) {
//		string temp;
//		getline(cin, temp);
//		if (temp == "")break;
//		dict.push_back(temp);
//	}
//	string st, ed;
//	int C = 0;
//	while (cin >> st >> ed) {
//		if (C != 0)cout << '\n';
//		C++;
//		// 두 문자열의 길이가 다른경우 바로 no solution
//		if (st.length() != ed.length()) {
//			cout << "No solution.\n";
//			continue;
//		}
//		// 두 문자중 하나라도 사전에 없는경우
//		bool ch = false;
//		st_idx = 0;
//		for (int i = 0; i < dict.size(); i++) {
//			if (st.compare(dict[i]) == 0) {
//				ch = true;
//				st_idx = i;// 시작 문자열 위치(배열내 idx) 저장
//			}
//		}
//		if (!ch)continue;
//
//		ch = false;
//
//		for (int i = 0; i < dict.size(); i++) {
//			if (ed.compare(dict[i]) == 0)ch = true;
//		}
//		if (!ch)continue;
//
//		//시작과 끝 문자열이 같은경우
//		if (st.compare(ed) == 0) {
//			cout << st << ' ' << ed << '\n';
//			continue;
//		}
//
//		//모든 조건 통과시 탐색 시작
//		BFS(st, ed, st_idx);
//	}
//
//
//	return 0;
//}
//
