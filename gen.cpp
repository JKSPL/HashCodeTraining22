#include <bits/stdc++.h>
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
// debug & operator << (debug & dd, P p) { dd << "(" << p.x << ", " << p.y << ")"; return dd; }
std::mt19937 gen;

#define ALL(x) (x).begin(), (x).end()

vector<int> sample_distinct(int n, int lb, int rb){
    uniform_int_distribution<> dist(lb, rb);
    set<int> numbers;
    while(numbers.size() != n){
        int x = dist(gen);
        if(!numbers.count(x)){
            numbers.insert(x);
        }
    }
    return {ALL(numbers)};
}

int argc = 0;

int main(int argc, char ** argv) {
    gen.seed(stoi(argv[1]));
    uniform_real_distribution<> dist(0, 1);
    int n = int(round(50 * pow(4, dist(gen))));
    vector<int> p1(10000);
    vector<int> p2(10000);

    for(auto p: {&p1, &p2}){
        iota(ALL(*p), 0);
        shuffle(ALL(*p), gen);
    }
    vector<int> Q = sample_distinct(n - 1, 1, 99999999);
    Q.insert(Q.begin(), 0);
    Q.push_back(100000000);
    cout << n << "\n";
    for(int i = 0; i < n; i++){
        int x = p1[i];
        int y = p2[i];
        int r = Q[i + 1] - Q[i];
        cout << x << " " << y << " " << r << "\n";
    }
}
