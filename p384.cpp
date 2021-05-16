#include <iostream>
#include <vector>
#include <string>
#include <utility>

#pragma warning(disable:4996)
using namespace std;

int T,SluC, SliC;
string s;
vector< pair<char, int> >VS;//���� �ش繮�� ���� ����


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p384.inp", "r", stdin);
	freopen("p384.out", "w", stdout);

	cin >> T;//�Է� ���ڿ� ����
	cout << "SLURPYS OUTPUT\n";
	for (int t = 0; t < T; t++) {
		cin >> s;//���ڿ� �Է¹���;
		SluC=0, SliC=0;// ������ ī���� A ������ C ���¿��� �۵� || ������ ī����
		bool NO = false;
		bool AH = false;
		//now_st_idx = 0;
		int i = 0;
		for (i; i < s.length(); i++) {
			//�ֱ�
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
			//����
			else if (s[i] == 'G') {//������ �����
				SluC++;
				if (VS.size() == 0) {//���� �������� ���� ���Ҵµ� �迭�� ����
					break;
				}
				else {
					if (VS.back().first == 'F') {// G -> Slump �⺻ ��Ʈ
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
			else if (s[i] == 'C') {//������ �����
				SliC++;
				if (VS.size() == 0) {//���� �������� ���� ���Ҵµ� �迭�� ����
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
					SluC = 0;// ������ ī���� �ʱ�ȭ
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

