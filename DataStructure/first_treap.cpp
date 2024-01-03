#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

struct node
{
    node *L, *R;
    int value, weight, siz;

    node(int x)
    {
        L = R = nullptr;
        value = x;
        weight = rand();
        siz = 1;
    }
};

int size_of_node(node *treap)
{
    return (treap == nullptr) ? 0 : treap -> siz;
}

void merge_treap(node *&treap, node *nodeL, node *nodeR)
{
    if(nodeL == nullptr)
    {
        treap = nodeR;
        return;
    }
    if(nodeR == nullptr)
    {
        treap = nodeL;
        return;
    }

    if(nodeL->weight < nodeR->weight)
    {
        merge_treap(nodeL->R, nodeL->R, nodeR);
        treap = nodeL;
    }
    else
    {
        merge_treap(nodeR->L, nodeL, nodeR->L);
        treap = nodeR;
    }

    treap->siz = size_of_node(treap->L) +  size_of_node(treap->R) + 1;
}

void split(node *treap, node *&nodeL, node *&nodeR, int need)
{
    if(treap == nullptr)
    {
        nodeL = nodeR = nullptr;
        return;
    }


    if(size_of_node(treap->L) < need)
    {
        split(treap->R, treap->R, nodeR, need - size_of_node(treap->L) - 1);
        nodeL = treap;
    }
    else
    {
        split(treap->L, nodeL, treap->L, need);
        nodeR = treap;
    }

    treap->siz = size_of_node(treap->L) +  size_of_node(treap->R) + 1;
}

int minimum(node *&treap)
{
    return (treap->L == nullptr) ? treap->value : minimum(treap->L);
}

int maximum(node *&treap)
{
    return (treap->R == nullptr) ? treap->value : maximum(treap->R);
}

vector <int> ans;

void checktreap(node *&treap)
{
    if(treap->L)
        checktreap(treap->L);
    ans.push_back(treap->value);
    if(treap->R)
        checktreap(treap->R);
}

int n, m, a[maxn];
node *root;

void Inp()
{
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
}

void Solve()
{
    root = nullptr;
    for(int i = 1; i <= n; ++i)
        merge_treap(root, root, new node(a[i]));

    while(m--)
    {
        int type, u, v;
        cin >>type >> u >> v;
        node *A, *B, *C;
        split(root, A, B, u - 1);
        split(B, B, C, v - u + 1);
        if(type == 1)
        {
            merge_treap(root, B, A);
            merge_treap(root, root, C);
        }
        else
        {
            merge_treap(root, A, C);
            merge_treap(root, root, B);
        }
    }

    ans.clear();
    checktreap(root);

    cout << abs(ans.back() - ans[0]) << "\n";
    for(int x : ans)
            cout << x << " " ;
    //cout << endl;
}

int main()
{
    //freopen(".inp","r",stdin);
    //freopen(".out","w",stdout);

    Inp();
    Solve();
}
