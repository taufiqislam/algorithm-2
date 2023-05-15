#pragma GCC Optimize ("Ofast")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define N '\n'
#define pb push_back
#define pob pop_back
#define ff first
#define ss second
#define bb begin()
#define ee end()
#define fastIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
//order_of_key (k) : Number of items strictly smaller than k .
//find_by_order(k) : K-th element in a set (counting from zero).

int indeg[100005];
int outdeg[100005];

struct SCC
{
    const static int Nsize = 100005;
    vector <int> adj[Nsize], r_adj[Nsize];
    int V, visit[Nsize], cnt, color[Nsize];
    stack <int> stk;

    SCC(int V) : V(V), cnt(0)
    {
        memset(visit, 0, sizeof(visit));
    }

    void add_edge(int x, int y)
    {
        adj[x].push_back(y);
        r_adj[y].push_back(x);
    }

    void dfs(int u)
    {
        visit[u] = true;
        for(int i = 0;i < adj[u].size();i++)
        {
            int v = adj[u][i];
            if(!visit[v])
            {
                dfs(v);

            }
        }
        stk.push(u);
    }
    void dfs(int u, int id)
    {
        visit[u] = false; color[u] = id;
        for(int i = 0;i < r_adj[u].size();i++)
        {
            int v = r_adj[u][i];
            if(visit[v])
            {
                dfs(v, id);
            }
        }
    }

    int get()
    {
        for(int i = 1; i <= V; i++)
        {
            if(!visit[i])
            {
                dfs(i);
            }
        }
        while(stk.size())
        {
            int v = stk.top(); stk.pop();
            //cout << v << N;
            if(visit[v])
            {
                dfs(v, ++cnt);
            }
        }
        //cout << cnt << N;
        for(int i = 1;i <= V;i++)
        {
            for(int j = 0;j < adj[i].size();j++)
            {
                if(color[i] != color[adj[i][j]])
                {
                    indeg[color[adj[i][j]]]++;
                    outdeg[color[i]]++;
                }
            }
        }
        return cnt;
    }

};


int main()
{
    fastIO();
    ll t = 1,it;
    cin >> t;
    for(it = 1;it <= t;it++)
    {
        ll n,q,i,j,k,s = 0,x,y,c = 0,d;
        cin >> n >> q;
        memset(indeg,0,sizeof(indeg));
        memset(outdeg,0,sizeof(outdeg));
        SCC g(n);
       for(i = 0;i < q;i++)
       {
           cin >> c >> d;
           g.add_edge(c,d);
       }
       x = g.get();
       for(i = 1;i <= x;i++)
       {
            if(indeg[i] == 0)
            {
                s++;
            }
       }
       cout << "Case " << it << ": " << s << N;
    }
    return 0;
}
