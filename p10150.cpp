//set ���� ����
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <queue>

#pragma warning(disable:4996)
using namespace std;

vector<string>dict;// ���� �Է� �ܾ��
vector<string>ANS;// ��� ��¿�
bool visit[25144];// ���ڿ� �湮 üũ
int arr[25144];// Ž������ ���� �迭
int st_idx;

bool CH(string a, string b) {// ���繮�ڿ��� 1���� �ܾ ���̳��� ���ڿ� �Ǻ�
	int cnt = 0;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] != b[i])cnt++;// �ٸ� ���� �߽߰� cnt++
		if (cnt > 1)return false;// �ٸ� ���ڰ� 2�� �̻��ΰ��� �ʿ��� ���ڰ� �ƴ�
	}
	if (cnt == 1) return true;
	return false;
}

void BFS(string st, string ed, int st_idx) {// ���۹��ڿ�, ������ ���ڿ�, ���۹��ڿ� ������ idx
	queue< pair<string, int > >Q;
	bool OUT = false;
	int ed_idx = 0;

	for (int i = 0; i < dict.size(); i++) {
		arr[i] = -1;
		visit[i] = false;
	}

	Q.push({ st, st_idx });// ���۹��ڿ��� ���۹��ڿ��� dict �� idx�� �־���

	// Ž��
	while (!Q.empty()) {
		string now_str = Q.front().first;
		int arr_idx = Q.front().second;
		Q.pop();

		if (now_str.compare(ed) == 0) {// ������ ����
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
		//�̹� now_str�� �湮�Ȱ�� >> ���̻� �� �ʿ� ����
		if (visit[arr_idx])continue;
		
		visit[arr_idx] = true;

		for (int i = 0; i < dict.size(); i++) {
			if (now_str.length() != dict[i].length())continue;//���̰� �ٸ��� ���ʿ� �������� �ƴ�

			if (CH(now_str, dict[i])) {// ���̰� ������� ���� ���ϴ� ���ڿ��� �´��� üũ
				//������ ���̰� 1���� ���
				//�ش� ���ڿ��� �湮���� �������
				if (!visit[i]) {
					Q.push({ dict[i], i });
					if (arr[i] == -1)arr[i] = arr_idx;
				}

			}
		}
	}
	//Ž���� �����µ��� ��� ����� ����
	if(!OUT)cout << "No solution.\n";
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p10150.inp", "r", stdin);
	//freopen("p10150.out", "w", stdout);

	//������ �� ���� �Է¹ޱ�
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
		// �� ���ڿ��� ���̰� �ٸ���� �ٷ� no solution
		if (st.length() != ed.length()) {
			cout << "No solution.\n";
			continue;
		}
		// �� ������ �ϳ��� ������ ���°��
		bool ch = false;
		st_idx = 0;
		for (int i = 0; i < dict.size(); i++) {
			if (st.compare(dict[i]) == 0) {
				ch = true;
				st_idx = i;// ���� ���ڿ� ��ġ(�迭�� idx) ����
			}
		}
		if (!ch)continue;

		ch = false;

		for (int i = 0; i < dict.size(); i++) {
			if (ed.compare(dict[i]) == 0)ch = true;
		}
		if (!ch)continue;

		//���۰� �� ���ڿ��� �������
		if (st.compare(ed) == 0) {
			cout << st << ' ' << ed << '\n';
			continue;
		}

		//��� ���� ����� Ž�� ����
		BFS(st, ed, st_idx);
	}


	return 0;
}

//set ����� ����
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
//vector<string>dict;// ���� �Է� �ܾ��
//vector<string>ANS;// ��� ��¿�
//int arr[25144];// �湮+Ž������ ���� �迭
//int st_idx;
//
//bool CH(string a, string b) {// ���繮�ڿ��� 1���� �ܾ ���̳��� ���ڿ� �Ǻ�
//	int cnt = 0;
//	for (int i = 0; i < a.length(); i++) {
//		if (a[i] != b[i])cnt++;// �ٸ� ���� �߽߰� cnt++
//		if (cnt > 1)return false;// �ٸ� ���ڰ� 2�� �̻��ΰ��� �ʿ��� ���ڰ� �ƴ�
//	}
//	if (cnt == 1) return true;
//	return false;
//}
//
//void BFS(string st, string ed, int st_idx) {// ���۹��ڿ�, ������ ���ڿ�, ���۹��ڿ� ������ idx
//	queue< pair<string, int > >Q;
//	set<string>visit;
//	bool OUT = false;
//	int ed_idx = 0;
//
//	for (int i = 0; i < dict.size(); i++)arr[i] = -1;
//
//	Q.push({ st, st_idx });// ���۹��ڿ��� ���۹��ڿ��� dict �� idx�� �־���
//
//	// Ž��
//	while (!Q.empty()) {
//		string now_str = Q.front().first;
//		int arr_idx = Q.front().second;
//		Q.pop();
//
//		if (now_str.compare(ed) == 0) {// ������ ����
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
//		//�̹� now_str�� �湮�Ȱ�� >> ���̻� �� �ʿ� ����
//		if (visit.find(now_str) != visit.end())continue;
//
//		visit.insert(now_str);
//
//		for (int i = 0; i < dict.size(); i++) {
//			if (now_str.length() != dict[i].length())continue;//���̰� �ٸ��� ���ʿ� �������� �ƴ�
//
//			if (CH(now_str, dict[i])) {// ���̰� ������� ���� ���ϴ� ���ڿ��� �´��� üũ
//				//������ ���̰� 1���� ���
//				if (visit.find(dict[i]) == visit.end()) {//�ش� ���ڿ��� �湮���� �������
//					//visit.insert(dict[i]);// �ش繮�ڿ� �湮 üũ
//					Q.push({ dict[i], i });
//					if (arr[i] == -1)arr[i] = arr_idx;
//				}
//
//			}
//		}
//	}
//	//Ž���� �����µ��� ANS�� �ƹ��͵� ���°�� >> ��� ����� ����
//	if (!OUT)cout << "No solution.\n";
//}
//
//int main()
//{
//	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	freopen("p10150.inp", "r", stdin);
//	freopen("p10150.out", "w", stdout);
//
//	//������ �� ���� �Է¹ޱ�
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
//		// �� ���ڿ��� ���̰� �ٸ���� �ٷ� no solution
//		if (st.length() != ed.length()) {
//			cout << "No solution.\n";
//			continue;
//		}
//		// �� ������ �ϳ��� ������ ���°��
//		bool ch = false;
//		st_idx = 0;
//		for (int i = 0; i < dict.size(); i++) {
//			if (st.compare(dict[i]) == 0) {
//				ch = true;
//				st_idx = i;// ���� ���ڿ� ��ġ(�迭�� idx) ����
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
//		//���۰� �� ���ڿ��� �������
//		if (st.compare(ed) == 0) {
//			cout << st << ' ' << ed << '\n';
//			continue;
//		}
//
//		//��� ���� ����� Ž�� ����
//		BFS(st, ed, st_idx);
//	}
//
//
//	return 0;
//}
//
