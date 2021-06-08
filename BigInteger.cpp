//Big Integer, 구현
#include <iostream>
#include <algorithm>
#include <string>

#pragma warning(disable:4996)
#define PLUS 1
#define MINUS -1
#define Len 100

using namespace std;

typedef struct {
	char num[Len];
	int sign;
	int last;
}Bnum;

void add(Bnum* a, Bnum* b, Bnum* c);
void sub(Bnum* a, Bnum* b, Bnum* c);
void mul(Bnum* a, Bnum* b, Bnum* c);
void div(Bnum* a, Bnum* b, Bnum* c);

string a, op, b, ans;
Bnum A, B, C;
int L;

void zero(Bnum* n) {
	while ((n->last > 0) && (n->num[n->last] == '0'))n->last--;
	if ((n->last == 0) && (n->num[0] == '0'))n->sign = PLUS;
}

Bnum init(string s) {
	Bnum temp;
	reverse(s.begin(), s.end());
	for (int i = 0; i < Len; i++)temp.num[i] = '0';
	for (int i = 0; i < s.length(); i++) temp.num[i] = s[i];
	if (s[s.length() - 1] == '-') {
		temp.num[s.length() - 1] = '0';
		temp.sign = MINUS;
		temp.last = s.length() - 2;
	}
	else temp.sign = PLUS, temp.last = s.length() - 1;
	zero(&temp);
	return temp;
}

void init2(Bnum* c) {
	for (int i = 0; i < Len; i++)c->num[i] = '0';
	c->last = 0;
	c->sign = PLUS;
}

int compare(Bnum* a, Bnum* b) {
	if (a->sign == MINUS && b->sign == PLUS)return PLUS;
	if (a->sign == PLUS && b->sign == MINUS)return MINUS;

	if (b->last > a->last)return PLUS * a->sign;
	if (a->last > b->last)return MINUS * a->sign;

	for (int i = a->last; i >= 0; i--) {
		if (a->num[i] > b->num[i])return MINUS * a->sign;
		if (b->num[i] > a->num[i])return PLUS * a->sign;
	}
	return 0;
}

void shift(Bnum* n, int d) {
	if (n->last == 0 && n->num[0] == '0')return;
	for (int i = n->last; i >= 0; i--) {
		//if (i + d >= n->num.length())continue;
		n->num[i + d] = n->num[i];
	}
	for (int i = 0; i < d; i++)n->num[i] = '0';
	n->last += d;
}

void add(Bnum* a, Bnum* b, Bnum* c) {
	int carry;
	init2(c);
	if (a->sign == b->sign) c->sign = a->sign;
	else {
		if (a->sign == MINUS) {
			a->sign = PLUS;
			sub(b, a, c);
			a->sign = MINUS;
		}
		else {
			b->sign = PLUS;
			sub(a, b, c);
			b->sign = MINUS;
		}
		return;
	}
	c->last = max(a->last, b->last) + 1;
	carry = 0;
	for (int i = 0; i <= c->last; i++) {
		c->num[i] = (carry + (a->num[i] - '0') + (b->num[i] - '0')) % 10 + '0';
		carry = (carry + (a->num[i] - '0') + (b->num[i] - '0')) / 10;
	}
	zero(c);
}

void sub(Bnum* a, Bnum* b, Bnum* c) {
	int borrow;
	init2(c);
	if (a->sign == MINUS || b->sign == MINUS) {
		b->sign *= -1;
		add(a, b, c);
		b->sign *= -1;
		return;
	}
	if (compare(a, b) == PLUS) {
		sub(b, a, c);
		c->sign = MINUS;
		return;
	}
	c->last = max(a->last, b->last);
	borrow = 0;
	for (int i = 0; i <= c->last; i++) {
		int v = (a->num[i] - '0') - borrow - (b->num[i] - '0');
		if ((a->num[i] - '0') > 0)borrow = 0;
		if (v < 0)v += 10, borrow = 1;
		c->num[i] = (v % 10) + '0';
	}
	zero(c);
}

void mul(Bnum* a, Bnum* b, Bnum* c) {
	Bnum row, temp;
	init2(c);
	init2(&temp);
	row = *a;
	temp.sign = row.sign;
	for (int i = 0; i <= b->last; i++) {
		for (int j = 1; j <= (b->num[i] - '0'); j++) {
			add(c, &row, &temp);
			*c = temp;
		}
		shift(&row, 1);
	}
	c->sign = a->sign * b->sign;
	zero(c);
}

void div(Bnum* a, Bnum* b, Bnum* c) {
	Bnum row, temp, temp2;

	init2(&row);
	init2(&temp);
	init2(&temp2);
	init2(c);

	c->sign = a->sign * b->sign;

	int asign = a->sign, bsign = b->sign;
	a->sign = b->sign = PLUS;
	c->last = a->last;

	for (int i = a->last; i >= 0; i--) {
		shift(&row, 1);
		row.num[0] = a->num[i];
		c->num[i] = '0';
		while (compare(&row, b) != PLUS) {
			int t = c->num[i] - '0';
			t++;
			c->num[i] = t + '0';
			sub(&row, b, &temp);
			row = temp;
		}
	}
	//몫이 음수인경우에는 -(몫+1) 해준값을 리턴
	if (c->sign == MINUS && (row.num[0] != '0' || row.last != 0)) {
		Bnum ADD_ONE = init("1");
		c->sign = PLUS;
		temp2 = *c;
		add(&temp2, &ADD_ONE, c);
		c->sign = MINUS;
	}
	zero(c);
	a->sign = asign;
	b->sign = bsign;
}

void mod(Bnum* a, Bnum* b, Bnum* c) {
	Bnum row, temp, temp2;

	init2(&row);
	init2(&temp);
	init2(&temp2);
	init2(c);

	c->sign = a->sign * b->sign;

	int asign = a->sign, bsign = b->sign;
	a->sign = b->sign = PLUS;
	c->last = a->last;

	for (int i = a->last; i >= 0; i--) {
		shift(&row, 1);
		row.num[0] = a->num[i];
		c->num[i] = '0';
		while (compare(&row, b) != PLUS) {
			int t = c->num[i] - '0';
			t++;
			c->num[i] = t + '0';
			sub(&row, b, &temp);
			row = temp;
		}
	}
	//row.sign = PLUS;
	//sub(b, &row, c);
	//나누어 떨어지는 경우 ( 나머지 == 0 )
	if ((row.num[0] == '0' && row.last == 0)) {
		//c값을 0으로 만들어줌
		sub(b, b, c);
	}
	else {
		if (asign == bsign) {
			//c값을 나머지로 만들어줌
			Bnum Z;
			init2(&Z);
			add(&Z, &row, c);
		}
		else {//몫에서 나머지를 빼준값을 c에 넣어줌
			sub(b, &row, c);
		}
	}
	zero(c);
	a->sign = asign;
	b->sign = bsign;
}


int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	freopen("bigi.inp", "r", stdin);
	freopen("bigi.out", "w", stdout);

	while (1) {
		cin >> a >> op >> b;
		if (a.compare("0") == 0 && b.compare("0") == 0)break;
		A = init(a);
		B = init(b);
		if (op.compare("+") == 0) {//ok
			add(&A, &B, &C);
		}
		else if (op.compare("-") == 0) {//ok
			sub(&A, &B, &C);
		}
		else if (op.compare("*") == 0) {//ok
			mul(&A, &B, &C);
		}
		else if (op.compare("/") == 0) {// no
			div(&A, &B, &C);
		}
		else if (op.compare("%") == 0) {// no
			mod(&A, &B, &C);
		}
		//출력
		if (C.sign == MINUS)cout << '-';
		for (int i = C.last; i >= 0; i--) {
			cout << C.num[i];
		}
		cout << '\n';
	}
	return 0;
}

