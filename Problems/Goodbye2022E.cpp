//https://codeforces.com/contest/1770/problem/E
#include <bits/stdc++.h>
using namespace std;

const int maxn = 300005;
const int R = 998244353;

typedef pair <int, int> II;

#define fi first
#define se second

int n, k;
II p[maxn];
bool but[maxn];
vector <int> g[maxn];

int exp(int u, int v)
{
    int kq = 1; 
    while(v)
    {
        if(v % 2)
            kq = 1ll * kq * u % R;
        u = 1ll * u * u % R;
        v /= 2;
    }
    return kq;
}

void Inp()
{
    cin >> n >> k;

    fill(but + 1, but + k + 1, false);
    for(int i = 1; i <= k; ++i)
    {
        int x;
        cin >> x;
        but[x] = true;
    }

    for(int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        p[i] = II(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

int dad[maxn], node[maxn], f[maxn];

void dfs(int u)
{
    if(but[u])
        node[u] = f[u] = 1;   
        
    for(int v: g[u])
        if(v != dad[u])
        {
            dad[v] = u;
            dfs(v);
            node[u] += node[v];
        }
}

void Solve()
{
    fill(node + 1, node + n + 1, 0);
    dad[1] = 0;
    dfs(1);

    int ans = 0;

    for(int i = 1; i < n; ++i)
    {
        int u = p[i].fi, v = p[i].se;
        if(dad[u] == v)
            swap(u, v);

        int puv = 1ll * f[u] * (1 - f[v] + R) % R, 
            pvu = 1ll * f[v] * (1 - f[u] + R) % R,
            delta = 0;

        delta = (delta - 1ll * puv * (1ll * node[v] * (k - node[v]) % R) % R + R) % R;
        delta = (delta - 1ll * pvu * (1ll * node[v] * (k - node[v]) % R) % R + R) % R;
        delta = (delta + 1ll * puv * (1ll * (node[v] + 1) * (k - node[v] - 1 + R) % R) % R) %R;
        delta = (delta + 1ll * pvu * (1ll * (node[v] - 1 + R) * (k - node[v] + 1) % R) % R) % R;

        ans = (ans + (1ll * node[v] * (k - node[v]) % R + 1ll * delta * exp(2, R - 2) % R) % R) % R;

        f[u] = f[v] = 1ll * (f[u] + f[v]) * exp(2, R - 2) % R;
    }

    cout << 1ll * ans * exp((1ll * k * (k - 1)/2)%R, R - 2) % R;
}

int cou[123];
int main()
{
    if(fopen(".inp","r"))
    {
        freopen(".inp","r",stdin);
        freopen(".out","w",stdout);
    }
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    while(cin >> n)
        cou[n]++;
    for(int i = 0; i <= 11; ++i)
    {
        cout << i << ": " << cou[i] << endl;
    }
    return 0;

    int n_test;
    n_test = 1;
    //cin >> n_test;

    while(n_test--)
    {
        Inp();
        Solve();
    }
}