//AH�� ���� �Ǵ� ���ɰ� �߸� ���ε� �������� �ϴ� ����
#include <iostream>
#include <vector>
#include <string>
#include <utility>

#pragma warning(disable:4996)
using namespace std;

int H, D,F,day;//�칰, �� ���, �� �ϰ�, �Ƿε�, �����̳���, �ϼ� 
double U,SH;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("snail.inp", "r", stdin);
	freopen("snail.out", "w", stdout);
	while (1) {
		cin >> H >> U >> D >> F;
		//F *= 0.01;
		if (H == 0)break;
		SH = 0;
		day = 0;
		//int u = (int)U;
		double temp = ((int)(U * F))*0.01;
		while (1) {
			day++;
			//��
			if(U>0) SH += U;//�ö�
			if (SH > H) {//������ ���� �칰���� ���� >> Ż��
				cout << "success on day " << day << '\n';
				break;
			}
			//��
			if (SH - D <= 7.1054273576010019e-15)SH = 0;//���� ���ǽ��� <=0�ε� �����̺������� ��������
			else SH -= D;//�̲�����
			//if (SH < 0)SH = 0;
			if (U - temp <= 6.6613381477509392e-16)U = 0;//���� ���ǽ��� <=0�ε� �����̺������� ��������
			else U -= temp;
			if (day != 1 && SH <= 0) {
				cout << "failure on day " << day << '\n';
				break;
			}
		}

	}




	return 0;
}

