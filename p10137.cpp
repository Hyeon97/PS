#include <iostream>
#include <algorithm>
#include <vector>


#pragma warning(disable:4996)
using namespace std;

int T;
double sum;
vector<double>arr;
//작년 DUCC 3학년 3번문제

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
			//소숫점 2자리는 확실하게 계산하기
			//ex) 5.995 * 100 = 599.5 || * 100 해줌으로써
			//출력에 필요한 소수점 2자리는 확실하게 살림
			//(int)599.5 = 599 || 불필요한 나머지 소숫점들을 모두 잘라냄
			//(double)599 = 599.0 || 다시 소숫점 2자리를 살려야함으로 double 형으로 전환
			//599.0 / 100 = 5.99 || / 100 해줘서 소숫점 2자리 다시 살려냄
			double temp = (double)( (int)( (arr[i] - avg) * 100 ) )/100;
			// 음수 나온건 음수대로 , 양수나온건 양수대로 모아서 둘중 큰걸 출력하면 그게 답
			//DUCC 3번이랑 유사
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

