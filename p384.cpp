#include <iostream>
#include <vector>
#include <string>
#include <utility>

#pragma warning(disable:4996)
using namespace std;

int T,SluC, SliC;
string s;
vector< pair<char, int> >VS;//문자 해당문자 연속 갯수


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p384.inp", "r", stdin);
	freopen("p384.out", "w", stdout);

	cin >> T;//입력 문자열 갯수
	cout << "SLURPYS OUTPUT\n";
	for (int t = 0; t < T; t++) {
		cin >> s;//문자열 입력받음;
		SluC=0, SliC=0;// 슬럼프 카운터 A 슬럼프 C 형태에서 작동 || 슬림프 카운터
		bool NO = false;
		bool AH = false;
		//now_st_idx = 0;
		int i = 0;
		for (i; i < s.length(); i++) {
			//넣기
			if (VS.size() == 0 && s[i] == 'F' || VS.size() != 0 && s[i]=='F' && (VS.back().first=='A' || VS.back().first=='B')) {
				NO = true;
				break;
			}
			if (s[i] == 'A') {
				if (s[i + 1] == 'B') {
					SliC++;
					//VS.push_back("AB");
					VS.push_back({ s[i],1 });//A
					VS.push_back({ s[i + 1],1 });//B
					i += 1;
				}
				else if (s[i + 1] == 'H') {
					if (AH) {
						NO = true;
						break;
					}
					AH = true;
					i += 1;
				}
				else if (s[i+1]=='D' || s[i+1]=='E') {
					//VS.push_back("AS");
					VS.push_back({ s[i],1 });//A
				}
			}
			else if (s[i] == 'D' || s[i] == 'E') {
				//VS.push_back("Slump_ST");
				if (VS.size() != 0 && VS.back().first == 'F' && VS.back().second==0) {
					NO = true;
					break;
				}
				VS.push_back({ s[i],1 });//D or E
				i++;//F
				int cnt = 0;
				while (1) {//F push
					if (s[i] == 'D' || s[i] == 'E' || s[i]=='G') {
						i--;
						VS.push_back({'F', cnt});
						break;
					}
					if (s[i] == 'C') {
						NO = true;
						break;
					}
					if (s[i] == 'F') {
						i++;
						cnt++;
					}
					//else VS.push_back(s[i++]);
				}
			}
			//뺴기
			else if (s[i] == 'G') {//슬럼프 지우기
				SluC++;
				if (VS.size() == 0) {//아직 지워야할 쌍이 남았는데 배열이 빈경우
					break;
				}
				else {
					if (VS.back().first == 'F') {// G -> Slump 기본 세트
						//Slump >> D(E)F*1 over + D(E) ~~~ G
						while (1) {
							int cnt = VS.back().second;//F count
							VS.pop_back();//F
							VS.pop_back();//D or E
							if (cnt==0 || VS.size()==0  || VS.back().first != 'F')break;
						}
					}
					else {
						break;
					}
				}
			}
			else if (s[i] == 'C') {//슬림프 지우기
				SliC++;
				if (VS.size() == 0) {//아직 지워야할 쌍이 남았는데 배열이 빈경우
					break;
				}
				else if (VS.back().first == 'B') {
					VS.pop_back();//B
					VS.pop_back();//A
				}
				else if (VS.back().first == 'A') {
					if (SluC > 1) {
						NO = true;
						break;
					}
					VS.pop_back();//A
					SluC = 0;// 슬럼프 카운터 초기화
				}
				else break;
			}
			if (NO)break;
		}

		if (!NO && VS.size()==0 && i==s.length())cout << "YES\n";
		//if (SliC == 0 && VS.size() == 0 && i == s.length())cout << "YES\n";
		else cout << "NO\n";
		VS.clear();

	}
	cout << "END OF OUTPUT\n";


	return 0;
}

