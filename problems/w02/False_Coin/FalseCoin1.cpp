#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> vi;
typedef vector<pair<vi, char> > vii;

bool evaluate(vi ineq, int var, char sign) {
    int left0 = 0;
    int left1 = 0;
    int right0 = 0;
    int right1 = 0;
    for(int l = 0, r = ineq.size()/2; l < ineq.size()/2; ++l, ++r) {
        int var_l = ineq[l];
        int var_r = ineq[r];
        left0 += (var_l == var) ? 0 : 1;
        left1 += (var_l == var) ? 1 : 0;
        right0 += (var_r == var) ? 0 : 1;
        right1 += (var_r == var) ? 1 : 0;
    }
    if(sign == '<') return (left0 < right0 || left1 < right1);
    else return (left0 > right0 || left1 > right1);
}

void testcase() {
    int N, K; cin >> N >> K;
    vi coins(N, 0);
    vii inequalities;

    for(int k = 0; k < K; ++k) {
        int C; cin >> C;
        vi equation(2*C);
        for(int i = 0; i < 2*C; ++i) {
            int c; cin >> c;
            equation[i] = c-1;
        }
        char sign; cin >> sign;
        if(sign == '<' || sign == '>') inequalities.push_back(make_pair(equation, sign));
        else for(int i = 0; i < 2*C; ++i) coins[equation[i]] = 1; 
    }

    int knowns = 0;
    int unknown = -1;
    for(int i = 0; i < N; ++i) {
        knowns += coins[i];
        if(coins[i] == 1) continue;
        for(int ineq = 0; ineq < inequalities.size(); ++ineq) {
            vi inequality = inequalities[ineq].first;
            bool result = evaluate(inequality, i, inequalities[ineq].second);
            if(!result) {
                coins[i] = 1;
                ++knowns;
                break;
            }
        }
        if(coins[i] == 0) unknown = i;
    }
    if(N - knowns == 1) cout << unknown+1 << "\n";
    else cout << 0 << "\n";
}

int main() {
    int TC; cin >> TC;
    while (TC--) testcase();
    return 0;
}
