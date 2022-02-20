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

#define ALL(x) (x).begin(), (x).end()

const int LIMIT = 10000;

// TODO, allow an ad not to contain the given point

int n; // the number of rectangles;
struct Ad {
	int id, x, y, target_area;
	int x1, y1, x2, y2;
	void read() {
		scanf("%d%d%d", &x, &y, &target_area);
	}
	bool check() const { // point inside & the coords are in [0, LIMIT]
		return x1 <= x && x < x2 && y1 <= y && y < y2
			&& 0 <= x1 && x2 <= LIMIT && 0 <= y1 && y2 <= LIMIT;
	}
	void make_small() {
		x1 = x;
		y1 = y;
		x2 = x + 1;
		y2 = y + 1;
		assert(check());
	}
	bool disjoint(const Ad& he) const {
		return x2 <= he.x1 || he.x2 <= x1
		    || y2 <= he.y1 || he.y2 <= y1;
	}
	bool intersects(const Ad& he) const {
		return !disjoint(he);
	}
	void print() const {
		printf("%d %d %d %d\n", x1, y1, x2, y2);
	}
	int get_area() const {
		return (x2 - x1) * (y2 - y1);
	}
	double score() const {
		assert(check());
		double s = get_area();
		double r = target_area;
		double tmp = (1 - min(r, s) / max(r, s));
		return 1 - tmp * tmp;
	}
};
vector<Ad> ads;

void read() {
	scanf("%d", &n);
	ads.resize(n);
	for(int i = 0; i < n; ++i) {
		ads[i].id = i;
		ads[i].read();
	}
}

void output() {
	// note: sort by id if you have changed the order of ads
	double total_score = 0;
	for(const Ad& ad : ads) {
		ad.print();
		total_score += ad.score();
	}
	// cerr << "sum = " << total_score << endl;
	cerr << llround(1e9 * total_score / n + 1e-9) << endl;
	// cerr << "score = " << llround(1e9 * total_score / n + 1e-9) / 1e7 << "%" << endl;
}

std::mt19937 gen(1337);

bool intersects_any(vector<Ad> & tads, int idx){
    for(int i = 0; i < (int)tads.size(); i++){
        if( i == idx ){
            continue;
        }
        if(tads[idx].intersects(tads[i])){
            return true;
        }
    }
    return false;
}

void expand(vector<Ad> & tads, int idx){
    struct dir {
        int * ptr;
        int dir; // 1 or -1
    };
    Ad & ad = tads[idx];
    vector<dir> dirs = {
            {&ad.x1, -1},
            {&ad.y1, -1},
            {&ad.x2, 1},
            {&ad.y2, 1}
    };
    shuffle(ALL(dirs), gen);
    for(auto possible_direction : dirs){
        int desired_area = ad.target_area;
        int * p = possible_direction.ptr;
        int d = possible_direction.dir;
        int l = 0, r = 5000;
        while(l < r){
            int m = (l + r + 1) / 2;
            *p += d * m;
            if(intersects_any(tads, idx) || ad.get_area() > desired_area || !ad.check()){
                r = m - 1;
            } else{
                l = m;
            }
            *p -= d * m;
        }
        *p += d * l;
    }
}

void improve(){
    uniform_int_distribution<> dist(0, (int)ads.size() - 1);
    int rid = dist(gen);
    expand(ads, rid);
}

int main() {
	// started at 14:30
	read();
	
	for(int i = 0; i < n; ++i) {
		ads[i].make_small();
	}
	
	vector<bool> finished(n);
	for(int turn = 0; turn < 8000; ++turn) {
		for(int i = 0; i < n; ++i) {
			if(finished[i]) {
				continue;
			}
			bool anything_happened = false;
			for(int rep = 0; rep < 4; ++rep) {
				Ad maybe = ads[i];
				if(rep == 0) maybe.x1--;
				else if(rep == 1) maybe.y1--;
				else if(rep == 2) maybe.x2++;
				else maybe.y2++;
				auto is_ok = [&]() {
					if(maybe.get_area() > maybe.target_area) {
						return false;
					}
					if(!maybe.check()) {
						return false;
					}
					for(int j = 0; j < n; ++j) {
						if(i != j && maybe.intersects(ads[j])) {
							return false;
						}
					}
					return true;
				};
				if(is_ok()) {
					ads[i] = maybe;
					anything_happened = true;
				}
			}
			if(!anything_happened) {
				finished[i] = true;
			}
		}
	}
	
    auto start_time = clock();
    while(clock() - start_time < CLOCKS_PER_SEC * 4.5){
        improve();
    }
	
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			assert(!ads[i].intersects(ads[j]));
		}
	}
	
	output();
}
