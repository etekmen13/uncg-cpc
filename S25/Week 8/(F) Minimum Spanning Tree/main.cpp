#pragma region
#include <bits/stdc++.h>

using namespace std;
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define PER(i, a, b) for (int i = a; i >= b; i--)
#define per(i, a, b) for (int i = a; i > b; i--)

#define pb push_back
#define mp make_pair
#define F first
#define S second
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;

const ll MOD = 1000000007;

ll mod_add(ll a, ll b, ll m) { return ((a % m) + (b % m)) % m; }
ll mod_sub(ll a, ll b, ll m) { return ((a % m) - (b % m) + m) % m; }
ll mod_mul(ll a, ll b, ll m) { return ((a % m) * (b % m)) % m; }
ll mod_exp(ll a, ll e, ll M) {
  ll res = 1;
  while (e) {
    if (e & 1) res = (res * a) % M;
    a = (a * a) % M;
    e >>= 1;
  }
  return res;
}

template <typename T, typename Func>
T bin_apply_func(T obj, Func func, ll n) {
  T result = std::move(obj);  // accumulator object
  Func f = func;              // f will be "squared" (repeatedly composed)

  while (n > 0) {
    if (n & 1) {
      result = f(result);  // appy the function
    }
    Func f_next = [f](T x) {  // compose the function
      return f(f(x));
    };
    f = std::move(f_next);  // avoid copying
    n >>= 1;                // next bit
  }

  return result;
}
template <class T>
ostream &operator<<(ostream &o, const vector<T> &vec) {
  for (const auto &e : vec) {
    o << e << " ";
  }
  o << endl;
  return o;
}

#pragma endregion

struct Edge {
  int u, v, w;
};
struct DSU {
  vector<int> repr, rank;
  DSU(int _n) : repr(_n), rank(_n, 0) { iota(repr.begin(), repr.end(), 0); };
  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (rank[a] < rank[b]) swap(a, b);
    repr[b] = a;
    if (rank[a] == rank[b]) ++rank[a];
    return true;
  }
  int find(int v) {
    if (v == repr[v]) return v;

    return repr[v] = find(repr[v]);
  }
};
void solve(bool &go) {
  int N, M;
  cin >> N >> M;
  if (N == 0 && M == 0) {
    go = false;
    return;
  }

  vector<Edge> edges;
  edges.reserve(M);
  DSU dsu(N);
  rep(i, 0, M) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({u, v, w});
  }

  sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.w < b.w; });

  vector<Edge> MST;
  MST.reserve(N - 1);
  ll cost = 0LL;
  for (const auto &x : edges) {
    if (dsu.unite(x.u, x.v)) {
      MST.push_back(x);
      cost += x.w;
      if ((int)MST.size() == N - 1) break;
    }
  }
  if (N > 0 && (int)MST.size() != N - 1) {
    cout << "Impossible\n";
    return;
  }
  cout << cost << "\n";
  sort(MST.begin(), MST.end(), [](const Edge &x, const Edge &y) {
    int xu = x.u, xv = x.v;
    int yu = y.u, yv = y.v;
    if (xv < xu) swap(xv, xu);
    if (yv < yu) swap(yv, yu);
    return (xu == yu) ? (xv < yv) : (xu < yu);
  });

  for (const auto &e : MST) {
    int a = e.u, b = e.v;
    if (b < a) swap(a, b);

    cout << a << " " << b << "\n";
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T = 1;
  // OPTIONAL FOR SOME CONTESTS
  // cin >> T;
  bool go = true;
  while (go) {
    solve(go);
  }
  return 0;
}