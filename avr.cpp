#include <bits/stdc++.h>
using namespace std;
int main() {
	double sum = 0;
	int x;
	int count = 0;
	while(cin >> x) {
		sum += x;
		count++;
	}
	assert(count != 0);
	printf("avr = %.2lf%%\n", sum / count / 1e7);
}
