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

void solve()
{
    const int INF = 1e9;
    int W, H;
    cin >> W >> H;
    vector<string> g(H);
    vi DC = {0, 0, 1, -1};
    vi DR = {1, -1, 0, 0};
    pair<int, int> start{-1, -1};
    queue<pair<int, int>> fq;

    vector<vi> fire(H, vi(W, INF));
    rep(r, 0, H)
    {
        cin >> g[r];
        rep(c, 0, W)
        {
            if (g[r][c] == '*')
            {
                fq.push({r, c});
                fire[r][c] = 0;
            }
            else if (g[r][c] == '@')
                start = {r, c};
        }
    }

    auto in_b = [&](int r, int c)
    { return r >= 0 && r < H && c >= 0 && c < W; };
    auto valid = [&](int r, int c)
    {
        return in_b(r, c) && g[r][c] != '#';
    };
    auto at_edge = [&](int r, int c) {
        return r == 0 || r == H-1 || c == 0 || c == W-1;
    };
    // compute fire times.
    while (!fq.empty())
    {
        auto [r, c] = fq.front();
        fq.pop();
        rep(i, 0, 4)
        {
            int nr = r + DR[i], nc = c + DC[i];
            if (valid(nr, nc) && fire[nr][nc] > fire[r][c] + 1)
            {
                fire[nr][nc] = fire[r][c] + 1;
                fq.push({nr, nc});
            }
        }
    }


    queue<pair<int, int>> q;
    vector<vi> dist(H, vi(W, INF));
    dist[start.first][start.second] = 0;
    q.push(start);
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        int d = dist[r][c];
        if(at_edge(r, c)) {
            cout << d +1<< "\n";
            return;
        }
        rep(i, 0, 4) {
            int nr = r + DR[i], nc = c + DC[i];
            if (valid(nr,nc) && d + 1 < fire[nr][nc] && dist[nr][nc] == INF) {
                dist[nr][nc] = d + 1;
                q.push({nr, nc});
            }
        }
    }
    cout << "IMPOSSIBLE\n";
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