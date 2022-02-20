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

#define ALL(x) (x).begin(), (x).end()

vector<int> sample_distinct(int n, int lb, int rb){
    int total = (rb - lb) + 1;
    uniform_int_distribution<> dist(lb, rb);
    set<int> numbers;
    while(numbers.size() != n){
        int x = rand() % total + lb;
        if(!numbers.count(x)){
            numbers.insert(x);
        }
    }
    return {ALL(numbers)};
}

double random_double(){
    return (double)rand() / RAND_MAX;
}

int argc = 0;

int main(int argc, char ** argv) {
    srand(stoi(argv[1]));
    int n = lround(50 * pow(4, random_double()));
    vector<int> p1(10000);
    vector<int> p2(10000);

    for(auto p: {&p1, &p2}){
        iota(ALL(*p), 0);
        random_shuffle(ALL(*p));
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
