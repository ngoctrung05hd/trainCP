// https://oj.vnoi.info/problem/olp_sc23_pquery
#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;

const int maxn = 150005;
const int maxB = 400;

typedef pair<int, int> II;
typedef pair<II, II> IV;

int n, q, p[maxn], loc[maxn];
long long a[maxn];
vector<int> nxt[maxn];
IV query[maxn];
bool tv4;

void Inp()
{
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> p[i], loc[p[i]] = i;

    tv4 = false;

    for (int i = 1; i <= q; ++i)
    {
        int type, u, v, val;
        cin >> type;
        if (type == 4)
        {
            tv4 = true;
            cin >> val;
            u = v = 0;
            nxt[val - 1].push_back(i);
        }
        else
        {
            cin >> u >> v;
            val = 0;
            if (type == 1)
                cin >> val;
            nxt[i - 1].push_back(i);
        }
        query[i] = IV(II(type, val), II(u, v));
    }
}

int N, m, block[maxn];
long long sum[maxB], ans[maxn],
    dt_sum[maxn], d_lazy[maxB];
int sl_sum[maxB][maxn], sl_lazy[maxB * 4][maxB * 4];

void dfs(int id)
{
    int type = query[id].fi.fi, val = query[id].fi.se, u = query[id].se.fi, v = query[id].se.se;

    ans[id] = LLONG_MIN;

    if (type == 1)
    {
        for (int i = u; i <= block[u] * N; ++i)
            dt_sum[i] += val;
        for (int i = v + 1; i <= min(n, block[v + 1] * N); ++i)
            dt_sum[i] -= val;

        for (int i = block[u]; i < block[v + 1]; ++i)
            d_lazy[i] += val;

        for (int j = 1; j <= m; ++j)
        {
            int sl = sl_sum[j][v] + sl_lazy[j][block[v] - 1];
            if (u > 1)
                sl -= (sl_sum[j][(u - 2) + 1] + sl_lazy[j][max(0, block[u - 1] - 1)]);
            sum[j] += 1ll * sl * val;
        }
    }
    else if (type == 2)
    {
        ans[id] = 0;
        for (int i = block[u] + 1; i <= block[v] - 1; ++i)
            ans[id] += sum[i];

        for (int i = u; i <= min(v, block[u] * N); ++i)
        {
            long long x = a[i] + d_lazy[block[loc[i]] - 1] + dt_sum[loc[i]];
            ans[id] += x;
        }

        for (int i = (block[v] - 1) * N + 1; i <= v && block[u] != block[v]; ++i)
        {
            long long x = a[i] + d_lazy[block[loc[i]] - 1] + dt_sum[loc[i]];
            ans[id] += x;
        }
    }
    else if (type == 3)
    {
        for (int i = u; i <= min(N * block[u], n); ++i)
        {
            sl_sum[block[p[u]]][i]--;
            sl_sum[block[p[v]]][i]++;
        }
        for (int i = block[u]; i <= m; ++i)
        {
            sl_lazy[block[p[u]]][i]--;
            sl_lazy[block[p[v]]][i]++;
        }
        for (int i = v; i <= min(N * block[v], n); ++i)
        {
            sl_sum[block[p[v]]][i]--;
            sl_sum[block[p[u]]][i]++;
        }
        for (int i = block[v]; i <= m; ++i)
        {
            sl_lazy[block[p[v]]][i]--;
            sl_lazy[block[p[u]]][i]++;
        }
        a[p[u]] = a[p[u]] + d_lazy[block[u] - 1] + dt_sum[u] - d_lazy[block[v] - 1] - dt_sum[v];
        a[p[v]] = a[p[v]] + d_lazy[block[v] - 1] + dt_sum[v] - d_lazy[block[u] - 1] - dt_sum[u];
        swap(loc[p[u]], loc[p[v]]);
        swap(p[u], p[v]);
    }

    for (int j : nxt[id])
        if (j != id)
            dfs(j);

    if (!tv4)
        return;

    if (type == 1)
    {
        for (int i = u; i <= block[u] * N; ++i)
            dt_sum[i] -= val;
        for (int i = v + 1; i <= min(n, block[v + 1] * N); ++i)
            dt_sum[i] += val;

        for (int i = block[u]; i < block[v + 1]; ++i)
            d_lazy[i] -= val;

        for (int j = 1; j <= m; ++j)
        {
            int sl = sl_sum[j][(v - 1) + 1] + sl_lazy[j][block[v] - 1];
            if (u > 1)
                sl -= (sl_sum[j][(u - 2) + 1] + sl_lazy[j][max(0, block[u - 1] - 1)]);
            sum[j] -= 1ll * sl * val;
        }
    }
    else if (type == 3)
    {
        swap(p[u], p[v]);
        swap(loc[p[u]], loc[p[v]]);
        a[p[u]] = a[p[u]] - d_lazy[block[u] - 1] - dt_sum[u] + d_lazy[block[v] - 1] + dt_sum[v];
        a[p[v]] = a[p[v]] - d_lazy[block[v] - 1] - dt_sum[v] + d_lazy[block[u] - 1] + dt_sum[u];
        for (int i = u; i <= min(N * block[u], n); ++i)
        {
            sl_sum[block[p[u]]][i]++;
            sl_sum[block[p[v]]][i]--;
        }
        for (int i = block[u]; i <= m; ++i)
        {
            sl_lazy[block[p[u]]][i]++;
            sl_lazy[block[p[v]]][i]--;
        }
        for (int i = v; i <= min(N * block[v], n); ++i)
        {
            sl_sum[block[p[v]]][i]++;
            sl_sum[block[p[u]]][i]--;
        }
        for (int i = block[v]; i <= m; ++i)
        {
            sl_lazy[block[p[v]]][i]++;
            sl_lazy[block[p[u]]][i]--;
        }
    }
}

void Solve()
{
    N = sqrt(n) * 4;
    block[0] = 0;
    for (int i = 1; i <= n + 1; ++i)
        block[i] = (i - 1) / N + 1;

    m = block[n];

    for (int i = 0; i <= m; ++i)
    {
        for (int j = 0; j <= m; ++j)
            sl_sum[i][j] = sl_lazy[i][j] = 0;
        sum[i] = d_lazy[i] = 0;
    }

    for (int i = 1; i <= n; ++i)
    {
        sum[block[i]] += a[i];
        dt_sum[i] = 0;

        sl_lazy[block[p[i]]][block[i]]++;
        sl_sum[block[p[i]]][i]++;
    }

    for (int i = 1; i <= n; ++i)
    {
        if (block[i] != block[i - 1])
        {
            for (int j = 1; j <= m; ++j)
                sl_lazy[j][block[i]] += sl_lazy[j][block[i] - 1];
        }
        else
        {
            for (int j = 1; j <= m; ++j)
                sl_sum[j][i] += sl_sum[j][i - 1];
        }
    }

    dfs(0);

    for (int i = 1; i <= q; ++i)
        if (ans[i] > LLONG_MIN)
            cout << ans[i] << endl;
}

int main()
{
    if (fopen(".inp", "r"))
    {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Inp();
    Solve();
}
