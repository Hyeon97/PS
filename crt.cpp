#include <iostream>
#include <algorithm>
#include <utility>

#pragma warning(disable:4996)

typedef long long ll;
using namespace std;

ll q, r, s, t, Gcd;
pair <ll, ll>S, T;

int Test_case, R_cnt;
ll R, n, ans_R, ans_n, ans_t_R, ans_t_n, gcd_n;
bool no;

ll gcd(ll a, ll b) {//최대공약수
	if (b == 0)return a;
	else gcd(b, a % b);
}

void E_gcd(ll r1, ll r2) {//확장유클리드
	S = { 1,0 };
	T = { 0,1 };
	//초기값 세팅
	q = r1 / r2;
	r = r1 % r2;
	s = S.first - q * S.second;
	t = T.first - q * T.second;
	while (1) {
		if (r == 0) {
			Gcd = r2;
			break;
		}
		r1 = r2;
		r2 = r;
		q = r1 / r2;
		r = r1 % r2;
		S.first = S.second;
		S.second = s;
		T.first = T.second;
		T.second = t;
		s = S.first - q * S.second;
		t = T.first - q * T.second;
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	freopen("crt.inp", "r", stdin);
	freopen("crt.out", "w", stdout);

	cin >> Test_case;
	while (Test_case--) {
		//초기화
		no = false;
		//메인
		cin >> R_cnt;
		for (int i = 0; i < R_cnt; i++) {
			cin >> R >> n;
			if (no)continue;
			if (i == 0) {
				ans_R = R; ans_n = n;
			}
			else {
				R -= ans_R;
				//0이상이 될때까지 n더해줌
				if (R < 0) {
					ll temp = abs(R) / n;
					temp += 1;
					R += (temp * n);
				}
				//n보다 큰경우 작아질때까지 빼줌
				if (R >= n) {
					ll temp = R / n;
					temp -= 1;
					R -= (temp * n);
				}
				//ans_n, n의 최대공약수를 구해줌
				gcd_n = ans_n >= n ? gcd(ans_n, n) : gcd(n, ans_n);
				//구해진 최대공약수와 R의 최대공약수를 구함
				gcd_n = gcd_n >= R ? gcd(gcd_n, R) : gcd(R, gcd_n);
				//구해진 최대공약수로 모두 나눠줌
				ans_t_n = ans_n;
				ans_t_n /= gcd_n;
				R /= gcd_n;
				n /= gcd_n;
				//확장 유클리드 쓰기전 구하는 수가 서로소인지 확인
				//서로소가 아닌경우엔 해 X
				//서로소 = 최대공략수 == 1인거
				Gcd = ans_t_n >= n ? gcd(ans_t_n, n) : gcd(n, ans_t_n);
				if (Gcd != 1) {
					cout << -1 << '\n';
					no = true;
					continue;
				}
				//확장유클리드로 해를 구함 t,s값 구함 이때 t값이 음수인경우 +mod 값 해줌
				E_gcd(ans_t_n, n);
				gcd_n = ans_t_n >= n ? gcd(ans_n, n) : gcd(n, ans_n);
				R *= S.second;
				if (R < 0) {
					ll temp = abs(R) / n;
					temp += 1;
					R += (temp * n);
				}
				R %= n;
				ans_R += (ans_n * R);
				ans_n *= n;
			}
		}
		if (!no) {
			if (ans_R > ans_n)ans_R -= ans_n;
			cout << ans_R << '\n';
		}
	}

	return 0;
}

