#include<iostream>

using namespace std;

/*
 * Dynamic programing. Running time O(n).
 */

int main() {
    int n, count, neven, nodd;

    // Read the input
    cin >> n;
    int x[n];
    for (int i = 0; i < n; i++) {
    	cin >> x[i];
    }
    // Calculate the values S_i
    // S_i = sum of elements from x[1] to x[i]
    int S[n];
    S[0] = x[0];
    for (int i = 1; i < n; i++) {
    	S[i] = x[i] + S[i-1];
    }

    // Calculate the result
    // If S[i] is even and there is k < i with S[k] is even,
    // then (k, i) is even pair. Similarly for odd S[i].
    count = 0;
    neven = 1;
    nodd = 0;
    for (int i = 0; i < n; i++) {
		if (S[i] % 2 == 0) {
			count += neven;
			neven++;
		} else {
			count += nodd;
			nodd++;
		}
    }
    cout << count << endl;

    return 0;
}
