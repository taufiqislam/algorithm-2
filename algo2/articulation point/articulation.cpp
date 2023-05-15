#include<bits/stdc++.h>
#define ll long long
#define N '\n'
using namespace std;

vector<ll> v[1000000];
ll start[1000000];
ll tin[1000000];
ll g;
vector<ll> vp;



void dfs(ll n,ll x)
{
    if(start[n] == -1)
    {

        start[n] = tin[n] = g;
        g++;
        ll children = 0,cnt = 0;
        for(ll i = 0;i < v[n].size();i++)
        {
            if(v[n][i] == x)
            {
                continue;
            }
            if(start[v[n][i]] != -1)
            {
                tin[n] = min(tin[n],start[v[n][i]]);
            }
            else
            {
                dfs(v[n][i],n);
                tin[n] = min(tin[n],tin[v[n][i]]);
                if((tin[v[n][i]] >= start[n]) && (x != -1))
                {
                    cnt++;
                }
                children++;
            }
        }
        if(cnt > 0)
        {
            vp.push_back(n);
        }
        if(x == -1 && children > 1)
        {
            vp.push_back(n);
        }
    }
}

int main()
{
    ll it,t = 1;
    for(it = 1;it <= t;it++)
    {
        g = 1;
        ll i,n,m,j,k,c,d,f = 0,x,y;
        vp.clear();
        cout << "Enter the number of vertices and edges: ";
        cin >> n >> m;

        for(i = 0;i <= n;i++)
        {
            v[i].clear();
            start[i] = -1;
            tin[i] = -1;

        }
        cout << "Enter the edges:\n";
        for(i = 0;i < m;i++)
        {
            cin >> c >> d;
            v[c].push_back(d);
            v[d].push_back(c);
        }
        for(i = 1;i <= n;i++)
        {
            dfs(i,-1);
        }
        c = vp.size();
        cout << "Number of articulation points: " << c << endl;
    }
    return 0;
}

