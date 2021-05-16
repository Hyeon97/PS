#include <iostream>


#pragma warning(disable:4996)
using namespace std;

int ST, ED, MAXL=0;
bool re = false;
int TN(int num) {
	int count = 1;
	while (num != 1) {
		count++;
		if (num % 2) {
			num *= 3;
			num += 1;
		}
		else {
			num /= 2;
		}
	}
	return count;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("p100.inp", "r", stdin);
	freopen("p100.out", "w", stdout);
	
	while (cin >> ST >> ED) {
		MAXL = 0;
		if (ST > ED) {//입력 숫자 반대인경우
			int temp;
			temp = ST;
			ST = ED;
			ED = temp;
			re = true;
		}
		if (ST == ED) {//입력숫자 같은경우
			MAXL = TN(ST);
		}
		else {
			for (int i = ST; i <= ED; i++) {
				int L=TN(i);
				if (L > MAXL)MAXL = L;
			}
		}
		if(re)cout <<ED<<' '<<ST<<' '<<MAXL << '\n';
		else cout << ST << ' ' << ED << ' ' << MAXL << '\n';
		re = false;
	}
	
    return 0;
}

