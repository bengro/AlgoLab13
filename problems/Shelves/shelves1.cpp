#include <iostream>

using namespace std;

int main(void) {
	// speeds up read and write
	ios_base::sync_with_stdio(false);

	// number of testcases we need to run
	int nrCases;
	cin >> nrCases;

	for(int i = 0; i < nrCases; i++) {
		// read the input for the test case
		int l, m, n;
		cin >> l >> m >> n;

		// number of the two shelves and remaining length
		int cm = 0;
		int cn = 0;
		int r = l;

		for(int tmpCn = l/n; tmpCn >= 0 && r != 0; tmpCn--) {
			// calculate the number of the small shelves
			int tmpCm  = (l - tmpCn * n) / m;
			if(tmpCm >= n) {
				break;
			}

			// calculate the new remaining space and use it when smaller
			int tmpR = l - tmpCn * n - tmpCm * m;
			if(tmpR < r) {
				cn = tmpCn;
				cm = tmpCm;
				r = tmpR;
			}
		}

		// output the result
		cout << cm << " " << cn << " " << r << '\n';
	}

	return 0;
}