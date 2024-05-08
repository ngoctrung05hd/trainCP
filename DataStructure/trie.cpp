#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;

struct node
{
    bool stop;
    node *nxt[10];

    node()
    {
        stop = false;
        for (int i = 0; i < 10; ++i)
            nxt[i] = nullptr;
    }
};

node *root;

bool Add(string s)
{
    node *trie = root;
    int sz = s.size();
    for (int i = 0; i < sz; ++i)
    {
        int k = s[i] - '0';
        if (trie->nxt[k] == nullptr)
            trie->nxt[k] = new node();
        trie = trie->nxt[k];
    }
    if (trie->stop)
        return false;
    trie->stop = true;
    return true;
}

bool Find(string s)
{
    node *trie = root;
    int sz = s.size();
    for (int i = 0; i < sz; ++i)
    {
        int k = s[i] - '0';
        if (trie->nxt[k] == nullptr)
            trie->nxt[k] = new node();
        trie = trie->nxt[k];
    }
    return trie->stop;
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

    root = new node();

    string q, u;

    while (cin >> u)
    {
        if (u[0] == '*')
            break;
        Add(u);
    }

    while (cin >> q)
    {
        if (q[0] == '*')
            break;
        cin >> u;

        if (q == "find")
            cout << (int)(Find(u)) << endl;
        else
            cout << (int)(Add(u)) << endl;
    }
}