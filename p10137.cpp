#include <iostream>
#include <algorithm>
#include <vector>


#pragma warning(disable:4996)
using namespace std;

int T;
double sum;
vector<double>arr;
//�۳� DUCC 3�г� 3������

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p10137.inp", "r", stdin);
	freopen("p10137.out", "w", stdout);
	while (1) {
		cin >> T;
		if (T == 0)break;
		double temp;
		sum = 0;
		for (int i = 0; i < T; i++) {
			cin >> temp;
			arr.push_back(temp);
			sum += temp;
		}
		double avg = sum / T;
		double PLUS = 0, MINUS = 0;
		
		for (int i = 0; i < arr.size(); i++) {
			//�Ҽ��� 2�ڸ��� Ȯ���ϰ� ����ϱ�
			//ex) 5.995 * 100 = 599.5 || * 100 �������ν�
			//��¿� �ʿ��� �Ҽ��� 2�ڸ��� Ȯ���ϰ� �츲
			//(int)599.5 = 599 || ���ʿ��� ������ �Ҽ������� ��� �߶�
			//(double)599 = 599.0 || �ٽ� �Ҽ��� 2�ڸ��� ����������� double ������ ��ȯ
			//599.0 / 100 = 5.99 || / 100 ���༭ �Ҽ��� 2�ڸ� �ٽ� �����
			double temp = (double)( (int)( (arr[i] - avg) * 100 ) )/100;
			// ���� ���°� ������� , ������°� ������ ��Ƽ� ���� ū�� ����ϸ� �װ� ��
			//DUCC 3���̶� ����
			if (temp < 0) {
				MINUS -= temp;
			}
			else {
				PLUS += temp;
			}

		}
		//cout << "$" << max(n, p) << '\n';
		printf("$%0.2f\n", max(PLUS, MINUS));
		arr.clear();

	}
	return 0;
}

