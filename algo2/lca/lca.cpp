#include<bits/stdc++.h>
#define ll long long
#define N '\n'
using namespace std;

vector<ll> v[1000000];
ll vis[1000000];
ll parent[100000][70];
ll dis[100000];
ll n,l;

void bfs(ll n)
{
	queue<ll> q;
	vis[n] = 1;
	q.push(n);
	parent[n][0] = n;
	while(!q.empty())
	{
		ll c = q.front();
		q.pop();
		for (ll j = 1; j <= l; ++j)
		{
			parent[c][j] = parent[parent[c][j-1]][j-1];
		}
		for(ll i = 0;i < v[c].size();i++)
		{
			if(vis[v[c][i]] == 0)
			{
				parent[v[c][i]][0] = c;
				dis[v[c][i]] = dis[c] + 1;
				vis[v[c][i]] = 1;

				q.push(v[c][i]);
			}
		}
	}
}

ll lca(ll u,ll v)
{
	ll a,b,c,i,j;
	if(dis[u] > dis[v])
	{
		swap(u,v);
	}
	while(dis[u] != dis[v])
	{
		a = log2(dis[v]-dis[u]);
		v = parent[v][a];
	}
	if(u == v)
	{
		return u;
	}
	b = log2(dis[v]);
	c = (ll)(pow(2,b)+0.5);
	for(ll i = b;i >= 0;i--)
	{
		if(parent[u][i] != parent[v][i])
		{
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	return parent[u][0];
}

int main()
{
    ll t = 1,it;
    for(it = 1;it <= t;it++)
    {
        ll q,i,j,k,s = 0,x,y,c = 0,d;
        cout << "Enter the number of nodes: ";
        cin >> n;
        for(i = 0;i <= n;i++)
		{
			v[i].clear();
			vis[i] = 0;
			dis[i] = 0;
		}
		cout << "Enter the edges:\n";
		for(i = 0;i < n-1;i++)
		{
			cin >> c >> d;
            v[c].push_back(d);
            v[d].push_back(c);
		}
		l = ceil(log2(n));
		for(i = 0;i <= n;i++)
		{
			for(j = 0;j <= l;j++)
			{
				parent[i][j] = 0;
			}
		}
		bfs(1);
		cout << "Enter the number of queries:";
		cin >> q;
		cout << "Enter the queries:\n";
		for(i = 0;i < q;i++)
		{
			cin >> c >> d;
			cout << "Lca :" << lca(c,d) << N;
		}
    }
    return 0;
}
