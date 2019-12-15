#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

//TODO: make this use whatever Bigintegers are in c++

bool isPerfectPower (int n) {
	//TODO: Make this work
	for (int i = 2; i <= ceil(log2(n)); i++) {
		float root = pow(n, 1/i);
		if (round(root) == root) {
			return true;
		}
	}
	return false;
}

int modPower (int x, int y, int n) {
	int m = y;
	int p = 1;
	int z = x;
	while (m > 0) {
		while (m % 2 == 0) {
			m = m / 2;
			z = (z * z) % n;
		}
		m--;
		p = (p * z) % n;	
	}
	return p;
}

int getR (int n) {
	float l = log2(n);
	
	int maxk = pow(l, 2);
	int maxr = max(3, int(ceil(pow(l, 5))));
	
	bool nextr = true;
	int r;
	
	for (r = 2; nextr && (r < maxr); r++) {
		
		nextr = false;
		for (int k = 1; !nextr && k<maxk; k++) {
			nextr = modPower(n, k, r)==0 || modPower(n, k, r)==1;
		}
		
	}
	
	r--;
	
	return r;
}

int gcd (int a, int b) {
	while (true) {
		if (a >= b) {
			a = a % b;
		} else if (a < b) {
			b = b % a;
		}
		if (a==0) {
			return b;
		}
		if (b==0) {
			return a;
		}
	}
}

int phi(int n){
	int t = 0;
	for (int i = 1; i < n; i++) {
		if (gcd(n, i)==1) {t++;}
	}
	return t;
}

bool isPrime(int n) {
	
	if (n % 2 == 0) {return false;}
	//if (isPerfectPower(n)) {return false;}
	
	int r = getR(n);
	
	int a = r;
	for (a=r; a>1 && a<n; a--) {if (gcd(a, n) != 1) {return false;}}
	
	if (n <= 5690034 && r >= n) {return true;}
	
	int bound = floor(sqrt(phi(r)) * log2(n));
	
	for (int a = 1; a <= bound; a++) {if (modPower(a, n, n) - a != 0) {return false;}}
	
	return true;
}

int main() {
	int n;
	cin >> n;
	cout << (isPrime(n) ? "prime" : "composite") << endl;
	system("PAUSE");
}