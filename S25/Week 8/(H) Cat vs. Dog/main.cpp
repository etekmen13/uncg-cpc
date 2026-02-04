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
ll mod_exp(ll a, ll e, ll M)
{
    ll res = 1;
    while (e)
    {
        if (e & 1)
            res = (res * a) % M;
        a = (a * a) % M;
        e >>= 1;
    }
    return res;
}

template <typename T, typename Func>
T bin_apply_func(T obj, Func func, ll n)
{
    T result = std::move(obj); // accumulator object
    Func f = func;             // f will be "squared" (repeatedly composed)

    while (n > 0)
    {
        if (n & 1)
        {
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
template <class T>
ostream &operator<<(ostream &o, const vector<T> &vec)
{
    for (const auto &e : vec)
    {
        o << e << " ";
    }
    o << endl;
    return o;
}

#pragma endregion
struct HopcroftKarp {
    static constexpr int NIL = 0;
    static constexpr int INF = INT_MAX;

    int m, n;                         // |U|, |V|
    vector<vector<int>> adj;          // 1..m -> neighbors in 1..n
    vector<int> pair_u, pair_v, dist; // sizes m+1, n+1, m+1

    HopcroftKarp(int m, int n) : m(m), n(n), adj(m + 1) {}

    void addEdge(int u, int v) {      // 1-based indices
        // assume 1 <= u <= m, 1 <= v <= n
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= m; ++u) {
            if (pair_u[u] == NIL) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        dist[NIL] = INF;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] < dist[NIL]) {
                for (int v : adj[u]) {
                    int uu = pair_v[v]; // matched U for v (or NIL)
                    if (dist[uu] == INF) {
                        dist[uu] = dist[u] + 1;
                        q.push(uu);
                    }
                }
            }
        }
        return dist[NIL] != INF; // there exists at least one shortest augmenting path
    }

    bool dfs(int u) {
        if (u == NIL) return true;
        for (int v : adj[u]) {
            int uu = pair_v[v];
            if (dist[uu] == dist[u] + 1 && dfs(uu)) {
                pair_v[v] = u;
                pair_u[u] = v;
                return true;
            }
        }
        dist[u] = INF; // prune this u in this phase
        return false;
    }

    int max_matching() {
        pair_u.assign(m + 1, NIL);
        pair_v.assign(n + 1, NIL);
        dist.assign(m + 1, 0);

        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= m; ++u)
                if (pair_u[u] == NIL && dfs(u))
                    ++matching;
        }
        return matching;
    }
};
struct voter {
    int l, h;
};
void solve()
{
    int C, D, V;
    cin >> C >> D >> V;
    vector<voter> cat_lovers, dog_lovers;
    rep(i, 0, V) {
        string loves, hates;
        cin >> loves >> hates;
        if (loves[0] == 'C') {
            cat_lovers.push_back({stoi(loves.substr(1)), stoi(hates.substr(1))});
        }
        else {
            dog_lovers.push_back({stoi(loves.substr(1)), stoi(hates.substr(1))});
        }
    }
    int N = cat_lovers.size(), M = dog_lovers.size();
    HopcroftKarp hk(N, M);
    rep(i, 0, N) {
        rep(j, 0, M) {
            auto c = cat_lovers[i];
            auto d = dog_lovers[j];
            if (c.l == d.h || d.l == c.h)
                hk.addEdge(i+1,j+1);
        }
    }
    cout << V - hk.max_matching() << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // OPTIONAL FOR SOME CONTESTS
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}