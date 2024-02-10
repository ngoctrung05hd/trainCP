// https://oj.vnoi.info/problem/tst23_f
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef vector<int> VI;
typedef pair<int, VI> pIV;

bool cmp(pIV a, pIV b)
{
    if (a.se.size() > b.se.size())
        return true;
    if (a.se.size() < b.se.size())
        return false;
    return (a.fi < b.fi);
}

string convert_to_binary(int u)
{
    string ans = "";
    while (u)
    {
        ans = char('0' + (u % 2)) + ans;
        u /= 2;
    }
    return ans;
}

int convert_to_int(string s)
{
    int x = 0, lt = 1, sum = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        x *= 2;
        x += (s[i] - '0');
        if (i > 0)
            sum += lt;
        lt *= 2;
    }

    x += sum;

    return x;
}

namespace client
{
    const int maxn = 66666;

    int n, id[maxn], p[maxn], sumlt[maxn], lt[maxn];
    string tmp[maxn];
    pIV g[maxn];

    void init(VI par)
    {
        n = par.size() + 1;
        for (int i = 0; i < n; ++i)
            g[i].fi = i, g[i].se.clear();

        for (int i = 0; i < n - 1; ++i)
        {
            int u = par[i], v = i + 1;
            g[u].se.push_back(v);
            g[v].se.push_back(u);
        }

        sort(g, g + n, cmp);
        for (int i = 0; i < n; ++i)
            id[g[i].fi] = i;

        lt[0] = 1;
        sumlt[0] = 0;
        for (int i = 1;; ++i)
        {
            lt[i] = lt[i - 1] * 2;
            sumlt[i] = sumlt[i - 1] + lt[i];
            if (sumlt[i] >= n + 3)
                break;
        }

        int x = 0;
        for (int i = 1;; ++i)
        {
            for (int j = 0; j < lt[i]; ++j)
            {
                if (x + j >= n + 3)
                    break;
                tmp[x + j] = convert_to_binary(j);
                while (tmp[x + j].size() < i)
                    tmp[x + j] = "0" + tmp[x + j];
            }

            x += lt[i];
            if (x >= n + 3)
                break;
        }
    }

    VI q;

    string request(VI P)
    {
        q = P;
        int u = q[0];
        if (g[id[u]].se.size() == 1)
            u = g[id[u]].se[0];
        return tmp[id[u]];
    }

    int answer(string T)
    {
        if (T == "0")
            return -1;
        int u = q[0];
        if (g[id[u]].se.size() == 1)
            u = g[id[u]].se[0];
        if (T == "1")
            return u;
        int i = convert_to_int(T) - 2;
        for (int x : q)
            if (x == g[id[u]].se[i])
                return x;
        return -1;
    }
}

namespace server
{
    const int maxn = 66666;

    int n, id[maxn], p[maxn], sumlt[maxn], lt[maxn];
    string tmp[maxn];
    pIV g[maxn];

    bool safe[maxn];
    VI old;

    void init(VI par)
    {
        n = par.size() + 1;
        for (int i = 0; i < n; ++i)
            g[i].fi = i, g[i].se.clear(), safe[i] = false;
        old.clear();

        for (int i = 0; i < n - 1; ++i)
        {
            int u = par[i], v = i + 1;
            g[u].se.push_back(v);
            g[v].se.push_back(u);
        }

        sort(g, g + n, cmp);
        for (int i = 0; i < n; ++i)
            id[g[i].fi] = i;

        lt[0] = 1;
        sumlt[0] = 0;
        for (int i = 1;; ++i)
        {
            lt[i] = lt[i - 1] * 2;
            sumlt[i] = sumlt[i - 1] + lt[i];
            if (sumlt[i] >= n + 3)
                break;
        }

        int x = 0;
        for (int i = 1;; ++i)
        {
            for (int j = 0; j < lt[i]; ++j)
            {
                if (x + j >= n + 3)
                    break;
                tmp[x + j] = convert_to_binary(j);
                while (tmp[x + j].size() < i)
                    tmp[x + j] = "0" + tmp[x + j];
            }

            x += lt[i];
            if (x >= n + 3)
                break;
        }
    }

    void update(vector<int> green)
    {
        for (int u : old)
            safe[u] = false;
        old.clear();
        old = green;

        for (int u : green)
            safe[u] = true;
    }

    string query(string S)
    {
        int u = convert_to_int(S);
        u = g[u].fi;

        if (safe[u])
            return "1";

        for (int x = 0; x < g[id[u]].se.size(); ++x)
        {
            int v = g[id[u]].se[x];
            if (safe[v])
                return tmp[x + 2];
        }

        return "0";
    }
}
