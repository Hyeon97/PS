//AH쪽 수정 또는 테케가 잘못 업로드 됬을수도 일단 정지
#include <iostream>
#include <vector>
#include <string>
#include <utility>

#pragma warning(disable:4996)
using namespace std;

int H, D,F,day;//우물, 낮 상승, 밤 하강, 피로도, 달팽이높이, 일수 
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
			//낮
			if(U>0) SH += U;//올라감
			if (SH > H) {//달팽이 높이 우물끝에 도착 >> 탈출
				cout << "success on day " << day << '\n';
				break;
			}
			//밤
			if (SH - D <= 7.1054273576010019e-15)SH = 0;//원래 조건식은 <=0인데 설정이병신인지 이지랄남
			else SH -= D;//미끄러짐
			//if (SH < 0)SH = 0;
			if (U - temp <= 6.6613381477509392e-16)U = 0;//원래 조건식은 <=0인데 설정이병신인지 이지랄남
			else U -= temp;
			if (day != 1 && SH <= 0) {
				cout << "failure on day " << day << '\n';
				break;
			}
		}

	}




	return 0;
}

