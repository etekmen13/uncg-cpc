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
    if (e & 1)
      res = (res * a) % M;
    a = (a * a) % M;
    e >>= 1;
  }
  return res;
}

template <typename T, typename Func> T bin_apply_func(T obj, Func func, ll n) {
  T result = std::move(obj); // accumulator object
  Func f = func;             // f will be "squared" (repeatedly composed)

  while (n > 0) {
    if (n & 1) {
      result = f(result); // appy the function
    }
    Func f_next = [f](T x) { // compose the function
      return f(f(x));
    };
    f = std::move(f_next); // avoid copying
    n >>= 1;               // next bit
  }

  return result;
}
template <class T> ostream &operator<<(ostream &o, const vector<T> &vec) {
  for (const auto &e : vec) {
    o << e << " ";
  }
  o << endl;
  return o;
}

#pragma endregion

<<<<<<< HEAD:S25/Week 8/(B) Coast Length/main.cpp void solve() { int N, M; cin >> N >> M; vector<string> g(N); vector<vector<bool>> vis(N, vector<bool>(M, 0)); ll coast = 0LL;
vector<pair<int, int>> look = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

cin.ignore();
rep(i, 0, N) { getline(cin, g[i]); }
auto in_b = [&](int r, int c) -> bool {
  return r >= 0 && r < N && c >= 0 && c < M;
};

auto get_coast = [&](int r, int c) -> int {
  int count = 0;
  for (const auto &[dr, dc] : look) {
    int nr = r + dr, nc = c + dc;
    if (in_b(nr, nc) && g[nr][nc] == '1')
      ++count;
  }
  return count;
};
auto search = [&](int r, int c) {
  if (!in_b(r, c) || vis[r][c] || g[r][c] == '1')
    return;
  queue<pair<int, int>> q;
  q.push({r, c});
  while (!q.empty()) {
    auto [_r, _c] = q.front();
    q.pop();

    if (vis[_r][_c])
      continue;
    vis[_r][_c] = 1;
    coast += get_coast(_r, _c);
    // cout << coast << "\n";
    for (const auto &[dr, dc] : look) {
      int nr = _r + dr, nc = _c + dc;
      if (in_b(nr, nc) && !vis[nr][nc] && g[nr][nc] == '0')
        q.push({nr, nc});
    }
  }
};
auto count_edge = [&](int r, int c) {
  if (in_b(r, c))
    coast += g[r][c] == '1';
};
rep(i, 0, max(N, M)) {
  search(0, i);
  search(i, 0);
  search(N - 1, i);
  search(i, M - 1);
  count_edge(0, i);
  count_edge(N - 1, i);
  count_edge(i, 0);
  count_edge(i, M - 1);
}
cout << coast << "\n";
=======
struct Edge {
  int u, v, w;
};
struct DSU {
  vector<int> repr, rank;
  DSU(int _n) : repr(_n), rank(_n, 0) { iota(repr.begin(), repr.end(), 0); };
  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return false;
    if (rank[a] < rank[b])
      swap(a, b);
    repr[b] = a;
    if (rank[a] == rank[b])
      ++rank[a];
    return true;
  }
  int find(int v) {
    if (v == repr[v])
      return v;

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
      if ((int)MST.size() == N - 1)
        break;
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
    if (xv < xu)
      swap(xv, xu);
    if (yv < yu)
      swap(yv, yu);
    return (xu == yu) ? (xv < yv) : (xu < yu);
  });

  for (const auto &e : MST) {
    int a = e.u, b = e.v;
    if (b < a)
      swap(a, b);

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
