#include <iostream>
#include "deque.hpp"

using namespace std;

int main() {
	Deque<int> p;
	p.push_back(42);
	p.push_back(43);
	p.push_back(44);

	cout << p[0] << ' ' << p[1] << ' ' << p[2] << endl;

	for (Deque<int>::iterator it = p.begin(); it != p.end(); ++it) {
		cout << *it << ' ';
	}
	cout << endl;

	for (auto n : p) {
		cout << n << ' ';
	}
	cout << endl;

	Deque<double> pSmall(2);
	pSmall.push_back(3.14);
	double& first = pSmall[0];
	pSmall.push_back(4.2);
	pSmall.push_back(8.5);
	pSmall.push_back(9.4);
	pSmall.push_back(15.5);
	pSmall.push_back(8.9);

	cout << first << endl;
	for (auto n : pSmall) {
		cout << n << ' ';
	}

	return 0;
}
