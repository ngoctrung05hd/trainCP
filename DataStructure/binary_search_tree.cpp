#include <bits/stdc++.h>
#define fi first
#define se second
#define endl "\n"
using namespace std;

const int maxn = 1000005;

struct node
{
    int key, keymax, keymin;
    node *dad, *childL, *childR;

    node(int x)
    {
        key = keymax = keymin = x;

        childL = childR = nullptr;
    }
};

node *nho[maxn];

typedef pair<int, long long> II;

II check(node *tree)
{
    II ans = II(1, 0);

    if (tree == nullptr)
        return ans;

    II treeL = check(tree->childL),
       treeR = check(tree->childR);

    ans.fi = min(treeL.fi, treeR.fi);
    if (tree->childL != nullptr)
    {
        if (tree->childL->keymax >= tree->key)
            ans.fi = 0;
        tree->keymin = min(tree->keymin, tree->childL->keymin);
        tree->keymax = max(tree->keymax, tree->childL->keymax);
    }
    if (tree->childR != nullptr)
    {
        if (tree->childR->keymin <= tree->key)
            ans.fi = 0;
        tree->keymin = min(tree->keymin, tree->childR->keymin);
        tree->keymax = max(tree->keymax, tree->childR->keymax);
    }

    ans.se += treeL.se + treeR.se + 1ll * tree->key;

    return ans;
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

    string q;
    int key;

    cin >> q >> key;

    node *root = new node(key);
    nho[key] = root;

    while (cin >> q)
    {
        if (q[0] == '*')
            break;

        int u, v;
        cin >> v >> u;

        node *tree = nho[u];
        if (tree != nullptr)
        {
            if (q == "AddLeft" && tree->childL == nullptr)
            {
                nho[v] = new node(v);
                tree->childL = nho[v];
            }

            if (q == "AddRight" && tree->childR == nullptr)
            {
                nho[v] = new node(v);
                tree->childR = nho[v];
            }
        }
    }

    II ans = check(root);

    cout << ans.fi << " " << ans.se;
}