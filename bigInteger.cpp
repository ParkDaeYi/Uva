#include <cstdio>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <string>
#define MAXDIGITS 100
#define PLUS 1
#define MINUS -1
#pragma warning(disable:4996)
using namespace std;

class bignum{
public:
	bignum();
	~bignum();
	bignum(int n);
	bignum(long long int n);
	bignum(string str);
	bignum(const bignum* other);

	// 사칙 연산
	const bignum add(bignum& other);
	const bignum multiply(bignum& other);
	const bignum divide(bignum& other);
	const bignum subtract(bignum& other);
	const bignum digitShift(unsigned int n);

	// 진수 변환
	string hexadecimal(bignum bn);
	string octal(bignum bn);
	string binary(bignum bn);

	// 비교 연산
	int compare(const bignum& other) const;

	// -0 방지
	const void zero_justify();

	// 비트 연산
	const bignum leftShift(unsigned int n);
	const bignum rightShift(unsigned int n);
	const bignum NOT () const;

	// 부호 연산
	const bignum operator-();
	const bignum operator+();

	//비트 연산
	const bignum operator <<(unsigned int n);
	const bignum operator >>(unsigned int n);
	const bignum operator ~() const;

	//대입 연산
	bignum& operator =(const bignum& other);
	bignum& operator +=(bignum& other);
	bignum& operator -=(bignum& other);
	bignum& operator *=(bignum& other);
	bignum& operator /=(bignum& other);
	bignum& operator %=(bignum& other);
	bignum& operator <<=(unsigned int n);
	bignum& operator >>=(unsigned int n);

	// 출력 연산
	const string asString() const;

private:
	char digits[MAXDIGITS];
	int signbit;
	int lastdigit;
};

bignum::bignum() {
	for (int i = 0; i < MAXDIGITS; ++i) digits[i] = 0;
	lastdigit = 0;
	signbit = PLUS;
}
bignum::bignum(int n) {
	lastdigit = 0;
	bool flag;
	if (n < 0) {
		flag = 0;
		n = -n;
	}
	else flag = 1;

	int tmp = n;
	while (tmp) {
		int d = tmp % 10;
		tmp /= 10;
		digits[lastdigit++] = (char)d;
	}
	for (int i = lastdigit; i < MAXDIGITS; ++i) digits[i] = 0;
	lastdigit--;
	signbit = flag ? PLUS : MINUS;
}
bignum::bignum(long long int n) {
	lastdigit = 0;
	bool flag;
	if (n < 0) {
		flag = 0;
		n = -n;
	}
	else flag = 1;

	while (n) {
		int d = n % 10;
		n /= 10;
		digits[lastdigit++] = (char)d;
	}
	for (int i = lastdigit; i < MAXDIGITS; ++i) digits[i] = 0;
	lastdigit--;
	signbit = flag ? PLUS : MINUS;
}
bignum::bignum(string str) {
	int eof = 0, len = str.size() -1;
	if (str[0] == '-') {
		eof++;
		signbit = MINUS;
	}
	else {
		if (str[0] == '+') eof++;
		signbit = PLUS;
	}
	int i, j;
	for (i = len, j = 0; i >= eof; --i) digits[j++] = str[i] - '0';
	for (; j < MAXDIGITS; ++j) digits[j] = 0;
	lastdigit = len;
}
bignum::bignum(const bignum* other) {
	for (int i = 0; i < MAXDIGITS; ++i) digits[i] = other->digits[i];
	lastdigit = other->lastdigit;
	signbit = other->signbit;
}
bignum::~bignum() {}

const bignum operator+(bignum& lhs, bignum& rhs) {
	return lhs.add(rhs);
}
const bignum operator-(bignum& lhs, bignum& rhs) {
	return lhs.subtract(rhs);
}
const bignum operator*(bignum& lhs, bignum& rhs) {
	return lhs.multiply(rhs);
}
const bignum operator/(bignum& lhs, bignum& rhs) {
	return lhs.divide(rhs);
}
const bignum bignum::operator<<(unsigned int n) {
	return leftShift(n);
}
const bignum bignum::operator>>(unsigned int n) {
	return rightShift(n);
}
const bignum bignum::operator~() const {
	return NOT();
}

string bignum::hexadecimal(bignum bn) {
	if ((bn.lastdigit == 0) && (bn.digits[0] == 0)) return "";

	string ret = "";
	bignum hx;
	hx.lastdigit = bn.lastdigit;
	int tmp = bn.digits[bn.lastdigit];
	for (int i = bn.lastdigit - 1; i >= 0; --i) {
		tmp *= 10;
		tmp += bn.digits[i];
		hx.digits[i] = (char)(tmp / 16);
		tmp %= 16;
	}

	switch (tmp % 16) {
	case 10: ret += 'A'; break;
	case 11: ret += 'B'; break;
	case 12: ret += 'C'; break;
	case 13: ret += 'D'; break;
	case 14: ret += 'E'; break;
	case 15: ret += 'F'; break;
	default: ret += tmp % 16 + '0';
	}
	hx.zero_justify();

	return ret = hexadecimal(hx) + ret;
}

string bignum::octal(bignum bn) {
	if ((bn.lastdigit == 0) && (bn.digits[0] == 0)) return "";

	string ret = "";
	bignum oc;
	oc.lastdigit = bn.lastdigit;
	int tmp = 0;
	for (int i = bn.lastdigit; i >= 0; --i) {
		tmp *= 10;
		tmp += bn.digits[i];
		oc.digits[i] = (char)(tmp / 8);
		tmp %= 8;
	}

	ret += tmp % 8 + '0';
	oc.zero_justify();

	return ret = octal(oc) + ret;
}

string bignum::binary(bignum bn) {
	if ((bn.lastdigit == 0) && (bn.digits[0] == 0)) return "";

	string ret = "";
	bignum bi;
	bi.lastdigit = bn.lastdigit;
	int tmp = 0;
	for (int i = bn.lastdigit; i >= 0; --i) {
		tmp *= 10;
		tmp += bn.digits[i];
		bi.digits[i] = (char)(tmp / 2);
		tmp %= 2;
	}

	ret += tmp % 2 + '0';
	bi.zero_justify();

	return ret = binary(bi) + ret;
}

const void bignum::zero_justify() {
	while ((lastdigit > 0) && (digits[lastdigit] == 0)) lastdigit--;
	if ((lastdigit == 0) && (digits[0] == 0)) signbit = PLUS;
}

const bignum bignum::add(bignum& other) {
	bignum ret;
	int carry;

	if (signbit == other.signbit) ret.signbit = signbit;
	else {
		if (signbit == MINUS) {
			signbit = PLUS;
			ret = other.subtract(*this);
			signbit = MINUS;
		}
		else {
			other.signbit = PLUS;
			ret = this->subtract(other);
			other.signbit = MINUS;
		}
		return ret;
	}
	ret.lastdigit = max(lastdigit, other.lastdigit) + 1;
	carry = 0;

	for (int i = 0; i <= (ret.lastdigit); ++i) {
		ret.digits[i] = (char)(carry + digits[i] + other.digits[i]) % 10;
		carry = (carry + digits[i] + other.digits[i]) / 10;
	}
	ret.zero_justify();
	return ret;
}

const bignum bignum::subtract(bignum& other) {
	bignum ret = new bignum();
	int borrow, v, i;
	
	if ((signbit == MINUS) || (other.signbit == MINUS)) {
		other.signbit = -1 * other.signbit;
		ret = this->add(other);
		other.signbit = -1 * other.signbit;
		return ret;
	}
	if (this->compare(other) == PLUS) {
		ret = other.subtract(*this);
		ret.signbit = MINUS;
		return ret;
	}
	ret.lastdigit = max(lastdigit, other.lastdigit);
	borrow = 0;
	for (i = 0; i <= (ret.lastdigit); ++i) {
		v = digits[i] - borrow - other.digits[i];
		if (v < 0) {
			v += 10;
			borrow = 1;
		}
		else borrow = 0;
		ret.digits[i] += (char)v % 10;
	}
	ret.zero_justify();
	return ret;
}

int bignum::compare(const bignum& other) const {
	if ((signbit == MINUS) && (other.signbit == PLUS)) return PLUS;
	if ((signbit == PLUS) && (other.signbit == MINUS)) return MINUS;

	if (other.lastdigit > lastdigit) return PLUS * signbit;
	if (lastdigit > other.lastdigit) return MINUS * signbit;

	for (int i = lastdigit; i >= 0; --i) {
		if (digits[i] > other.digits[i]) return MINUS * signbit;
		if (other.digits[i] > digits[i]) return PLUS * signbit;
	}
	return 0;
}

const bignum bignum::multiply(bignum& other) {
	bignum row, tmp, ret = new bignum();
	int i, j;

	row = *this;
	for (i = 0; i <= other.lastdigit; ++i) {
		for (j = 1; j <= other.digits[i]; ++j) {
			tmp = ret.add(row);
			ret = &tmp;
		}
		row.digitShift(1);
	}
	ret.signbit = signbit * other.signbit;
	ret.zero_justify();
	return ret;
}

const bignum bignum::digitShift(unsigned int n) {
	int i;

	if ((lastdigit == 0) && (digits[0] == 0)) return *this;

	for (i = lastdigit; i >= 0; --i) digits[i + n] = digits[i];

	for (int i = 0; i < n; ++i) digits[i] = 0;

	lastdigit = lastdigit + n;
	return *this;
}

const bignum bignum::divide(bignum& other) {
	bignum row, tmp, ret;
	int tsign, osign, i, j;

	ret.signbit = signbit * other.signbit;

	tsign = signbit;
	osign = other.signbit;

	signbit = PLUS;
	other.signbit = PLUS;

	ret.lastdigit = lastdigit;

	for (i = lastdigit; i >= 0; --i) {
		row.digitShift(1);
		row.digits[0] = digits[i];
		ret.digits[i] = 0;
		while (row.compare(other) != PLUS) {
			ret.digits[i]++;
			tmp = row.subtract(other);
			row = tmp;
		}
	}
	ret.zero_justify();
	signbit = tsign;
	other.signbit = osign;

	return ret;
}

const bignum bignum::leftShift(unsigned int n) {
	bignum ret(1), two(2);

	if ((lastdigit == 0) && (digits[0] == 0)) return *this;
	while (n) {
		ret *= two;
		n--;
	}
	return (*this) * ret;
}

const bignum bignum::rightShift(unsigned int n) {
	bignum ret(1), two(2);

	if ((lastdigit == 0) && (digits[0] == 0)) return *this;
	while (n) {
		ret *= two;
		n--;
	}
	return (*this) / ret;
}

const bignum bignum::NOT() const {
	bignum ret = *this, one(1);

	if (ret.signbit == PLUS) {
		ret += one;
		ret.signbit = MINUS;
	}
	else {
		ret += one;
		ret.signbit = PLUS;
	}
		
	return ret;
}

const bignum bignum::operator+() {
	return *this;
}
const bignum bignum::operator-() {
	signbit = signbit == PLUS ? MINUS : PLUS;
	return *this;
}
bignum& bignum::operator=(const bignum& other) {
	for (int i = 0; i < MAXDIGITS; ++i) digits[i] = other.digits[i];
	lastdigit = other.lastdigit;
	signbit = other.signbit;
	return *this;
}
bignum& bignum::operator+=(bignum& other) {
	return *this = (*this) + other;
}
bignum& bignum::operator-=(bignum& other) {
	return *this = (*this) - other;
}
bignum& bignum::operator*=(bignum& other) {
	return *this = (*this) * other;
}
bignum& bignum::operator/=(bignum& other) {
	return *this = (*this) / other;
}
bignum& bignum::operator<<=(unsigned int n) {
	return *this = (*this) << n;
}
bignum& bignum::operator>>=(unsigned int n) {
	return *this = (*this) >> n;
}

const string bignum::asString() const {
	string ret = "";
	if (signbit == MINUS) ret += '-';
	for (int i = lastdigit; i >= 0; --i) ret += digits[i] + '0';
	return ret;
}